#ifndef C_WINDOWS_PLATFORM_COMPATIBILITY_H
#define C_WINDOWS_PLATFORM_COMPATIBILITY_H
#define _POSIX_C_SOURCE 200809L  
#ifdef __cplusplus
#define APS_ZERO {}
#define APS_CAST(T) APS_ZERO
#define APS_ARRAY(T, N, S) std::unique_ptr<T> N(new T[S])
#else
#define APS_ZERO {0}
#define APS_CAST(T) (T)APS_ZERO
#define APS_ARRAY(T, N, S) T N[S]
#endif
#include <stdio.h>
#include <string.h>
#ifdef __cplusplus
extern "C" {
#endif
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <direct.h>
#include <stdarg.h>
#define CWPC_BUFSIZ (size_t)1024 
inline static FILE * cwpc_fopen(const char *filename, const char *mode)
{
    FILE *fp = 0;
    (void)fopen_s(&fp, filename, mode);
    return fp;
}
inline static int cwpc_sprintf(char *buffer, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int ret = vsprintf_s(buffer, CWPC_BUFSIZ, format, args);
    va_end(args);
    return ret;
}
inline static int cwpc_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int ret = vprintf_s(format, args);
    va_end(args);
    return ret;
}
inline static int cwpc_fprintf(FILE *fp, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int ret = vfprintf_s(fp, format, args);
    va_end(args);
    return ret;
}
inline static int cwpc_mkdir(const char * dirname, int mode)
{
    (void)mode;
    return _mkdir(dirname);
}
inline static int cwpc_rmdir(const char * dirname)
{
    return _mkdir(dirname);
}
inline static int cwpc_fclose(FILE *fp)
{
    return fclose(fp);
}
inline static int cwpc_remove(const char *filename)
{
    return remove(filename);
}
inline static char *cwpc_strdup(const char * srcStr)
{
    return _strdup(srcStr);
}
#ifdef _WIN64
#else
#endif
#else
#include <unistd.h>
#include <sys/stat.h>
#define cwpc_fopen(...) fopen(__VA_ARGS__)
#define cwpc_sprintf(...) sprintf(__VA_ARGS__)
#define cwpc_printf(...) printf(__VA_ARGS__)
#define cwpc_fprintf(...) fprintf(__VA_ARGS__)
#define cwpc_mkdir(...) mkdir(__VA_ARGS__)
#define cwpc_rmdir(...) rmdir(__VA_ARGS__)
#define cwpc_fclose(...) fclose(__VA_ARGS__)
#define cwpc_remove(...) remove(__VA_ARGS__)
#define cwpc_strdup(...) strdup(__VA_ARGS__)
#if __linux__ || __unix__
#endif
#if __ANDROID__
#endif
#if defined(_POSIX_VERSION)
#endif
#endif
#ifdef __cplusplus
}
#endif
#endif  
#ifndef ALGODAL_GENERATED_PARSER_HEADER_H
#define ALGODAL_GENERATED_PARSER_HEADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef struct AlgodalParser_TokenizeResult AlgodalParser_TokenizeResult;
typedef struct AlgodalParser_OtherTokenizeParams AlgodalParser_OtherTokenizeParams;
typedef struct AlgodalParser_Token AlgodalParser_Token;
typedef struct AlgodalParser_TokenChildren AlgodalParser_TokenChildren;
typedef struct AlgodalParser_TokenPair AlgodalParser_TokenPair;
typedef struct AlgodalParser_TokenPairList AlgodalParser_TokenPairList;
typedef struct AlgodalParser_AnalyzeResult AlgodalParser_AnalyzeResult;
typedef struct AlgodalParser_OtherAnalyzeParams AlgodalParser_OtherAnalyzeParams;
typedef struct AlgodalParser_Node AlgodalParser_Node;
typedef struct AlgodalParser_NodeChildren AlgodalParser_NodeChildren;
typedef struct AlgodalParser_NodePair AlgodalParser_NodePair;
typedef struct AlgodalParser_NodePairList AlgodalParser_NodePairList;
typedef struct AlgodalParser_ParserLine AlgodalParser_ParserLine; 
typedef struct AlgodalParser_Error AlgodalParser_Error;
typedef struct AlgodalParser_UserDefinedError AlgodalParser_UserDefinedError;
typedef struct AlgodalParser_Program AlgodalParser_Program;
typedef struct AlgodalParser_Linenumber AlgodalParser_Linenumber;
typedef struct AlgodalParser_Ast AlgodalParser_Ast;
typedef struct AlgodalParser_ParsedData AlgodalParser_ParsedData;
typedef struct AlgodalParser_ParsedParams AlgodalParser_ParsedParams;
struct AlgodalParser_ParserLine
{
    uint32_t offset;
};
struct AlgodalParser_Linenumber
{
    void* linenumber;
    struct AlgodalParser_ParserLine* lines;
    uint32_t numberOfLines;
};
struct AlgodalParser_Basic  
{
    union
    {
        void      * generic;
        const char* string;
        int64_t     number;
        struct 
        {
            uint32_t position;
            uint32_t length;
        } parsed;
    };
    int8_t   current_state;  
};
struct AlgodalParser_Variable  
{
    const char*                name;
    struct AlgodalParser_Basic basic;
};
struct AlgodalParser_String
{
    char*    text;
    uint16_t length;
};
struct AlgodalParser_Action
{
    uint16_t indexOfString;
    uint16_t indexOfCode;
};
struct AlgodalParser_Tokenizer
{
    uint16_t indexOfAction;
    uint8_t  type;
    uint8_t  flag;
    int8_t   priority;
};
struct AlgodalParser_Entrypoint
{
    uint16_t indexOfAction;
    uint8_t  type;
    uint8_t  flag;
    int8_t   priority;
};
struct AlgodalParser_Objectpoint
{
    uint16_t indexOfAction;
    uint8_t  type;
    uint8_t  flag;
    int8_t   priority;
};
struct AlgodalParser_Flags
{
    int8_t   first_entry;
};
struct AlgodalParser_Stack
{
    struct AlgodalParser_Basic* addr;
    uint32_t                    size;
    uint32_t                    alloc_size;
};
struct AlgodalParser_Special
{
    int8_t   UseTokenphaseInitialActionCall;
    int16_t  TokenphaseInitialActionCallAction;
    int8_t   UseTokenphasePopTokenCreation;
    int16_t  TokenphasePopTokenCreationLabel;
    int16_t  TokenphasePopTokenCreationStop;
    int8_t   UseTokenphasePopAll;
};
struct AlgodalParser_DynamicAllocations
{
    void**   addr;
    uint32_t size;
};
struct AlgodalParser_Program
{
    char                             *NameOfParser;
    struct AlgodalParser_String*      Strings;
    struct AlgodalParser_Action*      Actions;
    uint8_t*                          CodeOfActions;
    struct AlgodalParser_Tokenizer   *Tokenizers;
    struct AlgodalParser_Entrypoint  *Entrypoints;
    struct AlgodalParser_Objectpoint *Objectpoints;
    uint16_t                          CountOfTokenizers;
    uint16_t                          CountOfEntrypoints;
    uint16_t                          CountOfObjectpoints;
    int8_t                            successful_allocation_json;
    struct AlgodalParser_Flags       *Flags;
    struct AlgodalParser_Variable    *Variables;
    uint16_t                          CountOfVariables;
    uint16_t                          CountOfActions;
    uint16_t                          CountOfStrings;
    struct AlgodalParser_Stack       *Stack;
    struct AlgodalParser_Special     *Special;
    uint32_t                         *RV1;
    struct AlgodalParser_DynamicAllocations DA;  
};
struct AlgodalParser_UserDefinedError
{
    char* msg;
    uint32_t value;
    uint32_t extravalue;
};
struct AlgodalParser_Error
{
    uint32_t flags;
    uint32_t index;
    uint32_t index2;
    uint32_t eval1;
    uint32_t eval2;
    uint32_t text_length;
    struct 
    {
        AlgodalParser_UserDefinedError* addr;
        unsigned int                    size;
    } user;
    int8_t phase;  
};
struct AlgodalParser_Token
{
    uint16_t id;  
    uint32_t index;  
    uint32_t size;  
};
struct AlgodalParser_TokenChildren
{
    AlgodalParser_Token *addr;
    uint32_t             size;
};
struct AlgodalParser_TokenizeResult
{
    AlgodalParser_TokenChildren  tokens;  
    struct AlgodalParser_Error error;  
    int8_t postProcessed;  
};
struct AlgodalParser_OtherTokenizeParams
{
    int8_t res;  
};
struct AlgodalParser_NodeChildren
{
    AlgodalParser_Node* *addr;
    uint32_t      size;
};
struct AlgodalParser_Node
{
    uint16_t indexOfAction;  
    uint32_t indexOfToken;  
    uint32_t size;  
    uint8_t  terminal;  
    int8_t invisible;  
    int8_t priority;  
    struct AlgodalParser_NodeChildren children;  
    struct AlgodalParser_Node* sibling;  
};
struct AlgodalParser_AnalyzeResult
{
    struct AlgodalParser_NodeChildren nodes;  
    struct AlgodalParser_Error  error;  
};
struct AlgodalParser_OtherAnalyzeParams
{
    int8_t loopOnce;
};
struct AlgodalParser_TokenPairList
{
    AlgodalParser_TokenPair *addr;
    unsigned int             size;
};
struct AlgodalParser_TokenPair
{
    const char *key;  
    const char *value;  
    unsigned int offsetOfText;  
    unsigned int lineNumber;  
    unsigned int columnNumber;  
};
struct AlgodalParser_NodePairList
{
    AlgodalParser_NodePair *addr;
    unsigned int            size;
};
struct AlgodalParser_NodePair
{
    const char*          key;  
    const char          *value;  
    AlgodalParser_NodePairList  children;  
    unsigned int offsetOfText;  
    unsigned int lineNumber;  
    unsigned int columnNumber;  
};
struct AlgodalParser_Ast
{
    AlgodalParser_Program program;  
    AlgodalParser_TokenChildren tokens;  
    AlgodalParser_NodeChildren nodes;  
    AlgodalParser_Linenumber* linenumber;  
    char* text;  
    AlgodalParser_TokenizeResult tr;
    AlgodalParser_AnalyzeResult ar;
};
struct AlgodalParser_ParsedData
{
    AlgodalParser_Ast ast;
    const char*       text;
};
struct AlgodalParser_ParsedParams
{
    struct AlgodalParser_OtherTokenizeParams other_tokenize_params;
    struct AlgodalParser_OtherAnalyzeParams  other_analyze_params;
};
struct AlgodalParser_Linenumber *AlgodalParser_CreateParserLinenumber(const char* text, const uint32_t length);
void AlgodalParser_DestroyParserLinenumber(struct AlgodalParser_Linenumber * AlgodalParser_ParserLinenumber);
struct AlgodalParser_TokenizeResult AlgodalParser_GetTokenizeResult(struct AlgodalParser_Program Program, const char* text, const uint32_t size, struct AlgodalParser_OtherTokenizeParams* oparams);
void AlgodalParser_DestroyTokenizeResult(struct AlgodalParser_TokenizeResult TokenizeResult);
struct AlgodalParser_AnalyzeResult AlgodalParser_GetAnalyzeResult(struct AlgodalParser_Program Program, const char* text, struct AlgodalParser_Token *tokens, const uint32_t size, struct AlgodalParser_OtherAnalyzeParams* oparams);
void AlgodalParser_DestroyAnalyzeResult(struct AlgodalParser_AnalyzeResult AlgodalParser_AnalyzeResult);
void AlgodalParser_DestroyTokenPairList(struct AlgodalParser_TokenPairList pairList);
void AlgodalParser_DestroyNodePairList(struct AlgodalParser_NodePairList pairList);
const char *AlgodalParser_GetActionString_READONLY(struct AlgodalParser_Program program, unsigned int id);
const char * AlgodalParser_GetTokenizerString_READONLY(struct AlgodalParser_Program program, unsigned int id);
void AlgodalParser_PrintTokenizeResult(AlgodalParser_Ast ast, AlgodalParser_Error error);
void AlgodalParser_PrintAnalyzeResult(AlgodalParser_Ast ast, AlgodalParser_Error error);
struct AlgodalParser_TokenPairList AlgodalParser_ExportTokenizeResult(AlgodalParser_Ast ast);
struct AlgodalParser_NodePairList AlgodalParser_ExportAnalyzeResult(AlgodalParser_Ast ast);
void AlgodalParser_FreeStack(struct AlgodalParser_Stack stack);
void AlgodalParser_FreeProgramStack(struct AlgodalParser_Program Program);
void AlgodalParser_PrintProgram(struct AlgodalParser_Program p);
void AlgodalParser_DestroyNodePair(struct AlgodalParser_NodePair pair);
void AlgodalParser_DestroyTokenPair(struct AlgodalParser_TokenPair pair);
AlgodalParser_NodePair AlgodalParser_ExportNode(AlgodalParser_Ast ast, struct AlgodalParser_Node *node);
struct AlgodalParser_TokenPair AlgodalParser_ExportToken(AlgodalParser_Ast ast, AlgodalParser_Token token);
void AlgodalParser_PrintToken(AlgodalParser_Ast ast, AlgodalParser_Token token);
void AlgodalParser_PrintNode(AlgodalParser_Ast ast, struct AlgodalParser_Node *node, uint16_t indent);
void AlgodalParser_PrintAnalyzeParserError(AlgodalParser_Ast ast, AlgodalParser_Error error);
void AlgodalParser_PrintTokenizeParserError(AlgodalParser_Ast ast, struct AlgodalParser_Error error);
void AlgodalParser_PrintNodeSelfOnly(AlgodalParser_Ast ast, struct AlgodalParser_Node *node, uint16_t indent);
#ifdef ALGODAL_GENERATED_PARSER_JSON_CONVERTER_C
struct AlgodalParser_Program AlgodalJsonParser_GetProgramFromFile(const char *filename, struct AlgodalParser_Ast* ret_ast, struct AlgodalParser_Error *retError);
struct AlgodalParser_Program AlgodalJsonParser_GetProgramFromString(const char *stringBuffer, const unsigned int stringLength, struct AlgodalParser_Ast* ret_ast, struct AlgodalParser_Error *retError);
void AlgodalJsonParser_DestroyProgram(struct AlgodalParser_Program program);
#endif
uint32_t algodalparser_get_byte1_size(char byte1);
uint32_t algodalparser_utf8_read(const char* string);
const char* AlgodalParser_GetLinenumber(struct AlgodalParser_Linenumber *AlgodalParser_ParserLinenumber, uint32_t offset, char *buffer);
void AlgodalParser_GetLinenumberInteger(struct AlgodalParser_Linenumber *AlgodalParser_ParserLinenumber, uint32_t offset, uint32_t *pl, uint32_t *pc);
AlgodalParser_ParsedData AlgodalParser_ParseTextEx(AlgodalParser_Program in_program, const char* in_text, unsigned int in_length, AlgodalParser_ParsedParams in_params);
AlgodalParser_ParsedData AlgodalParser_ParseText(AlgodalParser_Program in_program, const char* in_text, unsigned int in_length);
void AlgodalParser_DestroyParsedData(AlgodalParser_ParsedData data);
void AlgodalParser_PrintParsedData(AlgodalParser_ParsedData data);
#ifdef ALGODAL_GENERATED_PARSER_JSON_CONVERTER_H
AlgodalParser_ParsedData AlgodalParser_ParseTextExJson(const char* json_file, const char* in_text, unsigned int in_length, AlgodalParser_ParsedParams in_params);
AlgodalParser_ParsedData AlgodalParser_ParseTextExJsonStr(const char* json_str, unsigned int json_str_length, const char* in_text, unsigned int in_length, AlgodalParser_ParsedParams in_params);
AlgodalParser_ParsedData AlgodalParser_ParseTextJson(const char* json_file, const char* in_text, unsigned int in_length);
AlgodalParser_ParsedData AlgodalParser_ParseTextJsonStr(const char* json_str, unsigned int json_str_length, const char* in_text, unsigned int in_length);
#endif
#ifdef __cplusplus
}
#endif
#endif  
#ifndef ALGODAL_GENERATED_PARSER_AST_H
#define ALGODAL_GENERATED_PARSER_AST_H
#include <stdint.h>
#include <string.h>
#ifdef __cplusplus
extern "C" {
#endif
#define ALGODALPARSER_INITIALIZEAST(PROGRAM) AlgodalParser_InitializeAst(PROGRAM, tr, ar, ln, text)
void AlgodalParser_DestroyAst(AlgodalParser_Ast ast);
AlgodalParser_Ast AlgodalParser_InitializeAst(
    AlgodalParser_Program program,
    AlgodalParser_TokenizeResult tr,
    AlgodalParser_AnalyzeResult ar,
    AlgodalParser_Linenumber* ln,
    const char* text
);
AlgodalParser_Node* AlgodalParser_GetNodeByValueOfRoots(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier
);
AlgodalParser_Node* AlgodalParser_GetNodeByKeyOfRoots(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier
);
AlgodalParser_Node* AlgodalParser_GetNodeByValueOfNode(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier,
    AlgodalParser_Node* node
);
AlgodalParser_Node* AlgodalParser_GetNodeByKeyOfNode(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier,
    AlgodalParser_Node* node
);
AlgodalParser_Node* AlgodalParser_GetChildNodeByValueOfNode(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier,
    AlgodalParser_Node* node
);
AlgodalParser_Node* AlgodalParser_GetChildNodeByKeyOfNode(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier,
    AlgodalParser_Node* node
);
AlgodalParser_Node* AlgodalParser_GetSiblingNodeByValueOfNode(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier,
    AlgodalParser_Node* node
);
AlgodalParser_Node* AlgodalParser_GetSiblingNodeByKeyOfNode(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier,
    AlgodalParser_Node* node
);
int AlgodalParser_IsNodeValue(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier,
    AlgodalParser_Node* node
);
int AlgodalParser_IsNodeKey(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier,
    AlgodalParser_Node* node
);
int AlgodalParser_IsNodeValueUnquoted(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier,
    AlgodalParser_Node* node
);
int AlgodalParser_IsNodeValueSubstring(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier,
    AlgodalParser_Node* node
);
char* AlgodalParser_GetNodeValue(AlgodalParser_Ast ast, struct AlgodalParser_Node *node, char *r_value);
char* AlgodalParser_AllocNodeValue(AlgodalParser_Ast ast, struct AlgodalParser_Node *node);
char* AlgodalParser_GetNodeKey(AlgodalParser_Ast ast, struct AlgodalParser_Node *node, char *r_key);
char* AlgodalParser_GetTokenValue(AlgodalParser_Ast ast, struct AlgodalParser_Token token, char *r_value);
char* AlgodalParser_GetTokenKey(AlgodalParser_Ast ast, struct AlgodalParser_Token token, char *r_key);
long AlgodalParser_GetNodeValueSize(AlgodalParser_Ast ast, struct AlgodalParser_Node *node);
char* AlgodalParser_GetTokenValueSimplified(AlgodalParser_Ast ast, struct AlgodalParser_Token token, char *r_value);
char* AlgodalParser_GetNodeValueSimplified(AlgodalParser_Ast ast, struct AlgodalParser_Node *node, char *r_value);
int AlgodalParser_IsNodeValueSimplified(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier,
    AlgodalParser_Node* node
);
char* AlgodalParser_GetNodeValueBySize(AlgodalParser_Ast ast, struct AlgodalParser_Node *node, char *r_value, unsigned int size);
#ifdef __cplusplus
}
#endif
#endif 
#ifndef ALGODAL_GENERATED_PARSER_SHARED_H
#define ALGODAL_GENERATED_PARSER_SHARED_H
#include <stdint.h>
#include <string.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef struct AlgodalParser_StringToNumber AlgodalParser_StringToNumber;
struct AlgodalParser_StringToNumber
{
    int base;   
    char* end;  
};
int AlgodalParser_StrCmp(int icase, const char* str1, const char* str2);
int AlgodalParser_SubStrCmp(int icase, const char* str1, const char* str2);
long long AlgodalParser_StrToInt(const char* str, AlgodalParser_StringToNumber* stn);
double AlgodalParser_StrToDec(const char* str, AlgodalParser_StringToNumber* stn);
char* AlgodalParser_UnquoteStr(const char* str, char* buf);
char* AlgodalParser_SimplifyStr(size_t size, char* r_str);
char* AlgodalParser_MakeLiteralString(char c[], uint32_t length);
char* AlgodalParser_UnbracketStr(const char* str, char* buf);
#ifdef __cplusplus
}
#endif
#endif 
#ifndef ALGODAL_GENERATED_PARSER_INTERNAL_H
#define ALGODAL_GENERATED_PARSER_INTERNAL_H
#include <stdint.h>
#include <string.h>
#ifdef __cplusplus
extern "C" {
#endif
#ifdef ALGODAL_GENERATED_PARSER_VM_SHOW_ALL_NODES_VALUES
#define SHOW_NODE_VALUE 1
#else
#define SHOW_NODE_VALUE node->terminal == 1
#endif
enum
{
    ALGODAL_PARSING_DUP         =   2,
    ALGODAL_PARSING_FAIL        =  16,   
    ALGODAL_PARSING_EOI         =  32,
    ALGODAL_PARSING_ERROR       =  64,
    ALGODAL_PARSING_USER        =  128
};
#ifdef ALGODALPARSER_VM_BIG_ENDIAN
#define ALGPAR_PU32(x) (uint8_t)((x>>24) & 0xFF), (uint8_t)((x>>16) & 0xFF), (uint8_t)((x>>8) & 0xFF), (uint8_t)(x & 0xFF)
#define ALGPAR_PU16(x) (uint8_t)((x>>8) & 0xFF), (uint8_t)(x & 0xFF)
#else
#define ALGPAR_PU32(x) (uint8_t)(x & 0xFF), (uint8_t)((x>>8) & 0xFF), (uint8_t)((x>>16) & 0xFF), (uint8_t)((x>>24) & 0xFF)
#define ALGPAR_PU16(x) (uint8_t)(x & 0xFF), (uint8_t)((x>>8) & 0xFF)
#endif
enum 
{
    ALGPAR_OP_RET  = 8,
    ALGPAR_OP_OPT,
    ALGPAR_OP_SER,
    ALGPAR_OP_CHR,
    ALGPAR_OP_ONE,
    ALGPAR_OP_NOT,
    ALGPAR_OP_ORD, 
    ALGPAR_OP_EXT,   
    ALGPAR_OP_PNT,
    ALGPAR_OP_TRM,    
    ALGPAR_OP_CNT,    
    ALGPAR_OP_PRV,
    ALGPAR_OP_AND,
    ALGPAR_OP_ZCR,  
    ALGPAR_OP_ZTR,  
    ALGPAR_OP_ZTS,  
    ALGPAR_OP_ZPR,  
    ALGPAR_OP_ZPS,  
    ALGPAR_OP_SCP,  
    ALGPAR_OP_NUL,  
    ALGPAR_OP_ZTN,  
    ALGPAR_OP_ZPN,  
    ALGPAR_OP_NLN,  
    ALGPAR_OP_XSP,  
    ALGPAR_OP_V_STO,
    ALGPAR_OP_V_CON,
    ALGPAR_OP_V_EXT,
    ALGPAR_OP_V_ORD,
    ALGPAR_OP_V_ONE,
    ALGPAR_OP_V_PNT,
    ALGPAR_OP_V_CNT,
    ALGPAR_OP_BYT,
    ALGPAR_OP_L_IFB,
    ALGPAR_OP_L_IF0,
    ALGPAR_OP_S_PUS,
    ALGPAR_OP_S_POP,
    ALGPAR_OP_S_PEK,
    ALGPAR_OP_A_GT0,
    ALGPAR_OP_A_LT0,
    ALGPAR_OP_A_GTE,
    ALGPAR_OP_A_LTE,
    ALGPAR_OP_A_EQ0,
    ALGPAR_OP_A_NE0
};
inline static const char * GetOpCodeString(int OpCode)
{
    switch(OpCode)
    {
        case ALGPAR_OP_RET: return "RET";
        case ALGPAR_OP_OPT: return "OPT";
        case ALGPAR_OP_SER: return "SER";
        case ALGPAR_OP_CHR: return "CHR";
        case ALGPAR_OP_ONE: return "ONE";
        case ALGPAR_OP_EXT: return "EXT";
        case ALGPAR_OP_ORD: return "ORD";
        case ALGPAR_OP_PNT: return "PNT";
        case ALGPAR_OP_TRM: return "TRM";
        case ALGPAR_OP_CNT: return "CNT";
        case ALGPAR_OP_NOT: return "NOT";
        case ALGPAR_OP_PRV: return "PRV";
        case ALGPAR_OP_AND: return "AND";
        case ALGPAR_OP_ZCR: return "ZCR";
        case ALGPAR_OP_ZTR: return "ZTR";
        case ALGPAR_OP_ZTS: return "ZTS";        
        case ALGPAR_OP_ZPR: return "ZPR";
        case ALGPAR_OP_ZPS: return "ZPS";
        case ALGPAR_OP_SCP: return "SCP";
        case ALGPAR_OP_NUL: return "NUL";
        case ALGPAR_OP_ZTN: return "ZTN";
        case ALGPAR_OP_ZPN: return "ZPN";
        case ALGPAR_OP_NLN: return "NLN";
        case ALGPAR_OP_XSP: return "XSP";
        case ALGPAR_OP_V_STO: return "V_STO";
        case ALGPAR_OP_V_CON: return "V_CON";
        case ALGPAR_OP_V_EXT: return "V_EXT";
        case ALGPAR_OP_V_ORD: return "V_ORD";
        case ALGPAR_OP_V_ONE: return "V_ONE";
        case ALGPAR_OP_V_PNT: return "V_PNT";
        case ALGPAR_OP_V_CNT: return "V_CNT";
        case ALGPAR_OP_BYT: return "BYT";
        case ALGPAR_OP_L_IFB: return "L_IFB";
        case ALGPAR_OP_L_IF0: return "L_IF0";
        case ALGPAR_OP_S_PUS: return "S_PUS";
        case ALGPAR_OP_S_POP: return "S_POP";
        case ALGPAR_OP_S_PEK: return "S_PEK";
        case ALGPAR_OP_A_GT0: return "A_GT0";
        case ALGPAR_OP_A_LT0: return "A_LT0";
        case ALGPAR_OP_A_GTE: return "A_GTE";
        case ALGPAR_OP_A_LTE: return "A_LTE";
        case ALGPAR_OP_A_EQ0: return "A_EQ0";
        case ALGPAR_OP_A_NE0: return "A_NE0";
    }
    return "UNK";
}
inline static uint8_t GetOpcodeInteger(const char * shortstring)
{
    if(strcmp(shortstring, "RET")==0) return ALGPAR_OP_RET;
    if(strcmp(shortstring, "OPT")==0) return ALGPAR_OP_OPT;
    if(strcmp(shortstring, "SER")==0) return ALGPAR_OP_SER;
    if(strcmp(shortstring, "CHR")==0) return ALGPAR_OP_CHR;
    if(strcmp(shortstring, "ONE")==0) return ALGPAR_OP_ONE;
    if(strcmp(shortstring, "NOT")==0) return ALGPAR_OP_NOT;
    if(strcmp(shortstring, "ORD")==0) return ALGPAR_OP_ORD;
    if(strcmp(shortstring, "EXT")==0) return ALGPAR_OP_EXT;
    if(strcmp(shortstring, "TRM")==0) return ALGPAR_OP_TRM;
    if(strcmp(shortstring, "PNT")==0) return ALGPAR_OP_PNT;
    if(strcmp(shortstring, "CNT")==0) return ALGPAR_OP_CNT;
    if(strcmp(shortstring, "PRV")==0) return ALGPAR_OP_PRV;
    if(strcmp(shortstring, "AND")==0) return ALGPAR_OP_AND;
    if(strcmp(shortstring, "ZCR")==0) return ALGPAR_OP_ZCR;
    if(strcmp(shortstring, "ZTR")==0) return ALGPAR_OP_ZTR;
    if(strcmp(shortstring, "ZTS")==0) return ALGPAR_OP_ZTS;
    if(strcmp(shortstring, "ZPR")==0) return ALGPAR_OP_ZPR;
    if(strcmp(shortstring, "ZPS")==0) return ALGPAR_OP_ZPS;
    if(strcmp(shortstring, "SCP")==0) return ALGPAR_OP_SCP;
    if(strcmp(shortstring, "NUL")==0) return ALGPAR_OP_NUL;
    if(strcmp(shortstring, "ZTN")==0) return ALGPAR_OP_ZTN;
    if(strcmp(shortstring, "ZPN")==0) return ALGPAR_OP_ZPN;
    if(strcmp(shortstring, "NLN")==0) return ALGPAR_OP_NLN;
    if(strcmp(shortstring, "XSP")==0) return ALGPAR_OP_XSP;
    if(strcmp(shortstring, "V_STO")==0) return ALGPAR_OP_V_STO;
    if(strcmp(shortstring, "V_CON")==0) return ALGPAR_OP_V_CON;
    if(strcmp(shortstring, "V_EXT")==0) return ALGPAR_OP_V_EXT;
    if(strcmp(shortstring, "V_ORD")==0) return ALGPAR_OP_V_ORD;
    if(strcmp(shortstring, "V_ONE")==0) return ALGPAR_OP_V_ONE;
    if(strcmp(shortstring, "V_PNT")==0) return ALGPAR_OP_V_PNT;
    if(strcmp(shortstring, "V_CNT")==0) return ALGPAR_OP_V_CNT;
    if(strcmp(shortstring, "BYT")==0) return ALGPAR_OP_BYT;
    if(strcmp(shortstring, "L_IFB")==0) return ALGPAR_OP_L_IFB;
    if(strcmp(shortstring, "L_IF0")==0) return ALGPAR_OP_L_IF0;
    if(strcmp(shortstring, "S_PUS")==0) return ALGPAR_OP_S_PUS;
    if(strcmp(shortstring, "S_POP")==0) return ALGPAR_OP_S_POP;
    if(strcmp(shortstring, "S_PEK")==0) return ALGPAR_OP_S_PEK;
    if(strcmp(shortstring, "A_GT0")==0) return ALGPAR_OP_A_GT0;
    if(strcmp(shortstring, "A_LT0")==0) return ALGPAR_OP_A_LT0;
    if(strcmp(shortstring, "A_GTE")==0) return ALGPAR_OP_A_GTE;
    if(strcmp(shortstring, "A_LTE")==0) return ALGPAR_OP_A_LTE;
    if(strcmp(shortstring, "A_EQ0")==0) return ALGPAR_OP_A_EQ0;
    if(strcmp(shortstring, "A_NE0")==0) return ALGPAR_OP_A_NE0;
    return 0;
}
#ifndef ALGODAL_GENERATED_PARSER_FUNC_STRCMPNC
#define ALGODAL_GENERATED_PARSER_FUNC_STRCMPNC
static inline int strcmpnc(char const *a, char const *b)
{
    for (;; a++, b++) {
        int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        if (d != 0 || !*a)
            return d;
    }
    return 0;
}
#endif 
#ifndef ALGODAL_GENERATED_PARSER_FUNC_STRSTRNC
#define ALGODAL_GENERATED_PARSER_FUNC_STRSTRNC
static inline char* strstrnc(char const *str1, char const *str2)
{
    const char* p1 = str1 ;
    const char* p2 = str2 ;
    const char* r = *p2 == 0 ? str1 : 0 ;
    while( *p1 != 0 && *p2 != 0 )
    {
        if( tolower( (unsigned char)*p1 ) == tolower( (unsigned char)*p2 ) )
        {
            if( r == 0 )
            {
                r = p1 ;
            }
            p2++ ;
        }
        else
        {
            p2 = str2 ;
            if( r != 0 )
            {
                p1 = r + 1 ;
            }
            if( tolower( (unsigned char)*p1 ) == tolower( (unsigned char)*p2 ) )
            {
                r = p1 ;
                p2++ ;
            }
            else
            {
                r = 0 ;
            }
        }
        p1++ ;
    }
    return *p2 == 0 ? (char*)r : 0 ;
}
#endif 
static inline int IsSpaceChar(int c)
{
    return c == '\n' || c == '\r' || c == '\t' || c == ' ';
}
#ifndef SET_ALGODALPARSER_SETTING  
#define SET_ALGODALPARSER_SETTING
#define ALGODALPARSER_STDERR stderr  
#define ALGODALPARSER_STDOUT stdout  
#else
#ifndef ALGODALPARSER_STDERR
#define ALGODALPARSER_STDERR stderr
#endif 
#ifndef ALGODALPARSER_STDOUT
#define ALGODALPARSER_STDOUT stdout
#endif 
#endif 
#ifdef __cplusplus
}
#endif
#endif 
#ifndef ALGODAL_GENERATED_PARSER_LOGGER_H
#define ALGODAL_GENERATED_PARSER_LOGGER_H
#ifdef __cplusplus
extern "C" {
#endif
#define VMLOG_PROC(OPCODE, INPUT, OUTPUT)
#define VMLOG_BRAN(OPCODE, INPUT, OUTPUT)
#define VMLOG_STAT(INPUT)
#define VMINFO(...)
#define VMLOG_PRINT_STACK(TEXT, PROG)
#define VMLOG_PRINT_VAR(TXT, PROG, IND)
#define VMLOG_PRINT_VARS(TXT, PROG)
#ifdef __cplusplus
}
#endif
#endif  
