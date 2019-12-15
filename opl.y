%{
#include <stdio.h>
extern FILE* yyin;
extern int yylineno;
%}

%token INT FLOAT CHAR STRING BOOL CONST
	   BEGIN_DECL END_DECL BEGIN_FNC END_FNC BEGIN_MAIN END_MAIN
	   ID 
	   UNSIGNED_NUMBER INTEGER_NUMBER FLOAT_NUMBER
	   STRING_VALUE BOOL_VALUE CHAR_VALUE
       FNC CALL
%start s

%%

s: progr {printf("Input corect sintactic\n");}
 ;

progr: declarations functions call_functions main
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

type: subtype maintype
    ;

subtype:
       | CONST 

maintype: INT
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




functions : BEGIN_FNC list_functions END_FNC
          ;

list_functions: function list_functions
              | function
              ;

function: FNC type ':' ID '(' content_function ')' ';'
        ;

content_function: variables
                 |
                 ;

variables: var_decl ',' variables
         | var_decl
         ;

 /* call_functions: call ';' call_functions
              | call ';'

call: ID '=' CALL FNC type ':' ID '(' list_parameters ')' ';'
    ;

list_parameters: param ',' list_parameters
               | param
               ;

param: value
     | ID
     | arith_op
     | '(' call ')'
     |
     ;

arith_op: operand operator operand
        | operand operator arith_op
        ;

operand: value
       | ID
       | '('call')'
       ;

operator : '+'
         | '-'
         | '*'
         | '/'
         ;

 */

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