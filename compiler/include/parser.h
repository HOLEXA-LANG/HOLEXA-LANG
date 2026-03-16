#ifndef PARSER_H
#define PARSER_H

#define _POSIX_C_SOURCE 200809L
#include "holexa.h"

typedef struct {
    Lexer*  lexer;
    Token*  current;
    Token*  previous;
    int     had_error;
} Parser;

Parser*  parser_new(Lexer* lexer);
ASTNode* parser_parse(Parser* parser);
void     parser_free(Parser* parser);

#endif
