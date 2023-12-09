#ifndef C_WINDOWS_PLATFORM_COMPATIBILITY_H
#define C_WINDOWS_PLATFORM_COMPATIBILITY_H
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
typedef struct AlgodalParser_AnalyzeResult AlgodalParser_AnalyzeResult;
typedef struct AlgodalParser_Token AlgodalParser_Token;
typedef struct AlgodalParser_Node AlgodalParser_Node;
typedef struct AlgodalParser_NodeChildren AlgodalParser_NodeChildren;
typedef struct AlgodalParser_Linenumber AlgodalParser_Linenumber;
typedef struct AlgodalParser_Program AlgodalParser_Program;
typedef struct AlgodalParser_Ast AlgodalParser_Ast;
typedef struct AlgodalParser_Error AlgodalParser_Error;
struct AlgodalParser_InternalLinenumber {
    const char * buffer;
    uint32_t lengthOfBuffer;
    unsigned int pos;
    struct {
        unsigned int row;
        unsigned int col;
        uint8_t      bufferUpdates;
    } metric;
};
typedef struct AlgodalParser_InternalLinenumber AlgodalParser_InternalLinenumber;
struct AlgodalParser_ParserLine
{
    uint32_t offset;
};
struct AlgodalParser_Linenumber
{
    AlgodalParser_InternalLinenumber* linenumber;
    struct AlgodalParser_ParserLine* lines;
    uint32_t numberOfLines;
};
struct AlgodalParser_Linenumber *AlgodalParser_CreateParserLinenumber(const char* nulltermText, const uint32_t length);
void AlgodalParser_DestroyParserLinenumber(struct AlgodalParser_Linenumber * AlgodalParser_ParserLinenumber);
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
};
struct AlgodalParser_Error
{
    uint32_t flags;
    uint32_t index;
    uint32_t index2;
    char *   userDefinedErrorMessage;
    struct 
    {
        uint32_t value;
        uint32_t extravalue;
    } user;
};
struct AlgodalParser_Token
{
    uint16_t id;
    uint32_t index;
    uint32_t size;
};
struct AlgodalParser_TokenizeResult
{
    struct
    {
        struct AlgodalParser_Token *addr;
        uint32_t      size;
    }   tokens;
    struct AlgodalParser_Error error;
    int8_t postProcessed;
};
struct AlgodalParser_OtherTokenizeParams
{
};
struct AlgodalParser_TokenizeResult AlgodalParser_GetTokenizeResult(struct AlgodalParser_Program Program, const char* text, const uint32_t size, struct AlgodalParser_OtherTokenizeParams* oparams);
void AlgodalParser_PrintTokenizeResult(struct AlgodalParser_Program program, struct AlgodalParser_TokenizeResult TokenizeResult, const char* text, struct AlgodalParser_Linenumber *AlgodalParser_ParserLinenumber);
void AlgodalParser_DestroyTokenizeResult(struct AlgodalParser_TokenizeResult TokenizeResult);
struct AlgodalParser_Node;
struct AlgodalParser_NodeChildren
{
    struct AlgodalParser_Node* *addr;
    uint32_t      size;
};
struct AlgodalParser_Node
{
    uint16_t indexOfAction;
    uint32_t indexOfToken;
    uint32_t size;
    uint8_t  terminal;
    int8_t   invisible;
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
struct AlgodalParser_AnalyzeResult AlgodalParser_GetAnalyzeResult(struct AlgodalParser_Program Program, const char* text, struct AlgodalParser_Token *tokens, const uint32_t size, struct AlgodalParser_OtherAnalyzeParams* oparams);
void AlgodalParser_PrintAnalyzeResult(struct AlgodalParser_Program program, struct AlgodalParser_AnalyzeResult AlgodalParser_AnalyzeResult, struct AlgodalParser_Token tokens[], const char* text, struct AlgodalParser_Linenumber *AlgodalParser_ParserLinenumber);
void AlgodalParser_DestroyAnalyzeResult(struct AlgodalParser_AnalyzeResult AlgodalParser_AnalyzeResult);
struct AlgodalParser_TokenPair;
struct AlgodalParser_TokenPairList
{
    struct AlgodalParser_TokenPair *addr;
    unsigned int       size;
};
struct AlgodalParser_TokenPair
{
    const char *key;
    const char *value;
    unsigned int offsetOfText;
    unsigned int lineNumber;
    unsigned int columnNumber;
};
struct AlgodalParser_NodePair;
struct AlgodalParser_NodePairList
{
    struct AlgodalParser_NodePair *addr;
    unsigned int     size;
};
struct AlgodalParser_NodePair
{
    const char*          key;
    const char          *value;
    struct AlgodalParser_NodePairList  children;
    unsigned int offsetOfText;
    unsigned int lineNumber;
    unsigned int columnNumber;
};
struct AlgodalParser_TokenPairList AlgodalParser_ExportTokenizeResult(struct AlgodalParser_TokenizeResult TokenizeResult, struct AlgodalParser_Program Program, const char *text, struct AlgodalParser_Linenumber *AlgodalParser_ParserLinenumber);
struct AlgodalParser_NodePairList AlgodalParser_ExportAnalyzeResult(struct AlgodalParser_Token *tokens, struct AlgodalParser_AnalyzeResult AlgodalParser_AnalyzeResult, struct AlgodalParser_Program Program, const char *text, struct AlgodalParser_Linenumber *AlgodalParser_ParserLinenumber);
void AlgodalParser_DestroyTokenPairList(struct AlgodalParser_TokenPairList pairList);
void AlgodalParser_DestroyNodePairList(struct AlgodalParser_NodePairList pairList);
void AlgodalParser_GetNodeValue(const char* text, const struct AlgodalParser_Token tokens[], struct AlgodalParser_Node *node, unsigned int size, char *r_value);
char* AlgodalParser_AllocNodeValue(AlgodalParser_Ast ast, struct AlgodalParser_Node *node);
void AlgodalParser_GetNodeKey(struct AlgodalParser_Program program, struct AlgodalParser_Node *node, char *r_key);
void AlgodalParser_GetTokenValue(const char* text, struct AlgodalParser_Token token, char *r_value);
void AlgodalParser_GetTokenKey(struct AlgodalParser_Program program, struct AlgodalParser_Token token, unsigned int size, char *r_key);
long AlgodalParser_GetNodeValueSize(const struct AlgodalParser_Token tokens[], struct AlgodalParser_Node *node);
const char *AlgodalParser_GetActionString_READONLY(struct AlgodalParser_Program program, unsigned int id);
const char * AlgodalParser_GetTokenizerString_READONLY(struct AlgodalParser_Program program, unsigned int id);
struct AlgodalParser_Ast
{
    AlgodalParser_Program program;
    AlgodalParser_Token* tokens;
    AlgodalParser_NodeChildren roots;
    AlgodalParser_Linenumber* linenumber;
    char* text;
};
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
#define VMINFO(...)
#ifdef __cplusplus
}
#endif
#endif  
