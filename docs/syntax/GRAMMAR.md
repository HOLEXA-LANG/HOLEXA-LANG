# HOLEXA Formal Grammar Rules

## Tokens
IDENTIFIER  = [a-zA-Z_][a-zA-Z0-9_]*
INT_LIT     = [0-9]+
FLOAT_LIT   = [0-9]+ '.' [0-9]+
STRING_LIT  = '"' [^"]* '"'
BOOL_LIT    = 'true' | 'false'
NONE_LIT    = 'none'

## Keywords
let const fn return if else while for loop
break continue class import from async await
spawn try catch finally raise match extern
implements trait self true false none

## Program Structure
program     = statement*
statement   = let_stmt | fn_stmt | if_stmt | loop_stmt
            | class_stmt | import_stmt | return_stmt
            | expr_stmt

## Expressions
expr        = assign_expr
assign_expr = logic_expr ('=' assign_expr)?
logic_expr  = compare_expr (('and'|'or') compare_expr)*
compare_expr= add_expr (('=='|'!='|'<'|'>'|'<='|'>=') add_expr)*
add_expr    = mul_expr (('+' | '-') mul_expr)*
mul_expr    = unary_expr (('*' | '/' | '%') unary_expr)*
unary_expr  = ('not' | '-') unary_expr | primary
primary     = INT_LIT | FLOAT_LIT | STRING_LIT | BOOL_LIT
            | IDENTIFIER | call_expr | index_expr
            | '(' expr ')'

## Function Call
call_expr   = IDENTIFIER '(' arg_list? ')'
arg_list    = expr (',' expr)*

## Type System
type        = 'Int' | 'Float' | 'String' | 'Bool'
            | 'List' '<' type '>'
            | 'Map' '<' type ',' type '>'
            | 'None' | 'Any' | IDENTIFIER
