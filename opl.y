%{
#include <stdio.h>
extern FILE* yyin;
extern int yylineno;
%}

%token INT FLOAT CHAR STRING BOOL CONST
	   BEGIN_DECL END_DECL 
     BEGIN_MAIN END_MAIN
	   ID 
	   UNSIGNED_NUMBER INTEGER_NUMBER FLOAT_NUMBER
	   STRING_VALUE BOOL_VALUE CHAR_VALUE
     FNC CALL 
     CLASS PUBLIC PRIVATE PROTECTED
     RET
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

decl: variable_decl ';'
    | function_decl ';'
    | class_decl
    ;

variable_decl: type ID
             | type ID '=' value
		         | type ID '[' UNSIGNED_NUMBER ']'
		         | type ID '[' UNSIGNED_NUMBER ']' '=' '{' '}'
		         | type ID '[' UNSIGNED_NUMBER ']' '=' '{' array '}'
             ;

type: subtype maintype
    ;

subtype:
       | CONST 
       ;

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

class_decl: segment CLASS ID '{' class_content '}'
          | CLASS ID '{' class_content '}'
          ;

segment: PUBLIC
       | PRIVATE
       | PROTECTED
       ;

class_content: segment ':' declarations_in_class segment ':' declarations_in_class segment ':' declarations_in_class
             | segment ':' declarations_in_class segment ':' declarations_in_class
             | segment ':' declarations_in_class
             ;

declarations_in_class: decl_in_class ';' declarations_in_class
                     | decl_in_class ';'
                     ;

decl_in_class: variable_decl_in_class
             | method_decl_in_class 
             ;

variable_decl_in_class: type ID     
                      | type ID '=' value
                      | type ID '[' UNSIGNED_NUMBER ']'
                      | type ID '[' UNSIGNED_NUMBER ']' '=' '{' '}'
                      | type ID '[' UNSIGNED_NUMBER ']' '=' '{' array '}'
                      ;

method_decl_in_class: type ID '(' function_param ')'
                    | type ID '(' function_param ')' '{' return_value '}'
                    ;

function_param: 
              | list_of_param
              ;

list_of_param: variable_decl
             | variable_decl ',' list_of_param
             ;

return_value: RET ';'
            | RET value ';'
            | RET ID ';'
            ;

function_decl: FNC type ':' ID '(' function_param ')'
             ;

main: BEGIN_MAIN main_content END_MAIN
    ;

main_content: statement ';'
            | statement ';' main_content
            ;

statement: assign
         | call
         ;

assign: ID '=' ID
      | ID '=' value
      | ID '[' UNSIGNED_NUMBER ']' '=' value
      ;

call: ID '=' CALL ID '(' call_param ')'
    ;

call_param: param ',' call_param
          | param
          ;

param: value
     | ID
     | arithmetic_expression
     | '(' call ')'
     |
     ;

arithmetic_expression: operand operator operand
                     | operand operator arithmetic_expression
                     ;

operand: value
       | ID
       | '(' call ')'
       ;

operator : '+'
         | '-'
         | '*'
         | '/'
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