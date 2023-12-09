#include "algodal-parser-header.h"
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
#ifndef ALGODAL_GENERATED_PARSER_AST_C
#define ALGODAL_GENERATED_PARSER_AST_C
#ifdef __cplusplus
extern "C" {
#endif
AlgodalParser_Ast AlgodalParser_InitializeAst(
    AlgodalParser_Program program,
    AlgodalParser_TokenizeResult tr,
    AlgodalParser_AnalyzeResult ar,
    AlgodalParser_Linenumber* ln,
    const char* text
)
{
    AlgodalParser_Ast ast = {};
    ast.text = (char*)text;
    ast.linenumber = ln;
    ast.tokens = tr.tokens.addr;
    ast.roots = ar.nodes;
    ast.program = program;
    return ast;
}
AlgodalParser_Node* AlgodalParser_GetNodeByValueOfRoots(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier
)
{
    AlgodalParser_Node root = {};
    root.children = ast.roots;
    return AlgodalParser_GetNodeByValueOfNode(ast, icase, identifier, &root);
}
AlgodalParser_Node* AlgodalParser_GetNodeByKeyOfRoots(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier
)
{
    AlgodalParser_Node root = {};
    root.children = ast.roots;
    return AlgodalParser_GetNodeByKeyOfNode(ast, icase, identifier, &root);
}
AlgodalParser_Node* AlgodalParser_GetNodeByValueOfNode(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier,
    AlgodalParser_Node* node
)
{
    AlgodalParser_Node* other = AlgodalParser_GetSiblingNodeByValueOfNode(ast, icase, identifier, node);
    if(other) return other;
    other = AlgodalParser_GetChildNodeByValueOfNode(ast, icase, identifier, node);
    return other;
}
AlgodalParser_Node* AlgodalParser_GetNodeByKeyOfNode(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier,
    AlgodalParser_Node* node
)
{
    AlgodalParser_Node* other = AlgodalParser_GetSiblingNodeByKeyOfNode(ast, icase, identifier, node);
    if(other) return other;
    other = AlgodalParser_GetChildNodeByKeyOfNode(ast, icase, identifier, node);
    return other;
}
AlgodalParser_Node* AlgodalParser_GetChildNodeByValueOfNode(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier,
    AlgodalParser_Node* node
)
{
    for(unsigned int i = 0; i < node->children.size; i++)
    {
        AlgodalParser_Node* child = node->children.addr[i];
        long size = AlgodalParser_GetNodeValueSize(ast.tokens, child);
        if(size == 0)
        {
            if(AlgodalParser_StrCmp(icase, identifier, ""))
            {
                return child;
            }
            else
            {
                continue;
            }
        }
        else
        {
            char value[size + 1];
            memset(value, 0, size + 1);
            AlgodalParser_GetNodeValue(ast.text, ast.tokens, child, size, value);
            if(AlgodalParser_StrCmp(icase, identifier, value))
            {
                return node;
            }
            else
            {
                continue;
            }
        } 
    }
    for(unsigned int i = 0; i < node->children.size; i++)
    {
        AlgodalParser_Node* grandparent = node->children.addr[i];
        AlgodalParser_Node* grandchild  = AlgodalParser_GetSiblingNodeByValueOfNode(ast, icase, identifier, grandparent);
        if(grandchild) return grandchild;
    }
    return NULL;
}
AlgodalParser_Node* AlgodalParser_GetChildNodeByKeyOfNode(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier,
    AlgodalParser_Node* node
)
{
    for(unsigned int i = 0; i < node->children.size; i++)
    {
        AlgodalParser_Node* child = node->children.addr[i];
        char* key = (char*)AlgodalParser_GetActionString_READONLY(ast.program, child->indexOfAction);
        if(AlgodalParser_StrCmp(icase, identifier, key))
        {
            return child;
        }
    }
    for(unsigned int i = 0; i < node->children.size; i++)
    {
        AlgodalParser_Node* child = node->children.addr[i];
        AlgodalParser_Node* grandchild  = AlgodalParser_GetChildNodeByKeyOfNode(ast, icase, identifier, child);
        if(grandchild) return grandchild;
    }
    return NULL;
}
AlgodalParser_Node* AlgodalParser_GetSiblingNodeByValueOfNode(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier,
    AlgodalParser_Node* node
)
{
    while(node->sibling)
    {
        node = node->sibling;  
        long size = AlgodalParser_GetNodeValueSize(ast.tokens, node);
        if(size == 0)
        {
            if(AlgodalParser_StrCmp(icase, identifier, ""))
            {
                return node;
            }
            else
            {
                continue;
            }
        }
        else
        {
            char value[size + 1];
            memset(value, 0, size + 1);
            AlgodalParser_GetNodeValue(ast.text, ast.tokens, node, size, value);
            if(AlgodalParser_StrCmp(icase, identifier, value))
            {
                return node;
            }
            else
            {
                continue;
            }
        }        
    }
    return NULL;
}
AlgodalParser_Node* AlgodalParser_GetSiblingNodeByKeyOfNode(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier,
    AlgodalParser_Node* node
)
{
    while(node->sibling)
    {
        node = node->sibling;  
        char* key = (char*)AlgodalParser_GetActionString_READONLY(ast.program, node->indexOfAction);
        if(AlgodalParser_StrCmp(icase, identifier, key))
        {
            return node;
        }
        else
        {
            continue;
        }    
    }
    return NULL;
}
int AlgodalParser_IsNodeValue(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier,
    AlgodalParser_Node* node
)
{
    long size = AlgodalParser_GetNodeValueSize(ast.tokens, node);
    if(size == 0) return AlgodalParser_StrCmp(icase, identifier, "");
    else
    {
        char value[size + 1];
        memset(value, 0, size + 1);
        AlgodalParser_GetNodeValue(ast.text, ast.tokens, node, size, value);
        return AlgodalParser_StrCmp(icase, identifier, value);
    }     
}
int AlgodalParser_IsNodeKey(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier,
    AlgodalParser_Node* node
)
{
    char* key = (char*)AlgodalParser_GetActionString_READONLY(ast.program, node->indexOfAction);
    return AlgodalParser_StrCmp(icase, identifier, key);
}
int AlgodalParser_IsNodeValueUnquoted(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier,
    AlgodalParser_Node* node
)
{
    size_t length = strlen(identifier) + 2 * sizeof(char);
    char identifierQuoted[length + 1];
    memset(identifierQuoted, 0, length + 1);
    strcat(identifierQuoted, "\"");
    strcat(identifierQuoted, identifier);
    strcat(identifierQuoted, "\"");
    return AlgodalParser_IsNodeValue(ast, icase, identifierQuoted, node);
}
int AlgodalParser_IsNodeValueSubstring(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier,
    AlgodalParser_Node* node
)
{
    long size = AlgodalParser_GetNodeValueSize(ast.tokens, node);
    if(size == 0) return AlgodalParser_StrCmp(icase, identifier, "");
    else
    {
        char value[size + 1];
        memset(value, 0, size + 1);
        AlgodalParser_GetNodeValue(ast.text, ast.tokens, node, size, value);
        return AlgodalParser_SubStrCmp(icase, value, identifier);
    }     
}
#ifdef __cplusplus
}
#endif
#endif 
#ifndef ALGODAL_GENERATED_PARSER_SHARED_C
#define ALGODAL_GENERATED_PARSER_SHARED_C
#ifdef __cplusplus
extern "C" {
#endif
int AlgodalParser_StrCmp(int icase, const char* str1, const char* str2)
{
    return icase ? strcmpnc(str1, str2)==0 : strcmp(str1, str2)==0;
}
int AlgodalParser_SubStrCmp(int icase, const char* str1, const char* str2)
{
    return icase ? strstrnc(str1, str2)!=NULL : strstr(str1, str2)!=NULL;
}
long long AlgodalParser_StrToInt(const char* str, AlgodalParser_StringToNumber* stn)
{
    if(stn)
    {
        return strtoll(str, &stn->end, stn->base);
    }
    else
    {
        return strtoll(str, 0, 10);
    }
}
double AlgodalParser_StrToDec(const char* str, AlgodalParser_StringToNumber* stn)
{
    if(stn)
    {
        return strtod(str, &stn->end);
    }
    else
    {
        return strtod(str, 0);
    }
}
char* AlgodalParser_UnquoteStr(const char* str, char* buf)
{
    const unsigned int length = strlen(str) - 2;
    memcpy(buf, &str[1], length);
    buf[length] = 0;
    return buf;
}
#ifdef __cplusplus
}
#endif
#endif 
#ifndef ALGODAL_GENERATED_PARSER_VM_C
#define ALGODAL_GENERATED_PARSER_VM_C
#ifdef ALGODAL_GENERATED_PARSER_VM_SHOW_ALL_NODES_VALUES
#define SHOW_NODE_VALUE 1
#else
#define SHOW_NODE_VALUE node->terminal == 1
#endif
#ifdef __cplusplus
extern "C" {
#endif
unsigned int clamp_index(unsigned int index, unsigned int size)
{
    if(size)
    {
        if(index >= size) return size - 1;
        return index;
    }
    return 0;
}
#ifndef ALGODAL_GENERATED_PARSER_FUNC_STRCMPNC
#define ALGODAL_GENERATED_PARSER_FUNC_STRCMPNC
static int strcmpnc(char const *a, char const *b)
{
    for (;; a++, b++) {
        int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
        if (d != 0 || !*a)
            return d;
    }
    return 0;
}
#endif 
inline static uint32_t uint32_binread(const uint8_t* codeOfActions, uint16_t* ptrOfIndexOfCode)
{
    uint32_t* valuePtr = (uint32_t*)(&codeOfActions[*ptrOfIndexOfCode]);
    *ptrOfIndexOfCode += sizeof(uint32_t);
    return *valuePtr;
}
inline static uint16_t uint16_binread(const uint8_t* codeOfActions, uint16_t* ptrOfIndexOfCode)
{
    uint16_t* valuePtr = (uint16_t*)(&codeOfActions[*ptrOfIndexOfCode]);
    *ptrOfIndexOfCode += sizeof(uint16_t);
    return *valuePtr;
}
inline static uint8_t uint8_binread(const uint8_t* codeOfActions, uint16_t* ptrOfIndexOfCode)
{
    uint8_t* valuePtr = (uint8_t*)(&codeOfActions[*ptrOfIndexOfCode]);
    *ptrOfIndexOfCode += sizeof(uint8_t);
    return *valuePtr;
}
#ifndef UTF_8_H
#define UTF_8_H
typedef uint32_t utf8_unicode_t; 
static inline size_t get_byte1_size(char byte1)
{
	return
		(byte1 & 128) == 0 ? 1u :
		(byte1 & (128 + 64 + 32)) == (128 + 64) ? 2u :
		(byte1 & (128 + 64 + 32 + 16)) == (128 + 64 + 32) ? 3u :
		(byte1 & (128 + 64 + 32 + 16 + 8)) == (128 + 64 + 32 + 16) ? 4u :
		0; 
}
static utf8_unicode_t utf8_read(const char* string)
{
    const size_t byte1Size = get_byte1_size(string[0]);
	utf8_unicode_t unicode = 0;
	memcpy(&unicode, string, sizeof(char) * byte1Size);
	return unicode;
}
static size_t utf8_get_unicode_size (utf8_unicode_t unicode)
{
	return
		unicode <= 0x7F ? 1u :
		unicode <= 0xDFBF ? 2u :
		unicode <= 0xEFBFBF ? 3u :
		4u;
}
#endif  
#ifndef LINENUMBER_H
#define LINENUMBER_H
static AlgodalParser_InternalLinenumber * Linenumber_create(const char * buffer, const uint32_t length);
static void Linenumber_destroy(AlgodalParser_InternalLinenumber * pln);
static void Linenumber_updateBuffer(AlgodalParser_InternalLinenumber * pln, const char* buffer, const uint32_t length);
static void Linenumber_next(AlgodalParser_InternalLinenumber * pln);
inline static AlgodalParser_InternalLinenumber * empty() {
    AlgodalParser_InternalLinenumber * pln = (AlgodalParser_InternalLinenumber *)malloc(sizeof(AlgodalParser_InternalLinenumber));
    memset(pln, 0, sizeof(AlgodalParser_InternalLinenumber));
    pln->metric.row = 1;
    pln->metric.col = 1;
    return pln;
}
inline static unsigned int n(unsigned int c) {
    if(c == '\n') return 1;
    return 0;
}
inline static unsigned int r(unsigned int c) {
    if(c == '\r') return 1;
    return 0;
}
static AlgodalParser_InternalLinenumber * Linenumber_create(const char * buffer, const uint32_t lengthOfBuffer) {
    AlgodalParser_InternalLinenumber * pln = empty();
    Linenumber_updateBuffer(pln, buffer, lengthOfBuffer);
    return pln;
}
static void Linenumber_destroy(AlgodalParser_InternalLinenumber * pln) {
    free(pln);
}
static void Linenumber_updateBuffer(AlgodalParser_InternalLinenumber * pln, const char* buffer, const uint32_t lengthOfBuffer) {
   if(buffer)
   {
        pln->buffer = buffer;
        pln->lengthOfBuffer = lengthOfBuffer;
        pln->pos = 0;
        pln->metric.bufferUpdates++;
   }
}
static void Linenumber_next(AlgodalParser_InternalLinenumber * pln) {
    if(pln->buffer)
    {
        const utf8_unicode_t c  = utf8_read(&pln->buffer[pln->pos]);
        const unsigned int size = utf8_get_unicode_size(c);
        pln->pos += size;
        if(n(c)) {
            pln->metric.col = 1;
            pln->metric.row ++;
        } else if (r(c)){
        } else {
            pln->metric.col ++;
        }
    }
}
static int Linenumber_nextLine(AlgodalParser_InternalLinenumber * pln, uint32_t length) {
    while(pln->pos < length) {
        const int c = pln->buffer[pln->pos];
        Linenumber_next(pln);
        if(c == '\n') return 1;
    }
    return 0;
}
inline static void append_line(struct AlgodalParser_Linenumber * AlgodalParser_ParserLinenumber)
{
    const uint32_t index = AlgodalParser_ParserLinenumber->numberOfLines++;
    AlgodalParser_ParserLinenumber->lines = (struct AlgodalParser_ParserLine *)realloc(AlgodalParser_ParserLinenumber->lines, sizeof(struct AlgodalParser_ParserLine) * AlgodalParser_ParserLinenumber->numberOfLines);
    AlgodalParser_ParserLinenumber->lines[index].offset = AlgodalParser_ParserLinenumber->linenumber->pos;
}
void UpdateParserLinenumberText(struct AlgodalParser_Linenumber * AlgodalParser_ParserLinenumber, const char* nulltermText, const uint32_t length)
{
    Linenumber_updateBuffer(AlgodalParser_ParserLinenumber->linenumber, nulltermText, length);
    while(AlgodalParser_ParserLinenumber->linenumber->pos < length)
    {
        append_line(AlgodalParser_ParserLinenumber);
        Linenumber_nextLine(AlgodalParser_ParserLinenumber->linenumber, length);
    }
}
struct AlgodalParser_Linenumber *AlgodalParser_CreateParserLinenumber(const char* nulltermText, const uint32_t length)
{
    struct AlgodalParser_Linenumber *AlgodalParser_ParserLinenumber = (struct AlgodalParser_Linenumber *)malloc(sizeof(struct AlgodalParser_Linenumber));
    memset(AlgodalParser_ParserLinenumber, 0, sizeof(struct AlgodalParser_Linenumber));
    AlgodalParser_ParserLinenumber->linenumber = Linenumber_create(nulltermText, length);
    UpdateParserLinenumberText(AlgodalParser_ParserLinenumber, nulltermText, length);
    return AlgodalParser_ParserLinenumber;
}
void AlgodalParser_DestroyParserLinenumber(struct AlgodalParser_Linenumber * AlgodalParser_ParserLinenumber)
{
    Linenumber_destroy(AlgodalParser_ParserLinenumber->linenumber);
    free(AlgodalParser_ParserLinenumber->lines);
    free(AlgodalParser_ParserLinenumber);
}
inline static void getlinenumber(struct AlgodalParser_Linenumber * AlgodalParser_ParserLinenumber, uint32_t offset, uint32_t* linePtr, uint32_t* colPtr)
{
    for(uint32_t i = 0; i < AlgodalParser_ParserLinenumber->numberOfLines - 1; i++)
    {
        if(offset >= AlgodalParser_ParserLinenumber->lines[i].offset && offset < AlgodalParser_ParserLinenumber->lines[i+1].offset)
        {
            *linePtr = 1 + i;
            *colPtr  = 1 + (offset - AlgodalParser_ParserLinenumber->lines[i].offset);
            return;
        }
        else 
        if(offset == AlgodalParser_ParserLinenumber->lines[i+1].offset)
        {
            *linePtr = 1 + i + 1;
            *colPtr  = 1;
            return;
        }
    }
    if(AlgodalParser_ParserLinenumber->numberOfLines)
    {
        *linePtr = AlgodalParser_ParserLinenumber->numberOfLines;
        *colPtr  = 1 + (offset - AlgodalParser_ParserLinenumber->lines[AlgodalParser_ParserLinenumber->numberOfLines - 1].offset); 
    }
}
const char* GetLn(struct AlgodalParser_Linenumber *AlgodalParser_ParserLinenumber, uint32_t offset, char *buffer)
{
    if(AlgodalParser_ParserLinenumber && AlgodalParser_ParserLinenumber->linenumber && AlgodalParser_ParserLinenumber->linenumber->metric.bufferUpdates)
    {
        uint32_t line = 1, col = 1;
        getlinenumber(AlgodalParser_ParserLinenumber, offset, &line, &col);
        cwpc_sprintf(buffer, "%d.%d", line, col);
    }
    else
    {
        cwpc_sprintf(buffer, "(%d)", offset);
    }
    return buffer;
}
void GetLnInt(struct AlgodalParser_Linenumber *AlgodalParser_ParserLinenumber, uint32_t offset, uint32_t *pl, uint32_t *pc)
{
    if(AlgodalParser_ParserLinenumber && AlgodalParser_ParserLinenumber->linenumber && AlgodalParser_ParserLinenumber->linenumber->metric.bufferUpdates)
    {
        uint32_t line = 1, col = 1;
        getlinenumber(AlgodalParser_ParserLinenumber, offset, &line, &col);
        if(pl) *pl = line;
        if(pc) *pc = col;
    }
}
#endif  
#ifndef SET_PARSER_SETTING  
#define SET_PARSER_SETTING
#define PARSER_STDERR stderr
#define PARSER_STDOUT stdout
#else
#ifndef PARSER_STDERR
#define PARSER_STDERR stderr
#endif 
#ifndef PARSER_STDOUT
#define PARSER_STDOUT stdout
#endif 
#endif 
struct ParserInput
{
    uint16_t       ID;
    uint16_t       IndexOfCode;
    union
    {
        const char*                       Chars;
        const struct AlgodalParser_Token* Tokens;
    };
    union 
    {
        uint32_t IndexOfChars;
        uint32_t IndexOfTokens;
        uint32_t Index;
    };
    union 
    {
        uint32_t SizeOfChars;
        uint32_t SizeOfTokens;
    };
    const char * LastActionName;
    struct AlgodalParser_Token LastToken;
    const char * refOfText;
    int8_t priority;
};
struct ParserOutput
{
    uint16_t ID;
    union 
    {
        uint32_t IndexOfChars;
        uint32_t IndexOfTokens;
    };
    uint16_t     NextIndexOfCode;
    uint32_t     Size;
    uint32_t     Flags;
    uint8_t      ZeroCountResult;  
    struct AlgodalParser_Token LastToken;
    int8_t       priority;
    uint16_t     value_duplicated;
    uint16_t     value_current;
};
struct AnalyzeExtra
{
    uint32_t FurthestTokenQueryIndex;
};
struct TokenizeExtra
{
};
static void PrintTokenizeParserError(struct AlgodalParser_Program Program, struct AlgodalParser_Error error, struct AlgodalParser_Linenumber *AlgodalParser_ParserLinenumber)
{
    (void)Program;
    char lineBuffer1[64], lineBuffer2[64];
    if(error.flags & ALGODAL_PARSING_FAIL)
    {
        cwpc_fprintf(PARSER_STDERR, "\033[31;1m%s: failed to tokenize text at %s - %s\033[0m\n", Program.NameOfParser, GetLn(AlgodalParser_ParserLinenumber, error.index, lineBuffer1), GetLn(AlgodalParser_ParserLinenumber, error.index2, lineBuffer2));
    }
    if(error.flags & ALGODAL_PARSING_DUP)
    {
        char * tok1 = Program.Strings[Program.Actions[Program.Tokenizers[error.user.value].indexOfAction].indexOfString].text;
        char * tok2 = Program.Strings[Program.Actions[Program.Tokenizers[error.user.extravalue].indexOfAction].indexOfString].text;
        cwpc_fprintf(PARSER_STDERR, "\033[31;1m%s: multiple non-discarded tokenizers returned equal tokens at %s - %s: `%s`, `%s`\033[0m\n", Program.NameOfParser, GetLn(AlgodalParser_ParserLinenumber, error.index, lineBuffer1), GetLn(AlgodalParser_ParserLinenumber, error.index2, lineBuffer2), tok1, tok2);
    }
    if(error.flags & ALGODAL_PARSING_ERROR)
    {
        cwpc_fprintf(PARSER_STDERR, "\033[31;1m%s: undefined tokenization error occurred at %s - %s\033[0m\n", Program.NameOfParser, GetLn(AlgodalParser_ParserLinenumber, error.index, lineBuffer1), GetLn(AlgodalParser_ParserLinenumber, error.index2, lineBuffer2));
    }
}
static void PrintAnalyzeParserError(struct AlgodalParser_Program Program, struct AlgodalParser_Error error, struct AlgodalParser_Linenumber *AlgodalParser_ParserLinenumber)
{
    (void)Program;
    char lineBuffer1[64], lineBuffer2[64];
    if(error.flags & ALGODAL_PARSING_FAIL)
    {
        cwpc_fprintf(PARSER_STDERR, "\033[31;1m%s: failed to analyze tokens at %s - %s\033[0m\n", Program.NameOfParser, GetLn(AlgodalParser_ParserLinenumber, error.index, lineBuffer1), GetLn(AlgodalParser_ParserLinenumber, error.index2, lineBuffer2));
    }
    if(error.flags & ALGODAL_PARSING_DUP)
    {
        cwpc_fprintf(PARSER_STDERR, "\033[31;1m%s: multiple analyzers returned equal nodes at %s - %s\033[0m\n", Program.NameOfParser, GetLn(AlgodalParser_ParserLinenumber, error.index, lineBuffer1), GetLn(AlgodalParser_ParserLinenumber, error.index2, lineBuffer2));
    }
    if(error.flags & ALGODAL_PARSING_EOI)
    {
        cwpc_fprintf(PARSER_STDERR, "\033[31;1m%s: not all tokens were parsed at %s - %s\033[0m\n", Program.NameOfParser, GetLn(AlgodalParser_ParserLinenumber, error.index, lineBuffer1), GetLn(AlgodalParser_ParserLinenumber, error.index2, lineBuffer2));
    }
    if(error.flags & ALGODAL_PARSING_ERROR)
    {
        cwpc_fprintf(PARSER_STDERR, "\033[31;1m%s: undefined analyzation error occurred at %s - %s\033[0m\n", Program.NameOfParser, GetLn(AlgodalParser_ParserLinenumber, error.index, lineBuffer1), GetLn(AlgodalParser_ParserLinenumber, error.index2, lineBuffer2));
    }
}
inline static int CharsAvailable(struct ParserInput Input)
{
    return Input.IndexOfChars < Input.SizeOfChars;
}
inline static int TokensAvailable(struct ParserInput Input)
{
    return Input.IndexOfTokens < Input.SizeOfTokens;
}
inline static int CharsAvailableAtleast(struct ParserInput Input, unsigned int amount)
{
    return (Input.IndexOfChars + amount) <= Input.SizeOfChars;
}
inline static int TokensAvailableAtleast(struct ParserInput Input, unsigned int amount)
{
    return (Input.IndexOfTokens + amount) <= Input.SizeOfTokens;
}
inline static struct ParserOutput AddOutputOutput(struct ParserOutput output, struct ParserOutput item)
{
    output.Size  += item.Size;
    output.Flags |= item.Flags;
    output.ZeroCountResult = item.ZeroCountResult;
    return output;
}
inline static struct ParserOutput AndOutputOutput(struct ParserOutput Prev, struct ParserOutput New)
{
    struct ParserOutput andoutput = {};
    if(Prev.Flags == 0 && New.Flags == 0)
    {
        if(Prev.Size > 0 && New.Size > 0)
        {
            andoutput.Size = 1;
        }
        return andoutput;
    }
    if(Prev.Flags != 0) return Prev;
    return New;
}
inline static struct ParserOutput NotOutput(struct ParserOutput output)
{
    struct ParserOutput notoutput = {};
    if(output.Flags == 0)
    {
        if(output.Size)
        {
            return notoutput;
        }
        if(output.ZeroCountResult)
        {
            return notoutput;
        }
        notoutput.Size = 1;
        return notoutput;
    }
    return output;
}
inline static struct ParserOutput GetMaxOutput(struct AlgodalParser_Program Program, struct ParserOutput *addr, uint16_t size, uint8_t addFlags)
{
    struct ParserOutput output = addr[0];
    uint8_t dup = 0;
    uint16_t flag = Program.Tokenizers[0].flag;
    for(uint16_t i = 1; i < size; i++)
    {
        if(addr[i].Size > output.Size && addr[i].Flags <= output.Flags)
        {
            output = addr[i];
            output.value_current = i;
            dup = 0;
            flag = Program.Tokenizers[i].flag;
        }
        else
        if(addr[i].Size == output.Size && addr[i].Flags == output.Flags)
        {
            if(Program.Tokenizers[i].flag == 1)
            {
                continue;
            }
            if(flag == 1)
            {
                output = addr[i];
                output.value_current = i;
                dup = 0;
                flag = Program.Tokenizers[i].flag;
                continue;
            }
            if(addr[i].priority > output.priority)
            {
                output = addr[i];
                output.value_current = i;
                dup = 0;
                flag = Program.Tokenizers[i].flag;
                continue;
            }
            else
            if(addr[i].priority == output.priority)
            {
                if(output.Size == 0)
                {
                    if(addr[i].ZeroCountResult > output.ZeroCountResult)
                    {
                        output = addr[i];
                        output.value_current = i;
                        dup = 0;
                        flag = Program.Tokenizers[i].flag;
                        continue;
                    }
                    else
                    if(addr[i].ZeroCountResult == output.ZeroCountResult)
                    {
                        dup = 1;
                        output.value_duplicated = i;
                        continue;
                    }
                }
                else
                {
                    dup = 1;
                    output.value_duplicated = i;
                    continue;
                }                
            }
        }
    }
    if(addFlags)
    {
        if(output.Size > 0 && dup)
        {
            output.Flags |= ALGODAL_PARSING_DUP;
        }
    }
    return output;
}
inline static uint16_t GetMaxIndex(struct ParserOutput *addr, uint16_t size, struct ParserOutput * ret_output)
{
    struct ParserOutput output = addr[0];
    uint32_t index = 0;
    uint8_t dup = 0;
    for(uint16_t i = 1; i < size; i++)
    {
        if(addr[i].Size > output.Size && addr[i].Flags <= output.Flags)
        {
            output = addr[i];
            output.value_current = i;
            dup = 0;
            index = i;
            continue;
        }
        else
        if(addr[i].Size == output.Size && addr[i].Flags == output.Flags)
        {
            if(addr[i].priority > output.priority)
            {
                output = addr[i];
                output.value_current = i;
                dup = 0;
                index = i;
                continue;
            }
            else
            if(addr[i].priority == output.priority)
            {
                if(output.Size == 0)
                {
                    if(addr[i].ZeroCountResult > output.ZeroCountResult)
                    {
                        output = addr[i];
                        output.value_current = i;
                        dup = 0;
                        index = i;
                        continue;
                    }
                    else
                    if(addr[i].ZeroCountResult == output.ZeroCountResult)
                    {
                        dup = 1;
                        output.value_duplicated = i;
                        continue;
                    }   
                }
                else
                {
                    dup = 1;
                    output.value_duplicated = i;
                    continue;
                }             
            }
        }
    }
    if(output.Size > 0 && dup)
    {
        output.Flags |= ALGODAL_PARSING_DUP;
    }
    if(ret_output) *ret_output = output; 
    return index;
}
inline static utf8_unicode_t GetUnicode(struct ParserInput Input)
{
    if(CharsAvailable(Input))
    {
        return utf8_read(&Input.Chars[Input.IndexOfChars]);
    }
    return 0;
}
inline static utf8_unicode_t GetSizeOfUnicode(struct ParserInput Input)
{
    if(CharsAvailable(Input))
    {
        return utf8_get_unicode_size(utf8_read(&Input.Chars[Input.IndexOfChars]));
    }
    return 0;
}
inline static struct ParserInput RelateInputToAction(struct AlgodalParser_Program Program, struct ParserInput Input, uint32_t IndexOfAction)
{
    Input.IndexOfCode = Program.Actions[IndexOfAction].indexOfCode;
    #ifdef ALGODAL_PARSER_LOGGER_DEBUG
    Input.LastActionName = Program.Strings[Program.Actions[IndexOfAction].indexOfString].text;
    #endif
    return Input;
}
inline static int CanContinue(struct ParserOutput output)
{
    return (output.Flags == 0 && output.Size > 0) || (output.Flags == 0 && output.ZeroCountResult > 0);
}
inline static int CanContinueBySizeOnly(struct ParserOutput output)
{
    return output.Flags == 0 && output.Size > 0;
}
inline static void UpdateAnalyzeExtraFurthestTokenQueryIndex(struct AnalyzeExtra *PtrOfExtra, struct ParserInput Input)
{
    if(PtrOfExtra->FurthestTokenQueryIndex < Input.IndexOfTokens)
    {
        PtrOfExtra->FurthestTokenQueryIndex = Input.IndexOfTokens;
    }
}
inline static int8_t equal(uint8_t icase, utf8_unicode_t A, utf8_unicode_t B)
{
    if(icase)
    {
        return tolower(A) == tolower(B);
    }
    return A == B;
}
inline static int sort_fn(const void* A, const void* B)
{
    return *(char*)A - *(char*)B;
}
inline static int sort_fn_icase(const void* A, const void* B)
{
    return tolower(*(char*)A) - tolower(*(char*)B);
}
inline static uint32_t Order
(
    struct ParserInput input,
    uint8_t icase, 
    struct AlgodalParser_String string
)
{
    if(CharsAvailableAtleast(input, string.length))
    {
        char textstr[string.length + 1];
        char copystr[string.length + 1];
        memcpy(textstr, &input.Chars[input.IndexOfChars], string.length);
        memcpy(copystr, string.text, string.length);
        textstr[string.length] = 0;
        copystr[string.length] = 0;
        if(icase)
        {
            qsort(textstr, string.length, sizeof(char), sort_fn_icase);
            qsort(copystr, string.length, sizeof(char), sort_fn_icase);
            if(strcmpnc(textstr, copystr) == 0)
            {
                return string.length;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            qsort(textstr, string.length, sizeof(char), sort_fn);
            qsort(copystr, string.length, sizeof(char), sort_fn);
            if(strcmp(textstr, copystr) == 0)
            {
                return string.length;
            }
            else
            {
                return 0;
            }
        }
    }
    return 0;
}
inline static uint32_t Exact
(
    struct ParserInput input,  
    uint8_t icase, 
    struct AlgodalParser_String string
)
{
    if(CharsAvailableAtleast(input, string.length))
    {
        size_t offset = 0;
        while(offset < string.length && (offset + input.IndexOfChars) < input.SizeOfChars )
        {
            const utf8_unicode_t stringcode = utf8_read(&string.text[offset]);
            const utf8_unicode_t textcode = utf8_read(&input.Chars[input.IndexOfChars + offset]);
            const size_t size = utf8_get_unicode_size(stringcode);
            if(equal(icase, textcode, stringcode) == 0)
            {
                return 0;
            }
            offset += size;
        }
        int flag = offset == string.length;
        return  flag ? string.length : 0;
    }
    return 0;
}
inline static uint32_t Oneof
(
    struct ParserInput input, 
    uint8_t icase, 
    struct AlgodalParser_String string
)
{
    if(CharsAvailable(input))
    {
        const utf8_unicode_t textcode = utf8_read(&input.Chars[input.IndexOfChars]);
        size_t offset = 0;
        while(offset < string.length)
        {
            const utf8_unicode_t stringcode = utf8_read(&string.text[offset]);
            const size_t size = utf8_get_unicode_size(stringcode);
            if(equal(icase, textcode, stringcode))
            {
                return size;
            }
            offset += size;
        }
    }
    return 0;
}
inline static uint32_t Previous
(
    struct ParserInput input,  
    uint16_t id
)
{
    uint32_t flag = input.LastToken.id == id ? 1 : 0;
    return flag;
}
inline static uint32_t CompareCharRange
(
    struct ParserInput input,  
    unsigned int leftmost,
    unsigned int rightmost
)
{
    const utf8_unicode_t textcode = utf8_read(&input.Chars[input.IndexOfChars]);
    const size_t size = utf8_get_unicode_size(textcode);
    int flag = rightmost?(textcode >= leftmost && textcode <= rightmost):(textcode == leftmost);
    return flag ? size : 0;
}
inline static uint32_t CompareSizeRange
(
    struct ParserInput input,  
    unsigned int size,
    unsigned int leftmost,
    unsigned int rightmost
)
{
    const utf8_unicode_t textcode = utf8_read(&input.refOfText[input.IndexOfChars]);
    const size_t textsize = utf8_get_unicode_size(textcode);
    if(size == textsize)
    {
        int flag = rightmost?(textcode >= leftmost && textcode <= rightmost):(textcode == leftmost);
        return flag ? size : 0;
    }
    return 0;
}
inline static uint32_t CompareSizeString
(
    struct AlgodalParser_Program program,
    struct ParserInput input,  
    unsigned int size,
    unsigned int id_string,
    int icase
)
{
    if(size != program.Strings[id_string].length) return 0;
    char parsedstring[size + 1];
    memset(parsedstring, 0, size + 1);
    memcpy(parsedstring, &input.refOfText[input.IndexOfChars], size);
    const char * string = program.Strings[id_string].text;
    int flag = icase?strcmpnc(parsedstring, string)==0:strcmp(parsedstring, string)==0;
    return flag?size:0;
}
inline static uint32_t CompareSizeStringLength
(
    struct AlgodalParser_Program program,
    struct ParserInput input,  
    unsigned int size,
    unsigned int id_string,
    int icase,
    unsigned int length
)
{
    if(size < length || length > program.Strings[id_string].length) return 0;
    char parsedstring[length + 1];
    memset(parsedstring, 0, length + 1);
    memcpy(parsedstring, &input.refOfText[input.IndexOfChars], length);
    char comparestring[length + 1];
    memset(comparestring, 0, length + 1);
    memcpy(comparestring, program.Strings[id_string].text, length);
    int flag = icase?strcmpnc(parsedstring, comparestring)==0:strcmp(parsedstring, comparestring)==0;
    return flag?size:0;
}
inline static struct ParserOutput Nullify(struct ParserOutput output)
{
    unsigned int size = output.Size;
    output.Size = 0;
    output.ZeroCountResult = size?1:output.ZeroCountResult;
    return output;
}
static struct ParserOutput GetTokenizeOutput(struct AlgodalParser_Program Program, struct ParserInput Input, struct TokenizeExtra *PtrOfExtra)
{
    VMINFO("--------------------------------\n");
    struct ParserOutput Output =
    {
        .ID              = Input.ID,
        .IndexOfChars    = Input.IndexOfChars,
        .NextIndexOfCode = Input.IndexOfCode,        
        .LastToken       = Input.LastToken
    };
    do
    {
        const uint8_t opcode = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
        switch(opcode)
        {
            case ALGPAR_OP_OPT: {
                const uint16_t  countOfOption = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  offsetCode    = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  firstMode     = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  nextCode      = offsetCode + Input.IndexOfCode;
                struct ParserOutput optionOutput[countOfOption];
                memset(optionOutput, 0, sizeof(struct ParserOutput) * countOfOption);
                for(uint16_t i = 0; i < countOfOption; i++)
                {
                    VMLOG_BRAN(ALGPAR_OP_OPT, Input, Output);
                    optionOutput[i] = GetTokenizeOutput(Program, Input, PtrOfExtra);
                    Input.IndexOfCode = optionOutput[i].NextIndexOfCode;
                    if(firstMode && !optionOutput[i].Flags && optionOutput[i].Size) break;
                }
                Input.IndexOfCode = nextCode;
                Output = AddOutputOutput(Output, GetMaxOutput(Program, optionOutput, countOfOption, 1));
                VMLOG_PROC(ALGPAR_OP_OPT, Input, Output);    
                continue;
            } break;
            case ALGPAR_OP_SER: {
                const uint16_t  countOfSerial = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  offsetCode    = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  nextCode      = offsetCode + Input.IndexOfCode;
                struct ParserOutput sumOutput = Output;
                struct ParserOutput iterOutput;
                for(uint16_t i = 0; i < countOfSerial; i++)
                {
                    VMLOG_BRAN(ALGPAR_OP_SER, Input, Output);
                    iterOutput = GetTokenizeOutput(Program, Input, PtrOfExtra);
                    if(CanContinue(iterOutput))
                    {
                        Input.IndexOfChars += iterOutput.Size;
                        sumOutput = AddOutputOutput(sumOutput, iterOutput);
                        Input.IndexOfCode = iterOutput.NextIndexOfCode;
                    }
                    else
                    {
                        goto TOKEN_SER_EXIT;
                    }
                }
                Output = sumOutput;
                TOKEN_SER_EXIT:
                Input.IndexOfCode = nextCode;
                VMLOG_PROC(ALGPAR_OP_SER, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_AND: {
                const uint16_t  countOfItem   = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  offsetCode    = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  nextCode      = offsetCode + Input.IndexOfCode;
                struct ParserOutput output_and = {.Size = 1};
                for(uint16_t i = 0; i < countOfItem; i++)
                {
                    VMLOG_BRAN(ALGPAR_OP_AND, Input, Output);
                    struct ParserOutput output_item = GetTokenizeOutput(Program, Input, PtrOfExtra);
                    output_and = AndOutputOutput(output_and, output_item);
                    if(CanContinue(output_and))
                    {
                        Input.IndexOfCode = output_item.NextIndexOfCode;
                    }
                    else
                    {
                        goto TOKEN_AND_EXIT;
                    }
                }
                Output = AddOutputOutput(Output, output_and);
                TOKEN_AND_EXIT:
                Input.IndexOfCode = nextCode;
                VMLOG_PROC(ALGPAR_OP_AND, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_NOT: {
                const uint16_t  offsetCode    = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  nextCode      = offsetCode + Input.IndexOfCode;
                struct ParserOutput output_not;
                VMLOG_BRAN(ALGPAR_OP_NOT, Input, Output);
                struct ParserOutput output_item = GetTokenizeOutput(Program, Input, PtrOfExtra);
                output_not = NotOutput(output_item);
                if(CanContinue(output_not))
                {
                    Input.IndexOfCode = output_item.NextIndexOfCode;
                }
                else
                {
                    goto TOKEN_NOT_EXIT;
                }
                Output = AddOutputOutput(Output, output_not);
                TOKEN_NOT_EXIT:
                Input.IndexOfCode = nextCode;
                VMLOG_PROC(ALGPAR_OP_NOT, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_NUL: {
                const uint16_t offsetCode = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t nextCode   = offsetCode + Input.IndexOfCode;
                VMLOG_BRAN(ALGPAR_OP_NUL, Input, Output);
                struct ParserOutput output_item = Nullify(GetTokenizeOutput(Program, Input, PtrOfExtra));
                Output = AddOutputOutput(Output, output_item);
                Input.IndexOfCode = nextCode;
                VMLOG_PROC(ALGPAR_OP_NUL, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_CNT: {
                const uint32_t begin      = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t begin2     = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t offsetCode = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t nextCode   = offsetCode + Input.IndexOfCode;
                const uint32_t end        = (begin2 > begin) ? begin2 - begin : 0;
                struct ParserOutput reqOutput  = Output;
                struct ParserOutput iterOutput;
                if(!(begin == 0 && end == 0))
                {
                    uint32_t count = 0;
                    if(begin)
                    {
                        do
                        {
                            VMLOG_BRAN(ALGPAR_OP_CNT, Input, Output);
                            iterOutput = GetTokenizeOutput(Program, Input, PtrOfExtra);
                            if(CanContinueBySizeOnly(iterOutput))
                            {
                                Input.IndexOfChars += iterOutput.Size;
                                reqOutput = AddOutputOutput(reqOutput, iterOutput);
                            }
                            else
                            {
                                break;
                            }
                            count++;
                        } while(count < begin);
                    }
                    if(count == begin)
                    {
                        Output = reqOutput;
                        if(!reqOutput.Flags && end && CharsAvailable(Input))
                        {
                            uint32_t count = 0;
                            do
                            {
                                VMLOG_BRAN(ALGPAR_OP_CNT, Input, Output);
                                iterOutput = GetTokenizeOutput(Program, Input, PtrOfExtra);
                                if(CanContinueBySizeOnly(iterOutput))
                                {
                                    Input.IndexOfChars += iterOutput.Size;
                                    Output = AddOutputOutput(Output, iterOutput);
                                }
                                else
                                {
                                    break;
                                }
                                count++;
                            } while(count < end && CharsAvailable(Input));
                        }
                    }                    
                }
                Input.IndexOfCode = nextCode;
                Output.ZeroCountResult = begin == 0;                
                VMLOG_PROC(ALGPAR_OP_CNT, Input, Output);              
                continue;
            } break;
            case ALGPAR_OP_PNT: {
                const uint16_t index = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                VMLOG_BRAN(ALGPAR_OP_PNT, Input, Output);
                Output = AddOutputOutput(Output, GetTokenizeOutput(Program, RelateInputToAction(Program, Input, index), PtrOfExtra));
                VMLOG_PROC(ALGPAR_OP_PNT, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_ZPR: {
                const uint16_t index_action = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t leftmost = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t rightmost = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                VMLOG_BRAN(ALGPAR_OP_ZPR, Input, Output);
                struct ParserOutput output_action = GetTokenizeOutput(Program, RelateInputToAction(Program, Input, index_action), PtrOfExtra);
                if(CanContinue(output_action))
                {
                    const uint32_t termSize = CompareSizeRange(Input, output_action.Size, leftmost, rightmost);
                    Output.Size += termSize;
                }                
                VMLOG_PROC(ALGPAR_OP_ZPR, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_ZPS: {
                const uint16_t index_action = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t id_string = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const int8_t icase = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                VMLOG_BRAN(ALGPAR_OP_ZPR, Input, Output);
                struct ParserOutput output_action = GetTokenizeOutput(Program, RelateInputToAction(Program, Input, index_action), PtrOfExtra);
                if(CanContinue(output_action))
                {
                    const uint32_t termSize = CompareSizeString(Program, Input, output_action.Size, id_string, icase);
                    Output.Size += termSize;
                }                
                VMLOG_PROC(ALGPAR_OP_ZPS, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_ZPN: {
                const uint16_t index_action = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t id_string = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const int8_t icase = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t length = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                VMLOG_BRAN(ALGPAR_OP_ZPN, Input, Output);
                struct ParserOutput output_action = GetTokenizeOutput(Program, RelateInputToAction(Program, Input, index_action), PtrOfExtra);
                if(CanContinue(output_action))
                {
                    const uint32_t termSize = CompareSizeStringLength(Program, Input, output_action.Size, id_string, icase, length);
                    Output.Size += termSize;
                }                
                VMLOG_PROC(ALGPAR_OP_ZPN, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_ORD: {
                const uint8_t icase = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t index = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const struct AlgodalParser_String string = Program.Strings[index];
                uint32_t termSize = Order(Input, icase, string);
                Output.Size += termSize;
                VMLOG_PROC(ALGPAR_OP_ORD, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_EXT: {
                const uint8_t icase = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t index = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const struct AlgodalParser_String string = Program.Strings[index];
                const uint32_t termSize = Exact(Input, icase, string);
                Output.Size += termSize;
                VMLOG_PROC(ALGPAR_OP_EXT, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_ONE: {
                const uint8_t icase = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t index = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const struct AlgodalParser_String string = Program.Strings[index];
                Output.Size += Oneof(Input, icase, string);
                VMLOG_PROC(ALGPAR_OP_ONE, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_CHR: {
                utf8_unicode_t unicode = GetUnicode(Input);
                Output.Size += unicode ? utf8_get_unicode_size(unicode) : 0;
                VMLOG_PROC(ALGPAR_OP_CHR, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_RET: {
                VMLOG_PROC(ALGPAR_OP_RET, Input, Output);
                goto EXIT;
            } break;
            case ALGPAR_OP_PRV: {
                const uint16_t id = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                Output.ZeroCountResult = Previous(Input, id);
                VMLOG_PROC(ALGPAR_OP_PRV, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_ZCR: {
                const uint32_t leftmost = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t rightmost = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t termSize = CompareCharRange(Input, leftmost, rightmost);
                Output.Size += termSize;
                VMLOG_PROC(ALGPAR_OP_ZCR, Input, Output);
                continue;
            } break;
            default: {
                Output.Flags |= ALGODAL_PARSING_ERROR;
                VMLOG_PROC(0, Input, Output);
                goto EXIT;
            } break;
        }
    } 
    while(!Output.Flags);
    EXIT:
    Output.NextIndexOfCode = Input.IndexOfCode;
    Output.priority = Input.priority;
    return Output;
}
static struct ParserOutput GetMaxTokenizeOutput(struct AlgodalParser_Program Program, struct ParserInput Input, struct TokenizeExtra *PtrOfExtra)
{
    VMINFO("================================\n");
    struct ParserOutput outputs[Program.CountOfTokenizers];
    for(uint16_t i = 0; i < Program.CountOfTokenizers; i++)
    {
        if(Program.Tokenizers[i].flag == 3)
        {
            outputs[i] = (struct ParserOutput){0};
            continue;
        }
        struct ParserInput input = Input;
        input.ID = i;
        input.IndexOfCode = Program.Actions[Program.Tokenizers[i].indexOfAction].indexOfCode;
        input.priority = Program.Tokenizers[i].priority;
        #ifdef ALGODAL_PARSER_LOGGER_DEBUG
        input.LastActionName = Program.Strings[Program.Actions[Program.Tokenizers[i].indexOfAction].indexOfString].text;
        #endif
        outputs[i] = GetTokenizeOutput(Program, input, PtrOfExtra);
    }
    return GetMaxOutput(Program, outputs, Program.CountOfTokenizers, 1);
}
inline static struct AlgodalParser_Token TokenFromOutput(struct ParserOutput Output)
{
    return (struct AlgodalParser_Token) {
        .id    = Output.ID,
        .index = Output.IndexOfChars,
        .size  = Output.Size
    };
}
static void TokenizeResultAddOutput(struct AlgodalParser_Program Program, struct AlgodalParser_TokenizeResult* ptr, struct ParserOutput output, uint32_t offset, size_t size, struct TokenizeExtra *ptrOfExtra, struct AlgodalParser_Token *returnLastToken)
{
    (void)ptrOfExtra;
    if(output.Flags == 0 && output.Size == 0) output.Flags |= ALGODAL_PARSING_FAIL;
    if(output.Flags)
    {
        ptr->error.flags = output.Flags;
        ptr->error.index = offset;
        ptr->error.index2 = clamp_index(ptr->error.index + output.Size, size);
        ptr->error.user.value = output.value_current;
        ptr->error.user.extravalue = output.value_duplicated;
        return;
    }
    struct AlgodalParser_Token token = TokenFromOutput(output);
    switch(Program.Tokenizers[token.id].flag)
    {
        case 1:
            return;
        break;
        case 2:
            if(output.LastToken.id == token.id) return;
        break;
    }
    const uint32_t index = ptr->tokens.size ++;
    ptr->tokens.addr = (struct AlgodalParser_Token *)realloc(ptr->tokens.addr, sizeof(struct AlgodalParser_Token) * ptr->tokens.size);
    ptr->tokens.addr[index] = token;
    returnLastToken[0] = token;
}
struct AlgodalParser_TokenizeResult AlgodalParser_GetTokenizeResult(struct AlgodalParser_Program Program, const char* text, const uint32_t size, struct AlgodalParser_OtherTokenizeParams* oparams)
{
    VMINFO("\nTOKENIZATION VIRTUAL MACHINE LOG\n");
    (void)oparams;
    struct AlgodalParser_TokenizeResult TokenizeResult = {};
    uint32_t index = 0;
    struct ParserInput Input =
    {
        .Chars = text, 
        .SizeOfChars = size,
        .LastToken = {.id = UINT16_MAX}, 
        .refOfText = text
    };
    while(index < size)
    {
        Input.IndexOfChars = index;
        struct TokenizeExtra extra = {};
        struct ParserOutput Output = GetMaxTokenizeOutput(Program, Input, &extra);
        TokenizeResultAddOutput(Program, &TokenizeResult, Output, index, size, &extra, &Input.LastToken);
        if(TokenizeResult.error.flags) break;
        index += Output.Size;
    }
    return TokenizeResult;
}
const char * AlgodalParser_GetTokenizerString_READONLY(struct AlgodalParser_Program program, unsigned int id)
{
    return program.Strings[program.Actions[program.Tokenizers[id].indexOfAction].indexOfString].text;
}
void AlgodalParser_GetTokenKey(struct AlgodalParser_Program program, struct AlgodalParser_Token token, unsigned int size, char *r_key)
{
    if(size) strncpy(r_key, AlgodalParser_GetTokenizerString_READONLY(program, token.id), size);
    else strcpy(r_key, AlgodalParser_GetTokenizerString_READONLY(program, token.id));
}
void AlgodalParser_GetTokenValue(const char* text, struct AlgodalParser_Token token, char *r_value)
{
    if(token.size > 0)
    {
        memcpy(r_value, &text[token.index], token.size);
        for(uint32_t i = 0; i < token.size; i++)
        {
            if(r_value[i] == '\n') r_value[i] = '\t';
        }
    }
}
static char * HorizontSpaceString(char * string)
{
    unsigned int i = 0;
    while(string[i] != 0) 
    {
        if(string[i] == '\r') string[i] = ' ';
        if(string[i] == '\n') string[i] = ' ';
        if(string[i] == '\t') string[i] = ' ';
        i++;
    }
    return string;
}
static void PrintToken(struct AlgodalParser_Program program, const char* text, struct AlgodalParser_Linenumber *AlgodalParser_ParserLinenumber, struct AlgodalParser_Token token)
{
    char lineBuffer[512] = {};
    cwpc_fprintf(PARSER_STDOUT, "%s ", GetLn(AlgodalParser_ParserLinenumber, token.index, lineBuffer));
    char key[1024] = {};
    const char * readonlykey = AlgodalParser_GetTokenizerString_READONLY(program, token.id);
    memcpy(key, readonlykey, strlen(readonlykey));
    cwpc_fprintf(PARSER_STDOUT, "%s ", HorizontSpaceString(key));
    if(program.Tokenizers[token.id].flag != 3 && program.Tokenizers[token.id].type != 0 && token.size > 0)
    {
        cwpc_fprintf(PARSER_STDOUT, ": ");
        char value[token.size + 1];
        memset(value, 0, token.size + 1);
        AlgodalParser_GetTokenValue(text, token, value);
        cwpc_fprintf(PARSER_STDOUT, "%s", HorizontSpaceString(value));
    }
    cwpc_fprintf(PARSER_STDOUT, "\n");
}
void AlgodalParser_PrintTokenizeResult(struct AlgodalParser_Program program, struct AlgodalParser_TokenizeResult TokenizeResult, const char* text, struct AlgodalParser_Linenumber *AlgodalParser_ParserLinenumber)
{
    for(uint32_t i = 0; i < TokenizeResult.tokens.size; i++)
    {
        struct AlgodalParser_Token token = TokenizeResult.tokens.addr[i];
        PrintToken(program, text, AlgodalParser_ParserLinenumber, token);
    }
    PrintTokenizeParserError(program, TokenizeResult.error, AlgodalParser_ParserLinenumber);
}
inline static int8_t GetObjectpointPriority(struct AlgodalParser_Program Program, uint16_t indexOfAction)
{
    for(uint16_t i = 0; i < Program.CountOfObjectpoints; i++)
    {
        if(Program.Objectpoints[i].indexOfAction == indexOfAction) return Program.Objectpoints[i].priority;
    }
    return 0;
}
inline static int8_t GetObjectpointFlag(struct AlgodalParser_Program Program, uint16_t indexOfAction)
{
    for(uint16_t i = 0; i < Program.CountOfObjectpoints; i++)
    {
        if(Program.Objectpoints[i].indexOfAction == indexOfAction) return Program.Objectpoints[i].flag;
    }
    return 0;
}
inline static int IsObjectpoint(struct AlgodalParser_Program Program, uint16_t indexOfAction, uint8_t terminal)
{
    for(uint16_t i = 0; i < Program.CountOfObjectpoints; i++)
    {
        if(Program.Objectpoints[i].type == terminal && Program.Objectpoints[i].indexOfAction == indexOfAction) return 1;
    }
    return 0;
}
inline static void AddChildrenNode(struct AlgodalParser_NodeChildren *children, struct AlgodalParser_Node *node)
{
    if(node)
    {
        if(node->invisible)
        {
            for(uint32_t i = 0; i < node->children.size; i++)
            {
                AddChildrenNode(children, node->children.addr[i]);
            }
            free(node->children.addr);
            free(node);
        }
        else
        {
            const uint32_t index = children->size ++;
            children->addr = (AlgodalParser_Node**)realloc(children->addr, sizeof(struct AlgodalParser_Node *) * children->size);
            children->addr[index] = node;
            if(index)
            {
                children->addr[index - 1]->sibling = node;
            }
        }
    }
}
inline static struct AlgodalParser_Node *AddNodeNode(struct AlgodalParser_Node **ptrOfNode, struct AlgodalParser_Node *node)
{
    if(ptrOfNode)
    {
        if(node)
        {
            if(*ptrOfNode)
            {
                AddChildrenNode(&(*ptrOfNode)->children, node); 
            }
            else
            {
                *ptrOfNode = node;
            }
        }
        return *ptrOfNode;
    }
    return 0;
}
inline static struct AlgodalParser_Node *CreateNode(struct AlgodalParser_Program Program, uint32_t Index, uint32_t Size, uint16_t indexOfAction, uint8_t terminal)
{
    if(IsObjectpoint(Program, indexOfAction, terminal))
    {
        if(Size)
        {
            struct AlgodalParser_Node *node = (AlgodalParser_Node *)malloc(sizeof(struct AlgodalParser_Node));
            memset(node, 0, sizeof(struct AlgodalParser_Node));
            node->indexOfAction = indexOfAction;
            node->size = Size;
            node->indexOfToken = Index;
            node->terminal = terminal;
            return node;
        }
    }
    return 0;
}
inline static struct AlgodalParser_Node *CreateInvisibleNode()
{
    struct AlgodalParser_Node *node = (struct AlgodalParser_Node *)malloc(sizeof(struct AlgodalParser_Node));
    memset(node, 0, sizeof(struct AlgodalParser_Node));
    node->invisible = 1;
    return node;
}
inline static void DestroyNode(struct AlgodalParser_Node **ptrOfNode)
{
    if(*ptrOfNode)
    {
        for(uint32_t i = 0; i < (*ptrOfNode)->children.size; i++)
        {
            DestroyNode(&(*ptrOfNode)->children.addr[i]);
        }
        free((*ptrOfNode)->children.addr);
        free(*ptrOfNode);
        *ptrOfNode = 0;
    }
}
inline static struct AlgodalParser_Node *SelectNode(struct AlgodalParser_Node *addr[], uint16_t size, uint16_t indexOfSelected)
{
    for(uint16_t i = 0; i < size; i++)
    {
        if(i != indexOfSelected) DestroyNode(&addr[i]);
    }
    return addr[indexOfSelected];
}
inline static uint8_t Term
(
    struct AlgodalParser_Program Program,
    struct ParserInput input, 
    uint16_t id
)
{
    (void)Program;
    int8_t flag = input.Tokens[input.IndexOfTokens].id == id;
    return flag ? 1 : 0;
}
inline static uint32_t CompareTermRange
(
    struct AlgodalParser_Program Program,
    struct ParserInput input,  
    unsigned int id,
    unsigned int leftmost,
    unsigned int rightmost
)
{
    int8_t opsize = Term(Program, input, id);
    if(opsize == 0) return 0;
    struct AlgodalParser_Token token = input.Tokens[input.IndexOfTokens];
    const utf8_unicode_t textcode = utf8_read(&input.refOfText[token.index]);
    const size_t textsize = utf8_get_unicode_size(textcode);
    const size_t remaindingsize = token.size - textsize;
    if(remaindingsize != 0) return 0;
    int flag = rightmost?(textcode >= leftmost && textcode <= rightmost):(textcode == leftmost); 
    return flag ? opsize : 0;
}
inline static uint32_t CompareTermString
(
    struct AlgodalParser_Program Program,
    struct ParserInput input,  
    unsigned int id,
    unsigned int id_string,
    int icase
)
{
    int8_t opsize = Term(Program, input, id);
    if(opsize == 0) return 0;
    struct AlgodalParser_Token token = input.Tokens[input.IndexOfTokens];
    char string_token[token.size + 1];
    memset(string_token, 0, token.size + 1);
    memcpy(string_token, &input.refOfText[token.index], token.size);
    const char * string = Program.Strings[id_string].text;
    int flag = icase?strcmpnc(string_token, string)==0:strcmp(string_token, string)==0;
    return flag?opsize:0;
}
inline static uint32_t CompareTermStringLength
(
    struct AlgodalParser_Program Program,
    struct ParserInput input,  
    unsigned int id,
    unsigned int id_string,
    int icase,
    unsigned int length
)
{
    int8_t opsize = Term(Program, input, id);
    if(opsize == 0 || length > input.Tokens[id].size) return 0;
    struct AlgodalParser_Token token = input.Tokens[input.IndexOfTokens];
    char string_token[length + 1];
    memset(string_token, 0, length + 1);
    memcpy(string_token, &input.refOfText[token.index], length);
    char string_compare[length + 1];
    memset(string_compare, 0, length + 1);
    memcpy(string_compare, Program.Strings[id_string].text, length);
    int flag = icase?strcmpnc(string_token, string_compare)==0:strcmp(string_token, string_compare)==0;
    return flag?opsize:0;
}
static struct ParserOutput GetAnalyzeOutput(struct AlgodalParser_Program Program, struct ParserInput Input, struct AlgodalParser_Node* *PtrOfNode, struct AnalyzeExtra *PtrOfExtra)
{
    VMINFO("--------------------------------\n");
    struct ParserOutput Output =
    {
        .ID              = Input.ID,
        .IndexOfTokens   = Input.IndexOfTokens,
        .NextIndexOfCode = Input.IndexOfCode
    };
    do
    {
        const uint8_t opcode = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
        switch(opcode)
        {
            case ALGPAR_OP_OPT: {
                const uint16_t  countOfOption = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  offsetCode    = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint8_t   firstMode     = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  nextCode      = offsetCode + Input.IndexOfCode;
                struct ParserOutput optionOutput[countOfOption];
                memset(optionOutput, 0, sizeof(struct ParserOutput) * countOfOption);
                struct AlgodalParser_Node *nodes[countOfOption];
                memset(nodes, 0, sizeof(struct AlgodalParser_Node *) * countOfOption);
                for(uint16_t i = 0; i < countOfOption; i++)
                {
                    VMLOG_BRAN(ALGPAR_OP_OPT, Input, Output);
                    optionOutput[i] = GetAnalyzeOutput(Program, Input, &nodes[i], PtrOfExtra);
                    Input.IndexOfCode = optionOutput[i].NextIndexOfCode;
                    if(firstMode && (optionOutput[i].Flags == 0 && optionOutput[i].Size > 0)) break;                    
                }
                Input.IndexOfCode = nextCode;
                struct ParserOutput output_selected = {};
                const uint16_t indexOfSelect = GetMaxIndex(optionOutput, countOfOption, &output_selected);
                Output = AddOutputOutput(Output,  output_selected);
                AddNodeNode(PtrOfNode, SelectNode(nodes, countOfOption, indexOfSelect));
                VMLOG_PROC(ALGPAR_OP_OPT, Input, Output); 
                continue;
            } break;
            case ALGPAR_OP_SCP: {
                const uint16_t offsetCode = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  nextCode      = offsetCode + Input.IndexOfCode;
                VMLOG_BRAN(ALGPAR_OP_SCP, Input, Output);
                struct ParserOutput output_option = GetAnalyzeOutput(Program, Input, 0, PtrOfExtra);
                Output = AddOutputOutput(Output, output_option);
                Input.IndexOfCode = nextCode;
                VMLOG_PROC(ALGPAR_OP_SCP, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_SER: {
                const uint16_t  countOfSerial = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  offsetCode    = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  nextCode      = offsetCode + Input.IndexOfCode;
                struct AlgodalParser_Node *node = CreateInvisibleNode();
                struct ParserOutput sumOutput = Output;
                struct ParserOutput iterOutput;
                for(uint16_t i = 0; i < countOfSerial; i++)
                {
                    VMLOG_BRAN(ALGPAR_OP_SER, Input, Output);
                    iterOutput = GetAnalyzeOutput(Program, Input, &node, PtrOfExtra);
                    if(CanContinue(iterOutput))
                    {
                        Input.IndexOfTokens += iterOutput.Size;
                        Input.IndexOfCode = iterOutput.NextIndexOfCode;
                        sumOutput = AddOutputOutput(sumOutput, iterOutput);
                    }
                    else
                    {
                        DestroyNode(&node);
                        goto NODE_SER_EXIT;
                    }
                }
                Output = sumOutput;
                NODE_SER_EXIT:
                Input.IndexOfCode = nextCode;
                UpdateAnalyzeExtraFurthestTokenQueryIndex(PtrOfExtra, Input);
                AddNodeNode(PtrOfNode, node);
                VMLOG_PROC(ALGPAR_OP_SER, Input, Output);    
                continue;
            } break;
            case ALGPAR_OP_AND: {
                const uint16_t  countOfItems  = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  offsetCode    = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  nextCode      = offsetCode + Input.IndexOfCode;
                struct ParserOutput output_and = {.Size = 1};    
                unsigned int id_action = Program.Tokenizers[Input.Tokens[Input.IndexOfTokens].id].indexOfAction;      
                for(uint16_t i = 0; i < countOfItems; i++)
                {
                    VMLOG_BRAN(ALGPAR_OP_AND, Input, Output);
                    struct ParserOutput output_item = GetAnalyzeOutput(Program, Input, 0, PtrOfExtra);
                    output_and = AndOutputOutput(output_and, output_item);
                    if(CanContinue(output_and))
                    {
                        Input.IndexOfCode = output_item.NextIndexOfCode;
                    }
                    else
                    {
                        goto NODE_AND_EXIT;
                    }
                }
                AddNodeNode(PtrOfNode, CreateNode(Program, Input.IndexOfTokens, output_and.Size, id_action, 1));
                Output = AddOutputOutput(Output, output_and);  
                NODE_AND_EXIT:
                Input.IndexOfCode = nextCode;
                UpdateAnalyzeExtraFurthestTokenQueryIndex(PtrOfExtra, Input);                
                VMLOG_PROC(ALGPAR_OP_AND, Input, Output);    
                continue;
            } break;
            case ALGPAR_OP_NOT: {
                const uint16_t  offsetCode    = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  nextCode      = offsetCode + Input.IndexOfCode;
                struct ParserOutput output_not;
                unsigned int id_action = Program.Tokenizers[Input.Tokens[Input.IndexOfTokens].id].indexOfAction;
                VMLOG_BRAN(ALGPAR_OP_NOT, Input, Output);
                struct ParserOutput output_item = GetAnalyzeOutput(Program, Input, 0, PtrOfExtra);
                output_not = NotOutput(output_item);
                if(CanContinue(output_not))
                {
                    Input.IndexOfCode = output_item.NextIndexOfCode;
                }
                else
                {
                    goto NODE_NOT_EXIT;
                }
                AddNodeNode(PtrOfNode, CreateNode(Program, Input.IndexOfTokens, output_not.Size, id_action, 1));
                Output = AddOutputOutput(Output, output_not);  
                NODE_NOT_EXIT:
                Input.IndexOfCode = nextCode;
                VMLOG_PROC(ALGPAR_OP_NOT, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_NUL: {
                const uint16_t offsetCode = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t nextCode   = offsetCode + Input.IndexOfCode;
                VMLOG_BRAN(ALGPAR_OP_NUL, Input, Output);
                struct ParserOutput output_item = Nullify(GetAnalyzeOutput(Program, Input, 0, PtrOfExtra));
                Output = AddOutputOutput(Output, output_item);
                Input.IndexOfCode = nextCode;
                VMLOG_PROC(ALGPAR_OP_NUL, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_CNT: {
                const uint32_t begin      = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t begin2     = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t offsetCode = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t nextCode   = offsetCode + Input.IndexOfCode;
                const uint16_t end = (begin2 > begin) ? begin2 - begin : 0;
                struct AlgodalParser_Node *node      = CreateInvisibleNode();
                struct ParserOutput reqOutput        = Output;
                struct ParserOutput iterOutput;
                if(!(begin == 0 && end == 0))
                {
                    uint16_t count = 0;
                    if(begin)
                    {
                        do
                        {
                            VMLOG_BRAN(ALGPAR_OP_CNT, Input, Output);
                            iterOutput = GetAnalyzeOutput(Program, Input, &node, PtrOfExtra);
                            if(CanContinueBySizeOnly(iterOutput))
                            {
                                Input.IndexOfTokens += iterOutput.Size;
                                reqOutput = AddOutputOutput(reqOutput, iterOutput);
                            }
                            else
                            {
                                break;
                            }
                            count++;
                        } while(count < begin && CharsAvailable(Input));
                    }
                    if(count == begin)
                    {
                        Output = reqOutput;
                        if(!reqOutput.Flags && end && CharsAvailable(Input))
                        {
                            uint16_t count = 0;
                            do
                            {
                                VMLOG_BRAN(ALGPAR_OP_CNT, Input, Output);
                                iterOutput = GetAnalyzeOutput(Program, Input, &node, PtrOfExtra);
                                if(CanContinueBySizeOnly(iterOutput))
                                {
                                    Input.IndexOfTokens += iterOutput.Size;
                                    Output = AddOutputOutput(Output, iterOutput);
                                }
                                else
                                {
                                    break;
                                }
                                count++;
                            } while(count < end && CharsAvailable(Input));
                        }
                        AddNodeNode(PtrOfNode, node);
                    } else DestroyNode(&node);             
                }
                Input.IndexOfCode = nextCode;
                Output.ZeroCountResult = begin == 0;
                UpdateAnalyzeExtraFurthestTokenQueryIndex(PtrOfExtra, Input);            
                VMLOG_PROC(ALGPAR_OP_CNT, Input, Output);              
                continue;
            } break;
            case ALGPAR_OP_PNT: {
                const uint16_t indexOfAction = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                struct AlgodalParser_Node *nodeOfChildren = 0;
                VMLOG_BRAN(ALGPAR_OP_PNT, Input, Output);
                struct ParserOutput reqOutput = GetAnalyzeOutput(Program, RelateInputToAction(Program, Input, indexOfAction), &nodeOfChildren, PtrOfExtra);
                struct AlgodalParser_Node *ThisNode = CreateNode(Program, Input.IndexOfTokens, reqOutput.Size, indexOfAction, 0);
                Output = AddOutputOutput(Output, reqOutput);
                AddNodeNode(PtrOfNode, AddNodeNode(&ThisNode, nodeOfChildren));                
                VMLOG_PROC(ALGPAR_OP_PNT, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_ZPR: {
                const uint16_t index_action = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t leftmost = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t rightmost = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                VMLOG_BRAN(ALGPAR_OP_ZPR, Input, Output);
                struct AlgodalParser_Node *nodeOfChildren   = 0;
                struct ParserOutput output_action = GetAnalyzeOutput(Program, RelateInputToAction(Program, Input, index_action), &nodeOfChildren, PtrOfExtra);
                if(CanContinue(output_action))
                {
                    const uint32_t OpSize = CompareSizeRange(Input, output_action.Size, leftmost, rightmost);
                    Output.Size += OpSize;
                    struct AlgodalParser_Node *ThisNode = CreateNode(Program, Input.IndexOfTokens, OpSize, index_action, 0);
                    AddNodeNode(PtrOfNode, AddNodeNode(&ThisNode, nodeOfChildren)); 
                } 
                else
                {
                    DestroyNode(&nodeOfChildren);
                }         
                VMLOG_PROC(ALGPAR_OP_ZPR, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_ZPS: {
                const uint16_t index_action = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t id_string = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const int8_t icase = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                VMLOG_BRAN(ALGPAR_OP_ZPS, Input, Output);
                struct AlgodalParser_Node *nodeOfChildren   = 0;
                struct ParserOutput output_action = GetAnalyzeOutput(Program, RelateInputToAction(Program, Input, index_action), &nodeOfChildren, PtrOfExtra);
                if(CanContinue(output_action))
                {
                    const uint32_t OpSize = CompareSizeString(Program, Input, output_action.Size, id_string, icase);
                    Output.Size += OpSize;
                    struct AlgodalParser_Node *ThisNode = CreateNode(Program, Input.IndexOfTokens, OpSize, index_action, 0);
                    AddNodeNode(PtrOfNode, AddNodeNode(&ThisNode, nodeOfChildren)); 
                }
                else
                {
                    DestroyNode(&nodeOfChildren);
                }  
                VMLOG_PROC(ALGPAR_OP_ZPS, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_ZPN: {
                const uint16_t index_action = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t id_string = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const int8_t icase = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t length = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                VMLOG_BRAN(ALGPAR_OP_ZPN, Input, Output);
                struct AlgodalParser_Node *nodeOfChildren   = 0;
                struct ParserOutput output_action = GetAnalyzeOutput(Program, RelateInputToAction(Program, Input, index_action), &nodeOfChildren, PtrOfExtra);
                if(CanContinue(output_action))
                {
                    const uint32_t OpSize = CompareSizeStringLength(Program, Input, output_action.Size, id_string, icase, length);
                    Output.Size += OpSize;
                    struct AlgodalParser_Node *ThisNode = CreateNode(Program, Input.IndexOfTokens, OpSize, index_action, 0);
                    AddNodeNode(PtrOfNode, AddNodeNode(&ThisNode, nodeOfChildren)); 
                }
                else
                {
                    DestroyNode(&nodeOfChildren);
                }  
                VMLOG_PROC(ALGPAR_OP_ZPN, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_TRM: {
                const uint16_t id = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t indexOfAction = Program.Tokenizers[id].indexOfAction;
                const uint32_t OpSize = Term(Program, Input, id);
                Output.Size += OpSize;
                struct AlgodalParser_Node *node = CreateNode(Program, Input.IndexOfTokens, OpSize, indexOfAction, 1);
                AddNodeNode(PtrOfNode, node);
                VMLOG_PROC(ALGPAR_OP_TRM, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_ZTR: {
                const uint16_t id = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t leftmost = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t rightmost = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t OpSize = CompareTermRange(Program, Input, id, leftmost, rightmost);
                Output.Size += OpSize;
                const uint16_t indexOfAction = Program.Tokenizers[id].indexOfAction;
                struct AlgodalParser_Node *node = CreateNode(Program, Input.IndexOfTokens, OpSize, indexOfAction, 1);
                AddNodeNode(PtrOfNode, node);
                VMLOG_PROC(ALGPAR_OP_ZTR, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_ZTS: {
                const uint16_t id = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t stringID = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const int8_t icase = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t OpSize = CompareTermString(Program, Input, id, stringID, icase);
                Output.Size += OpSize;
                const uint16_t indexOfAction = Program.Tokenizers[id].indexOfAction;
                struct AlgodalParser_Node *node = CreateNode(Program, Input.IndexOfTokens, OpSize, indexOfAction, 1);
                AddNodeNode(PtrOfNode, node);
                VMLOG_PROC(ALGPAR_OP_ZTS, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_ZTN: {
                const uint16_t id = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t stringID = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const int8_t icase = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t length = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t OpSize = CompareTermStringLength(Program, Input, id, stringID, icase, length);
                Output.Size += OpSize;
                const uint16_t indexOfAction = Program.Tokenizers[id].indexOfAction;
                struct AlgodalParser_Node *node = CreateNode(Program, Input.IndexOfTokens, OpSize, indexOfAction, 1);
                AddNodeNode(PtrOfNode, node);
                VMLOG_PROC(ALGPAR_OP_ZTN, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_RET: {
                VMLOG_PROC(ALGPAR_OP_RET, Input, Output);
                goto EXIT;
            } break;
            default: {
                Output.Flags |= ALGODAL_PARSING_ERROR;
                goto EXIT;
            } break;
        }
    } while(!Output.Flags);
    EXIT:
    Output.NextIndexOfCode = Input.IndexOfCode;
    Output.priority = Input.priority;
    return Output;
}
inline static struct ParserOutput GetMaxOutputWithNode(struct ParserOutput addr[], uint16_t size, struct AlgodalParser_Node *arrOfNodes[], struct AlgodalParser_Node **ptrOfNode)
{
    struct ParserOutput output_selected = {};
    const uint16_t index = GetMaxIndex(addr, size, &output_selected);
    AddNodeNode(ptrOfNode, SelectNode(arrOfNodes, size, index));
    return output_selected;
}
inline static struct ParserOutput GetMaxAnalyzeOutput(struct AlgodalParser_Program Program, struct ParserInput Input, struct AlgodalParser_Node* *PtrOfNode, struct AnalyzeExtra *PtrOfExtra)
{
    VMINFO("================================\n");
    struct AlgodalParser_Node *entryNodes[Program.CountOfEntrypoints], *nodes[Program.CountOfEntrypoints];
    memset(entryNodes, 0, Program.CountOfEntrypoints * sizeof(struct AlgodalParser_Node *));
    memset(nodes, 0, Program.CountOfEntrypoints * sizeof(struct AlgodalParser_Node *));
    struct ParserOutput outputs[Program.CountOfEntrypoints];
    for(uint16_t i = 0; i < Program.CountOfEntrypoints; i++)
    {
        const uint16_t indexOfAction = Program.Entrypoints[i].indexOfAction;
        struct ParserInput input = Input;
        input.ID = indexOfAction;
        input.IndexOfCode = Program.Actions[indexOfAction].indexOfCode;
        input.priority = Program.Entrypoints[i].priority;
        #ifdef ALGODAL_PARSER_LOGGER_DEBUG
        input.LastActionName = Program.Strings[Program.Actions[indexOfAction].indexOfString].text;
        #endif
        outputs[i] = GetAnalyzeOutput(Program, input, &nodes[i], PtrOfExtra);
        entryNodes[i] = CreateNode(Program, input.IndexOfTokens, outputs[i].Size, indexOfAction, 0);
        AddNodeNode(&entryNodes[i], nodes[i]);
    }
    return GetMaxOutputWithNode(outputs, Program.CountOfEntrypoints, entryNodes, PtrOfNode);
}
static void AnalyzeResultAdd(struct AlgodalParser_Program Program, struct AlgodalParser_AnalyzeResult* ptr, struct ParserOutput output, struct AlgodalParser_Token *tokens, uint32_t size, uint32_t index, struct AlgodalParser_Node *node, struct AnalyzeExtra *ptrOfExtra)
{
    (void)Program;
    AddChildrenNode(&ptr->nodes, node);
    if(output.Flags == 0 && output.Size == 0) output.Flags |= ALGODAL_PARSING_FAIL;
    if(output.Flags)
    {
        const uint32_t index2 = ptrOfExtra->FurthestTokenQueryIndex ? ptrOfExtra->FurthestTokenQueryIndex : index + output.Size;
        ptr->error.flags = output.Flags;
        ptr->error.index = tokens[index].index;
        ptr->error.index2 = tokens[clamp_index(index2, size)].index;
        ptr->error.user.value = output.value_current;
        ptr->error.user.extravalue = output.value_duplicated;
    }
}
struct AlgodalParser_AnalyzeResult AlgodalParser_GetAnalyzeResult(struct AlgodalParser_Program Program, const char *text, struct AlgodalParser_Token *tokens, const uint32_t size, struct AlgodalParser_OtherAnalyzeParams* oparams)
{
    VMINFO("\nANALYZATION VIRTUAL MACHINE LOG\n");
    int8_t loopOnce = oparams ? oparams->loopOnce : 0;
    struct AlgodalParser_AnalyzeResult AlgodalParser_AnalyzeResult = {};
    uint32_t index = 0;
    struct ParserInput Input = {.Tokens = tokens, .SizeOfTokens = size, .refOfText = text};
    if(Program.CountOfEntrypoints)
    {
        while(index < size)
        {
            struct AlgodalParser_Node *AlgodalParser_Node = 0;
            Input.IndexOfTokens = index;
            struct AnalyzeExtra extra = {.FurthestTokenQueryIndex = index};
            struct ParserOutput Output = GetMaxAnalyzeOutput(Program, Input, &AlgodalParser_Node, &extra);            
            AnalyzeResultAdd(Program, &AlgodalParser_AnalyzeResult, Output, tokens, size, index, AlgodalParser_Node, &extra);
            if(AlgodalParser_AnalyzeResult.error.flags) break;
            index += Output.Size;
            if(loopOnce) break;
        }
        if(loopOnce && index < size)
        {
            AlgodalParser_AnalyzeResult.error.flags |= ALGODAL_PARSING_EOI;
            AlgodalParser_AnalyzeResult.error.index = index;
            AlgodalParser_AnalyzeResult.error.index2 = clamp_index(size, size);
        }
    }
    return AlgodalParser_AnalyzeResult;
}
static void printIndent(uint32_t indent)
{
    for(uint32_t i = 0; i < indent; i++) cwpc_fprintf(PARSER_STDOUT, "\t");
}
const char *AlgodalParser_GetActionString_READONLY(struct AlgodalParser_Program program, unsigned int id)
{
    return program.Strings[program.Actions[id].indexOfString].text;
}
void AlgodalParser_GetNodeKey(struct AlgodalParser_Program program, struct AlgodalParser_Node *node, char *r_key)
{
    strcpy(r_key, AlgodalParser_GetActionString_READONLY(program, node->indexOfAction));
}
static inline int IsSpaceChar(int c)
{
    return c == '\n' || c == '\r' || c == '\t' || c == ' ';
}
static inline void SimplifyNodeValue(char* buffer, size_t size)
{
    char bufferNew[size + 1];
    memset(bufferNew, 0, size + 1);
    unsigned int iNew = 0;
    int flagSpace = 0;
    for(unsigned int i = 0; i < size; i++)
    {
        int c = buffer[i];
        if(IsSpaceChar(c))
        {
            if(flagSpace)
            {
                continue;
            }
            bufferNew[iNew++] = ' ';
            flagSpace = 1;
        }
        else
        {
            flagSpace = 0;
            bufferNew[iNew++] = c;
        }
    }
    memcpy(buffer, bufferNew, size);
}
void AlgodalParser_GetNodeValue(const char* text, const struct AlgodalParser_Token tokens[], struct AlgodalParser_Node *node, unsigned int size, char *r_value)
{
    if(r_value)
    {
        long offsetStart = tokens[node->indexOfToken].index;
        memcpy(r_value, &text[offsetStart], size);
    }
}
char* AlgodalParser_AllocNodeValue(AlgodalParser_Ast ast, struct AlgodalParser_Node *node)
{
    const unsigned int size = AlgodalParser_GetNodeValueSize(ast.tokens, node);
    char* value = (char*)malloc(size + 1);
    memset(value, 0, size + 1);
    AlgodalParser_GetNodeValue(ast.text, ast.tokens, node, size, value);
    return value;
}
void PrintNode(struct AlgodalParser_Program program, struct AlgodalParser_Node *node, const struct AlgodalParser_Token tokens[], const char* text, uint16_t indent, struct AlgodalParser_Linenumber *AlgodalParser_ParserLinenumber)
{
    if(node->invisible)
    {
        for(uint32_t i = 0; i < node->children.size; i++)
        {
            PrintNode(program, node->children.addr[i], tokens, text, indent, AlgodalParser_ParserLinenumber);
        }
    }
    else
    {
        printIndent(indent);
        char lineBuffer[512];
        cwpc_fprintf(PARSER_STDOUT, "%s ", GetLn(AlgodalParser_ParserLinenumber, tokens[node->indexOfToken].index, lineBuffer));
        char key[tokens[node->indexOfToken].size + 1];
        key[tokens[node->indexOfToken].size] = 0;
        AlgodalParser_GetNodeKey(program, node, key);
        cwpc_fprintf(PARSER_STDOUT, "%s ", key);
        const int showNodeValue = SHOW_NODE_VALUE;
        if(GetObjectpointFlag(program, node->indexOfAction) == 0 && showNodeValue)
        {
            cwpc_fprintf(PARSER_STDOUT, ": ");
            unsigned int size = AlgodalParser_GetNodeValueSize(tokens, node);
            char value[size + 1];
            memset(value, 0, size + 1);
            AlgodalParser_GetNodeValue(text, tokens, node, size, value);
            SimplifyNodeValue(value, size);
            cwpc_fprintf(PARSER_STDOUT, "%s", HorizontSpaceString(value));
        }
        cwpc_fprintf(PARSER_STDOUT, "\n");
        for(uint32_t i = 0; i < node->children.size; i++)
        {
            PrintNode(program, node->children.addr[i], tokens, text, indent + 1, AlgodalParser_ParserLinenumber);
        }
    }
}
void AlgodalParser_PrintAnalyzeResult(struct AlgodalParser_Program program, struct AlgodalParser_AnalyzeResult AlgodalParser_AnalyzeResult, struct AlgodalParser_Token tokens[], const char* text, struct AlgodalParser_Linenumber *AlgodalParser_ParserLinenumber)
{
    for(uint32_t i = 0; i < AlgodalParser_AnalyzeResult.nodes.size; i++)
    {
        struct AlgodalParser_Node *node = AlgodalParser_AnalyzeResult.nodes.addr[i];
        PrintNode(program, node, tokens, text, 0, AlgodalParser_ParserLinenumber);
    }
    PrintAnalyzeParserError(program, AlgodalParser_AnalyzeResult.error, AlgodalParser_ParserLinenumber);
}
void AlgodalParser_DestroyTokenizeResult(struct AlgodalParser_TokenizeResult TokenizeResult) 
{
    free(TokenizeResult.tokens.addr);
}
void AlgodalParser_DestroyAnalyzeResult(struct AlgodalParser_AnalyzeResult AlgodalParser_AnalyzeResult) 
{
    for(uint32_t i = 0; i < AlgodalParser_AnalyzeResult.nodes.size; i++) 
        DestroyNode(&AlgodalParser_AnalyzeResult.nodes.addr[i]);
    free(AlgodalParser_AnalyzeResult.nodes.addr);
}
long AlgodalParser_GetNodeValueSize(const struct AlgodalParser_Token tokens[], struct AlgodalParser_Node *node)
{
    long offsetStart = tokens[node->indexOfToken].index;
    AlgodalParser_Token tokenEnd = tokens[node->indexOfToken + node->size - 1];
    long offsetEnd   = tokenEnd.index + tokenEnd.size;
    return offsetEnd - offsetStart;
}
struct AlgodalParser_TokenPair ExportToken(struct AlgodalParser_Token token, struct AlgodalParser_Program Program, const char *text, struct AlgodalParser_Linenumber *AlgodalParser_ParserLinenumber)
{
    struct AlgodalParser_TokenPair pair = {};
    pair.offsetOfText = token.index;
    pair.key = strdup(Program.Strings[Program.Actions[Program.Tokenizers[token.id].indexOfAction].indexOfString].text);
    if(Program.Tokenizers[token.id].type != 3 && token.size > 0)
    {
        char buf[token.size + 1]; buf[token.size] = 0;
        memcpy(buf, &text[token.index], token.size);
        pair.value = strdup(buf);
    }
    GetLnInt(AlgodalParser_ParserLinenumber, token.index, &pair.lineNumber, &pair.columnNumber);
    return pair;
}
struct AlgodalParser_TokenPairList AlgodalParser_ExportTokenizeResult(struct AlgodalParser_TokenizeResult TokenizeResult, struct AlgodalParser_Program Program, const char *text, struct AlgodalParser_Linenumber *AlgodalParser_ParserLinenumber)
{
    struct AlgodalParser_TokenPairList pairList = {};
    pairList.size = TokenizeResult.tokens.size;
    pairList.addr = (struct AlgodalParser_TokenPair *)malloc(sizeof(struct AlgodalParser_TokenPair) * pairList.size);
    memset(pairList.addr, 0, sizeof(struct AlgodalParser_TokenPair) * pairList.size);
    for(uint32_t i = 0; i < pairList.size; i++)
    {
        pairList.addr[i] = ExportToken(TokenizeResult.tokens.addr[i], Program, text, AlgodalParser_ParserLinenumber);
    }
    return pairList;
}
static struct AlgodalParser_NodePair ExportNode(struct AlgodalParser_Token *tokens, struct AlgodalParser_Node *node, struct AlgodalParser_Program Program, const char *text, struct AlgodalParser_Linenumber *AlgodalParser_ParserLinenumber)
{
    struct AlgodalParser_NodePair pair = {};
    pair.offsetOfText = tokens[node->indexOfToken].index;
    pair.key = strdup(Program.Strings[Program.Actions[node->indexOfAction].indexOfString].text);
    GetLnInt(AlgodalParser_ParserLinenumber, tokens[node->indexOfToken].index, &pair.lineNumber, &pair.columnNumber);
    const int showNodeValue = SHOW_NODE_VALUE;
    if(showNodeValue)
    {
        uint32_t length = tokens[node->indexOfToken + node->size - 1].index - tokens[node->indexOfToken].index + tokens[node->indexOfToken + node->size - 1].size;
        char buf[length + 1]; buf[length] = 0;
        memcpy(buf, &text[tokens[node->indexOfToken].index], length);
        pair.value = strdup(buf);
    }
    pair.children.size = node->children.size;
    pair.children.addr = (struct AlgodalParser_NodePair *)malloc(sizeof(struct AlgodalParser_NodePair) * pair.children.size);
    for(uint32_t i = 0; i < pair.children.size; i++)
    {
        pair.children.addr[i] = ExportNode(tokens, node->children.addr[i], Program, text, AlgodalParser_ParserLinenumber);
    }
    return pair;
}
struct AlgodalParser_NodePairList AlgodalParser_ExportAnalyzeResult(struct AlgodalParser_Token *tokens, struct AlgodalParser_AnalyzeResult AlgodalParser_AnalyzeResult, struct AlgodalParser_Program Program, const char *text, struct AlgodalParser_Linenumber *AlgodalParser_ParserLinenumber)
{
    struct AlgodalParser_NodePairList pairList = {};
    pairList.size = AlgodalParser_AnalyzeResult.nodes.size;
    pairList.addr = (struct AlgodalParser_NodePair *)malloc(sizeof(struct AlgodalParser_NodePair) * pairList.size);
    memset(pairList.addr, 0, sizeof(struct AlgodalParser_NodePair) * pairList.size);
    for(uint32_t i = 0; i < pairList.size; i++)
    {
        pairList.addr[i] = ExportNode(tokens, AlgodalParser_AnalyzeResult.nodes.addr[i], Program, text, AlgodalParser_ParserLinenumber);
    }
    return pairList;
}
void DestroyTokenPair(struct AlgodalParser_TokenPair pair)
{
    free((void*)pair.key);
    if(pair.value)free((void*)pair.value);
}
void AlgodalParser_DestroyTokenPairList(struct AlgodalParser_TokenPairList pairList)
{
    for(uint32_t i = 0; i < pairList.size; i++)
    {
        DestroyTokenPair(pairList.addr[i]);
    }
    free(pairList.addr);
}
void DestroyNodePair(struct AlgodalParser_NodePair pair)
{
    free((void*)pair.key);
    free((void*)pair.value);
    for(uint32_t i = 0; i < pair.children.size; i++)
    {
        DestroyNodePair(pair.children.addr[i]);
    }
    free(pair.children.addr);
}
void AlgodalParser_DestroyNodePairList(struct AlgodalParser_NodePairList pairList)
{
    for(uint32_t i = 0; i < pairList.size; i++)
    {
        DestroyNodePair(pairList.addr[i]);
    }
    free(pairList.addr);
}
#ifdef __cplusplus
}
#endif
#endif  
