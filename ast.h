/*
 * @Author: ThearchyHelios (Yilun JIANG)
 * @Date: 2023-04-19 22:01:10
 * @LastEditTime: 2023-05-02 14:49:27
 * @LastEditors: ThearchyHelios
 * @Description: 
 * @FilePath: /INF404/Projet_final/ast.h
 */
#ifndef __AST_H__
#define __AST_H__

typedef enum
{
    TEXT,
    HEADER,
    BOLD,
    ITALIC,
    LINK,
    QUOTE,
    STRIKETHROUGH,
    SUB,
    IMG,
    LI,
    UL, // Unordered list
    UL_CLOSE, // Unordered list close
    // OL, // Ordered list
    BR, // Line break
    CODE, // Code `code`
    CODE_BLOCK, // Code block ```code```
    CHECKED_BOX, // [x]
    UNCHECKED_BOX, // [ ]
} NodeType;

typedef struct Node
{
    NodeType type;
    char *value;
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
    Node *tail;
} AST;

Node *create_node(NodeType type, char *value); // create a node with type and value
void free_node(Node *node); // free a node
AST *create_ast(); // create an AST
void append_node(AST *ast, Node *node); // append a node to the AST
void free_ast(AST *ast); // free an AST

#endif