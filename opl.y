%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

extern int yylex();
extern int yyerror(char * syntaxError);

VariableTable listOfVariables;
FunctionTable listOfFunctions;
ClassTable listOfClasses;

%}

%token INT FLOAT CHAR STRING BOOL CONST
     BEGIN_DECL END_DECL 
     BEGIN_MAIN END_MAIN
     ID
     INTEGER_NUMBER 
     FLOAT_NUMBER
     STRING_VALUE BOOL_VALUE CHAR_VALUE
     FNC CALL 
     CLASS
     IF THEN ELSE WHILE DO FOR
     LE GE EQ NE OR AND
     RET
     EVAL
     CONCAT LENGTH COMPARE LOWER UPPER
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
    | function_decl
    | class_decl
    ;

variable_decl: type variable_list
             ;

variable_list: var ',' variable_list
             | var
             ;

var: ID
   | ID '=' value
   | ID '=' ID
   | ID '[' INTEGER_NUMBER ']'
   | ID '[' INTEGER_NUMBER ']' '=' '{' '}'
   | ID '[' INTEGER_NUMBER ']' '=' '{' array '}'
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
     | FLOAT_NUMBER
     | STRING_VALUE
     | BOOL_VALUE
     | CHAR_VALUE
     ;

array: array_element
     | array_element ',' array
     ;

array_element: value
             | ID
             ;

function_decl: FNC type ':' ID '(' function_param ')' '{' code_block return_value ';' '}'
             ;

function_param: 
              | list_of_param
              ;

list_of_param: variables
             | variables ',' list_of_param
             ;

variables: type ID
         | type ID '=' value 
         | type ID '[' INTEGER_NUMBER ']'
         | type ID '[' INTEGER_NUMBER ']' '=' '{' '}'
         | type ID '[' INTEGER_NUMBER ']' '=' '{' array '}'
         | ID ID 
         ;

class_decl: CLASS ID '{' class_content '}'
          ;

class_content: decl_in_class class_content
             | decl_in_class
             ;

decl_in_class: variable_decl_in_class ';'
             | method_decl_in_class 
             ;

variable_decl_in_class: type variable_list
                      ;

method_decl_in_class: type ID '(' function_param ')'
                    | type ID '(' function_param ')' '{' code_block return_value ';' '}'
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
         | eval_statement ';'
         | string_statement ';'
         ;

assign: ID '=' ID
      | ID '.' ID '=' ID
      | ID '=' ID '.' ID
      | ID '.' ID '=' ID '.' ID
      | ID '=' value
      | ID '.' ID '=' value
      | ID '=' arithmetic_expression
      | ID '.' ID '=' arithmetic_expression
      | ID '[' INTEGER_NUMBER ']' '=' value
      | ID '.' ID '[' INTEGER_NUMBER ']' '=' value
      | ID '[' INTEGER_NUMBER ']' '=' ID
      | ID '.' ID '[' INTEGER_NUMBER ']' '=' ID
      | ID '[' INTEGER_NUMBER ']' '=' ID '.' ID
      | ID '.' ID '[' INTEGER_NUMBER ']' '=' ID '.' ID
      | ID '[' INTEGER_NUMBER ']' '=' ID '[' INTEGER_NUMBER ']'
      | ID '[' INTEGER_NUMBER ']' '=' ID '.' ID '[' INTEGER_NUMBER ']'
      | ID '.' ID '[' INTEGER_NUMBER ']' '=' ID '[' INTEGER_NUMBER ']'
      | ID '.' ID '[' INTEGER_NUMBER ']' '=' ID '.' ID '[' INTEGER_NUMBER ']'
      ;

call: ID '=' CALL ID '(' call_param ')'
    | ID '=' CALL ID '.' ID '(' call_param ')'
    | ID '.' ID '=' CALL ID '(' call_param ')'
    | ID '.' ID '=' CALL ID '.' ID '(' call_param ')'
    ;

call_param: 
          | list_call_param
          ;

list_call_param: param
               | param ',' list_call_param
               ;

param: value
     | ID
     | ID '.' ID
     | arithmetic_expression
     | '(' call ')'
     | string_function
     ;

arithmetic_expression: operand operator operand
                     | operand operator arithmetic_expression
                     ;

operand: value
       | ID
       | ID '.' ID
       | '(' call ')'
       ;

operator : '+'
         | '-'
         | '*'
         | '/'
         ;

if_statement: IF condition THEN '{' code_block '}' else_statement
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
         | '(' call ')'
         | value
         | ID
         | ID '.' ID
         | arithmetic_expression
         ;

code_block:
          | statement code_block
          ;

while_statement: WHILE condition DO '{' code_block '}'
               ;

for_statement: FOR '(' for_initialization ';' condition ';' assign ')' '{' code_block '}'
             ;

for_initialization: assign
                  | variable_decl
                  ;

eval_statement: EVAL '(' eval_expression ')'
              ;

// eval_expression: eval_result {printf("Rezultatul expresiei :%d\n", $<intval>$);}
//                ;

// eval_result: eval_result '+' eval_result
//            | eval_result '-' eval_result
//            | eval_result '*' eval_result
//            | eval_result '/' eval_result
//            |

eval_expression: eval_operand operator eval_operand
               | eval_operand operator eval_expression
               ;

eval_operand: ID
            | ID '.' ID
            | INTEGER_NUMBER
            | '(' call ')'
            | LENGTH '(' string_content')'
            ;

string_statement: ID '=' string_function
                ;

string_function: CONCAT '(' strings_content ')'
               | LENGTH '(' string_content')'
               | COMPARE '(' strings_content ')'
               | LOWER '(' string_content ')'
               | UPPER '(' string_content ')'
               ;

strings_content: string_content ',' string_content 
               ;

string_content: ID
              | STRING_VALUE
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