%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "functions.h"

extern int yylex();
extern int yyerror(char * syntaxError);

VariableTable listOfVariables;
FunctionTable listOfFunctions;
ClassTable listOfClasses;
ArrayEval listOfEval;

struct Variable v;
struct Function fun;
struct Class cl;
struct EvalExpr expr;

int noSyntacticErrors = 0;
int noSemanticErrors = 1;
int isFunction = 0;
int arithmeticExprType = -2;
int returnType;

void update_scope();

//3.1
void variable_previously_defined(char* id);
void class_variable_previously_defined(char* className, char* id);

//3.2
void variable_was_declared(char* id);
void class_variable_was_declared(VariableTable arr, char* id);

//3.3
int variable_is_init(VariableTable arr, char* id);
int class_variable_is_init(ClassTable arr, char* className, char* id);
void set_init_variable(VariableTable* arr, char* id);
void set_init_class_variable(ClassTable* arr, char* className, char* id);
void check_variable_is_init(VariableTable arr, char* id);
void check_class_variable_is_init(ClassTable arr, char* className, char* id);

//3.4
int compare_params(struct Variable v1, struct Variable v2);
void function_was_declared(FunctionTable arr, struct Function fun);
void method_was_declared(FunctionTable arr, struct Function fun);

//3.5
void function_previously_defined(char* id);
void method_previously_defined(char* className, char* id);

//3.6
int leftType, rightType, valueType;
int type_of_variable(VariableTable arr, char* id);
int type_of_class_variable(ClassTable arr, char* className, char* id);
int type_of_return_function(FunctionTable arr, char* id);
int type_of_return_method(ClassTable arr, char* className, char* id);
void different_types();

//3.7
int variable_is_array(VariableTable arr, char* id);
int class_variable_is_array(ClassTable arr, char* className, char* id);
void check_function_signature(FunctionTable arr, struct Function fun);
void check_method_signature(ClassTable arr, char* className, struct Function fun);

//3.8
expr_info* create_int_expr(int value);
expr_info* create_str_expr(char* value1, char* value2);
void free_expr(expr_info* expr);
void print_expr(expr_info* expr);

//extra
void check_array_length(int len);
int variable_is_const(VariableTable arr, char* id);
int class_variable_is_const(ClassTable arr, char* className, char* id);
void check_variable_is_const(VariableTable arr, char* id);
void check_class_variable_is_const(ClassTable arr, char* className, char* id);

%}

%union 
{
    int intval;
    char* strval;
    struct expr_info* expr_ptr;
}

%type <expr_ptr>eval_expression
%type <expr_ptr>eval_result

%token INT FLOAT CHAR STRING BOOL CONST
     BEGIN_DECL END_DECL 
     BEGIN_MAIN END_MAIN
     <strval>ID
     <intval>INTEGER_NUMBER 
     FLOAT_NUMBER
     <strval>STRING_VALUE
     BOOL_VALUE CHAR_VALUE
     FNC CALL 
     CLASS MTH
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

s: progr {printf("No syntactic errors\n"); noSyntacticErrors = 1;}
 ;

progr: declarations main
     | main
     | 
     ;

declarations: BEGIN_DECL {strcpy(v.scope, "#\0");} declarations_content END_DECL
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

variable_list: var {insert_variable(&listOfVariables, v);} ',' variable_list
             | var {insert_variable(&listOfVariables, v);}
             ;

var: ID 
    {
        variable_was_declared($1);
        if (v.t.isConst == 1)
        {
            printf("Const variable %s (line: %d) must be initialized\n", $1, yylineno);
            noSemanticErrors = 0;
        }
        v.t.isInit = 0;
        v.line = yylineno;
        v.t.isArray = 0;
        strcpy(v.name, $1);
    }
    | ID '=' value
    {
        variable_was_declared($1);
        leftType = v.t.mainType;
        if (leftType != valueType)
        {
            different_types();
        }
        v.t.isInit = 1;
        v.line = yylineno;
        v.t.isArray = 0;
        strcpy(v.name, $1);
    }
    | ID '=' ID
    {
        variable_was_declared($1);
        variable_previously_defined($3);
        check_variable_is_init(listOfVariables, $3);
        leftType = v.t.mainType;
        if (leftType != type_of_variable(listOfVariables, $3))
        {
            different_types();
        }
        v.t.isInit = 1;
        v.line = yylineno;
        v.t.isArray = 0;
        strcpy(v.name, $1);
    }
    | ID '[' INTEGER_NUMBER ']'
    {
        variable_was_declared($1);
        check_array_length($3);
        v.line = yylineno;
        if (v.t.isConst == 1)
        {
            printf("Const variable %s (line: %d) must be initialized\n", $1, v.line);
            noSemanticErrors = 0;
        }
        v.t.isInit = 0;
        v.t.isArray = 1;
        v.t.lengthOfArray = $3;
        strcpy(v.name, $1);
    }
    | ID '[' INTEGER_NUMBER ']' '=' '{' '}'
    {
        variable_was_declared($1);
        v.line = yylineno;
        check_array_length($3);
        v.t.isInit = 1;
        v.t.isArray = 1;
        v.t.lengthOfArray = $3;
        strcpy(v.name, $1);
    }
    | ID '[' INTEGER_NUMBER ']' '=' '{' array '}'
    {
        variable_was_declared($1);
        v.line = yylineno;
        check_array_length($3);
        v.t.isInit = 1;
        v.t.isArray = 1;
        v.t.lengthOfArray = $3;
        strcpy(v.name, $1);
    }
    ;

type: subtype maintype
    ;

subtype: {v.t.isConst = 0;}
       | CONST {v.t.isConst = 1;}
       ;

maintype: INT {if(isFunction == 0) {v.t.mainType = 0;} else {fun.returnType = 0;}}
        | FLOAT {if(isFunction == 0) {v.t.mainType = 1;} else {fun.returnType = 1;}}
        | CHAR {if(isFunction == 0) {v.t.mainType = 2;} else {fun.returnType = 2;}}
        | STRING {if(isFunction == 0) {v.t.mainType = 3;} else {fun.returnType = 3;}}
        | BOOL {if(isFunction == 0) {v.t.mainType = 4;} else {fun.returnType = 4;}}
        ;

value: INTEGER_NUMBER {valueType = 0;}
     | FLOAT_NUMBER {valueType = 1;}
     | CHAR_VALUE {valueType = 2;}
     | STRING_VALUE {valueType = 3;}
     | BOOL_VALUE {valueType = 4;}
     ;

array: array_element
     | array_element ',' array
     ;

array_element: value
             {
                leftType = v.t.mainType;
                if (leftType != valueType)
                {
                    different_types();
                }
             }
             | ID 
             {
                variable_previously_defined($1);
                check_variable_is_init(listOfVariables, $1);
                leftType = v.t.mainType;
                if (leftType != type_of_variable(listOfVariables, $1))
                {
                    different_types();
                }
             }
             ;

function_decl: FNC {isFunction = 1; strcat(v.scope, "function#\0"); init_variables(&fun.paramTable);}
               type ':' ID {fun.line = yylineno; isFunction = 0; strcpy(fun.name, $5);}
               '(' function_param ')'
               '{' code_block return_value ';' '}' 
                {
                    function_was_declared(listOfFunctions, fun);
                    insert_function(&listOfFunctions, fun);
                    free_variables(&fun.paramTable);
                    update_scope();
                }
             ;

function_param:
              | list_of_param
              ;

list_of_param: variable {insert_variable(&fun.paramTable, v);} ',' list_of_param
             | variable {insert_variable(&fun.paramTable, v);}
             ;

variable: type ID
        {
            v.t.isArray = 0;
            strcpy(v.name, $2);
        }
        | type ID '=' value
        {
            leftType = v.t.mainType;
            if (leftType != valueType)
            {
                different_types();
            }
            v.t.isArray = 0;
            strcpy(v.name, $2);
        }
        | type ID '[' INTEGER_NUMBER ']'
        {
            check_array_length($4);
            v.t.isArray = 1;
            v.t.lengthOfArray = $4;
            strcpy(v.name, $2);
        }
        | type ID '[' INTEGER_NUMBER ']' '=' '{' '}' 
        {
            check_array_length($4);
            v.t.isArray = 1;
            v.t.lengthOfArray = $4;
            strcpy(v.name, $2);
        }
        | type ID '[' INTEGER_NUMBER ']' '=' '{' array '}'
        {
            check_array_length($4);
            v.t.isArray = 1;
            v.t.lengthOfArray = $4;
            strcpy(v.name, $2);
        }
        ;

class_decl: CLASS ID 
            {
                cl.line = yylineno;
                strcat(v.scope, "class#method#\0");
                strcpy(cl.name, $2);
                init_variables(&cl.attribTable);
                init_functions(&cl.methTable);
            } 
            '{' class_content '}'
            {
                insert_class(&listOfClasses, cl);
                free_functions(&cl.methTable);
                free_variables(&cl.attribTable);
                update_scope();
                update_scope();
            }
          ;

class_content: decl_in_class class_content
             | 
             ;

decl_in_class: variable_decl_in_class ';'
             | method_decl_in_class
             ;

variable_decl_in_class: type class_variable_list
                      ;

class_variable_list: class_variable {insert_variable(&cl.attribTable, v);}',' class_variable_list
                   | class_variable {insert_variable(&cl.attribTable, v);}
                   ;

class_variable: ID
              {
                class_variable_was_declared(cl.attribTable, $1);
                if (v.t.isConst == 1)
                {
                    printf("Const variable %s (line: %d) must be initialized\n", $1, yylineno);
                    noSemanticErrors = 0;
                }
                v.line = yylineno;
                v.t.isInit = 0;
                v.t.isArray = 0;
                strcpy(v.name, $1);
              }
              | ID '=' value 
              {
                class_variable_was_declared(cl.attribTable, $1);
                leftType = v.t.mainType;
                if (leftType != valueType)
                {
                   different_types();
                }
                v.line = yylineno;
                v.t.isInit = 1;
                v.t.isArray = 0;
                strcpy(v.name, $1);
              }
              | ID '[' INTEGER_NUMBER ']'
              {
                class_variable_was_declared(cl.attribTable, $1);
                check_array_length($3);
                v.line = yylineno;
                if (v.t.isConst == 1)
                {
                    printf("Const variable %s (line: %d) must be initialized\n", $1, v.line);
                    noSemanticErrors = 0;
                }
                v.t.isInit = 0;
                v.t.isArray = 1;
                v.t.lengthOfArray = $3;
                strcpy(v.name, $1);
              }
              | ID '[' INTEGER_NUMBER ']' '=' '{' '}' 
              {
                class_variable_was_declared(cl.attribTable, $1);
                v.line = yylineno;
                check_array_length($3);
                v.t.isInit = 1;
                v.t.isArray = 1;
                v.t.lengthOfArray = $3;
                strcpy(v.name, $1);
              }
              | ID '[' INTEGER_NUMBER ']' '=' '{' array '}' 
              {
                class_variable_was_declared(cl.attribTable, $1);
                v.line = yylineno;
                check_array_length($3);
                v.t.isInit = 1;
                v.t.isArray = 1;
                v.t.lengthOfArray = $3;
                strcpy(v.name, $1);
              }
              ;

method_decl_in_class: MTH {isFunction = 1;} type ID {isFunction = 0; fun.line = yylineno; strcpy(fun.name, $4); init_variables(&fun.paramTable);} 
                     '(' method_param ')' 
                     '{' code_block return_value ';' '}' 
                     {
                        method_was_declared(cl.methTable, fun);
                        insert_function(&cl.methTable, fun);
                        free_variables(&fun.paramTable);
                     }
                    ;

method_param:
            | list_of_method_param
            ;

list_of_method_param: type class_variable {insert_variable(&fun.paramTable, v);}
                    | type class_variable {insert_variable(&fun.paramTable, v);} ',' list_of_method_param
                    ;

return_value: RET
            | RET value
            {
                if (fun.returnType != valueType)
                {
                    printf("Invalid return type (line: %d)\n", yylineno);
                    noSemanticErrors = 0;
                }
            }
            | RET ID 
            {
                variable_previously_defined($2);
                check_variable_is_init(listOfVariables, $2);
                if (fun.returnType != type_of_variable(listOfVariables, $2))
                {
                    printf("Invalid return type (line: %d)\n", yylineno);
                    noSemanticErrors = 0;
                }
            }
            ;

main: BEGIN_MAIN {strcat(v.scope, "main#\0");} main_content END_MAIN
    ;

main_content: statement
            | statement main_content
            ;

statement: assign ';'
         | call ';'
         {
            free_variables(&fun.paramTable);
         }
         | if_statement
         | while_statement
         | for_statement
         | eval_statement ';'
         | string_statement ';'
         ;

assign: ID '=' ID 
      {
        variable_previously_defined($1);
        variable_previously_defined($3);
        check_variable_is_init(listOfVariables, $3);
        set_init_variable(&listOfVariables, $1);
        check_variable_is_const(listOfVariables, $1);

        if (type_of_variable(listOfVariables, $1) != type_of_variable(listOfVariables, $3))
        {
            different_types();
        }
      }
      | ID '.' ID '=' ID 
      {
        variable_previously_defined($5);
        class_variable_previously_defined($1, $3);
        check_variable_is_init(listOfVariables, $5);
        set_init_class_variable(&listOfClasses, $1, $3);
        check_class_variable_is_const(listOfClasses, $1, $3);

        if (type_of_class_variable(listOfClasses, $1, $3) != type_of_variable(listOfVariables, $5))
        {
            different_types();
        }
      }
      | ID '=' ID '.' ID
      {
        variable_previously_defined($1);
        class_variable_previously_defined($3, $5);
        check_class_variable_is_init(listOfClasses, $3, $5);
        set_init_variable(&listOfVariables, $1);
        check_variable_is_const(listOfVariables, $1);

        if (type_of_variable(listOfVariables, $1) != type_of_class_variable(listOfClasses, $3, $5))
        {
            different_types();
        }
      }
      | ID '.' ID '=' ID '.' ID 
      {
        class_variable_previously_defined($1, $3);
        class_variable_previously_defined($5, $7);
        check_class_variable_is_init(listOfClasses, $5, $7);
        set_init_class_variable(&listOfClasses, $1, $3);
        check_class_variable_is_const(listOfClasses, $1, $3);

        if (type_of_class_variable(listOfClasses, $1, $3) != type_of_class_variable(listOfClasses, $5, $7))
        {
            different_types();
        }
      }
      | ID '=' value 
      {
        variable_previously_defined($1);
        set_init_variable(&listOfVariables, $1);
        check_variable_is_const(listOfVariables, $1);

        if (type_of_variable(listOfVariables, $1) != valueType)
        {
            different_types();
        }
      }
      | ID '.' ID '=' value 
      {
        class_variable_previously_defined($1, $3);
        set_init_class_variable(&listOfClasses, $1, $3);
        check_class_variable_is_const(listOfClasses, $1, $3);

        if (type_of_class_variable(listOfClasses, $1, $3) != valueType)
        {
            different_types();
        }
      }
      | ID '=' arithmetic_expression 
      {
        variable_previously_defined($1);
        set_init_variable(&listOfVariables, $1);
        check_variable_is_const(listOfVariables, $1);

        if (type_of_variable(listOfVariables, $1) != arithmeticExprType)
        {
            different_types();
        }
        arithmeticExprType = -2;
      }
      | ID '.' ID '=' arithmetic_expression
      {
        class_variable_previously_defined($1, $3);
        set_init_class_variable(&listOfClasses, $1, $3);
        check_class_variable_is_const(listOfClasses, $1, $3);

        if (type_of_class_variable(listOfClasses, $1, $3) != arithmeticExprType)
        {
            different_types();
        }
        arithmeticExprType = -2;
      }
      | ID '[' INTEGER_NUMBER ']' '=' value 
      {
        check_array_length($3);
        variable_previously_defined($1);
        set_init_variable(&listOfVariables, $1);
        check_variable_is_const(listOfVariables, $1);

        if (type_of_variable(listOfVariables, $1) != valueType)
        {
            different_types();
        }
      }
      | ID '.' ID '[' INTEGER_NUMBER ']' '=' value 
      {
        check_array_length($5);
        class_variable_previously_defined($1, $3);
        set_init_class_variable(&listOfClasses, $1, $3);
        check_class_variable_is_const(listOfClasses, $1, $3);

        if (type_of_class_variable(listOfClasses, $1, $3) != valueType)
        {
            different_types();
        }
      }
      | ID '[' INTEGER_NUMBER ']' '=' ID 
      {
        check_array_length($3); 
        variable_previously_defined($1); 
        variable_previously_defined($6);
        check_variable_is_init(listOfVariables, $6);
        set_init_variable(&listOfVariables, $1);
        check_variable_is_const(listOfVariables, $1);

        if (type_of_variable(listOfVariables, $1) != type_of_variable(listOfVariables, $6))
        {
            different_types();
        }
      }
      | ID '.' ID '[' INTEGER_NUMBER ']' '=' ID 
      {
        check_array_length($5);
        variable_previously_defined($8);
        class_variable_previously_defined($1, $3);
        check_variable_is_init(listOfVariables, $8);
        set_init_class_variable(&listOfClasses, $1, $3);
        check_class_variable_is_const(listOfClasses, $1, $3);

        if (type_of_class_variable(listOfClasses, $1, $3) != type_of_variable(listOfVariables, $8))
        {
            different_types();
        }
      }
      | ID '[' INTEGER_NUMBER ']' '=' ID '.' ID 
      {
        check_array_length($3);
        variable_previously_defined($1);
        class_variable_previously_defined($6, $8);
        check_class_variable_is_init(listOfClasses, $6, $8);
        set_init_variable(&listOfVariables, $1);
        check_variable_is_const(listOfVariables, $1);

        if (type_of_variable(listOfVariables, $1) != type_of_class_variable(listOfClasses, $6, $8))
        {
            different_types();
        }
      }
      | ID '.' ID '[' INTEGER_NUMBER ']' '=' ID '.' ID 
      {
        check_array_length($5);
        class_variable_previously_defined($1, $3);
        class_variable_previously_defined($8, $10);
        check_class_variable_is_init(listOfClasses, $8, $10);
        set_init_class_variable(&listOfClasses, $1, $3);
        check_class_variable_is_const(listOfClasses, $1, $3);

        if (type_of_class_variable(listOfClasses, $1, $3) != type_of_class_variable(listOfClasses, $8, $10))
        {
            different_types();
        }
      }
      | ID '[' INTEGER_NUMBER ']' '=' ID '[' INTEGER_NUMBER ']' 
      {
        check_array_length($3);
        check_array_length($8);
        variable_previously_defined($1);
        variable_previously_defined($6);
        check_variable_is_init(listOfVariables, $6);
        set_init_variable(&listOfVariables, $1);
        check_variable_is_const(listOfVariables, $1);

        if (type_of_variable(listOfVariables, $1) != type_of_variable(listOfVariables, $6))
        {
            different_types();
        }
      }
      | ID '[' INTEGER_NUMBER ']' '=' ID '.' ID '[' INTEGER_NUMBER ']' 
      {
        check_array_length($3); 
        check_array_length($10); 
        variable_previously_defined($1);
        class_variable_previously_defined($6, $8);
        check_class_variable_is_init(listOfClasses, $6, $8);
        set_init_variable(&listOfVariables, $1);
        check_variable_is_const(listOfVariables, $1);

        if (type_of_variable(listOfVariables, $1) != type_of_class_variable(listOfClasses, $6, $8))
        {
            different_types();
        }
      }
      | ID '.' ID '[' INTEGER_NUMBER ']' '=' ID '[' INTEGER_NUMBER ']' 
      {
        check_array_length($5);
        check_array_length($10);
        variable_previously_defined($8);
        class_variable_previously_defined($1, $3);
        check_variable_is_init(listOfVariables, $8);
        set_init_class_variable(&listOfClasses, $1, $3);
        check_class_variable_is_const(listOfClasses, $1, $3);

        if (type_of_class_variable(listOfClasses, $1, $3) != type_of_variable(listOfVariables, $8))
        {
            different_types();
        }
      }
      | ID '.' ID '[' INTEGER_NUMBER ']' '=' ID '.' ID '[' INTEGER_NUMBER ']' 
      {
        check_array_length($5);
        check_array_length($12);
        class_variable_previously_defined($1, $3);
        class_variable_previously_defined($8, $10);
        check_class_variable_is_init(listOfClasses, $8, $10);
        set_init_class_variable(&listOfClasses, $1, $3);
        check_class_variable_is_const(listOfClasses, $1, $3);

        if (type_of_class_variable(listOfClasses, $1, $3) != type_of_class_variable(listOfClasses, $8, $10))
        {
            different_types();
        }
      }
      ;

call: ID '=' CALL ID {init_variables(&fun.paramTable);} '(' call_param ')'
    {
        variable_previously_defined($1);
        function_previously_defined($4);
        check_variable_is_const(listOfVariables, $1);
        set_init_variable(&listOfVariables, $1);

        if (type_of_variable(listOfVariables, $1) != type_of_return_function(listOfFunctions, $4))
        {
            different_types();
        }
        returnType = type_of_return_function(listOfFunctions, $4);
        strcpy(fun.name, $4);
        check_function_signature(listOfFunctions, fun);
    }
    | ID '.' ID '=' CALL ID {init_variables(&fun.paramTable);} '(' call_param ')' 
    {
        class_variable_previously_defined($1, $3);
        function_previously_defined($6);
        check_class_variable_is_const(listOfClasses, $1, $3);
        set_init_class_variable(&listOfClasses, $1, $3);

        if(type_of_class_variable(listOfClasses, $1, $3) != type_of_return_function(listOfFunctions, $6))
        {
            different_types();
        }
        returnType = type_of_return_function(listOfFunctions, $6);
        strcpy(fun.name, $6);
        check_function_signature(listOfFunctions, fun);
    }
    | ID '=' CALL ID '.' ID {init_variables(&fun.paramTable);} '(' call_param ')' 
    {
        variable_previously_defined($1);
        method_previously_defined($4, $6);
        check_variable_is_const(listOfVariables, $1);
        set_init_variable(&listOfVariables, $1);

        if(type_of_variable(listOfVariables, $1) != type_of_return_method(listOfClasses, $4, $6))
        {
            different_types();
        }
        returnType = type_of_return_method(listOfClasses, $4, $6);
        strcpy(fun.name, $6);
        check_method_signature(listOfClasses, $4, fun);
    }
    | ID '.' ID '=' CALL ID '.' ID {init_variables(&fun.paramTable);} '(' call_param ')'
    {
        class_variable_previously_defined($1, $3);
        method_previously_defined($6, $8);
        check_class_variable_is_const(listOfClasses, $1, $3);
        set_init_class_variable(&listOfClasses, $1, $3);

        if(type_of_class_variable(listOfClasses, $1, $3) != type_of_return_method(listOfClasses, $6, $8))
        {
            different_types();
        }
        returnType = type_of_return_method(listOfClasses, $6, $8);
        strcpy(fun.name, $8);
        check_method_signature(listOfClasses, $6, fun);
    }
    ;

call_param: 
          | list_call_param
          ;

list_call_param: param {insert_variable(&fun.paramTable, v);}
               | param {insert_variable(&fun.paramTable, v);} ',' list_call_param
               ;

param: value 
     {
        v.t.mainType = valueType;
        v.t.isArray = 0;
     }
     | ID 
     {
        variable_previously_defined($1);
        check_variable_is_init(listOfVariables, $1);
        v.t.mainType = type_of_variable(listOfVariables, $1);
        v.t.isArray = variable_is_array(listOfVariables, $1);
     }
     | ID '.' ID 
     {
        class_variable_previously_defined($1, $3);
        check_class_variable_is_init(listOfClasses, $1, $3);
        v.t.mainType = type_of_class_variable(listOfClasses, $1, $3);
        v.t.isArray = class_variable_is_array(listOfClasses, $1, $3);
     }
     ;

arithmetic_expression: operand operator operand
                     | operand operator arithmetic_expression
                     ;

operand: value
       {
            if (arithmeticExprType != -1)
            {
                if (arithmeticExprType == -2)
                {
                    arithmeticExprType = valueType;
                }

                if (arithmeticExprType != valueType)
                {
                    arithmeticExprType = -1;
                }
            }
       }
       | ID 
       {
            variable_previously_defined($1);
            check_variable_is_init(listOfVariables, $1);

            if (arithmeticExprType != -1)
            { 
                if (arithmeticExprType == -2)
                {
                    arithmeticExprType = type_of_variable(listOfVariables, $1);
                }

                if (arithmeticExprType != type_of_variable(listOfVariables, $1))
                {
                    arithmeticExprType = -1;
                }
            }
       }
       | ID '.' ID 
       {
            class_variable_previously_defined($1, $3);
            check_class_variable_is_init(listOfClasses, $1, $3);

            if (arithmeticExprType != -1)
            {
                if (arithmeticExprType == -2)
                {
                    arithmeticExprType = type_of_class_variable(listOfClasses, $1, $3);
                }

                if (arithmeticExprType != type_of_class_variable(listOfClasses, $1, $3))
                {
                    arithmeticExprType = -1;
                }
            }
       }
       | '(' call ')'
       {
            if (arithmeticExprType != -1)
            {
                if (arithmeticExprType == -2)
                {
                    arithmeticExprType = returnType;
                }

                if (arithmeticExprType != returnType)
                {
                    arithmeticExprType = -1;
                }
            }
       }
       ;

operator : '+'
         | '-'
         | '*'
         | '/'
         ;

if_statement: IF condition THEN {strcat(v.scope, "if#\0");} '{' code_block '}' {update_scope();} else_statement
            ;

else_statement: ELSE {strcat(v.scope, "else#\0");} '{' code_block '}' {update_scope();}
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
         | ID {variable_previously_defined($1); check_variable_is_init(listOfVariables, $1);}
         | ID '.' ID {class_variable_previously_defined($1, $3); check_class_variable_is_init(listOfClasses, $1, $3);}
         | arithmetic_expression {arithmeticExprType = -2;}
         ;

code_block:
          | statement code_block
          | variable_decl ';' code_block
          ;

while_statement: WHILE condition DO {strcat(v.scope, "while#\0");} '{' code_block '}' {update_scope();}
               ;

for_statement: {strcat(v.scope, "for#\0");} FOR '(' for_initialization ';' condition ';' assign ')' '{' code_block '}' {update_scope();}
             ;

for_initialization: assign
                  | variable_decl
                  ;

eval_statement: EVAL '(' eval_expression ')'
              ;

eval_expression: eval_result 
               {
                expr.line = yylineno;
                expr.result = $$->intvalue;
                insert_eval(&listOfEval, expr); 
                free_expr($$);
               }
               ;

eval_result: eval_result '+' eval_result
            { 
                $$ = create_int_expr($1->intvalue + $3->intvalue);
                free_expr($1); 
                free_expr($3);
            }
           | eval_result '-' eval_result
            { 
                $$ = create_int_expr($1->intvalue - $3->intvalue);
                free_expr($1); 
                free_expr($3);
            }
           | eval_result '*' eval_result
            { 
                $$ = create_int_expr($1->intvalue * $3->intvalue);
                free_expr($1);
                free_expr($3);
            }
           | eval_result '/' eval_result
            { 
                $$ = create_int_expr($1->intvalue / $3->intvalue);
                free_expr($1);
                free_expr($3);
            }
           | INTEGER_NUMBER {$$ = create_int_expr($1);}

string_statement: ID '=' string_function 
                {
                    variable_previously_defined($1);
                    set_init_variable(&listOfVariables, $1);
                    check_variable_is_const(listOfVariables, $1);

                    if (type_of_variable(listOfVariables, $1) != 3)
                    {
                        different_types();
                    }
                }
                | ID '=' LENGTH '(' string_content')'
                {
                    variable_previously_defined($1);
                    set_init_variable(&listOfVariables, $1);
                    check_variable_is_const(listOfVariables, $1);

                    if (type_of_variable(listOfVariables, $1) != 0)
                    {
                        different_types();
                    }
                }
                | ID '=' COMPARE '(' strings_content ')'
                {
                    variable_previously_defined($1);
                    set_init_variable(&listOfVariables, $1);
                    check_variable_is_const(listOfVariables, $1);

                    if (type_of_variable(listOfVariables, $1) != 0)
                    {
                        different_types();
                    }
                }
                | ID '.' ID '=' string_function
                {
                    class_variable_previously_defined($1, $3);
                    set_init_class_variable(&listOfClasses, $1, $3);
                    check_class_variable_is_const(listOfClasses, $1, $3);

                    if (type_of_class_variable(listOfClasses, $1, $3) != 3)
                    {
                        different_types();
                    }
                }
                | ID '.' ID '=' LENGTH '(' string_content')'
                {
                    class_variable_previously_defined($1, $3);
                    set_init_class_variable(&listOfClasses, $1, $3);
                    check_class_variable_is_const(listOfClasses, $1, $3);

                    if (type_of_class_variable(listOfClasses, $1, $3) != 0)
                    {
                        different_types();
                    }
                }
                | ID '.' ID '=' COMPARE '(' strings_content ')'
                {
                    class_variable_previously_defined($1, $3);
                    set_init_class_variable(&listOfClasses, $1, $3);
                    check_class_variable_is_const(listOfClasses, $1, $3);

                    if (type_of_class_variable(listOfClasses, $1, $3) != 0)
                    {
                        different_types();
                    }
                }
                ;

string_function: CONCAT '(' strings_content ')'
               | LOWER '(' string_content ')'
               | UPPER '(' string_content ')'
               ;

strings_content: string_content ',' string_content 
               ;

string_content: ID 
              {
                variable_previously_defined($1);
                check_variable_is_init(listOfVariables, $1);

                if (type_of_variable(listOfVariables, $1) != 3)
                {
                    different_types();
                }
              }
              | ID '.' ID 
              {
                class_variable_previously_defined($1, $3);
                check_class_variable_is_init(listOfClasses, $1, $3);

                if (type_of_class_variable(listOfClasses, $1, $3) != 3)
                {
                    different_types();
                }
              }
              | STRING_VALUE
              ;

%%

expr_info* create_int_expr(int value)
{
   expr_info* expr = (expr_info*)malloc(sizeof(expr_info));
   expr->intvalue = value;
   expr->type = 1;
   return expr;
}

expr_info* create_str_expr(char* value1, char* value2) 
{
    expr_info* expr = (expr_info*)malloc(sizeof(expr_info));
    int len2 = value2 ? strlen(value2) : 0;
    expr->strvalue = (char*) malloc(sizeof(char)*(strlen(value1) + len2 + 1)); 
    strcpy(expr->strvalue, value1);
    if(value2)
    {
        strcat(expr->strvalue, value2);
    }
    expr->type = 2;
    return expr;
}

void free_expr(expr_info* expr)
{
    if(expr->type == 2)
    {
        free(expr->strvalue);
    }
    free(expr);
}


void print_expr(expr_info* expr)
{
    if(expr->type == 1) 
    {
        printf("Eval expr(line: %d) with value:%d\n", yylineno, expr->intvalue);
    }
    else
    {
        printf("Str expr with value:%s\n", expr->strvalue); 
    } 
}

void update_scope()
{
    int len = strlen(v.scope);
    v.scope[len - 1] = 0;
    len = len - 2;
    while (v.scope[len] != '#')
    {
        v.scope[len] = 0;
        --len;
    }
}

void check_array_length(int len)
{
    if (len <= 0)
    {
        printf("Invalid array length(line: %d)\n", yylineno);
        noSemanticErrors = 0;
    }
}

void variable_was_declared(char* id)
{
    for (int i = 0; i < listOfVariables.varNumber; ++i)
    {
        if (strcmp(listOfVariables.varTable[i].name, id) == 0)
        {
            printf("Variable %s (line: %d) was already declared (line %d)\n", id, yylineno, listOfVariables.varTable[i].line);
            noSemanticErrors = 0;
        }
    }
}

void class_variable_was_declared(VariableTable arr, char* id)
{
    for (int i = 0; i < arr.varNumber; ++i)
    {
        if (strcmp(arr.varTable[i].name, id) == 0)
        {
            printf("Variable %s (line: %d) from class %s was already declared (line %d)\n", id, yylineno, cl.name, arr.varTable[i].line);
            noSemanticErrors = 0;
        }
    }
}

int variable_is_init(VariableTable arr, char* id)
{
    for (int i = 0; i < arr.varNumber; ++i)
    {
        if (strcmp(arr.varTable[i].name, id) == 0)
        {
            return arr.varTable[i].t.isInit;
        }
    }
}

int class_variable_is_init(ClassTable arr, char* className, char* id)
{
    for (int i = 0; i < arr.classNumber; ++i)
    {
        if (strcmp(arr.classTable[i].name, className) == 0)
        {
            for (int j = 0; j < arr.classTable[i].attribTable.varNumber; ++j)
            {
                if (strcmp(arr.classTable[i].attribTable.varTable[j].name, id) == 0)
                {
                    return arr.classTable[i].attribTable.varTable[j].t.isInit;
                }
            }
        }
    }
}

void set_init_variable(VariableTable* arr, char* id)
{
    for (int i = 0; i < arr->varNumber; ++i)
    {
        if (strcmp(arr->varTable[i].name, id) == 0)
        {
            arr->varTable[i].t.isInit = 1;
        }
    }
}

void set_init_class_variable(ClassTable* arr, char* className, char* id)
{
    for (int i = 0; i < arr->classNumber; ++i)
    {
        if (strcmp(arr->classTable[i].name, className) == 0)
        {
            for (int j = 0; j < arr->classTable[i].attribTable.varNumber; ++j)
            {
                if (strcmp(arr->classTable[i].attribTable.varTable[j].name, id) == 0)
                {
                    arr->classTable[i].attribTable.varTable[j].t.isInit = 1;
                }
            }
        }
    }
}

void check_variable_is_init(VariableTable arr, char* id)
{
    if (variable_is_init(arr, id) == 0)
    {
        printf("A variable (%s) appearing in the right side of an expression should have been initialized explicitly (line: %d)\n", id, yylineno);
        noSemanticErrors = 0;
    }
}

void check_class_variable_is_init(ClassTable arr, char* className, char* id)
{
    if (class_variable_is_init(arr, className, id) == 0)
    {
        printf("A variable (%s.%s) appearing in the right side of an expression should have been initialized explicitly (line: %d)\n", className, id, yylineno);
        noSemanticErrors = 0;
    }
}

void variable_previously_defined(char* id)
{
    for (int i = 0; i < listOfVariables.varNumber; ++i)
    {
        if (strcmp(listOfVariables.varTable[i].name, id) == 0)
        {
            return;
        }
    }
    printf("Variable %s (line: %d) has not been previously defined\n", id, yylineno);
    noSemanticErrors = 0;
}

void class_variable_previously_defined(char* className, char* id)
{
    for (int i = 0; i < listOfClasses.classNumber; ++i)
    {
        if (strcmp(listOfClasses.classTable[i].name, className) == 0)
        {
            for (int j = 0; j < listOfClasses.classTable[i].attribTable.varNumber; ++j)
            {
                if (strcmp(listOfClasses.classTable[i].attribTable.varTable[j].name, id) == 0)
                {
                    return;
                }
            }
            printf("Variable %s (line: %d) from class %s has not been previously defined\n", id, yylineno, className);
            noSemanticErrors = 0;
            return;
        }
    }
    printf("Class %s (line: %d) has not been previously defined\n", className, yylineno);
    noSemanticErrors = 0;
}

int compare_params(struct Variable v1, struct Variable v2)
{
    if (v1.t.mainType != v2.t.mainType)
    {
        return 0;
    }
    if (v1.t.isArray != v2.t.isArray)
    {
        return 0;
    }
    return 1;
}

void different_types()
{
    printf("The left side of an assignment must have the same type as the right side (line: %d)\n", yylineno);
    noSemanticErrors = 0;
}

void function_was_declared(FunctionTable arr, struct Function fun)
{
    for (int i = 0; i < arr.funcNumber; ++i)
    {
        if (strcmp(fun.name, arr.funcTable[i].name) == 0)
        {
            if (fun.returnType == arr.funcTable[i].returnType)
            {
                if (fun.paramTable.varNumber == arr.funcTable[i].paramTable.varNumber)
                {
                    for (int j = 0; j < fun.paramTable.varNumber; ++j)
                    {
                        if (compare_params(fun.paramTable.varTable[j], arr.funcTable[i].paramTable.varTable[j]) == 0)
                        {
                            return;
                        }
                    }
                    noSemanticErrors = 0;
                    printf("Function %s (line: %d) was already declared (line: %d)\n", fun.name, yylineno, arr.funcTable[i].line);
                }
                else
                {
                    return;
                }
            }
            else
            {
                return;
            }
        }
    }
}


void method_was_declared(FunctionTable arr, struct Function fun)
{
    for (int i = 0; i < arr.funcNumber; ++i)
    {
        if (strcmp(fun.name, arr.funcTable[i].name) == 0)
        {
            if (fun.returnType == arr.funcTable[i].returnType)
            {
                if (fun.paramTable.varNumber == arr.funcTable[i].paramTable.varNumber)
                {
                    for (int j = 0; j < fun.paramTable.varNumber; ++j)
                    {
                        if (compare_params(fun.paramTable.varTable[j], arr.funcTable[i].paramTable.varTable[j]) == 0)
                        {
                            return;
                        }
                    }
                    noSemanticErrors = 0;
                    printf("Method %s (line: %d) from class %s was already declared (line: %d)\n", fun.name, yylineno, cl.name, arr.funcTable[i].line);
                }
                else
                {
                    return;
                }
            }
            else
            {
                return;
            }
        }
    }
}

void function_previously_defined(char* id)
{
    for (int i = 0; i < listOfFunctions.funcNumber; ++i)
    {
        if (strcmp(listOfFunctions.funcTable[i].name, id) == 0)
        {
            return;
        }
    }
    printf("Function %s (line: %d) has not been previously defined\n", id, yylineno);
    noSemanticErrors = 0;
}

void method_previously_defined(char* className, char* id)
{
    for (int i = 0; i < listOfClasses.classNumber; ++i)
    {
        if (strcmp(listOfClasses.classTable[i].name, className) == 0)
        {
            for (int j = 0; j < listOfClasses.classTable[i].methTable.funcNumber; ++j)
            {
                if (strcmp(listOfClasses.classTable[i].methTable.funcTable[j].name, id) == 0)
                {
                    return;
                }
            }
            printf("Method %s (line: %d) from class %s has not been previously defined\n", id, yylineno, className);
            noSemanticErrors = 0;
        }
        return;
    }
    printf("Class %s (line: %d) has not been previously defined\n", className, yylineno);
    noSemanticErrors = 0;
}

int type_of_variable(VariableTable arr, char* id)
{
    for (int i = 0; i < arr.varNumber; ++i)
    {
        if (strcmp(arr.varTable[i].name, id) == 0)
        {
            return (arr.varTable[i].t.mainType);
        }
    }
}

int type_of_class_variable(ClassTable arr, char* className, char* id)
{
    for (int i = 0; i < arr.classNumber; ++i)
    {
        if (strcmp(arr.classTable[i].name, className) == 0)
        {
            for (int j = 0; j < arr.classTable[i].attribTable.varNumber; ++j)
            {
                if (strcmp(arr.classTable[i].attribTable.varTable[j].name, id) == 0)
                {
                    return (arr.classTable[i].attribTable.varTable[j].t.mainType);
                }
            }
        }
    }
}

int type_of_return_function(FunctionTable arr, char* id)
{
    for (int i = 0; i < arr.funcNumber; ++i)
    {
        if (strcmp(arr.funcTable[i].name, id) == 0)
        {
            return arr.funcTable[i].returnType;
        }
    }
}

int type_of_return_method(ClassTable arr, char* className, char* id)
{
    for (int i = 0; i < arr.classNumber; ++i)
    {
        if (strcmp(arr.classTable[i].name, className) == 0)
        {
            for (int j = 0; j < arr.classTable[i].methTable.funcNumber; ++j)
            {
                if (strcmp(arr.classTable[i].methTable.funcTable[j].name, id) == 0)
                {
                    return arr.classTable[i].methTable.funcTable[j].returnType;
                }
            }
        }
    }
}

int variable_is_array(VariableTable arr, char* id)
{
    for (int i = 0; i < arr.varNumber; ++i)
    {
        if (strcmp(arr.varTable[i].name, id) == 0)
        {
            return (arr.varTable[i].t.isArray);
        }
    }
}

int class_variable_is_array(ClassTable arr, char* className, char* id)
{
    for (int i = 0; i < arr.classNumber; ++i)
    {
        if (strcmp(arr.classTable[i].name, className) == 0)
        {
            for (int j = 0; j < arr.classTable[i].attribTable.varNumber; ++j)
            {
                if (strcmp(arr.classTable[i].attribTable.varTable[j].name, id) == 0)
                {
                    return (arr.classTable[i].attribTable.varTable[j].t.isArray);
                }
            }
        }
    }
}

void check_function_signature(FunctionTable arr, struct Function fun)
{
    for (int i = 0; i < arr.funcNumber; ++i)
    {
        if (strcmp(arr.funcTable[i].name, fun.name) == 0)
        {
            if (fun.paramTable.varNumber == arr.funcTable[i].paramTable.varNumber)
            {
                for (int j = 0; j < fun.paramTable.varNumber; ++j)
                {
                    if (compare_params(fun.paramTable.varTable[j], arr.funcTable[i].paramTable.varTable[j]) == 0)
                    {
                        printf("Wrong type of argument no. %d for function %s (line: %d)\n", (j + 1), fun.name, yylineno);
                        noSemanticErrors = 0;
                        return;
                    }
                }
                return;
            }
            else
            {   
                printf("Wrong number of arguments for function %s (line: %d)\n", fun.name, yylineno);
                noSemanticErrors = 0;
                return;
            }
        }
    }
}

void check_method_signature(ClassTable arr, char* className, struct Function fun)
{
    for (int i = 0; i < arr.classNumber; ++i)
    {
        if (strcmp(arr.classTable[i].name, className) == 0)
        {
            for (int j = 0; j < arr.classTable[i].methTable.funcNumber; ++j)
            {
                if (strcmp(arr.classTable[i].methTable.funcTable[j].name, fun.name) == 0)
                {
                    if (fun.paramTable.varNumber == arr.classTable[i].methTable.funcTable[j].paramTable.varNumber)
                    {
                        for (int k = 0; j < fun.paramTable.varNumber; ++j)
                        {
                            if (compare_params(fun.paramTable.varTable[k], arr.classTable[i].methTable.funcTable[j].paramTable.varTable[k]) == 0)
                            {
                                printf("Wrong type of argument no. %d for method %s.%s (line: %d)\n", (k + 1), className, fun.name, yylineno);
                                noSemanticErrors = 0;
                                return;
                            }
                        }
                        return;
                    }
                    else
                    {   
                        printf("Wrong number of arguments for method %s.%s (line: %d)\n", className, fun.name, yylineno);
                        noSemanticErrors = 0;
                        return;
                    }
                }
            }
        }
    }
}

int variable_is_const(VariableTable arr, char* id)
{
    for (int i = 0; i < arr.varNumber; ++i)
    {
        if (strcmp(arr.varTable[i].name, id) == 0)
        {
            return (arr.varTable[i].t.isConst);
        }
    }
}

int class_variable_is_const(ClassTable arr, char* className, char* id)
{
    for (int i = 0; i < arr.classNumber; ++i)
    {
        if (strcmp(arr.classTable[i].name, className) == 0)
        {
            for (int j = 0; j < arr.classTable[i].attribTable.varNumber; ++j)
            {
                if (strcmp(arr.classTable[i].attribTable.varTable[j].name, id) == 0)
                {
                    return (arr.classTable[i].attribTable.varTable[j].t.isConst);
                }
            }
        }
    }
}

void check_variable_is_const(VariableTable arr, char* id)
{
    if (variable_is_const(arr, id) == 1)
    {
        printf("Const variable %s cannot be reassigned (line: %d)\n", id, yylineno);
        noSemanticErrors = 0;
    }
}

void check_class_variable_is_const(ClassTable arr, char* className, char* id)
{
    if (class_variable_is_const(arr, className, id) == 1)
    {
        printf("Const variable %s.%s cannot be reassigned (line: %d)\n", className, id, yylineno);
        noSemanticErrors = 0;
    }
}

int yyerror(char *s)
{
    printf("Error(line %d): %s\n", yylineno, s);
}

int main(int argc, char** argv)
{
    yyin = fopen(argv[1], "r");

    init_variables(&listOfVariables);
    init_functions(&listOfFunctions);
    init_classes(&listOfClasses);
    init_eval(&listOfEval);

    yyparse();

    if (noSyntacticErrors + noSemanticErrors == 2)
    {
        printf("No semantic errors\n");

        for (int i = 0; i < listOfEval.evalNumber; ++i)
        {
            printf("Eval expr(line: %d) with value: %d\n", listOfEval.evalExpressions[i].line, listOfEval.evalExpressions[i].result);
        }
    }

    FILE* f = fopen("symbol_table.txt", "w");
    fclose(f);
    f = fopen("symbol_table.txt", "a");

    if (listOfVariables.varNumber > 0)
    {
        fprintf(f, "Variables:\n");
        for (int i = 0; i < listOfVariables.varNumber; ++i)
        {
            fprintf(f, "%d) name: %s ", (i + 1), listOfVariables.varTable[i].name);
            fprintf(f, "|| scope: ");
            if (strcmp(listOfVariables.varTable[i].scope, "#") == 0)
            {
                fprintf(f, "global ");
            }
            else
            {
                fprintf(f, "%s ", listOfVariables.varTable[i].scope);
            }
            fprintf(f, "|| type: ");
            switch (listOfVariables.varTable[i].t.mainType)
            {
                case 0:
                    fprintf(f, "integer");
                    break;
                case 1:
                    fprintf(f, "float");
                    break;
                case 2:
                    fprintf(f, "char");
                    break;
                case 3:
                    fprintf(f, "string");
                    break;
                case 4:
                    fprintf(f, "bool");
            }

            if (listOfVariables.varTable[i].t.isConst == 1)
            {
                fprintf(f, " || const");
            }

            if (listOfVariables.varTable[i].t.isInit == 1)
            {
                fprintf(f, " || init");
            }

            if (listOfVariables.varTable[i].t.isArray == 1)
            {
                fprintf(f, " || array of length: ");
                char str[10];
                sprintf(str, "%d", listOfVariables.varTable[i].t.lengthOfArray);
                fprintf(f, "%s", str);
            }
            fprintf(f, " || line: %d\n", listOfVariables.varTable[i].line);
        }
        fprintf(f, "\n\n---------------------\n\n\n");
    }

    if (listOfFunctions.funcNumber > 0)
    {
        fprintf(f, "Functions:\n");
        for (int i = 0; i < listOfFunctions.funcNumber; ++i)
        {
            fprintf(f, "%d) name: %s ", (i + 1), listOfFunctions.funcTable[i].name);
            fprintf(f, "|| return type: ");
            switch (listOfFunctions.funcTable[i].returnType)
            {
                case 0:
                    fprintf(f, "integer");
                    break;
                case 1:
                    fprintf(f, "float");
                    break;
                case 2:
                    fprintf(f, "char");
                    break;
                case 3:
                    fprintf(f, "string");
                    break;
                case 4:
                    fprintf(f, "bool");
            }
            fprintf(f, " || line: %d", listOfFunctions.funcTable[i].line);
            fprintf(f, " || parameters: ");

            if (listOfFunctions.funcTable[i].paramTable.varNumber > 0)
            {
                fprintf(f, "\n");
                for (int j = 0; j < listOfFunctions.funcTable[i].paramTable.varNumber; ++j)
                {
                    fprintf(f, ">>> %d.%d) name: %s ", (i + 1), (j + 1), listOfFunctions.funcTable[i].paramTable.varTable[j].name);
                    fprintf(f, "|| type: ");
                    switch (listOfFunctions.funcTable[i].paramTable.varTable[j].t.mainType)
                    {
                        case 0:
                            fprintf(f, "integer");
                            break;
                        case 1:
                            fprintf(f, "float");
                            break;
                        case 2:
                            fprintf(f, "char");
                            break;
                        case 3:
                            fprintf(f, "string");
                            break;
                        case 4:
                            fprintf(f, "bool");
                            break;
                        case 5:
                            fprintf(f, "object");
                    }

                    if (listOfFunctions.funcTable[i].paramTable.varTable[j].t.isConst == 1)
                    {
                        fprintf(f, " || const");
                    }

                    if (listOfFunctions.funcTable[i].paramTable.varTable[j].t.isArray == 1)
                    {
                        fprintf(f, " || array of length: ");
                        char str[10];
                        sprintf(str, "%d", listOfFunctions.funcTable[i].paramTable.varTable[j].t.lengthOfArray);
                        fprintf(f, "%s", str);
                    }
                    fprintf(f, "\n");
                }
            }
            else
            {
                fprintf(f, "no\n");
            }
            fprintf(f, "\n");
        }
        fprintf(f, "\n\n---------------------\n\n\n");
    }

    if (listOfClasses.classNumber > 0)
    {
        fprintf(f, "Classes: \n");
        for (int i = 0; i < listOfClasses.classNumber; ++i)
        {
            fprintf(f, "%d) name: %s", (i + 1), listOfClasses.classTable[i].name);
            fprintf(f, " || line: %d\n", listOfClasses.classTable[i].line);
            fprintf(f, "***variables: ");
            if (listOfClasses.classTable[i].attribTable.varNumber > 0)
            {
                fprintf(f, "\n");
                for (int j = 0; j < listOfClasses.classTable[i].attribTable.varNumber; ++j)
                {
                    fprintf(f, ">>>>>> %d.%d) name: %s ", (i + 1), (j + 1), listOfClasses.classTable[i].attribTable.varTable[j].name);
                    fprintf(f, "|| type: ");
                    switch (listOfClasses.classTable[i].attribTable.varTable[j].t.mainType)
                    {
                        case 0:
                            fprintf(f, "integer");
                            break;
                        case 1:
                            fprintf(f, "float");
                            break;
                        case 2:
                            fprintf(f, "char");
                            break;
                        case 3:
                            fprintf(f, "string");
                            break;
                        case 4:
                            fprintf(f, "bool");
                            break;
                    }

                    if (listOfClasses.classTable[i].attribTable.varTable[j].t.isConst == 1)
                    {
                        fprintf(f, " || const");
                    }

                    if (listOfClasses.classTable[i].attribTable.varTable[j].t.isInit == 1)
                    {
                        fprintf(f, " || init");
                    }

                    if (listOfClasses.classTable[i].attribTable.varTable[j].t.isArray == 1)
                    {
                        fprintf(f, " || array of length: ");
                        char str[10];
                        sprintf(str, "%d", listOfClasses.classTable[i].attribTable.varTable[j].t.lengthOfArray);
                        fprintf(f, "%s", str);
                    }
                    fprintf(f, " || line: %d\n", listOfClasses.classTable[i].attribTable.varTable[j].line);
                }
            }
            else
            {
                fprintf(f, "no\n");
            }

            fprintf(f, "***methods: ");
            if (listOfClasses.classTable[i].methTable.funcNumber > 0)
            {
                fprintf(f, "\n");
                for (int j = 0; j < listOfClasses.classTable[i].methTable.funcNumber; ++j)
                {
                    fprintf(f, ">>>>>> %d.%d) name: %s ", (i + 1), (j + 1), listOfClasses.classTable[i].methTable.funcTable[j].name);
                    fprintf(f, "|| return type: ");
                    switch (listOfClasses.classTable[i].methTable.funcTable[j].returnType)
                    {
                        case 0:
                            fprintf(f, "integer");
                            break;
                        case 1:
                            fprintf(f, "float");
                            break;
                        case 2:
                            fprintf(f, "char");
                            break;
                        case 3:
                            fprintf(f, "string");
                            break;
                        case 4:
                            fprintf(f, "bool");
                    }
                    fprintf(f, " || line: %d", listOfClasses.classTable[i].methTable.funcTable[j].line);
                    fprintf(f, " || parameters: ");
                    if (listOfClasses.classTable[i].methTable.funcTable[j].paramTable.varNumber > 0)
                    {
                        fprintf(f, "\n");
                        for (int k = 0; k < listOfClasses.classTable[i].methTable.funcTable[j].paramTable.varNumber; ++k)
                        {
                            fprintf(f, ">>>>>>>>> %d.%d.%d) name: %s ", (i + 1), (j + 1), (k + 1), listOfClasses.classTable[i].methTable.funcTable[j].paramTable.varTable[k].name);
                            fprintf(f, "|| type: ");
                            switch (listOfClasses.classTable[i].methTable.funcTable[j].paramTable.varTable[k].t.mainType)
                            {
                                case 0:
                                    fprintf(f, "integer");
                                    break;
                                case 1:
                                    fprintf(f, "float");
                                    break;
                                case 2:
                                    fprintf(f, "char");
                                    break;
                                case 3:
                                    fprintf(f, "string");
                                    break;
                                case 4:
                                    fprintf(f, "bool");
                                    break;
                            }

                            if (listOfClasses.classTable[i].methTable.funcTable[j].paramTable.varTable[k].t.isConst == 1)
                            {
                                fprintf(f, " || const ");
                            }

                            if (listOfClasses.classTable[i].methTable.funcTable[j].paramTable.varTable[k].t.isArray == 1)
                            {
                                fprintf(f, " || array of length: ");
                                char str[10];
                                sprintf(str, "%d", listOfClasses.classTable[i].methTable.funcTable[j].paramTable.varTable[k].t.lengthOfArray);
                                fprintf(f, "%s", str);
                            }
                            fprintf(f, "\n");
                        }
                    }
                    else
                    {
                        fprintf(f, "no\n");
                    }
                }
            }
            else
            {
                fprintf(f, "no\n");
            }
            fprintf(f, "\n");
        }
        fprintf(f, "\n\n---------------------\n\n\n");
    }

    fclose(f);

    free_variables(&listOfVariables);
    free_functions(&listOfFunctions);
    free_classes(&listOfClasses);
    free_eval(&listOfEval);
}