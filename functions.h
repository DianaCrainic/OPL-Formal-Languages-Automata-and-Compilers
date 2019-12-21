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

// Maximum effective number of variables per body
#define MAX_VARIABLE_NUMBER 64

extern FILE* yyin;
extern int yylineno;

typedef struct
{
  int mainType;
  // 0-int, 1-float, 2-char, 3-string, 4-bool
  int isConst;
} Type;

typedef struct 
{
  char name[MAX_STRING_LENGTH];
  char scope[MAX_STRING_LENGTH];
  Type t;
} Variable;

typedef struct 
{
  Variable varTable[MAX_VARIABLE_NUMBER];
  int varNumber;
} VariableTable;

typedef struct 
{
  char name[MAX_STRING_LENGTH];
  Type returnType;
  Variable paramTable[MAX_PARAMETER_NUMBER];
  int paramNumber;
} Function;

typedef struct 
{
  Function funcTable[MAX_METHOD_NUMBER];
  int funcNumber;
} FunctionTable;

typedef struct
{
  char name[MAX_STRING_LENGTH];
  Variable attribTable[MAX_ATTRIBUTE_NUMBER];
  int attribNumber;
  Function methTable[MAX_METHOD_NUMBER];
  int methNumber;
} Class;

typedef struct 
{
  Class classTable[MAX_CLASS_NUMBER];
  int classNumber;
} ClassTable;