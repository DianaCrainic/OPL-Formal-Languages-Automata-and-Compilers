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
  // 0-int, 1-float, 2-char, 3-string, 4-bool
  int isConst;
  int isArray;
  int lengthOfArray;
} Type;

struct Variable
{
  char name[MAX_STRING_LENGTH];
  char scope[MAX_STRING_LENGTH];
  Type t;
};

typedef struct 
{
  struct Variable *varTable;
  int varNumber;
  int size;
} VariableTable;

struct Function
{
  char name[MAX_STRING_LENGTH];
  Type returnType;
  struct Variable paramTable[MAX_PARAMETER_NUMBER];
  int paramNumber;
};

typedef struct 
{
  struct Function *funcTable;
  int funcNumber;
  int size;
} FunctionTable;

struct Class
{
  char name[MAX_STRING_LENGTH];
  struct Variable attribTable[MAX_ATTRIBUTE_NUMBER];
  int attribNumber;
  struct Function methTable[MAX_METHOD_NUMBER];
  int methNumber;
};

typedef struct 
{
  struct Class *classTable;
  int classNumber;
  int size;
} ClassTable;

typedef struct expr_info {
  int intvalue;
        char* strvalue;
  int type;
} expr_info;