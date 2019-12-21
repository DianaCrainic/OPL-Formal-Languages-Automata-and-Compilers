%{
#include <stdio.h>
#include "y.tab.h"
%}
%%
 
"/*"(.|\n)+"*/" ;

int {return INT;}
float {return FLOAT;}
char {return CHAR;}
string {return STRING;}
bool {return BOOL;}
const {return CONST;}

"begin_declarations" {return BEGIN_DECL;}
"end_declarations" {return END_DECL;}
"begin_main" {return BEGIN_MAIN;}
"end_main" {return END_MAIN;}

"class" {return CLASS;}
"return" {return RET;}
"function" {return FNC;}
"call" {return CALL;}

"if" {return IF;}
"then" {return THEN;}
"else" {return ELSE;}
"while" {return WHILE;}
"do" {return DO;}
"for" {return FOR;}

"concat" {return CONCAT;}
"length" {return LENGTH;}
"compare" {return COMPARE;}
"lower" {return LOWER;}
"upper" {return UPPER;}

"<=" {return LE;}
">=" {return GE;}
"==" {return EQ;}
"!=" {return NE;}
"||" {return OR;}
"&&" {return AND;}
"Eval" {return EVAL;}

[-+]?([1-9][0-9]*|0) {return INTEGER_NUMBER;}
([1-9][0-9]*\.[0-9]+)|(0\.[0-9]+) {return FLOAT_NUMBER;}
"true"|"false" {return BOOL_VALUE;}
\"[^\"]+\" {return STRING_VALUE;}
\'.\' {return CHAR_VALUE;}
[A-Za-z][A-Za-z0-9]* {return ID;}

[ \t] ;
\n {++yylineno;}
. {return yytext[0];}

%%
 
 