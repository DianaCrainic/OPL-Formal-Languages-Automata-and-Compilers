%{
#include <stdio.h>
#include "y.tab.h"
%}
%%

"/*"(.|\n)+"*/" ;

"int" {return INT;}
"float" {return FLOAT;}
"char" {return CHAR;}
"string" {return STRING;}
"bool" {return BOOL;}

[A-Za-z][A-Za-z0-9]* {return ID;}
[1-9][0-9]*|0 {return UNSIGNED_NUMBER;}
([1-9][0-9]*\.[0-9]+)|(0\.[0-9]+) {return FLOAT_NUMBER;}
\"[^\"]+\" {return STRING_VALUE;}
"true"|"false" {return BOOL_VALUE;}

[ \t] ;
\n {++yylineno;}
. {return yytext[0];}

%%
 
