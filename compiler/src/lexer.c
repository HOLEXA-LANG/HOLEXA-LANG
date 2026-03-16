#define _POSIX_C_SOURCE 200809L
#include "../include/holexa.h"

typedef struct { const char* word; TokenType type; } Keyword;

static Keyword keywords[] = {
    {"let",        TOK_LET},
    {"const",      TOK_CONST},
    {"fn",         TOK_FN},
    {"return",     TOK_RETURN},
    {"if",         TOK_IF},
    {"else",       TOK_ELSE},
    {"while",      TOK_WHILE},
    {"for",        TOK_FOR},
    {"loop",       TOK_LOOP},
    {"break",      TOK_BREAK},
    {"continue",   TOK_CONTINUE},
    {"class",      TOK_CLASS},
    {"import",     TOK_IMPORT},
    {"from",       TOK_FROM},
    {"async",      TOK_ASYNC},
    {"await",      TOK_AWAIT},
    {"spawn",      TOK_SPAWN},
    {"try",        TOK_TRY},
    {"catch",      TOK_CATCH},
    {"finally",    TOK_FINALLY},
    {"raise",      TOK_RAISE},
    {"match",      TOK_MATCH},
    {"true",       TOK_TRUE},
    {"false",      TOK_FALSE},
    {"and",        TOK_AND},
    {"or",         TOK_OR},
    {"not",        TOK_NOT},
    {"in",         TOK_IN},
    {"self",       TOK_SELF},
    {"trait",      TOK_TRAIT},
    {"implements", TOK_IMPLEMENTS},
    {"none",       TOK_NONE},
    {NULL,         TOK_ERROR}
};

static char current_char(Lexer* l) { return l->source[l->pos]; }
static char peek_char(Lexer* l) {
    if (l->pos + 1 >= l->length) return '\0';
    return l->source[l->pos + 1];
}
static char advance_char(Lexer* l) {
    char c = l->source[l->pos++];
    if (c == '\n') { l->line++; l->column = 1; }
    else l->column++;
    return c;
}

static Token* make_token(TokenType type, const char* val, int line, int col) {
    Token* t  = malloc(sizeof(Token));
    t->type   = type;
    t->value  = strdup(val ? val : "");
    t->line   = line;
    t->column = col;
    return t;
}

Lexer* lexer_new(const char* source) {
    Lexer* l  = malloc(sizeof(Lexer));
    l->source = source;
    l->pos    = 0;
    l->line   = 1;
    l->column = 1;
    l->length = (int)strlen(source);
    return l;
}

Token* lexer_next_token(Lexer* l) {
    while (l->pos < l->length && isspace(current_char(l))) advance_char(l);
    if (l->pos >= l->length)
        return make_token(TOK_EOF, "EOF", l->line, l->column);

    int line = l->line, col = l->column;
    char c = current_char(l);

    if (c == '/' && peek_char(l) == '/') {
        while (l->pos < l->length && current_char(l) != '\n') advance_char(l);
        return lexer_next_token(l);
    }

    if (c == '"') {
        advance_char(l);
        int start = l->pos;
        while (l->pos < l->length && current_char(l) != '"') advance_char(l);
        int len = l->pos - start;
        char* str = malloc(len + 1);
        strncpy(str, l->source + start, len);
        str[len] = '\0';
        advance_char(l);
        Token* t = make_token(TOK_STRING, str, line, col);
        free(str);
        return t;
    }

    if (isdigit(c)) {
        int start = l->pos, is_float = 0;
        while (l->pos < l->length && isdigit(current_char(l))) advance_char(l);
        if (l->pos < l->length && current_char(l) == '.' && peek_char(l) != '.') {
            is_float = 1; advance_char(l);
            while (l->pos < l->length && isdigit(current_char(l))) advance_char(l);
        }
        int len = l->pos - start;
        char* num = malloc(len + 1);
        strncpy(num, l->source + start, len);
        num[len] = '\0';
        Token* t = make_token(is_float ? TOK_FLOAT : TOK_INT, num, line, col);
        free(num);
        return t;
    }

    if (isalpha(c) || c == '_') {
        int start = l->pos;
        while (l->pos < l->length && (isalnum(current_char(l)) || current_char(l) == '_'))
            advance_char(l);
        int len = l->pos - start;
        char* ident = malloc(len + 1);
        strncpy(ident, l->source + start, len);
        ident[len] = '\0';
        TokenType type = TOK_IDENT;
        for (int i = 0; keywords[i].word != NULL; i++) {
            if (strcmp(ident, keywords[i].word) == 0) { type = keywords[i].type; break; }
        }
        Token* t = make_token(type, ident, line, col);
        free(ident);
        return t;
    }

    if (isalpha(c) || c == '_') {
        int start = l->pos;
        while (l->pos < l->length && (isalnum(current_char(l)) || current_char(l) == '_'))
            advance_char(l);
        int len = l->pos - start;
        char* ident = malloc(len + 1);
        strncpy(ident, l->source + start, len);
        ident[len] = '\0';
        TokenType type = TOK_IDENT;
        for (int i = 0; keywords[i].word != NULL; i++) {
            if (strcmp(ident, keywords[i].word) == 0) { type = keywords[i].type; break; }
        }
        Token* t = make_token(type, ident, line, col);
        free(ident);
        return t;
    }

    advance_char(l);
    switch (c) {
        case '+': return make_token(TOK_PLUS,    "+", line, col);
        case '-': {
            if (current_char(l) == '>') { advance_char(l); return make_token(TOK_ARROW, "->", line, col); }
            return make_token(TOK_MINUS, "-", line, col);
        }
        case '*': return make_token(TOK_STAR,    "*", line, col);
        case '/': return make_token(TOK_SLASH,   "/", line, col);
        case '%': return make_token(TOK_PERCENT, "%", line, col);
        case '=': {
            if (current_char(l) == '=') { advance_char(l); return make_token(TOK_EQ, "==", line, col); }
            return make_token(TOK_ASSIGN, "=", line, col);
        }
        case '!': {
            if (current_char(l) == '=') { advance_char(l); return make_token(TOK_NEQ, "!=", line, col); }
            return make_token(TOK_ERROR, "!", line, col);
        }
        case '<': {
            if (current_char(l) == '=') { advance_char(l); return make_token(TOK_LTE, "<=", line, col); }
            return make_token(TOK_LT, "<", line, col);
        }
        case '>': {
            if (current_char(l) == '=') { advance_char(l); return make_token(TOK_GTE, ">=", line, col); }
            return make_token(TOK_GT, ">", line, col);
        }
        case '.': {
            if (current_char(l) == '.') { advance_char(l); return make_token(TOK_DOTDOT, "..", line, col); }
            return make_token(TOK_DOT, ".", line, col);
        }
        case '(': return make_token(TOK_LPAREN,    "(", line, col);
        case ')': return make_token(TOK_RPAREN,    ")", line, col);
        case '{': return make_token(TOK_LBRACE,    "{", line, col);
        case '}': return make_token(TOK_RBRACE,    "}", line, col);
        case '[': return make_token(TOK_LBRACKET,  "[", line, col);
        case ']': return make_token(TOK_RBRACKET,  "]", line, col);
        case ',': return make_token(TOK_COMMA,     ",", line, col);
        case ':': return make_token(TOK_COLON,     ":", line, col);
        case ';': return make_token(TOK_SEMICOLON, ";", line, col);
        default: {
            char err[2] = {c, '\0'};
            return make_token(TOK_ERROR, err, line, col);
        }
    }
}

void lexer_free(Lexer* l) { if (l) free(l); }
void token_free(Token* t) { if (t) { if (t->value) free(t->value); free(t); } }

const char* token_type_name(TokenType type) {
    switch(type) {
        case TOK_INT:    return "INT";
        case TOK_FLOAT:  return "FLOAT";
        case TOK_STRING: return "STRING";
        case TOK_IDENT:  return "IDENT";
        case TOK_LET:    return "LET";
        case TOK_FN:     return "FN";
        case TOK_IF:     return "IF";
        case TOK_ELSE:   return "ELSE";
        case TOK_RETURN: return "RETURN";
        case TOK_CLASS:  return "CLASS";
        case TOK_FOR:    return "FOR";
        case TOK_WHILE:  return "WHILE";
        case TOK_EOF:    return "EOF";
        default:         return "TOKEN";
    }
}
