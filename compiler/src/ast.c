#define _POSIX_C_SOURCE 200809L
#include "../include/holexa.h"

ASTNode* ast_node_new(NodeType type, int line) {
    ASTNode* node     = malloc(sizeof(ASTNode));
    node->type        = type;
    node->str_val     = NULL;
    node->int_val     = 0;
    node->float_val   = 0.0;
    node->bool_val    = 0;
    node->children    = NULL;
    node->child_count = 0;
    node->line        = line;
    return node;
}

void ast_node_add_child(ASTNode* parent, ASTNode* child) {
    if (!parent || !child) return;
    parent->children = realloc(parent->children,
        sizeof(ASTNode*) * (parent->child_count + 1));
    parent->children[parent->child_count++] = child;
}

void ast_node_free(ASTNode* node) {
    if (!node) return;
    for (int i = 0; i < node->child_count; i++)
        ast_node_free(node->children[i]);
    if (node->children) free(node->children);
    if (node->str_val)  free(node->str_val);
    free(node);
}

void ast_print(ASTNode* node, int indent) {
    if (!node) return;
    for (int i = 0; i < indent; i++) printf("  ");
    switch (node->type) {
        case NODE_INT:      printf("INT(%lld)\n",  node->int_val); break;
        case NODE_FLOAT:    printf("FLOAT(%g)\n",  node->float_val); break;
        case NODE_STRING:   printf("STRING(\"%s\")\n", node->str_val ? node->str_val : ""); break;
        case NODE_BOOL:     printf("BOOL(%s)\n",   node->bool_val ? "true" : "false"); break;
        case NODE_NONE:     printf("NONE\n"); break;
        case NODE_IDENT:    printf("IDENT(%s)\n",  node->str_val ? node->str_val : ""); break;
        case NODE_LET:      printf("LET(%s)\n",    node->str_val ? node->str_val : ""); break;
        case NODE_CONST:    printf("CONST(%s)\n",  node->str_val ? node->str_val : ""); break;
        case NODE_FUNCTION: printf("FN(%s)\n",     node->str_val ? node->str_val : ""); break;
        case NODE_CLASS:    printf("CLASS(%s)\n",  node->str_val ? node->str_val : ""); break;
        case NODE_CALL:     printf("CALL(%s)\n",   node->str_val ? node->str_val : ""); break;
        case NODE_RETURN:   printf("RETURN\n"); break;
        case NODE_IF:       printf("IF\n"); break;
        case NODE_WHILE:    printf("WHILE\n"); break;
        case NODE_FOR:      printf("FOR(%s)\n",    node->str_val ? node->str_val : ""); break;
        case NODE_LOOP:     printf("LOOP\n"); break;
        case NODE_BREAK:    printf("BREAK\n"); break;
        case NODE_CONTINUE: printf("CONTINUE\n"); break;
        case NODE_BLOCK:    printf("BLOCK\n"); break;
        case NODE_BINOP:    printf("BINOP(%s)\n",  node->str_val ? node->str_val : ""); break;
        case NODE_TRY:      printf("TRY\n"); break;
        case NODE_MATCH:    printf("MATCH\n"); break;
        case NODE_PROGRAM:  printf("PROGRAM\n"); break;
        default:            printf("NODE(%d)\n",   node->type); break;
    }
    for (int i = 0; i < node->child_count; i++)
        ast_print(node->children[i], indent + 1);
}
