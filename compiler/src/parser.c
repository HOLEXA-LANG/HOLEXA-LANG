#define _POSIX_C_SOURCE 200809L
#include "../include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void advance(Parser* p) {
    if (p->previous) token_free(p->previous);
    p->previous = p->current;
    p->current  = lexer_next_token(p->lexer);
}
static int check(Parser* p, TokenType t) { return p->current->type == t; }
static int match(Parser* p, TokenType t) { if (check(p,t)){advance(p);return 1;} return 0; }
static Token* expect(Parser* p, TokenType type, const char* msg) {
    if (!check(p, type)) {
        fprintf(stderr, "\n[HOLEXA ERROR HLX100] Line %d: %s\n", p->current->line, msg);
        fprintf(stderr, "  Expected: %s\n", token_type_name(type));
        fprintf(stderr, "  Found:    %s ('%s')\n\n",
            token_type_name(p->current->type), p->current->value);
        p->had_error = 1;
        return p->current;
    }
    advance(p);
    return p->previous;
}

static ASTNode* parse_statement(Parser* p);
static ASTNode* parse_expression(Parser* p);
static ASTNode* parse_block(Parser* p);

static ASTNode* parse_block(Parser* p) {
    int line = p->current->line;
    expect(p, TOK_LBRACE, "Expected '{'");
    ASTNode* block = ast_node_new(NODE_BLOCK, line);
    while (!check(p, TOK_RBRACE) && !check(p, TOK_EOF)) {
        ASTNode* s = parse_statement(p);
        if (s) ast_node_add_child(block, s);
    }
    expect(p, TOK_RBRACE, "Expected '}'");
    return block;
}

static ASTNode* parse_primary(Parser* p) {
    int line = p->current->line;

    if (match(p, TOK_INT)) {
        ASTNode* n = ast_node_new(NODE_INT, line);
        n->int_val = atoll(p->previous->value);
        return n;
    }
    if (match(p, TOK_FLOAT)) {
        ASTNode* n = ast_node_new(NODE_FLOAT, line);
        n->float_val = atof(p->previous->value);
        return n;
    }
    if (match(p, TOK_STRING)) {
        ASTNode* n = ast_node_new(NODE_STRING, line);
        n->str_val = strdup(p->previous->value);
        return n;
    }
    if (match(p, TOK_TRUE))  { ASTNode* n = ast_node_new(NODE_BOOL, line); n->bool_val=1; return n; }
    if (match(p, TOK_FALSE)) { ASTNode* n = ast_node_new(NODE_BOOL, line); n->bool_val=0; return n; }
    if (match(p, TOK_NONE))  { return ast_node_new(NODE_NONE, line); }

    if (match(p, TOK_SELF)) {
        ASTNode* node = ast_node_new(NODE_IDENT, line);
        node->str_val = strdup("self");
        while (match(p, TOK_DOT)) {
            Token* mem = expect(p, TOK_IDENT, "Expected name after '.'");
            ASTNode* dot = ast_node_new(NODE_BINOP, line);
            dot->str_val = strdup(".");
            ast_node_add_child(dot, node);
            ASTNode* field = ast_node_new(NODE_IDENT, line);
            field->str_val = strdup(mem->value);
            if (match(p, TOK_LPAREN)) {
                ASTNode* call = ast_node_new(NODE_CALL, line);
                call->str_val = strdup(mem->value);
                if (field->str_val) free(field->str_val);
                free(field);
                while (!check(p, TOK_RPAREN) && !check(p, TOK_EOF)) {
                    ast_node_add_child(call, parse_expression(p));
                    if (!check(p, TOK_RPAREN)) expect(p, TOK_COMMA, "Expected ','");
                }
                expect(p, TOK_RPAREN, "Expected ')'");
                ast_node_add_child(dot, call);
            } else {
                ast_node_add_child(dot, field);
            }
            node = dot;
        }
        return node;
    }

    if (match(p, TOK_IDENT)) {
        char* name = strdup(p->previous->value);
        ASTNode* node;
        if (match(p, TOK_LPAREN)) {
            node = ast_node_new(NODE_CALL, line);
            node->str_val = name;
            while (!check(p, TOK_RPAREN) && !check(p, TOK_EOF)) {
                ast_node_add_child(node, parse_expression(p));
                if (!check(p, TOK_RPAREN)) expect(p, TOK_COMMA, "Expected ','");
            }
            expect(p, TOK_RPAREN, "Expected ')'");
        } else {
            node = ast_node_new(NODE_IDENT, line);
            node->str_val = name;
        }
        while (match(p, TOK_DOT)) {
            Token* mem = expect(p, TOK_IDENT, "Expected name after '.'");
            ASTNode* dot = ast_node_new(NODE_BINOP, line);
            dot->str_val = strdup(".");
            ast_node_add_child(dot, node);
            if (match(p, TOK_LPAREN)) {
                ASTNode* call = ast_node_new(NODE_CALL, line);
                call->str_val = strdup(mem->value);
                while (!check(p, TOK_RPAREN) && !check(p, TOK_EOF)) {
                    ast_node_add_child(call, parse_expression(p));
                    if (!check(p, TOK_RPAREN)) expect(p, TOK_COMMA, "Expected ','");
                }
                expect(p, TOK_RPAREN, "Expected ')'");
                ast_node_add_child(dot, call);
            } else {
                ASTNode* field = ast_node_new(NODE_IDENT, line);
                field->str_val = strdup(mem->value);
                ast_node_add_child(dot, field);
            }
            node = dot;
        }
        return node;
    }

    if (match(p, TOK_LPAREN)) {
        ASTNode* e = parse_expression(p);
        expect(p, TOK_RPAREN, "Expected ')'");
        return e;
    }

    fprintf(stderr, "[HOLEXA ERROR HLX101] Line %d: Unexpected token '%s'\n",
        line, p->current->value);
    p->had_error = 1;
    advance(p);
    return ast_node_new(NODE_NONE, line);
}

static ASTNode* parse_comparison(Parser* p) {
    ASTNode* left = parse_primary(p);
    while (check(p,TOK_EQ)||check(p,TOK_NEQ)||check(p,TOK_LT)||
           check(p,TOK_GT)||check(p,TOK_LTE)||check(p,TOK_GTE)) {
        char* op = strdup(p->current->value);
        int line = p->current->line;
        advance(p);
        ASTNode* b = ast_node_new(NODE_BINOP, line);
        b->str_val = op;
        ast_node_add_child(b, left);
        ast_node_add_child(b, parse_primary(p));
        left = b;
    }
    return left;
}

static ASTNode* parse_addition(Parser* p) {
    ASTNode* left = parse_comparison(p);
    while (check(p,TOK_PLUS)||check(p,TOK_MINUS)) {
        char* op = strdup(p->current->value);
        int line = p->current->line;
        advance(p);
        ASTNode* b = ast_node_new(NODE_BINOP, line);
        b->str_val = op;
        ast_node_add_child(b, left);
        ast_node_add_child(b, parse_comparison(p));
        left = b;
    }
    return left;
}

static ASTNode* parse_expression(Parser* p) {
    ASTNode* left = parse_addition(p);
    while (check(p,TOK_STAR)||check(p,TOK_SLASH)||check(p,TOK_PERCENT)) {
        char* op = strdup(p->current->value);
        int line = p->current->line;
        advance(p);
        ASTNode* b = ast_node_new(NODE_BINOP, line);
        b->str_val = op;
        ast_node_add_child(b, left);
        ast_node_add_child(b, parse_addition(p));
        left = b;
    }
    return left;
}

static ASTNode* parse_let(Parser* p) {
    int line = p->previous->line;
    Token* name = expect(p, TOK_IDENT, "Expected variable name");
    ASTNode* node = ast_node_new(NODE_LET, line);
    node->str_val = strdup(name->value);
    if (match(p, TOK_COLON)) { advance(p); }
    expect(p, TOK_ASSIGN, "Expected '='");
    ast_node_add_child(node, parse_expression(p));
    return node;
}

static ASTNode* parse_fn(Parser* p) {
    int line = p->previous->line;
    Token* name = expect(p, TOK_IDENT, "Expected function name");
    ASTNode* node = ast_node_new(NODE_FUNCTION, line);
    node->str_val = strdup(name->value);
    expect(p, TOK_LPAREN, "Expected '('");
    while (!check(p, TOK_RPAREN) && !check(p, TOK_EOF)) {
        if (check(p, TOK_IDENT) || check(p, TOK_SELF)) advance(p);
        if (match(p, TOK_COLON)) advance(p);
        if (check(p, TOK_COMMA)) advance(p);
    }
    expect(p, TOK_RPAREN, "Expected ')'");
    if (match(p, TOK_ARROW)) advance(p);
    ast_node_add_child(node, parse_block(p));
    return node;
}

static ASTNode* parse_class(Parser* p) {
    int line = p->previous->line;
    Token* name = expect(p, TOK_IDENT, "Expected class name");
    ASTNode* node = ast_node_new(NODE_CLASS, line);
    node->str_val = strdup(name->value);
    expect(p, TOK_LBRACE, "Expected '{'");
    while (!check(p, TOK_RBRACE) && !check(p, TOK_EOF)) {
        if (match(p, TOK_FN)) {
            ast_node_add_child(node, parse_fn(p));
        } else if (check(p, TOK_IDENT)) {
            advance(p);
            if (match(p, TOK_COLON)) advance(p);
        } else {
            advance(p);
        }
    }
    expect(p, TOK_RBRACE, "Expected '}'");
    return node;
}

static ASTNode* parse_if(Parser* p) {
    int line = p->previous->line;
    ASTNode* node = ast_node_new(NODE_IF, line);
    ast_node_add_child(node, parse_expression(p));
    ast_node_add_child(node, parse_block(p));
    if (match(p, TOK_ELSE)) {
        if (match(p, TOK_IF)) ast_node_add_child(node, parse_if(p));
        else ast_node_add_child(node, parse_block(p));
    }
    return node;
}

static ASTNode* parse_while(Parser* p) {
    int line = p->previous->line;
    ASTNode* node = ast_node_new(NODE_WHILE, line);
    ast_node_add_child(node, parse_expression(p));
    ast_node_add_child(node, parse_block(p));
    return node;
}

static ASTNode* parse_for(Parser* p) {
    int line = p->previous->line;
    Token* var = expect(p, TOK_IDENT, "Expected variable in 'for'");
    ASTNode* node = ast_node_new(NODE_FOR, line);
    node->str_val = strdup(var->value);
    expect(p, TOK_IN, "Expected 'in'");
    ast_node_add_child(node, parse_expression(p));
    if (match(p, TOK_DOTDOT)) ast_node_add_child(node, parse_expression(p));
    ast_node_add_child(node, parse_block(p));
    return node;
}

static ASTNode* parse_try(Parser* p) {
    int line = p->previous->line;
    ASTNode* node = ast_node_new(NODE_TRY, line);
    ast_node_add_child(node, parse_block(p));
    if (match(p, TOK_CATCH)) {
        if (check(p, TOK_IDENT)) advance(p);
        ast_node_add_child(node, parse_block(p));
    }
    if (match(p, TOK_FINALLY)) ast_node_add_child(node, parse_block(p));
    return node;
}

static ASTNode* parse_statement(Parser* p) {
    if (match(p, TOK_LET))     return parse_let(p);
    if (match(p, TOK_FN))      return parse_fn(p);
    if (match(p, TOK_CLASS))   return parse_class(p);
    if (match(p, TOK_IF))      return parse_if(p);
    if (match(p, TOK_WHILE))   return parse_while(p);
    if (match(p, TOK_FOR))     return parse_for(p);
    if (match(p, TOK_TRY))     return parse_try(p);
    if (match(p, TOK_RETURN)) {
        int line = p->previous->line;
        ASTNode* node = ast_node_new(NODE_RETURN, line);
        if (!check(p, TOK_RBRACE) && !check(p, TOK_EOF))
            ast_node_add_child(node, parse_expression(p));
        return node;
    }
    if (match(p, TOK_BREAK))    return ast_node_new(NODE_BREAK,    p->previous->line);
    if (match(p, TOK_CONTINUE)) return ast_node_new(NODE_CONTINUE, p->previous->line);
    if (match(p, TOK_LOOP)) {
        ASTNode* node = ast_node_new(NODE_LOOP, p->previous->line);
        ast_node_add_child(node, parse_block(p));
        return node;
    }
    return parse_expression(p);
}

Parser* parser_new(Lexer* lexer) {
    Parser* p    = malloc(sizeof(Parser));
    p->lexer     = lexer;
    p->previous  = NULL;
    p->had_error = 0;
    p->current   = lexer_next_token(lexer);
    return p;
}

ASTNode* parser_parse(Parser* p) {
    ASTNode* program = ast_node_new(NODE_PROGRAM, 1);
    while (!check(p, TOK_EOF)) {
        ASTNode* s = parse_statement(p);
        if (s) ast_node_add_child(program, s);
    }
    return program;
}

void parser_free(Parser* p) {
    if (!p) return;
    if (p->current)  token_free(p->current);
    if (p->previous) token_free(p->previous);
    free(p);
}
