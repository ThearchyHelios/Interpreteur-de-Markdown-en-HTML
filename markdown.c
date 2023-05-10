/*
 * @Author: ThearchyHelios (Yilun JIANG)
 * @Date: 2023-04-19 22:01:10
 * @LastEditTime: 2023-05-02 14:42:56
 * @LastEditors: ThearchyHelios
 * @Description: Principal file of the project
 * @FilePath: /INF404/Projet_final/markdown.c
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "analyse_lexicale.h"
#include "parser.h"

int main(int argc, char const *argv[])
{
    char input[1024];
    char output[2048];
    // open a file only ends with .md
    FILE *fp = fopen(argv[1], "r");
    // FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("Error opening file: %s", argv[1]);
        return 1;
    } else if (strstr(argv[1], ".md") == NULL) {
        printf("Error: %s is not a markdown file", argv[1]);
        return 1;
    } else
    {
        // remove the ancient output file
        remove("output.html");
        // read each lines of the file
        while (fgets(input, 1024, fp) != NULL) // read a line
        {
            // lex the input
            AST *ast = lex(input);
            // parse the ast
            parse(ast, output);
            // print the output
            printf("%s", output);
            // free the ast
            free_ast(ast);
            // write the output to a file in the same directory of the input file
            FILE *fp2 = fopen("output.html", "a");
            if (fp2 == NULL)
            {
                printf("Error opening file: %s", "output.html");
                return 1;
            } else {
                fputs(output, fp2);
                fclose(fp2);
            }
        }
        fclose(fp);
        const char *filename = "output.html";
        // Use default browser to open the output file
        const char *command = "open %s";
        char* full_commande = (char*)malloc(strlen(command) + strlen(filename) + 1);
        sprintf(full_commande, command, filename);
        system(full_commande);
        free(full_commande);
    }
    return 0;
}