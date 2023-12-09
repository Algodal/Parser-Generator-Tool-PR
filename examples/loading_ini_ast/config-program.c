#include "algodal-parser-header.h"
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
#ifndef ALGODAL_GENERATED_PARSER_INTERNAL_H
#define ALGODAL_GENERATED_PARSER_INTERNAL_H
#include <stdint.h>
#include <string.h>
#ifdef __cplusplus
extern "C" {
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
    ALGPAR_OP_ZPN   
};
inline static const char * AlgodalParser_GetOpCodeString(int OpCode)
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
    }
    return "UNK";
}
inline static uint8_t AlgodalParser_GetOpcodeInteger(const char * shortstring)
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
#ifdef __cplusplus
}
#endif
#endif 
#ifndef config_ALGODAL_GENERATED_PARSER_PROGRAM_C
#define config_ALGODAL_GENERATED_PARSER_PROGRAM_C
static struct AlgodalParser_String config_TheStrings[]=
{
	{(char*)"\n", 1},
	{(char*)"name", 4},
	{(char*)"[", 1},
	{(char*)"]", 1},
	{(char*)"comment", 7},
	{(char*)"space", 5},
	{(char*)"value", 5},
	{(char*)".", 1},
	{(char*)"=", 1},
	{(char*)"alpha", 5},
	{(char*)"ABCDEFGHIJKLMNOPQRSTUVWXYZ", 26},
	{(char*)"numeral", 7},
	{(char*)"0123456789", 10},
	{(char*)"a_other", 7},
	{(char*)"_", 1},
	{(char*)";", 1},
	{(char*)"#", 1},
	{(char*)"\r\t ", 3},
	{(char*)"\n;#", 3},
	{(char*)"ini", 3},
	{(char*)"section", 7},
	{(char*)"heading", 7},
	{(char*)"setvalue", 8},
	{0, 0}
};

static uint8_t config_TheCodeOfActions[]=
{
	ALGPAR_OP_CNT, ALGPAR_PU32(1u), ALGPAR_PU32(4294967295u), ALGPAR_PU16(5u),
	ALGPAR_OP_ONE, 1, ALGPAR_PU16(10u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_CNT, ALGPAR_PU32(1u), ALGPAR_PU32(4294967295u), ALGPAR_PU16(5u),
	ALGPAR_OP_ONE, 1, ALGPAR_PU16(12u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_OPT, ALGPAR_PU16(3u), ALGPAR_PU16(25u), 1,
	ALGPAR_OP_PNT, ALGPAR_PU16(1u),
	ALGPAR_OP_RET,
	ALGPAR_OP_CNT, ALGPAR_PU32(1u), ALGPAR_PU32(4294967295u), ALGPAR_PU16(5u),
	ALGPAR_OP_EXT, 0, ALGPAR_PU16(14u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_PNT, ALGPAR_PU16(0u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_SER, ALGPAR_PU16(3u), ALGPAR_PU16(37u),
	ALGPAR_OP_CNT, ALGPAR_PU32(0u), ALGPAR_PU32(4294967295u), ALGPAR_PU16(5u),
	ALGPAR_OP_EXT, 0, ALGPAR_PU16(14u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_PNT, ALGPAR_PU16(0u),
	ALGPAR_OP_RET,
	ALGPAR_OP_CNT, ALGPAR_PU32(0u), ALGPAR_PU32(4294967295u), ALGPAR_PU16(4u),
	ALGPAR_OP_PNT, ALGPAR_PU16(2u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_SER, ALGPAR_PU16(3u), ALGPAR_PU16(43u),
	ALGPAR_OP_OPT, ALGPAR_PU16(2u), ALGPAR_PU16(10u), 0,
	ALGPAR_OP_EXT, 0, ALGPAR_PU16(15u),
	ALGPAR_OP_RET,
	ALGPAR_OP_EXT, 0, ALGPAR_PU16(16u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_CNT, ALGPAR_PU32(0u), ALGPAR_PU32(4294967295u), ALGPAR_PU16(9u),
	ALGPAR_OP_NOT, ALGPAR_PU16(5u),
	ALGPAR_OP_EXT, 0, ALGPAR_PU16(0u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_EXT, 0, ALGPAR_PU16(0u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_CNT, ALGPAR_PU32(1u), ALGPAR_PU32(4294967295u), ALGPAR_PU16(5u),
	ALGPAR_OP_ONE, 0, ALGPAR_PU16(17u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_SER, ALGPAR_PU16(2u), ALGPAR_PU16(25u),
	ALGPAR_OP_PRV, ALGPAR_PU16(8u),
	ALGPAR_OP_RET,
	ALGPAR_OP_CNT, ALGPAR_PU32(0u), ALGPAR_PU32(4294967295u), ALGPAR_PU16(9u),
	ALGPAR_OP_NOT, ALGPAR_PU16(5u),
	ALGPAR_OP_ONE, 0, ALGPAR_PU16(18u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_EXT, 0, ALGPAR_PU16(0u),
	ALGPAR_OP_RET,
	ALGPAR_OP_EXT, 0, ALGPAR_PU16(2u),
	ALGPAR_OP_RET,
	ALGPAR_OP_EXT, 0, ALGPAR_PU16(3u),
	ALGPAR_OP_RET,
	ALGPAR_OP_EXT, 0, ALGPAR_PU16(7u),
	ALGPAR_OP_RET,
	ALGPAR_OP_EXT, 0, ALGPAR_PU16(8u),
	ALGPAR_OP_RET,
	ALGPAR_OP_CNT, ALGPAR_PU32(0u), ALGPAR_PU32(4294967295u), ALGPAR_PU16(4u),
	ALGPAR_OP_PNT, ALGPAR_PU16(14u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_SER, ALGPAR_PU16(3u), ALGPAR_PU16(65u),
	ALGPAR_OP_TRM, ALGPAR_PU16(2u),
	ALGPAR_OP_RET,
	ALGPAR_OP_OPT, ALGPAR_PU16(2u), ALGPAR_PU16(50u), 1,
	ALGPAR_OP_SER, ALGPAR_PU16(2u), ALGPAR_PU16(30u),
	ALGPAR_OP_TRM, ALGPAR_PU16(1u),
	ALGPAR_OP_RET,
	ALGPAR_OP_CNT, ALGPAR_PU32(0u), ALGPAR_PU32(1u), ALGPAR_PU16(14u),
	ALGPAR_OP_SER, ALGPAR_PU16(2u), ALGPAR_PU16(8u),
	ALGPAR_OP_TRM, ALGPAR_PU16(7u),
	ALGPAR_OP_RET,
	ALGPAR_OP_TRM, ALGPAR_PU16(1u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_SER, ALGPAR_PU16(2u), ALGPAR_PU16(8u),
	ALGPAR_OP_TRM, ALGPAR_PU16(7u),
	ALGPAR_OP_RET,
	ALGPAR_OP_TRM, ALGPAR_PU16(1u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_TRM, ALGPAR_PU16(3u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_SER, ALGPAR_PU16(2u), ALGPAR_PU16(42u),
	ALGPAR_OP_PNT, ALGPAR_PU16(13u),
	ALGPAR_OP_RET,
	ALGPAR_OP_CNT, ALGPAR_PU32(0u), ALGPAR_PU32(1u), ALGPAR_PU16(26u),
	ALGPAR_OP_SER, ALGPAR_PU16(2u), ALGPAR_PU16(20u),
	ALGPAR_OP_TRM, ALGPAR_PU16(0u),
	ALGPAR_OP_RET,
	ALGPAR_OP_CNT, ALGPAR_PU32(0u), ALGPAR_PU32(4294967295u), ALGPAR_PU16(4u),
	ALGPAR_OP_PNT, ALGPAR_PU16(15u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_SER, ALGPAR_PU16(4u), ALGPAR_PU16(28u),
	ALGPAR_OP_TRM, ALGPAR_PU16(1u),
	ALGPAR_OP_RET,
	ALGPAR_OP_TRM, ALGPAR_PU16(8u),
	ALGPAR_OP_RET,
	ALGPAR_OP_TRM, ALGPAR_PU16(6u),
	ALGPAR_OP_RET,
	ALGPAR_OP_CNT, ALGPAR_PU32(0u), ALGPAR_PU32(1u), ALGPAR_PU16(4u),
	ALGPAR_OP_TRM, ALGPAR_PU16(0u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	0
};

static struct AlgodalParser_Action config_TheActions[]=
{
	{9, 0},
	{11, 17},
	{13, 34},
	{1, 66},
	{4, 109},
	{5, 158},
	{6, 175},
	{0, 206},
	{2, 211},
	{3, 216},
	{7, 221},
	{8, 226},
	{19, 231},
	{21, 247},
	{20, 318},
	{22, 366},
	{0, 0}
};

static struct AlgodalParser_Tokenizer config_TheTokenizers[]=
{
	{7, 0, 2, 0},
	{3, 1, 0, 0},
	{8, 0, 0, 0},
	{9, 0, 0, 0},
	{4, 1, 1, 0},
	{5, 1, 1, 0},
	{6, 1, 0, 10},
	{10, 0, 0, 0},
	{11, 0, 0, 0},
	{0, 0, 0, 0}
};

enum
{
	config_TheCountOfTokenizers = 9

};

static struct AlgodalParser_Entrypoint config_TheEntrypoints[]=
{
	{12, 0, 0, 0},
	{0, 0, 0, 0}
};

static struct AlgodalParser_Objectpoint config_TheObjectpoints[]=
{
	{12, 0, 0, 0},
	{14, 0, 0, 0},
	{13, 0, 0, 0},
	{15, 0, 0, 0},
	{3, 1, 0, 0},
	{6, 1, 0, 0},
	{0, 0, 0, 0}
};

enum
{
	 config_TheCountOfEntrypoints = 1
	,config_TheCountOfObjectpoints = 6

};

struct AlgodalParser_Program configProgram =
{
	.NameOfParser = (char*)"config",
	.Strings = config_TheStrings,
	.Actions = config_TheActions,
	.CodeOfActions = config_TheCodeOfActions,
	.Tokenizers = config_TheTokenizers,
	.Entrypoints = config_TheEntrypoints,
	.Objectpoints = config_TheObjectpoints,
	.CountOfTokenizers = config_TheCountOfTokenizers,
	.CountOfEntrypoints = config_TheCountOfEntrypoints,
	.CountOfObjectpoints = config_TheCountOfObjectpoints,

};

#endif

