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
     FNC 
     CALL 
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

declarations_content : declaration_list functions classes 
                     ;

declaration_list: decl 
                | decl declaration_list
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


classes: class_list
       ;


class_list: class class_list
          | class
          ;

class: segment CLASS ID '{' class_content '}'
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

declarations_in_class: decl_in_class declarations_in_class
                     | decl_in_class
                     ;

decl_in_class: var_decl_in_class ';'
             ;


var_decl_in_class: type ID     
                 | type ID '=' value
                 | type ID '[' UNSIGNED_NUMBER ']'
                 | type ID '[' UNSIGNED_NUMBER ']' '=' '{' '}'
                 | type ID '[' UNSIGNED_NUMBER ']' '=' '{' array '}'
                 | type ID fct
                 | type ID fct_ret
                 ;

fct: '(' function_content ')'
   ;

fct_ret: fct '{' ret_val '}'
       ;

ret_val: RET ';'
       | RET value ';'
       | RET ID ';'
       ;




functions: functions_list
         ;

functions_list: function functions_list
              | function
              ;

function: FNC type ':' ID '(' function_content ')' ';'
        ;

function_content: declarations_content
                |
                ;

declarations_content: var_decl ',' declarations_content
                    | var_decl
                    ;




main: BEGIN_MAIN main_content END_MAIN
    ;


main_content: assign_list call_list
           ;

assign_list : assign_list  assign
            | assign 
            ;

assign: ID '=' ID ';'
      | ID '=' value ';'
      | ID '[' UNSIGNED_NUMBER ']' '=' value ';'
      ;




call_list: call ';' call_list
         | call ';'
         ; 

call: ID '=' CALL ID'(' call_content ')'
    ;

call_content: param ',' call_content
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