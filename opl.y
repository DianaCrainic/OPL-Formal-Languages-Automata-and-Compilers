%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opl.h"

extern int yylex();
extern int yyerror(char * syntaxError);

VariableTable listOfVariables;
FunctionTable listOfFunctions;
ClassTable listOfClasses;

struct Variable v;
struct Function fun;
struct Class cl;

int noErrors = 0;

expr_info* create_int_expr(int value);
expr_info* create_str_expr(char* value1, char* value2);
void free_expr(expr_info* expr);
void print_expr(expr_info* expr);

void init_variables(VariableTable* arr);
void init_functions(FunctionTable* arr);
void init_classes(ClassTable* arr);

void insert_variable(VariableTable* arr, struct Variable var);
void insert_function(FunctionTable* arr, struct Function fun);
void insert_class(ClassTable* arr, struct Class cl);

void free_variables(VariableTable* arr);
void free_functions(FunctionTable* arr);
void free_classes(ClassTable* arr);

void update_scope();
void check_array_length(int len);

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

s: progr {printf("Correct input, well done\n"); noErrors = 1;}
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
        v.line = yylineno;
        v.t.isArray = 0;
        strcpy(v.name, $1);
    }
   | ID '=' value 
    {
        v.line = yylineno;
        v.t.isArray = 0;
        strcpy(v.name, $1);
    }
   | ID '=' ID 
    {
        v.line = yylineno;
        v.t.isArray = 0;
        strcpy(v.name, $1);
    }
   | ID '[' INTEGER_NUMBER ']' 
    {
        v.line = yylineno;
        check_array_length($3);
        v.t.isArray = 1;
        v.t.lengthOfArray = $3;
        strcpy(v.name, $1);
    }
   | ID '[' INTEGER_NUMBER ']' '=' '{' '}' 
    {
        v.line = yylineno;
        check_array_length($3);
        v.t.isArray = 1;
        v.t.lengthOfArray = $3;
        strcpy(v.name, $1);
    }
   | ID '[' INTEGER_NUMBER ']' '=' '{' array '}' 
    {
        v.line = yylineno;
        check_array_length($3);
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

maintype: INT {v.t.mainType = 0; fun.returnType = 0;}
        | FLOAT {v.t.mainType = 1; fun.returnType = 1;}
        | CHAR {v.t.mainType = 2; fun.returnType = 2;}
        | STRING {v.t.mainType = 3; fun.returnType = 3;}
        | BOOL {v.t.mainType = 4; fun.returnType = 4;}
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

function_decl: FNC {strcat(v.scope, "function#\0"); init_variables(&fun.paramTable);}
               type ':' ID {fun.line = yylineno;} 
               '(' function_param ')'
               '{' code_block return_value ';' '}' 
                {
                    strcpy(fun.name, $5);
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
        | ID ID
        {
            v.t.isArray = 0;
            v.t.mainType = 5;
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
                v.line = yylineno;
                v.t.isArray = 0;
                strcpy(v.name, $1);
              }
              | ID '=' value 
              {
                v.line = yylineno;
                v.t.isArray = 0;
                strcpy(v.name, $1);
              }
              | ID '[' INTEGER_NUMBER ']' 
              {
                v.line = yylineno;
                check_array_length($3);
                v.t.isArray = 1;
                v.t.lengthOfArray = $3;
                strcpy(v.name, $1);
              }
              | ID '[' INTEGER_NUMBER ']' '=' '{' '}' 
              {
                v.line = yylineno;
                check_array_length($3);
                v.t.isArray = 1;
                v.t.lengthOfArray = $3;
                strcpy(v.name, $1);
              }
              | ID '[' INTEGER_NUMBER ']' '=' '{' array '}' 
              {
                v.line = yylineno;
                check_array_length($3);
                v.t.isArray = 1;
                v.t.lengthOfArray = $3;
                strcpy(v.name, $1);
              }
              ;

method_decl_in_class: type ID {fun.line = yylineno; strcpy(fun.name, $2); init_variables(&fun.paramTable);} 
                     '(' method_param ')' 
                     '{' code_block return_value ';' '}' 
                     {
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
            | RET ID
            ;

main: BEGIN_MAIN {strcat(v.scope, "main#\0");} main_content END_MAIN
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
      | ID '[' INTEGER_NUMBER ']' '=' value {check_array_length($3);}
      | ID '.' ID '[' INTEGER_NUMBER ']' '=' value {check_array_length($5);}
      | ID '[' INTEGER_NUMBER ']' '=' ID {check_array_length($3);}
      | ID '.' ID '[' INTEGER_NUMBER ']' '=' ID {check_array_length($5);}
      | ID '[' INTEGER_NUMBER ']' '=' ID '.' ID {check_array_length($3);}
      | ID '.' ID '[' INTEGER_NUMBER ']' '=' ID '.' ID {check_array_length($5);}
      | ID '[' INTEGER_NUMBER ']' '=' ID '[' INTEGER_NUMBER ']' {check_array_length($3); check_array_length($8);}
      | ID '[' INTEGER_NUMBER ']' '=' ID '.' ID '[' INTEGER_NUMBER ']' {check_array_length($3); check_array_length($10);}
      | ID '.' ID '[' INTEGER_NUMBER ']' '=' ID '[' INTEGER_NUMBER ']' {check_array_length($5); check_array_length($10);}
      | ID '.' ID '[' INTEGER_NUMBER ']' '=' ID '.' ID '[' INTEGER_NUMBER ']' {check_array_length($5); check_array_length($12);}
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
         | ID
         | ID '.' ID
         | arithmetic_expression
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

eval_expression: eval_result {print_expr($$); free_expr($$);}
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

// eval_expression: eval_operand operator eval_operand
//                | eval_operand operator eval_expression
//                ;

// eval_operand: ID
//             | ID '.' ID
//             | INTEGER_NUMBER
//             | '(' call ')'
//             | LENGTH '(' string_content')'
//             ;

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

void init_variables(VariableTable* arr)
{
    arr->varTable = (struct Variable *)malloc(MAX_VARIABLE_NUMBER * sizeof(struct Variable));
    arr->varNumber = 0;
    arr->size = MAX_VARIABLE_NUMBER;
}

void init_functions(FunctionTable* arr)
{
    arr->funcTable = (struct Function *)malloc(MAX_METHOD_NUMBER * sizeof(struct Function));
    arr->funcNumber = 0;
    arr->size = MAX_METHOD_NUMBER;
}

void init_classes(ClassTable* arr)
{
    arr->classTable = (struct Class *)malloc(MAX_CLASS_NUMBER * sizeof(struct Class));
    arr->classNumber = 0;
    arr->size = MAX_CLASS_NUMBER;
}

void insert_variable(VariableTable* arr, struct Variable var)
{
    if (arr->varNumber == arr->size)
    {
        printf("Too many variables\n");
        exit(2);
    }

    strcpy(arr->varTable[arr->varNumber].name, var.name);
    strcpy(arr->varTable[arr->varNumber].scope, var.scope);
    arr->varTable[arr->varNumber].line = var.line;
    arr->varTable[arr->varNumber].t.mainType = var.t.mainType;
    arr->varTable[arr->varNumber].t.isConst = var.t.isConst;
    arr->varTable[arr->varNumber].t.isArray = var.t.isArray;
    arr->varTable[arr->varNumber].t.lengthOfArray = var.t.lengthOfArray;
    ++arr->varNumber;
}

void insert_function(FunctionTable* arr, struct Function fun)
{
    if (arr->funcNumber == arr->size)
    {
        printf("Too many functions\n");
        exit(3);
    }

    arr->funcTable[arr->funcNumber].returnType = fun.returnType;
    arr->funcTable[arr->funcNumber].line = fun.line;
    strcpy(arr->funcTable[arr->funcNumber].name, fun.name);

    init_variables(&arr->funcTable[arr->funcNumber].paramTable);
    for (int i = 0; i < fun.paramTable.varNumber; ++i)
    {
        insert_variable(&arr->funcTable[arr->funcNumber].paramTable, fun.paramTable.varTable[i]);
    }

    ++arr->funcNumber;
}

void insert_class(ClassTable* arr, struct Class cl)
{
    if (arr->classNumber == arr->size)
    {
        printf("Too many classes\n");
        exit(3);
    }

    strcpy(arr->classTable[arr->classNumber].name, cl.name);
    arr->classTable[arr->classNumber].line = cl.line;

    init_variables(&arr->classTable[arr->classNumber].attribTable);
    for (int i = 0; i < cl.attribTable.varNumber; ++i)
    {
        insert_variable(&arr->classTable[arr->classNumber].attribTable, cl.attribTable.varTable[i]);
    }

    init_functions(&arr->classTable[arr->classNumber].methTable);
    for (int i = 0; i < cl.methTable.funcNumber; ++i)
    {
        insert_function(&arr->classTable[arr->classNumber].methTable, cl.methTable.funcTable[i]);
    }

    ++arr->classNumber;
}

void free_variables(VariableTable* arr)
{
    free(arr->varTable);
    arr->varNumber = 0;
    arr->size = 0;
}

void free_functions(FunctionTable* arr)
{
    free(arr->funcTable);
    arr->funcNumber = 0;
    arr->size = 0;
}

void free_classes(ClassTable* arr)
{
    free(arr->classTable);
    arr->classNumber = 0;
    arr->size = 0;
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
        exit(1);
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

    yyparse();

    if (noErrors == 1)
    {
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
            }
            fprintf(f, "\n\n---------------------\n\n\n");
        }

        fclose(f);
    }

    free_variables(&listOfVariables);
    free_functions(&listOfFunctions);
    free_classes(&listOfClasses);
}