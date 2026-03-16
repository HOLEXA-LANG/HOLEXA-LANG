#include "../include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ─────────────────────────────────────
// HELPER FUNCTIONS
// ─────────────────────────────────────

static void advance(Parser* p) {
    if (p->previous) token_free(p->previous);
    p->previous = p->current;
    p->current  = lexer_next_token(p->lexer);
}

static int check(Parser* p, TokenType type) {
    return p->current->type == type;
}

static int match(Parser* p, TokenType type) {
    if (check(p, type)) { advance(p); return 1; }
    return 0;
}

static Token* expect(Parser* p, TokenType type, const char* msg) {
    if (!check(p, type)) {
        fprintf(stderr, "\n[HOLEXA ERROR HLX100] Line %d: %s\n",
            p->current->line, msg);
        fprintf(stderr, "  Expected: %s\n", token_type_name(type));
        fprintf(stderr, "  Found:    %s ('%s')\n\n",
            token_type_name(p->current->type), p->current->value);
        p->had_error = 1;
        return p->current;
    }
    advance(p);
    return p->previous;
}

// ─────────────────────────────────────
// FORWARD DECLARATIONS
// ─────────────────────────────────────
static ASTNode* parse_statement(Parser* p);
static ASTNode* parse_expression(Parser* p);
static ASTNode* parse_block(Parser* p);

// ─────────────────────────────────────
// PARSE BLOCK  { ... }
// ─────────────────────────────────────
static ASTNode* parse_block(Parser* p) {
    int line = p->current->line;
    expect(p, TOK_LBRACE, "Expected '{' to start block");
    ASTNode* block = ast_node_new(NODE_BLOCK, line);
    while (!check(p, TOK_RBRACE) && !check(p, TOK_EOF)) {
        ASTNode* stmt = parse_statement(p);
        if (stmt) ast_node_add_child(block, stmt);
    }
    expect(p, TOK_RBRACE, "Expected '}' to end block");
    return block;
}

// ─────────────────────────────────────
// PARSE PRIMARY  (basic values)
// ─────────────────────────────────────
static ASTNode* parse_primary(Parser* p) {
    int line = p->current->line;

    // Integer
    if (match(p, TOK_INT)) {
        ASTNode* n = ast_node_new(NODE_INT, line);
        n->int_val = atoll(p->previous->value);
        return n;
    }

    // Float
    if (match(p, TOK_FLOAT)) {
        ASTNode* n = ast_node_new(NODE_FLOAT, line);
        n->float_val = atof(p->previous->value);
        return n;
    }

    // String
    if (match(p, TOK_STRING)) {
        ASTNode* n = ast_node_new(NODE_STRING, line);
        n->str_val = strdup(p->previous->value);
        return n;
    }

    // True / False
    if (match(p, TOK_TRUE)) {
        ASTNode* n = ast_node_new(NODE_BOOL, line);
        n->bool_val = 1;
        return n;
    }
    if (match(p, TOK_FALSE)) {
        ASTNode* n = ast_node_new(NODE_BOOL, line);
        n->bool_val = 0;
        return n;
    }

    // None
    if (match(p, TOK_NONE)) {
        return ast_node_new(NODE_NONE, line);
    }

    // Identifier or Function Call
    if (match(p, TOK_IDENT)) {
        char* name = strdup(p->previous->value);

        // Function Call: name(...)
        if (match(p, TOK_LPAREN)) {
            ASTNode* call = ast_node_new(NODE_CALL, line);
            call->str_val = name;
            while (!check(p, TOK_RPAREN) && !check(p, TOK_EOF)) {
                ast_node_add_child(call, parse_expression(p));
                if (!check(p, TOK_RPAREN)) expect(p, TOK_COMMA, "Expected ','");
            }
            expect(p, TOK_RPAREN, "Expected ')' after arguments");
            return call;
        }

        // Just identifier
        ASTNode* n = ast_node_new(NODE_IDENT, line);
        n->str_val = name;
        return n;
    }

    // Grouped expression: (expr)
    if (match(p, TOK_LPAREN)) {
        ASTNode* expr = parse_expression(p);
        expect(p, TOK_RPAREN, "Expected ')'");
        return expr;
    }

    fprintf(stderr, "[HOLEXA ERROR HLX101] Line %d: Unexpected token '%s'\n",
        line, p->current->value);
    p->had_error = 1;
    advance(p);
    return ast_node_new(NODE_NONE, line);
}

// ─────────────────────────────────────
// PARSE COMPARISON  == != < > <= >=
// ─────────────────────────────────────
static ASTNode* parse_comparison(Parser* p) {
    ASTNode* left = parse_primary(p);
    int line = p->current->line;

    while (check(p, TOK_EQ)  || check(p, TOK_NEQ) ||
           check(p, TOK_LT)  || check(p, TOK_GT)  ||
           check(p, TOK_LTE) || check(p, TOK_GTE)) {
        char* op = strdup(p->current->value);
        advance(p);
        ASTNode* right = parse_primary(p);
        ASTNode* binop = ast_node_new(NODE_BINOP, line);
        binop->str_val = op;
        ast_node_add_child(binop, left);
        ast_node_add_child(binop, right);
        left = binop;
    }
    return left;
}

// ─────────────────────────────────────
// PARSE ADDITION  + -
// ─────────────────────────────────────
static ASTNode* parse_addition(Parser* p) {
    ASTNode* left = parse_comparison(p);
    int line = p->current->line;

    while (check(p, TOK_PLUS) || check(p, TOK_MINUS)) {
        char* op = strdup(p->current->value);
        advance(p);
        ASTNode* right = parse_comparison(p);
        ASTNode* binop = ast_node_new(NODE_BINOP, line);
        binop->str_val = op;
        ast_node_add_child(binop, left);
        ast_node_add_child(binop, right);
        left = binop;
    }
    return left;
}

// ─────────────────────────────────────
// PARSE MULTIPLICATION  * / %
// ─────────────────────────────────────
static ASTNode* parse_expression(Parser* p) {
    ASTNode* left = parse_addition(p);
    int line = p->current->line;

    while (check(p, TOK_STAR) || check(p, TOK_SLASH) || check(p, TOK_PERCENT)) {
        char* op = strdup(p->current->value);
        advance(p);
        ASTNode* right = parse_addition(p);
        ASTNode* binop = ast_node_new(NODE_BINOP, line);
        binop->str_val = op;
        ast_node_add_child(binop, left);
        ast_node_add_child(binop, right);
        left = binop;
    }
    return left;
}

// ─────────────────────────────────────
// PARSE LET  →  let name = value
// ─────────────────────────────────────
static ASTNode* parse_let(Parser* p) {
    int line = p->previous->line;
    Token* name = expect(p, TOK_IDENT, "Expected variable name after 'let'");
    ASTNode* node = ast_node_new(NODE_LET, line);
    node->str_val = strdup(name->value);

    // Optional type: let x: Int = 5
    if (match(p, TOK_COLON)) advance(p); // skip type for now

    expect(p, TOK_ASSIGN, "Expected '=' after variable name");
    ast_node_add_child(node, parse_expression(p));
    return node;
}

// ─────────────────────────────────────
// PARSE FN  →  fn name(...) { }
// ─────────────────────────────────────
static ASTNode* parse_fn(Parser* p) {
    int line = p->previous->line;
    Token* name = expect(p, TOK_IDENT, "Expected function name after 'fn'");
    ASTNode* node = ast_node_new(NODE_FUNCTION, line);
    node->str_val = strdup(name->value);

    expect(p, TOK_LPAREN, "Expected '(' after function name");
    while (!check(p, TOK_RPAREN) && !check(p, TOK_EOF)) {
        advance(p); // skip params for now
        if (check(p, TOK_COMMA)) advance(p);
    }
    expect(p, TOK_RPAREN, "Expected ')'");

    // Optional return type: -> Type
    if (match(p, TOK_ARROW)) advance(p);

    ast_node_add_child(node, parse_block(p));
    return node;
}

// ─────────────────────────────────────
// PARSE IF
// ─────────────────────────────────────
static ASTNode* parse_if(Parser* p) {
    int line = p->previous->line;
    ASTNode* node = ast_node_new(NODE_IF, line);
    ast_node_add_child(node, parse_expression(p));  // condition
    ast_node_add_child(node, parse_block(p));        // then block
    if (match(p, TOK_ELSE)) {
        if (match(p, TOK_IF)) {
            ast_node_add_child(node, parse_if(p));
        } else {
            ast_node_add_child(node, parse_block(p));
        }
    }
    return node;
}

// ─────────────────────────────────────
// PARSE WHILE
// ─────────────────────────────────────
static ASTNode* parse_while(Parser* p) {
    int line = p->previous->line;
    ASTNode* node = ast_node_new(NODE_WHILE, line);
    ast_node_add_child(node, parse_expression(p));
    ast_node_add_child(node, parse_block(p));
    return node;
}

// ─────────────────────────────────────
// PARSE FOR
// ─────────────────────────────────────
static ASTNode* parse_for(Parser* p) {
    int line = p->previous->line;
    ASTNode* node = ast_node_new(NODE_FOR, line);
    Token* var = expect(p, TOK_IDENT, "Expected variable in 'for'");
    node->str_val = strdup(var->value);
    expect(p, TOK_IN, "Expected 'in' after variable");
    ast_node_add_child(node, parse_expression(p));
    ast_node_add_child(node, parse_block(p));
    return node;
}

// ─────────────────────────────────────
// PARSE RETURN
// ─────────────────────────────────────
static ASTNode* parse_return(Parser* p) {
    int line = p->previous->line;
    ASTNode* node = ast_node_new(NODE_RETURN, line);
    if (!check(p, TOK_RBRACE) && !check(p, TOK_EOF))
        ast_node_add_child(node, parse_expression(p));
    return node;
}

// ─────────────────────────────────────
// PARSE STATEMENT
// ─────────────────────────────────────
static ASTNode* parse_statement(Parser* p) {
    if (match(p, TOK_LET))    return parse_let(p);
    if (match(p, TOK_FN))     return parse_fn(p);
    if (match(p, TOK_IF))     return parse_if(p);
    if (match(p, TOK_WHILE))  return parse_while(p);
    if (match(p, TOK_FOR))    return parse_for(p);
    if (match(p, TOK_RETURN)) return parse_return(p);
    if (match(p, TOK_BREAK))  return ast_node_new(NODE_BREAK, p->previous->line);
    if (match(p, TOK_CONTINUE))return ast_node_new(NODE_CONTINUE, p->previous->line);
    return parse_expression(p);
}

// ─────────────────────────────────────
// MAIN PARSE
// ─────────────────────────────────────
Parser* parser_new(Lexer* lexer) {
    Parser* p   = malloc(sizeof(Parser));
    p->lexer    = lexer;
    p->previous = NULL;
    p->had_error= 0;
    p->current  = lexer_next_token(lexer);
    return p;
}

ASTNode* parser_parse(Parser* p) {
    ASTNode* program = ast_node_new(NODE_PROGRAM, 1);
    while (!check(p, TOK_EOF)) {
        ASTNode* stmt = parse_statement(p);
        if (stmt) ast_node_add_child(program, stmt);
    }
    return program;
}

void parser_free(Parser* p) {
    if (p->current)  token_free(p->current);
    if (p->previous) token_free(p->previous);
    free(p);
}
