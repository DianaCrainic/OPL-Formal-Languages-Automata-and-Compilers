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

void init_eval(ArrayEval* arr)
{
    arr->evalExpressions = (struct EvalExpr *)malloc(MAX_VARIABLE_NUMBER * sizeof(struct EvalExpr));
    arr->evalNumber = 0;
    arr->size = MAX_VARIABLE_NUMBER;
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
    arr->varTable[arr->varNumber].t.isInit = var.t.isInit;
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

void insert_eval(ArrayEval* arr, struct EvalExpr expr)
{
    if (arr->evalNumber == arr->size)
    {
        arr->size *= 2;
        arr->evalExpressions = (struct EvalExpr *)realloc(arr->evalExpressions, arr->size * sizeof(struct EvalExpr));
    }

    arr->evalExpressions[arr->evalNumber].result = expr.result;
    arr->evalExpressions[arr->evalNumber].line = expr.line;
    ++arr->evalNumber;
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

void free_eval(ArrayEval* arr)
{
    free(arr->evalExpressions);
    arr->evalNumber = 0;
    arr->size = 0;
}