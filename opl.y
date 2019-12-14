%{
#include <stdio.h>
extern FILE* yyin;
extern int yylineno;
%}

%token INT FLOAT CHAR STRING BOOL
	   ID 
	   UNSIGNED_NUMBER FLOAT_NUMBER
	   STRING_VALUE BOOL_VALUE
%start s

%%

s: progr {printf("Input corect sintactic\n");}

progr:

%%

int yyerror(char *s)
{
	printf("Eroare: %s la linia: %d\n", s, yylineno);
}

int main(int argc, char** argv)
{
	yyin = fopen(argv[1], "r");
	yyparse();
}