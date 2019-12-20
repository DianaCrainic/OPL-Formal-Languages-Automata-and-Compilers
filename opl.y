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
     CLASS
     IF THEN ELSE WHILE FOR
     LE GE EQ NE OR AND
     RET
%start s

%right '='
%left AND OR
%left '<' '>' LE GE EQ NE
%left '+' '-'
%left '*' '/'
%left '!'

%%

s: progr {printf("Input corect sintactic\n");}
 ;

progr: declarations main
     | main
     | 
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

variable_decl: type variable_list
             ;

variable_list: var ',' variable_list
             | var
             ;

var: ID
   | ID '=' value
   | ID '[' UNSIGNED_NUMBER ']'
   | ID '[' UNSIGNED_NUMBER ']' '=' '{' '}'
   | ID '[' UNSIGNED_NUMBER ']' '=' '{' array '}'
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

function_decl: FNC type ':' ID '(' function_param ')'
             ;

function_param: 
              | list_of_param
              ;

list_of_param: variables
             | variables ',' list_of_param
             ;

variables: type ID
         | type ID '=' value
         | type ID '[' UNSIGNED_NUMBER ']'
         | type ID '[' UNSIGNED_NUMBER ']' '=' '{' '}'
         | type ID '[' UNSIGNED_NUMBER ']' '=' '{' array '}'
         ;

class_decl: CLASS ID '{' class_content '}'
          ;

class_content: decl_in_class ';' class_content
             | decl_in_class ';'
             ;

decl_in_class: variable_decl_in_class
             | method_decl_in_class 
             ;

variable_decl_in_class: type variable_list
                      ;

method_decl_in_class: type ID '(' function_param ')'
                    | type ID '(' function_param ')' '{' return_value ';' '}'
                    ;

return_value: RET
            | RET value
            | RET ID
            ;

main: BEGIN_MAIN main_content END_MAIN
    ;

main_content: statement
            | statement main_content
            ;

statement: assign ';'
         | call ';'
         | if_statement
         | while_statement
         | for_statement
         ;

assign: ID '=' ID
      | ID '=' value
      | ID '[' UNSIGNED_NUMBER ']' '=' value
      ;

call: ID '=' CALL ID '(' call_param ')'
    | CALL ID '(' call_param ')'
    ;

call_param: 
          | list_call_param
          ;

list_call_param: param
               | param ',' list_call_param
               ;

param: value
     | ID
     | arithmetic_expression
     | '(' call ')'
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

if_statement: IF '(' condition ')' THEN '{' code_block '}' else_statement
            ;

else_statement: ELSE '{' code_block '}'
              |
              ;

condition: condition '<' condition
         | condition '>' condition
         | condition LE condition
         | condition GE condition
         | condition EQ condition
         | condition NE condition
         | condition OR condition
         | condition AND condition
         | '(' condition ')'
         | ID
         | value
         | arithmetic_expression
         ;

code_block:
          | statement code_block
          ;

while_statement: WHILE '(' condition ')' '{' code_block '}'
               ;

for_statement: FOR '(' for_initialization ';' condition ';' for_step  ')' '{' code_block '}'
             ;

for_initialization: assign
                  | variable_decl
                  ;

for_step: '-' '-' ID
        | '+' '+' ID
        | ID '+' '+'
        | ID '-' '-'
        | ID '=' arithmetic_expression
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