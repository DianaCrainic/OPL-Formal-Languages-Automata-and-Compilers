// Maximum effective size of strings
#define MAX_STRING_LENGTH 255

// Maximum effective number of classes
#define MAX_CLASS_NUMBER 16

// Maximum effective number of attributes per class
#define MAX_ATTRIBUTE_NUMBER 16

// Maximum effective number of methods per class
#define MAX_METHOD_NUMBER 64

// Maximum effective number of parameters per method
#define MAX_PARAMETER_NUMBER 16

// Maximum effective number of variables
#define MAX_VARIABLE_NUMBER 64

extern FILE* yyin;
extern int yylineno;

typedef struct
{
    int mainType;
    // 0-int, 1-float, 2-char, 3-string, 4-bool, 5-object
    int isConst;
    int isArray;
    int lengthOfArray;
} Type;

struct Variable
{
    char name[MAX_STRING_LENGTH];
    char scope[MAX_STRING_LENGTH];
    Type t;
    int line;
};

typedef struct 
{
    struct Variable *varTable;
    int varNumber;
    int size;
} VariableTable;

struct Function
{
    VariableTable paramTable;
    char name[MAX_STRING_LENGTH];
    int returnType;
    int line;
};

typedef struct 
{
    struct Function *funcTable;
    int funcNumber;
    int size;
} FunctionTable;

struct Class
{
    VariableTable attribTable;
    FunctionTable methTable;
    char name[MAX_STRING_LENGTH];
    int line;
};

typedef struct 
{
    struct Class *classTable;
    int classNumber;
    int size;
} ClassTable;

struct EvalExpr
{
    int result;
    int line;
};

typedef struct
{
    struct EvalExpr *evalExpressions;
    int evalNumber;
    int size;
}ArrayEval;

typedef struct expr_info 
{
    int intvalue;
    char* strvalue;
    int type;
} expr_info;