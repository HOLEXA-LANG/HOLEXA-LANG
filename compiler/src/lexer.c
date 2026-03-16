#include "../include/holexa.h"

// ─────────────────────────────────────
// KEYWORDS TABLE
// ─────────────────────────────────────
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

// ─────────────────────────────────────
// HELPER FUNCTIONS
// ─────────────────────────────────────
static char current(Lexer* l) {
    return l->source[l->pos];
}

static char peek(Lexer* l) {
    if (l->pos + 1 >= l->length) return '\0';
    return l->source[l->pos + 1];
}

static char advance(Lexer* l) {
    char c = l->source[l->pos++];
    if (c == '\n') { l->line++; l->column = 1; }
    else { l->column++; }
    return c;
}

static Token* make_token(TokenType type, const char* val, int line, int col) {
    Token* t = malloc(sizeof(Token));
    t->type   = type;
    t->value  = val ? strdup(val) : strdup("");
    t->line   = line;
    t->column = col;
    return t;
}

// ─────────────────────────────────────
// LEXER NEW
// ─────────────────────────────────────
Lexer* lexer_new(const char* source) {
    Lexer* l = malloc(sizeof(Lexer));
    l->source = source;
    l->pos    = 0;
    l->line   = 1;
    l->column = 1;
    l->length = strlen(source);
    return l;
}

// ─────────────────────────────────────
// NEXT TOKEN
// ─────────────────────────────────────
Token* lexer_next_token(Lexer* l) {
    // Skip whitespace
    while (l->pos < l->length && isspace(current(l))) advance(l);

    if (l->pos >= l->length)
        return make_token(TOK_EOF, "EOF", l->line, l->column);

    int line = l->line, col = l->column;
    char c = current(l);

    // Comments
    if (c == '/' && peek(l) == '/') {
        while (l->pos < l->length && current(l) != '\n') advance(l);
        return lexer_next_token(l);
    }

    // String
    if (c == '"') {
        advance(l);
        int start = l->pos;
        while (l->pos < l->length && current(l) != '"') advance(l);
        int len = l->pos - start;
        char* str = malloc(len + 1);
        strncpy(str, l->source + start, len);
        str[len] = '\0';
        advance(l);
        Token* t = make_token(TOK_STRING, str, line, col);
        free(str);
        return t;
    }

    // Numbers
    if (isdigit(c)) {
        int start = l->pos;
        int is_float = 0;
        while (l->pos < l->length && isdigit(current(l))) advance(l);
        if (l->pos < l->length && current(l) == '.' && peek(l) != '.') {
            is_float = 1;
            advance(l);
            while (l->pos < l->length && isdigit(current(l))) advance(l);
        }
        int len = l->pos - start;
        char* num = malloc(len + 1);
        strncpy(num, l->source + start, len);
        num[len] = '\0';
        Token* t = make_token(is_float ? TOK_FLOAT : TOK_INT, num, line, col);
        free(num);
        return t;
    }

    // Identifiers and Keywords
    if (isalpha(c) || c == '_') {
        int start = l->pos;
        while (l->pos < l->length && (isalnum(current(l)) || current(l) == '_'))
            advance(l);
        int len = l->pos - start;
        char* ident = malloc(len + 1);
        strncpy(ident, l->source + start, len);
        ident[len] = '\0';

        TokenType type = TOK_IDENT;
        for (int i = 0; keywords[i].word != NULL; i++) {
            if (strcmp(ident, keywords[i].word) == 0) {
                type = keywords[i].type;
                break;
            }
        }
        Token* t = make_token(type, ident, line, col);
        free(ident);
        return t;
    }

    // Operators and Delimiters
    advance(l);
    switch (c) {
        case '+': return make_token(peek(l)=='='?(advance(l),TOK_PLUS_ASSIGN):TOK_PLUS, "+", line, col);
        case '-': {
            if (current(l) == '>') { advance(l); return make_token(TOK_ARROW, "->", line, col); }
            return make_token(peek(l)=='='?(advance(l),TOK_MINUS_ASSIGN):TOK_MINUS, "-", line, col);
        }
        case '*': return make_token(TOK_STAR,    "*", line, col);
        case '/': return make_token(TOK_SLASH,   "/", line, col);
        case '%': return make_token(TOK_PERCENT, "%", line, col);
        case '=': {
            if (current(l) == '=') { advance(l); return make_token(TOK_EQ, "==", line, col); }
            return make_token(TOK_ASSIGN, "=", line, col);
        }
        case '!': {
            if (current(l) == '=') { advance(l); return make_token(TOK_NEQ, "!=", line, col); }
            return make_token(TOK_ERROR, "!", line, col);
        }
        case '<': {
            if (current(l) == '=') { advance(l); return make_token(TOK_LTE, "<=", line, col); }
            return make_token(TOK_LT, "<", line, col);
        }
        case '>': {
            if (current(l) == '=') { advance(l); return make_token(TOK_GTE, ">=", line, col); }
            return make_token(TOK_GT, ">", line, col);
        }
        case '.': {
            if (current(l) == '.') { advance(l); return make_token(TOK_DOTDOT, "..", line, col); }
            return make_token(TOK_DOT, ".", line, col);
        }
        case '(': return make_token(TOK_LPAREN,   "(", line, col);
        case ')': return make_token(TOK_RPAREN,   ")", line, col);
        case '{': return make_token(TOK_LBRACE,   "{", line, col);
        case '}': return make_token(TOK_RBRACE,   "}", line, col);
        case '[': return make_token(TOK_LBRACKET, "[", line, col);
        case ']': return make_token(TOK_RBRACKET, "]", line, col);
        case ',': return make_token(TOK_COMMA,    ",", line, col);
        case ':': return make_token(TOK_COLON,    ":", line, col);
        case ';': return make_token(TOK_SEMICOLON,";", line, col);
        default: {
            char err[4] = {c, '\0'};
            return make_token(TOK_ERROR, err, line, col);
        }
    }
}

void lexer_free(Lexer* l) { free(l); }
void token_free(Token* t) { if (t) { free(t->value); free(t); } }

const char* token_type_name(TokenType type) {
    switch(type) {
        case TOK_INT:    return "INT";
        case TOK_FLOAT:  return "FLOAT";
        case TOK_STRING: return "STRING";
        case TOK_BOOL:   return "BOOL";
        case TOK_IDENT:  return "IDENT";
        case TOK_LET:    return "LET";
        case TOK_FN:     return "FN";
        case TOK_IF:     return "IF";
        case TOK_ELSE:   return "ELSE";
        case TOK_RETURN: return "RETURN";
        case TOK_EOF:    return "EOF";
        default:         return "TOKEN";
    }
}
