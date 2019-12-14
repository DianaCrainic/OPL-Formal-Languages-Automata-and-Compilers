%{
#include <stdio.h>
extern FILE* yyin;
extern int yylineno;
%}

%token INT FLOAT CHAR STRING BOOL
	   BEGIN_DECL END_DECL BEGIN_MAIN END_MAIN
	   ID 
	   UNSIGNED_NUMBER INTEGER_NUMBER FLOAT_NUMBER
	   STRING_VALUE BOOL_VALUE CHAR_VALUE
%start s

%%

s: progr {printf("Input corect sintactic\n");}
 ;

progr: declarations main
     | main
     ;

declarations: BEGIN_DECL declarations_content END_DECL
            ;

declarations_content: decl 
                    | decl declarations_content
                    ;

decl: var_decl ';'
    ;

var_decl: type ID
        | type ID '=' value
		| type ID '[' UNSIGNED_NUMBER ']'
		| type ID '[' UNSIGNED_NUMBER ']' '=' '{' '}'
		| type ID '[' UNSIGNED_NUMBER ']' '=' '{' array '}'
        ;

type: INT
    | FLOAT
    | CHAR
    | STRING
    | BOOL
    ;

value: INTEGER_NUMBER
     | UNSIGNED_NUMBER
     | FLOAT_NUMBER
     | STRING_VALUE
     | BOOL_VALUE
     | CHAR_VALUE
     ;

array: array_element
     | array_element ',' array
     ;

array_element: ID
             | value
             ;

main: BEGIN_MAIN main_content END_MAIN
    ;

main_content: instruction ';'
            | instruction ';' main_content
            ;

instruction: assign
           ;

assign: ID '=' ID 
      | ID '=' value
      | ID '[' UNSIGNED_NUMBER ']' '=' value
      ;

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