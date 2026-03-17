#define _POSIX_C_SOURCE 200809L
#include "../include/holexa.h"

typedef struct { const char* word; TokenType type; } Keyword;
static Keyword keywords[] = {
    {"let",TOK_LET},{"const",TOK_CONST},{"fn",TOK_FN},
    {"return",TOK_RETURN},{"if",TOK_IF},{"else",TOK_ELSE},
    {"while",TOK_WHILE},{"for",TOK_FOR},{"loop",TOK_LOOP},
    {"break",TOK_BREAK},{"continue",TOK_CONTINUE},
    {"class",TOK_CLASS},{"import",TOK_IMPORT},{"from",TOK_FROM},
    {"async",TOK_ASYNC},{"await",TOK_AWAIT},{"spawn",TOK_SPAWN},
    {"try",TOK_TRY},{"catch",TOK_CATCH},{"finally",TOK_FINALLY},
    {"raise",TOK_RAISE},{"match",TOK_MATCH},{"true",TOK_TRUE},
    {"false",TOK_FALSE},{"and",TOK_AND},{"or",TOK_OR},
    {"not",TOK_NOT},{"in",TOK_IN},{"self",TOK_SELF},
    {"trait",TOK_TRAIT},{"implements",TOK_IMPLEMENTS},
    {"none",TOK_NONE},{NULL,TOK_ERROR}
};

static char cur(Lexer* l)  { return l->source[l->pos]; }
static char peek(Lexer* l) { return (l->pos+1<l->length)?l->source[l->pos+1]:'\0'; }
static char adv(Lexer* l)  {
    char c=l->source[l->pos++];
    if(c=='\n'){l->line++;l->column=1;}else l->column++;
    return c;
}
static Token* mktok(TokenType t,const char* v,int line,int col){
    Token* tk=malloc(sizeof(Token));
    tk->type=t; tk->value=strdup(v?v:"");
    tk->line=line; tk->column=col;
    return tk;
}

Lexer* lexer_new(const char* source){
    Lexer* l=malloc(sizeof(Lexer));
    l->source=source; l->pos=0;
    l->line=1; l->column=1;
    l->length=(int)strlen(source);
    return l;
}

Token* lexer_next_token(Lexer* l){
    while(l->pos<l->length && isspace(cur(l))) adv(l);
    if(l->pos>=l->length) return mktok(TOK_EOF,"EOF",l->line,l->column);

    int line=l->line, col=l->column;
    char c=cur(l);

    // Comments
    if(c=='/'&&peek(l)=='/'){
        while(l->pos<l->length&&cur(l)!='\n') adv(l);
        return lexer_next_token(l);
    }
    if(c=='/'&&peek(l)=='*'){
        adv(l); adv(l);
        while(l->pos<l->length){
            if(cur(l)=='*'&&peek(l)=='/'){adv(l);adv(l);break;}
            adv(l);
        }
        return lexer_next_token(l);
    }

    // String
    if(c=='"'){
        adv(l);
        int start=l->pos;
        while(l->pos<l->length&&cur(l)!='"'){
            if(cur(l)=='\\') adv(l);
            adv(l);
        }
        int len=l->pos-start;
        char* s=malloc(len+1);
        strncpy(s,l->source+start,len);
        s[len]='\0';
        adv(l);
        Token* t=mktok(TOK_STRING,s,line,col);
        free(s); return t;
    }

    // Numbers
    if(isdigit(c)){
        int start=l->pos, is_f=0;
        while(l->pos<l->length&&isdigit(cur(l))) adv(l);
        if(l->pos<l->length&&cur(l)=='.'&&peek(l)!='.'){
            is_f=1; adv(l);
            while(l->pos<l->length&&isdigit(cur(l))) adv(l);
        }
        int len=l->pos-start;
        char* num=malloc(len+1);
        strncpy(num,l->source+start,len); num[len]='\0';
        Token* t=mktok(is_f?TOK_FLOAT:TOK_INT,num,line,col);
        free(num); return t;
    }

    // Identifiers/Keywords
    if(isalpha(c)||c=='_'){
        int start=l->pos;
        while(l->pos<l->length&&(isalnum(cur(l))||cur(l)=='_')) adv(l);
        int len=l->pos-start;
        char* id=malloc(len+1);
        strncpy(id,l->source+start,len); id[len]='\0';
        TokenType type=TOK_IDENT;
        for(int i=0;keywords[i].word;i++)
            if(strcmp(id,keywords[i].word)==0){type=keywords[i].type;break;}
        Token* t=mktok(type,id,line,col);
        free(id); return t;
    }

    adv(l);
    switch(c){
        case '+': return mktok(TOK_PLUS,    "+", line,col);
        case '-': {
            if(cur(l)=='>'){adv(l);return mktok(TOK_ARROW,"->",line,col);}
            return mktok(TOK_MINUS,"-",line,col);
        }
        case '*': return mktok(TOK_STAR,    "*", line,col);
        case '/': return mktok(TOK_SLASH,   "/", line,col);
        case '%': return mktok(TOK_PERCENT, "%", line,col);
        case '=': {
            if(cur(l)=='='){adv(l);return mktok(TOK_EQ,"==",line,col);}
            return mktok(TOK_ASSIGN,"=",line,col);
        }
        case '!': {
            if(cur(l)=='='){adv(l);return mktok(TOK_NEQ,"!=",line,col);}
            return mktok(TOK_ERROR,"!",line,col);
        }
        case '<': {
            if(cur(l)=='='){adv(l);return mktok(TOK_LTE,"<=",line,col);}
            return mktok(TOK_LT,"<",line,col);
        }
        case '>': {
            if(cur(l)=='='){adv(l);return mktok(TOK_GTE,">=",line,col);}
            return mktok(TOK_GT,">",line,col);
        }
        case '.': {
            if(cur(l)=='.'){adv(l);return mktok(TOK_DOTDOT,"..",line,col);}
            return mktok(TOK_DOT,".",line,col);
        }
        case '(': return mktok(TOK_LPAREN,   "(",line,col);
        case ')': return mktok(TOK_RPAREN,   ")",line,col);
        case '{': return mktok(TOK_LBRACE,   "{",line,col);
        case '}': return mktok(TOK_RBRACE,   "}",line,col);
        case '[': return mktok(TOK_LBRACKET, "[",line,col);
        case ']': return mktok(TOK_RBRACKET, "]",line,col);
        case ',': return mktok(TOK_COMMA,    ",",line,col);
        case ':': return mktok(TOK_COLON,    ":",line,col);
        case ';': return mktok(TOK_SEMICOLON,";",line,col);
        default:  { char e[2]={c,'\0'}; return mktok(TOK_ERROR,e,line,col); }
    }
}

void lexer_free(Lexer* l){ if(l) free(l); }
void token_free(Token* t){ if(t){if(t->value)free(t->value);free(t);} }

const char* token_type_name(TokenType t){
    switch(t){
        case TOK_INT:    return "INT";
        case TOK_FLOAT:  return "FLOAT";
        case TOK_STRING: return "STRING";
        case TOK_IDENT:  return "IDENT";
        case TOK_LET:    return "LET";
        case TOK_CONST:  return "CONST";
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
