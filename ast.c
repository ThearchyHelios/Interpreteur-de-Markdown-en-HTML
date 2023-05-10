/*
 * @Author: ThearchyHelios (Yilun JIANG)
 * @Date: 2023-04-19 22:02:59
 * @LastEditTime: 2023-05-02 14:49:10
 * @LastEditors: ThearchyHelios
 * @Description: 
 * @FilePath: /INF404/Projet_final/ast.c
 */

#include <stdlib.h>
#include <string.h>
#include "ast.h"

// 在 ast.c 文件中，我们定义创建、追加和释放节点以及抽象语法树（AST）的函数。

Node *create_node(NodeType type, char *value)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->type = type;
    node->value = strdup(value);
    node->next = NULL;
    return node;
}

void free_node(Node *node)
{
    if (node != NULL)
    {
        free(node->value);
        free(node);
    }
}

AST *create_ast()
{
    AST *ast = (AST *)malloc(sizeof(AST));
    ast->head = NULL;
    ast->tail = NULL;
    return ast;
}

void append_node(AST *ast, Node *node)
{
    if (ast->head == NULL)
    {
        ast->head = node;
        ast->tail = node;
    }
    else
    {
        ast->tail->next = node;
        ast->tail = node;
    }
}

void free_ast(AST *ast)
{
    Node *node = ast->head;
    while (node != NULL)
    {
        Node *next = node->next;
        free_node(node);
        node = next;
    }
    free(ast);
}

// 这些函数可以帮助您处理 AST 中的节点，包括创建、追加、释放节点以及处理整个 AST。通过这些函数，您可以更轻松地管理和扩展 Markdown 解析器的功能。
// 