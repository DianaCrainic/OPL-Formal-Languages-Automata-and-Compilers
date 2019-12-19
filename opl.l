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

begin_declarations {return BEGIN_DECL;}
end_declarations {return END_DECL;}
begin_functions {return BEGIN_FNC;}
end_functions {return END_FNC;}
begin_call {return BEGIN_CALL;}
end_call {return END_CALL;}
begin_classes {return BEGIN_CLASS;}
end_classes {return END_CLASS;}
begin_main {return BEGIN_MAIN;}
end_main {return END_MAIN;}

"class" {return CLASS;}
"return" {return RET;}
"public" {return PUBLIC;}
"private" {return PRIVATE;}
"protected" {return PROTECTED;}
"function" {return FNC;}
"call" {return CALL;}

[-+]([1-9][0-9]*|0) {return INTEGER_NUMBER;}
[1-9][0-9]*|0 {return UNSIGNED_NUMBER;}
([1-9][0-9]*\.[0-9]+)|(0\.[0-9]+) {return FLOAT_NUMBER;}
true|false {return BOOL_VALUE;}
\"[^\"]+\" {return STRING_VALUE;}
\'.\' {return CHAR_VALUE;}
[A-Za-z][A-Za-z0-9]* {return ID;}

[ \t] ;
\n {++yylineno;}
. {return yytext[0];}

%%
 
 