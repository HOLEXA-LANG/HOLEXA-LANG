#ifndef HOLEXA_H
#define HOLEXA_H

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    TOK_INT, TOK_FLOAT, TOK_STRING, TOK_BOOL, TOK_NONE,
    TOK_IDENT,
    TOK_LET, TOK_CONST, TOK_FN, TOK_RETURN,
    TOK_IF, TOK_ELSE, TOK_WHILE, TOK_FOR,
    TOK_LOOP, TOK_BREAK, TOK_CONTINUE,
    TOK_CLASS, TOK_IMPORT, TOK_FROM,
    TOK_ASYNC, TOK_AWAIT, TOK_SPAWN,
    TOK_TRY, TOK_CATCH, TOK_FINALLY, TOK_RAISE,
    TOK_MATCH, TOK_TRUE, TOK_FALSE,
    TOK_AND, TOK_OR, TOK_NOT, TOK_IN,
    TOK_SELF, TOK_TRAIT, TOK_IMPLEMENTS,
    TOK_PLUS, TOK_MINUS, TOK_STAR, TOK_SLASH, TOK_PERCENT,
    TOK_EQ, TOK_NEQ, TOK_LT, TOK_GT, TOK_LTE, TOK_GTE,
    TOK_ASSIGN, TOK_PLUS_ASSIGN, TOK_MINUS_ASSIGN,
    TOK_ARROW, TOK_DOT, TOK_DOTDOT,
    TOK_LPAREN, TOK_RPAREN,
    TOK_LBRACE, TOK_RBRACE,
    TOK_LBRACKET, TOK_RBRACKET,
    TOK_COMMA, TOK_COLON, TOK_SEMICOLON,
    TOK_EOF, TOK_ERROR
} TokenType;

typedef struct {
    TokenType type;
    char*     value;
    int       line;
    int       column;
} Token;

typedef struct {
    const char* source;
    int         pos;
    int         line;
    int         column;
    int         length;
} Lexer;

typedef enum {
    NODE_PROGRAM,
    NODE_LET, NODE_CONST,
    NODE_FUNCTION, NODE_RETURN,
    NODE_IF, NODE_WHILE, NODE_FOR, NODE_LOOP,
    NODE_BREAK, NODE_CONTINUE,
    NODE_CLASS,
    NODE_CALL, NODE_INDEX,
    NODE_ASSIGN,
    NODE_BINOP, NODE_UNOP,
    NODE_INT, NODE_FLOAT, NODE_STRING,
    NODE_BOOL, NODE_NONE,
    NODE_IDENT, NODE_LIST, NODE_MAP,
    NODE_IMPORT, NODE_FROM,
    NODE_TRY, NODE_RAISE,
    NODE_MATCH,
    NODE_BLOCK
} NodeType;

typedef struct ASTNode {
    NodeType         type;
    char*            str_val;
    long long        int_val;
    double           float_val;
    int              bool_val;
    struct ASTNode** children;
    int              child_count;
    int              line;
} ASTNode;

Lexer*      lexer_new(const char* source);
Token*      lexer_next_token(Lexer* lexer);
void        lexer_free(Lexer* lexer);
void        token_free(Token* token);
const char* token_type_name(TokenType type);

ASTNode* ast_node_new(NodeType type, int line);
void     ast_node_add_child(ASTNode* parent, ASTNode* child);
void     ast_node_free(ASTNode* node);
void     ast_print(ASTNode* node, int indent);

void hlx_error(const char* msg, int line, int col);

#endif
