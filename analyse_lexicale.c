/*
 * @Author: ThearchyHelios (Yilun JIANG)
 * @Date: 2023-04-19 21:29:53
 * @LastEditTime: 2023-05-02 14:47:55
 * @LastEditors: ThearchyHelios
 * @Description: Analyse de la chaîne d'entrée et stockage des résultats dans un AST
 * @FilePath: /INF404/Projet_final/analyse_lexicale.c
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "analyse_lexicale.h"

int tab_level = 0; // tab_level: Current tab level
int tabs_before_dash = 0; // tabs_before_dash: Number of tabs before the dash
int tabs_before_dash_old = 0; // tabs_before_dash_old: Number of tabs before the dash in the previous line
int break_ul = 0; // break_ul: Whether to break the ul list
int ul_counter =0; // ul_counter: Number of ul lists

// fonction count_tabs: Count the number of tabs before the dash
int count_tabs(const char *input, int dash_position)
{
    int count_tabs = 0;
    int count_spaces = 0;
    int i = dash_position - 1;

    // 计算前导制表符数量
    // Calculate the number of leading tabs
    while (i >= 0 && input[i] == '\t')
    {
        count_tabs++;
        i--;
    }

    // 计算前导空格数量
    // Calculate the number of leading spaces
    while (i >= 0 && input[i] == ' ')
    {
        count_spaces++;
        i--;
    }

    count_tabs += count_spaces / 2;
    return count_tabs;
}

// fonction lex: Analyse the input string and store the results in an AST
AST *lex(const char *input)
{
    AST *ast = create_ast(); // ast: Abstract syntax tree

    size_t len = strlen(input); // len: Length of the input string
    for (size_t i = 0; i < len; ++i) // Boucle de parcours de la chaîne d'entrée
    {
        switch (input[i])
        {
        case '#': // Header
        {
            size_t j = i;
            while (input[j] == '#')
            {
                ++j;
            }
            int header_level = j - i;
            if (input[j] == ' ')
            {
                char value[32];
                snprintf(value, sizeof(value), "h%d", header_level);
                append_node(ast, create_node(HEADER, value));
                i = j;
            }
            else
            {
                append_node(ast, create_node(TEXT, "#"));
            }
            break;
        }
        case '*': // soit un text a gras, soit un text a italic
        {
            if (input[i + 1] == '*')
            {
                append_node(ast, create_node(BOLD, "**"));
                ++i;
            }
            else
            {
                append_node(ast, create_node(ITALIC, "*"));
            }
            break;
        }
        case '[': // un text a link
        {
            size_t j = i + 1;
            while (j < len && input[j] != ']')
            {
                ++j;
            }
            if (j < len && input[j + 1] == '(')
            {
                size_t k = j + 2;
                while (k < len && input[k] != ')')
                {
                    ++k;
                }
                if (k < len)
                {
                    append_node(ast, create_node(LINK, input + i));
                    i = k;
                }
            }
            else
            {
                append_node(ast, create_node(TEXT, "["));
            }
            break;
        }
        case '>': // un text a quote
        {
            append_node(ast, create_node(QUOTE, ">"));
            break;
        }
        case '~': // soit un text a strikethrough, soit un text a sub
        {
            if (input[i + 1] == '~')
            {
                append_node(ast, create_node(STRIKETHROUGH, "~~"));
                ++i;
            }
            else
            {
                append_node(ast, create_node(SUB, "~"));
            }
            break;
        }
        case '!': // un text a img
        {
            if (input[i + 1] == '[')
            {
                size_t j = i + 2;
                while (j < len && input[j] != ']')
                {
                    ++j;
                }
                if (j < len && input[j + 1] == '(')
                {
                    size_t k = j + 2;
                    while (k < len && input[k] != ')')
                    {
                        ++k;
                    }
                    if (k < len)
                    {
                        append_node(ast, create_node(IMG, input + i));
                        i = k;
                    }
                }
                else
                {
                    append_node(ast, create_node(TEXT, "!"));
                }
            }
            else
            {
                append_node(ast, create_node(TEXT, "!"));
            }
            break;
        }
        case '-': // unordered list
        {
            break_ul = 0;
            if (input[i + 1] == ' ')
            {
                int tabs_before_dash_before = tabs_before_dash; // tabs_before_dash_before: Number of tabs before the dash in the previous line
                int tabs_before_dash_after = count_tabs(input, i); // tabs_before_dash_after: Number of tabs before the dash in the current line
                if (tabs_before_dash_after > tabs_before_dash_before) // If the number of tabs before the dash in the current line is greater than the number of tabs before the dash in the previous line, then add a ul list
                {
                    for (int j = 0; j < tabs_before_dash_after - tabs_before_dash_before; ++j)
                    {
                        append_node(ast, create_node(UL, "\t"));
                    }
                    tabs_before_dash = tabs_before_dash_after;
                }
                else if (tabs_before_dash_after < tabs_before_dash_before) // If the number of tabs before the dash in the current line is less than the number of tabs before the dash in the previous line, then close the ul list
                {
                    for (int j = 0; j < tabs_before_dash_before - tabs_before_dash_after; ++j)
                    {
                        append_node(ast, create_node(UL_CLOSE, "\t"));
                    }
                    tabs_before_dash = tabs_before_dash_after;
                }
                append_node(ast, create_node(LI, "-"));
                if (input[i + 2] == '[' && input[i + 3] == 'x' && input[i + 4] == ']') // If the current line is a checked box, then add a checked box
                {
                    append_node(ast, create_node(CHECKED_BOX, "[x]"));
                    i += 4;
                }
                else if (input[i + 2] == '[' && input[i + 3] == ' ' && input[i + 4] == ']') // If the current line is an unchecked box, then add an unchecked box
                {
                    append_node(ast, create_node(UNCHECKED_BOX, "[ ]"));
                    i += 4;
                }
                ++i;
            }
            else
            {
                append_node(ast, create_node(TEXT, "-"));
            }
            break;
        }
        case '\n': // line break
        {
            if (break_ul) // If the previous line is a ul list, then close the ul list
            {
                if (tabs_before_dash > 0) // If the number of tabs before the dash in the previous line is greater than 0, then close the ul list and reset the number of tabs before the dash to 0
                {
                    for (int j = 0; j < tabs_before_dash; ++j)
                    {
                        append_node(ast, create_node(UL_CLOSE, "\t"));
                    }
                    tabs_before_dash = 0;
                }
                append_node(ast, create_node(BR, "\n"));
                ++i;
                break_ul = 0;
            }
            else
            {
                append_node(ast, create_node(BR, "\n"));
                break_ul = 1;
            }
            break;
        }
        case '`':
        {
            // 两种情况：代码块 ```CODE_BLOCK``` 和代码 `code`
            // 如果是代码块，那么就将两个```之间的内容都作为代码块的内容， 并且不进行翻译，比如\n -> <br>
            // 如果是代码，那么就将`之间的内容作为代码的内容
            size_t j = i + 1;
            while (j < len && input[j] != '`')
            {
                ++j;
            }
            if (j < len && input[j + 1] == '`' && input[j + 2] == '`') // CODE_BLOCK mais bugged
            {
                size_t k = j + 3;
                while (k < len && input[k] != '`')
                {
                    ++k;
                }
                if (k < len)
                {
                    append_node(ast, create_node(CODE_BLOCK, input + i));
                    i = k;
                }
            }
            else // CODE
            {
                append_node(ast, create_node(CODE, "`"));
            }
            break;
        }
        default: // text
        {
            char value[2] = {input[i], '\0'};
            append_node(ast, create_node(TEXT, value));
            break;
        }
        }
    }
    return ast;
}
// lex 函数根据输入字符串中的字符来确定节点类型（例如，文本、标题、粗体、斜体和链接等），并将节点添加到 AST 中。这样，我们就可以在解析阶段使用 AST 来生成 HTML 输出。
