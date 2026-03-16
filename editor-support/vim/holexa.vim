" HOLEXA Vim Syntax Highlighting
" File: ~/.vim/syntax/holexa.vim
" Code like a Dragon. Think like a Human.

if exists("b:current_syntax")
    finish
endif

" Keywords
syn keyword holexaKeyword    let const fn return if else while for loop break continue
syn keyword holexaKeyword    class import from async await spawn try catch finally raise match
syn keyword holexaKeyword    trait implements self extern in
syn keyword holexaType       Int Float String Bool List Map None Any Byte
syn keyword holexaBoolean    true false none
syn keyword holexaBuiltin    print input len str int float type range append

" Strings
syn region holexaString start='"' end='"' skip='\\"'

" Numbers
syn match holexaNumber '\b[0-9]\+\(\.[0-9]\+\)\?\b'

" Comments
syn match holexaComment '//.*$'
syn region holexaComment start='/\*' end='\*/'

" Functions
syn match holexaFunction '\b[a-zA-Z_][a-zA-Z0-9_]*\s*('

" Operators
syn match holexaOperator '[+\-*/%=<>!&|^~]\+'
syn match holexaOperator '->'
syn match holexaOperator '\.\.'

" Colors
hi def link holexaKeyword   Keyword
hi def link holexaType      Type
hi def link holexaBoolean   Boolean
hi def link holexaBuiltin   Function
hi def link holexaString    String
hi def link holexaNumber    Number
hi def link holexaComment   Comment
hi def link holexaFunction  Function
hi def link holexaOperator  Operator

let b:current_syntax = "holexa"
