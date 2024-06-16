#include "algodal-parser-header.h"
#include "algodal-parser-header.h"
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
    AlgodalParser_Ast ast = APS_ZERO;
    ast.text = (char*)text;
    ast.linenumber = ln;
    ast.tokens = tr.tokens;
    ast.nodes = ar.nodes;
    ast.program = program;
    ast.tr = tr;
    ast.ar = ar;
    return ast;
}
void AlgodalParser_DestroyAst(AlgodalParser_Ast ast)
{
    if(ast.linenumber) AlgodalParser_DestroyParserLinenumber(ast.linenumber);
    if(ast.tokens.size) AlgodalParser_DestroyTokenizeResult(ast.tr);
    if(ast.nodes.size) AlgodalParser_DestroyAnalyzeResult(ast.ar);
}
AlgodalParser_Node* AlgodalParser_GetNodeByValueOfRoots(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier
)
{
    AlgodalParser_Node root = APS_ZERO;
    root.children = ast.nodes;
    return AlgodalParser_GetNodeByValueOfNode(ast, icase, identifier, &root);
}
AlgodalParser_Node* AlgodalParser_GetNodeByKeyOfRoots(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier
)
{
    AlgodalParser_Node root = APS_ZERO;
    root.children = ast.nodes;
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
    if(node)
    {
        for(unsigned int i = 0; i < node->children.size; i++)
        {
            AlgodalParser_Node* child = node->children.addr[i];
            long size = AlgodalParser_GetNodeValueSize(ast, child);
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
                AlgodalParser_GetNodeValue(ast, child, value);
                if(AlgodalParser_StrCmp(icase, identifier, value))
                {
                    return child;
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
            AlgodalParser_Node* grandchild  = AlgodalParser_GetChildNodeByValueOfNode(ast, icase, identifier, grandparent);
            if(grandchild) return grandchild;
        }
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
        long size = AlgodalParser_GetNodeValueSize(ast, node);
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
            AlgodalParser_GetNodeValue(ast, node, value);
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
    long size = AlgodalParser_GetNodeValueSize(ast, node);
    if(size == 0) return AlgodalParser_StrCmp(icase, identifier, "");
    else
    {
        char value[size + 1];
        memset(value, 0, size + 1);
        AlgodalParser_GetNodeValue(ast, node, value);
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
    long size = AlgodalParser_GetNodeValueSize(ast, node);
    if(size == 0) return AlgodalParser_StrCmp(icase, identifier, "");
    else
    {
        char value[size + 1];
        memset(value, 0, size + 1);
        AlgodalParser_GetNodeValue(ast, node, value);
        return AlgodalParser_SubStrCmp(icase, value, identifier);
    }     
}
int AlgodalParser_IsNodeValueSimplified(
    AlgodalParser_Ast ast, 
    int icase,
    const char* identifier,
    AlgodalParser_Node* node
)
{
    long size = AlgodalParser_GetNodeValueSize(ast, node);
    if(size == 0) return AlgodalParser_StrCmp(icase, identifier, "");
    else
    {
        char value[size + 1];
        memset(value, 0, size + 1);
        AlgodalParser_GetNodeValueSimplified(ast, node, value);
        return AlgodalParser_StrCmp(icase, identifier, value);
    }
}
char* AlgodalParser_GetNodeKey(AlgodalParser_Ast ast, struct AlgodalParser_Node *node, char *r_key)
{
    return strcpy(r_key, AlgodalParser_GetActionString_READONLY(ast.program, node->indexOfAction));
}
char* AlgodalParser_GetNodeValueBySize(AlgodalParser_Ast ast, struct AlgodalParser_Node *node, char *r_value, unsigned int size)
{
    if(r_value)
    {
        long offsetStart = ast.tokens.addr[node->indexOfToken].index;
        memcpy(r_value, &ast.text[offsetStart], size);
    }
    return r_value;
}
char* AlgodalParser_GetNodeValue(AlgodalParser_Ast ast, struct AlgodalParser_Node *node, char *r_value)
{
    return AlgodalParser_GetNodeValueBySize(ast, node, r_value, AlgodalParser_GetNodeValueSize(ast, node));
}
char* AlgodalParser_GetNodeValueSimplified(AlgodalParser_Ast ast, struct AlgodalParser_Node *node, char *r_value)
{
    AlgodalParser_GetNodeValue(ast, node, r_value);
    return AlgodalParser_SimplifyStr(strlen(r_value), r_value);
}
char* AlgodalParser_AllocNodeValue(AlgodalParser_Ast ast, struct AlgodalParser_Node *node)
{
    const unsigned int size = AlgodalParser_GetNodeValueSize(ast, node);
    char* value = (char*)malloc(size + 1);
    memset(value, 0, size + 1);
    AlgodalParser_GetNodeValue(ast, node, value);
    return value;
}
long AlgodalParser_GetNodeValueSize(AlgodalParser_Ast ast, struct AlgodalParser_Node *node)
{
    long offsetStart = ast.tokens.addr[node->indexOfToken].index;
    AlgodalParser_Token tokenEnd = ast.tokens.addr[node->indexOfToken + node->size - 1];
    long offsetEnd   = tokenEnd.index + tokenEnd.size;
    return offsetEnd - offsetStart;
}
char* AlgodalParser_GetTokenKey(AlgodalParser_Ast ast, AlgodalParser_Token token, char *r_key)
{
    return strcpy(r_key, AlgodalParser_GetTokenizerString_READONLY(ast.program, token.id));
}
char* AlgodalParser_GetTokenValue(AlgodalParser_Ast ast, struct AlgodalParser_Token token, char *r_value)
{
    if(token.size > 0)
    {
        memcpy(r_value, &ast.text[token.index], token.size);
        r_value[token.size] = 0;
    }
    return r_value;
}
char* AlgodalParser_GetTokenValueSimplified(AlgodalParser_Ast ast, struct AlgodalParser_Token token, char *r_value)
{
    AlgodalParser_GetTokenValue(ast, token, r_value);
    return AlgodalParser_SimplifyStr(strlen(r_value), r_value);
}
#ifdef __cplusplus
}
#endif
#endif 
#ifndef ALGODAL_GENERATED_PARSER_SHARED_C
#define ALGODAL_GENERATED_PARSER_SHARED_C
#define ALGODALPARSER_LEX_TEXT_LEN 256
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
    if(str && '"' == str[0] && buf)
    {
        const unsigned int length = strlen(str) - 2;
        memcpy(buf, &str[1], length);
        buf[length] = 0;
        return buf;
    }
    return (char*)str;
}
char* AlgodalParser_UnbracketStr(const char* str, char* buf)
{
    if(str && '(' == str[0] && buf)
    {
        const unsigned int length = strlen(str) - 2;
        memcpy(buf, &str[1], length);
        buf[length] = 0;
        return buf;
    }
    return (char*)str;
}
char* AlgodalParser_SimplifyStr(size_t size, char* r_str)
{
    char bufferNew[size + 1];
    memset(bufferNew, 0, size + 1);
    unsigned int iNew = 0;
    int flagSpace = 0;
    for(unsigned int i = 0; i < size; i++)
    {
        int c = r_str[i];
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
    memcpy(r_str, bufferNew, size);
    return r_str;
}
char* AlgodalParser_MakeLiteralString(char c[], uint32_t length)
{
    uint32_t r = 0, w = 0;
    while(r < length && c[r] != 0)
    {
        switch(c[r])
        {
            case '\\':
            {
                r++;
                switch(c[r])
                {
                    case 'n': 
                    {
                        r++;
                        c[w++] = 0x0a;
                    } break;
                    case 'r': 
                    {
                        r++;
                        c[w++] = 0x0d;
                    } break;
                    case 't': 
                    {
                        r++;
                        c[w++] = 0x09;
                    } break;
                    case '\\': 
                    {
                        r++;
                        c[w++] = 0x5c;
                    } break;
                    case '"': 
                    {
                        r++;
                        c[w++] = 0x22;
                    } break;
                    case '\'': 
                    {
                        r++;
                        c[w++] = 0x27;
                    } break;
                    case 'x': 
                    {
                        r++;
                        char x[3] = {0};
                        if(r < ALGODALPARSER_LEX_TEXT_LEN - 2)
                        {
                            x[0] = c[r++];
                            x[1] = c[r++];
                            c[w++] = strtol(x, NULL, 16);
                        } else {
                            cwpc_printf("Error at String's Hexadecimal insert.\n");
                        }
                    } break;
                }
            } break;
            default:
            {
                c[w++] = c[r++];
            } break;
        }
    }
    c[w++] = 0;
    return c;
}
#ifdef __cplusplus
}
#endif
#endif 
#ifndef ALGODAL_GENERATED_PARSER_VM_C
#define ALGODAL_GENERATED_PARSER_VM_C
#ifdef __cplusplus
extern "C" {
#endif
static inline unsigned int clamp_index(unsigned int index, unsigned int size)
{
    if(size)
    {
        if(index >= size) return size - 1;
        return index;
    }
    return 0;
}
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
uint32_t algodalparser_get_byte1_size(char byte1)
{
	return
		(byte1 & 128) == 0 ? 1u :
		(byte1 & (128 + 64 + 32)) == (128 + 64) ? 2u :
		(byte1 & (128 + 64 + 32 + 16)) == (128 + 64 + 32) ? 3u :
		(byte1 & (128 + 64 + 32 + 16 + 8)) == (128 + 64 + 32 + 16) ? 4u :
		0; 
}
static inline int is_other_byte_trailing(char other_byte)
{
    return
		((unsigned char)other_byte & (128 + 64)) == 128 ? 1 : 0;
}
uint32_t algodalparser_utf8_read(const char* string)
{
    const uint32_t byte1Size = algodalparser_get_byte1_size(string[0]);
	uint32_t unicode = 0;
	memcpy(&unicode, string, sizeof(char) * byte1Size);
	return unicode;
}
static size_t utf8_get_unicode_size (uint32_t unicode)
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
static AlgodalParser_InternalLinenumber * Linenumber_create(const char * buffer, const uint32_t length);
static void Linenumber_destroy(AlgodalParser_InternalLinenumber * pln);
static void Linenumber_updateBuffer(AlgodalParser_InternalLinenumber * pln, const char* buffer, const uint32_t length);
static void Linenumber_next(AlgodalParser_InternalLinenumber * pln);
inline static AlgodalParser_InternalLinenumber * empty(void) {
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
static inline AlgodalParser_InternalLinenumber * Linenumber_create(const char * buffer, const uint32_t lengthOfBuffer) {
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
        const uint32_t c  = algodalparser_utf8_read(&pln->buffer[pln->pos]);
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
    AlgodalParser_ParserLinenumber->lines[index].offset = ((AlgodalParser_InternalLinenumber*)AlgodalParser_ParserLinenumber->linenumber)->pos;
}
static void UpdateParserLinenumberText(struct AlgodalParser_Linenumber * AlgodalParser_ParserLinenumber, const char* textDoc, const uint32_t length)
{
    Linenumber_updateBuffer((AlgodalParser_InternalLinenumber*)AlgodalParser_ParserLinenumber->linenumber, textDoc, length);
    while(((AlgodalParser_InternalLinenumber*)AlgodalParser_ParserLinenumber->linenumber)->pos < length)
    {
        append_line(AlgodalParser_ParserLinenumber);
        Linenumber_nextLine((AlgodalParser_InternalLinenumber*)AlgodalParser_ParserLinenumber->linenumber, length);
    }
}
struct AlgodalParser_Linenumber *AlgodalParser_CreateParserLinenumber(const char* textDoc, const uint32_t length)
{
    struct AlgodalParser_Linenumber *AlgodalParser_ParserLinenumber = (struct AlgodalParser_Linenumber *)malloc(sizeof(struct AlgodalParser_Linenumber));
    memset(AlgodalParser_ParserLinenumber, 0, sizeof(struct AlgodalParser_Linenumber));
    AlgodalParser_ParserLinenumber->linenumber = (void*)Linenumber_create(textDoc, length);
    UpdateParserLinenumberText(AlgodalParser_ParserLinenumber, textDoc, length);
    return AlgodalParser_ParserLinenumber;
}
void AlgodalParser_DestroyParserLinenumber(struct AlgodalParser_Linenumber * AlgodalParser_ParserLinenumber)
{
    Linenumber_destroy((AlgodalParser_InternalLinenumber*)AlgodalParser_ParserLinenumber->linenumber);
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
const char* AlgodalParser_GetLinenumber(struct AlgodalParser_Linenumber *AlgodalParser_ParserLinenumber, uint32_t offset, char *buffer)
{
    if(AlgodalParser_ParserLinenumber && AlgodalParser_ParserLinenumber->linenumber && ((AlgodalParser_InternalLinenumber*)AlgodalParser_ParserLinenumber->linenumber)->metric.bufferUpdates)
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
void AlgodalParser_GetLinenumberInteger(struct AlgodalParser_Linenumber *AlgodalParser_ParserLinenumber, uint32_t offset, uint32_t *pl, uint32_t *pc)
{
    if(AlgodalParser_ParserLinenumber && AlgodalParser_ParserLinenumber->linenumber && ((AlgodalParser_InternalLinenumber*)AlgodalParser_ParserLinenumber->linenumber)->metric.bufferUpdates)
    {
        uint32_t line = 1, col = 1;
        getlinenumber(AlgodalParser_ParserLinenumber, offset, &line, &col);
        if(pl) *pl = line;
        if(pc) *pc = col;
    }
}
#endif  
inline static int IsUnder32BytePrintableAsText(int c)
{
    int under32allowed[] =
    {
        '\r', '\n', '\t'
    };
    for(int i = 0; i < (int)(sizeof(under32allowed)/sizeof(int)); i++)
    {
        if(c == under32allowed[i]) return 1;
    }
    return 0;
}
inline static int IsUTF8Malformed(const char* c, int length) 
{
    for(int i = 0; i < length;)
    {
        if(0 == algodalparser_get_byte1_size(c[0])) return 1;
        if(1 == algodalparser_get_byte1_size(c[i])) 
        {
            if((unsigned char)c[i] < 32u)
            {
                if(0 == IsUnder32BytePrintableAsText((unsigned char)c[i])) return 1;
            }
            i ++;
            continue;
        }
        else
        if(2 == algodalparser_get_byte1_size(c[i])) 
        {
            i ++;
            if(is_other_byte_trailing(c[i]))
            {
                i++;
                continue;
            }
            else
            {
                return 1;
            }
        }
        else
        if(3 == algodalparser_get_byte1_size(c[i])) 
        {
            i ++;
            int n = i + 2;
            for(; i < n; i++)
            {
                if(is_other_byte_trailing(c[i]))
                {
                    continue;
                }
                else
                {
                    return 1;
                }
            }
        }
        else
        if(4 == algodalparser_get_byte1_size(c[i])) 
        {
            i ++;
            int n = i + 3;
            for(; i < n; i++)
            {
                if(is_other_byte_trailing(c[i]))
                {
                    continue;
                }
                else
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}
inline static void PrintHex(const char* c, int length)
{
    cwpc_fprintf(ALGODALPARSER_STDOUT, "-- ");
    for(int i = 0; i < length; i++)
    {
        cwpc_fprintf(ALGODALPARSER_STDOUT, "0x%X ", (unsigned char)c[i]);
    }
}
static inline struct AlgodalParser_Basic CastIntegerAsBasic(int64_t integer)
{
    struct AlgodalParser_Basic basic = APS_ZERO;
    basic.number = integer;
    basic.current_state = 1;
    return basic;
}
static inline struct AlgodalParser_Basic CastStringAsBasic(const char* string)
{
    struct AlgodalParser_Basic basic = APS_ZERO;
    basic.string = string;
    basic.current_state = 2;
    return basic;
}
static inline char* CopyBasicAsString(const char* text, struct AlgodalParser_Basic basic, char* ret_string)
{
    if(1 == basic.current_state)
    {
        cwpc_sprintf(ret_string, "%ld", basic.number);
    }
    else
    if(3 == basic.current_state)
    {
        memcpy(ret_string, &text[basic.parsed.position], basic.parsed.length);
        ret_string[basic.parsed.length] = 0;
    }
    else
    if(2 == basic.current_state)
    {
        cwpc_sprintf(ret_string, "%s", basic.string);
    }
    return ret_string;
}
static inline int IsIntegerTypeForBasicConversion(int flag)
{
    return flag >= 2 && flag <= 6;
}
static inline int IsCopyTypeForBasicConversion(int flag)
{
    return flag == 7;
}
static inline int IsArithDiffSuccessByOpcode(int opcode, int diff)
{
    switch(opcode)
    {
        case ALGPAR_OP_A_GT0: return diff >  0;
        case ALGPAR_OP_A_LT0: return diff <  0;
        case ALGPAR_OP_A_GTE: return diff >= 0;
        case ALGPAR_OP_A_LTE: return diff <= 0;
        case ALGPAR_OP_A_EQ0: return diff == 0;
        case ALGPAR_OP_A_NE0: return diff != 0;
    }
    return 0;
}
static inline int64_t ConvertStringToIntegerAccordingToVarTypes(const char* string, int flag)
{
    if(IsIntegerTypeForBasicConversion(flag))
    {
        if(2 == flag)
        {
            uint16_t number = 0;
            memcpy(&number, string, sizeof(uint16_t));
            return (int64_t)number;
        }
        else
        if(3 == flag)
        {
            uint32_t number = 0;
            memcpy(&number, string, sizeof(uint32_t));
            return (int64_t)number;
        }
        else
        if(4 == flag)
        {
            uint64_t number = 0;
            memcpy(&number, string, sizeof(uint64_t));
            return (int64_t)number;
        }
        else
        if(5 == flag)
        {
            return (int64_t)strlen(string);
        }else
        if(6 == flag)
        {
            return strtoll(string, 0, 10);
        }
    }
    else
    {
        return strtoll(string, 0, 10);
    }
    return 0;
}
static inline int64_t CopyBasicAsInteger(const char* text, int8_t flag, struct AlgodalParser_Basic basic)
{
    if(1 == basic.current_state)
    {
        return basic.number;
    }
    else
    if(3 == basic.current_state)
    {
        char* temp_chars = (char*)malloc(basic.parsed.length + 1);
        memset(temp_chars, 0, basic.parsed.length + 1);
        memcpy(temp_chars, &text[basic.parsed.position], basic.parsed.length);
        int64_t integer = ConvertStringToIntegerAccordingToVarTypes(temp_chars, flag);
        free(temp_chars);
        return integer;
    }
    else
    if(2 == basic.current_state)
    {
        return ConvertStringToIntegerAccordingToVarTypes(basic.string, flag);
    }
    return 0;
}
static inline struct AlgodalParser_Basic GetBasicFromArithData(const char* text, struct AlgodalParser_Program Program,int8_t type, int8_t subtype, int64_t value)
{
    if(type)
    {
        if(subtype)
        {
            const char* string = Program.Strings[value].text;
            struct AlgodalParser_Basic basic = CastStringAsBasic(string);
            return basic;
        }
        else
        {
            struct AlgodalParser_Basic basic = CastIntegerAsBasic(value);
            return basic;
        }
    }
    else
    {
        struct AlgodalParser_Basic basic = Program.Variables[value].basic;
        if(IsIntegerTypeForBasicConversion(subtype))
        {
            basic = CastIntegerAsBasic(CopyBasicAsInteger(text, type, basic));
        }
        return basic;
    }
    return APS_CAST(struct AlgodalParser_Basic);
}
static inline struct AlgodalParser_Basic CastBasicAsBasic(const char* text, int8_t type, struct AlgodalParser_Basic basic)
{
    if(IsIntegerTypeForBasicConversion(type))
    {
        basic = CastIntegerAsBasic(CopyBasicAsInteger(text, type, basic));
    }
    return basic;
}
static inline void PrintStack(const char* text, AlgodalParser_Program program)
{
    struct AlgodalParser_Stack stack = *program.Stack;
    cwpc_fprintf(ALGODALPARSER_STDOUT, "===== STACK [%d] =====\n", stack.size);
    if(stack.size)
    {
        for(int32_t i = stack.size - 1; i > -1 ; i--)
        {
            char buffer[1024] = APS_ZERO;
            CopyBasicAsString(text, stack.addr[i], buffer);
            cwpc_fprintf(
                ALGODALPARSER_STDOUT, "[ %2d ] :: %s\n", 
                i, 
                buffer
            );        
        }
    }
}
static inline int BasicComparison(const char* text, int8_t icase, struct AlgodalParser_Basic b0, struct AlgodalParser_Basic b1)
{
    if(b0.current_state == b1.current_state)
    {
        if(3 == b0.current_state)
        {
            const int diff = b0.parsed.length - b1.parsed.length;
            if(0 == diff && 0 < b0.parsed.length)
            {
                char* buf0 = (char*)malloc(b0.parsed.length + 1);
                memset(buf0, 0, b0.parsed.length + 1);
                memcpy(buf0, &text[b0.parsed.position], b0.parsed.length);
                char* buf1 = (char*)malloc(b1.parsed.length + 1);
                memset(buf1, 0, b1.parsed.length + 1);
                memcpy(buf1, &text[b1.parsed.position], b1.parsed.length);
                const int diff = icase ? strcmpnc(buf0, buf1) : strcmp(buf0, buf1);
                free(buf0);
                free(buf1);
                return diff;
            }
            else
            {
                return diff;
            }
        }
        else
        if(2 == b0.current_state)
        {
            if(b0.string && b1.string)
            {
                return icase ? strcmpnc(b0.string, b1.string) : strcmp(b0.string, b1.string);
            }
            else
            {
                if(b0.string) return +1;
                if(b1.string) return -1;
                return 0;
            }
        }
        else
        if(1 == b0.current_state)
        {
            return b0.number - b1.number;
        }
    }
    else
    if(3 == b0.current_state)
    {
        if(2 == b1.current_state)
        {
            if(b1.string)
            {
                char* buf0 = (char*)malloc(b0.parsed.length + 1);
                memset(buf0, 0, b0.parsed.length + 1);
                CopyBasicAsString(text, b0, buf0);
                const int diff = icase ? strcmpnc(buf0, b1.string) : strcmp(buf0, b1.string);
                free(buf0); 
                return diff;
            }
            else
            {
                return +1;
            }
        }
        else
        if(1 == b1.current_state)
        {
            char* buf0 = (char*)malloc(b0.parsed.length + 1);
            memset(buf0, 0, b0.parsed.length + 1);
            CopyBasicAsString(text, b0, buf0);
            int64_t num0 = strtoll(buf0, 0, 10);
            const int diff = num0 - b1.number;
            free(buf0);
            return diff;
        }
    }
    else
    if(2 == b0.current_state)
    {
        if(3 == b1.current_state)
        {
            if(b0.string)
            {
                char* buf1 = (char*)malloc(b1.parsed.length + 1);
                memset(buf1, 0, b1.parsed.length + 1);
                CopyBasicAsString(text, b1, buf1);
                const int diff = icase ? strcmpnc(buf1, b0.string) : strcmp(buf1, b0.string);
                free(buf1); 
                return diff;
            }
            else
            {
                return -1;
            }
        }
        else
        if(1 == b1.current_state)
        {
            if(b0.string)
            {
                int64_t num0 = strtoll(b0.string, 0, 10);
                const int diff = num0 - b1.number;
                return diff;
            }
        }
    }
    else
    if(1 == b0.current_state)
    {
        if(3 == b1.current_state)
        {
            char* buf1 = (char*)malloc(b1.parsed.length + 1);
            memset(buf1, 0, b1.parsed.length + 1);
            CopyBasicAsString(text, b1, buf1);
            int64_t num1 = strtoll(buf1, 0, 10);
            free(buf1); 
            const int diff = b0.number - num1;
            return diff;
        }
        else
        if(2 == b1.current_state)
        {
            if(b1.string)
            {
                int64_t num1 = strtoll(b1.string, 0, 10);
                int diff = b0.number - num1;
                return diff;
            }
            else
            {
                return +1;
            }
        }
    }
    return 0;
}
static inline void PrintVariables(const char* text, AlgodalParser_Program program)
{
    cwpc_fprintf(ALGODALPARSER_STDOUT, "===== VARIABLES [%d] =====\n", program.CountOfVariables);
    for(uint32_t i = 0; i < program.CountOfVariables; i++)
    {
        char buffer[1024] = APS_ZERO;
        CopyBasicAsString(text, program.Variables[i].basic, buffer);
        cwpc_fprintf(
            ALGODALPARSER_STDOUT, "&%-8s :: %s\n", 
            program.Variables[i].name, 
            buffer
        );        
    }
}
static inline void PrintVariable(const char* text, AlgodalParser_Program program, uint16_t index)
{
    cwpc_fprintf(ALGODALPARSER_STDOUT, "VARIABLE(%d)::", index);
    char buffer[1024] = APS_ZERO;
    CopyBasicAsString(text, program.Variables[index].basic, buffer);
    int length = strlen(buffer);
    if(IsUTF8Malformed(buffer, length))
    {
        cwpc_fprintf(
            ALGODALPARSER_STDOUT, "&%s::", 
            program.Variables[index].name
        ); 
        PrintHex(buffer, length);   
        cwpc_fprintf(ALGODALPARSER_STDOUT, "\n");      
    }
    else
    {
        cwpc_fprintf(
            ALGODALPARSER_STDOUT, "&%s::%s\n", 
            program.Variables[index].name, 
            buffer
        ); 
    }
}
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
    uint32_t     ErrorSize;
};
struct AnalyzeExtra
{
    uint32_t FurthestTokenQueryIndex;
};
struct TokenizeExtra
{
    int8_t res;
};
inline static int CharsAvailable(struct ParserInput Input)
{
    return Input.IndexOfChars < Input.SizeOfChars;
}
inline static int64_t GetRemainingChars(struct ParserInput Input)
{
    return (int64_t)Input.SizeOfChars - (int64_t)Input.IndexOfChars;
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
    struct ParserOutput andoutput = APS_ZERO;
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
    struct ParserOutput notoutput = APS_ZERO;
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
inline static int OutputIsGreater(struct ParserOutput A, struct ParserOutput B)
{
    if(A.Flags == 0 && B.Flags == 0)
    {
        return A.Size > B.Size;
    }
    else
    {
        return A.Flags < B.Flags;
    }
    return 0;
}
inline static int OutputIsEqual(struct ParserOutput A, struct ParserOutput B)
{
    return A.Size == B.Size && A.Flags == B.Flags;
}
inline static struct ParserOutput GetMaxOutput(struct AlgodalParser_Program Program, struct ParserOutput *addr, uint16_t size, uint8_t addFlags)
{
    struct ParserOutput output = addr[0];
    uint8_t dup = 0;
    uint16_t flag = Program.Tokenizers[0].flag;
    for(uint16_t i = 1; i < size; i++)
    {
        if(OutputIsGreater(addr[i], output))
        {
            output = addr[i];
            output.value_current = i;
            dup = 0;
            flag = Program.Tokenizers[i].flag;
        }
        else
        if(OutputIsEqual(addr[i], output))
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
inline static uint32_t GetUnicode(struct ParserInput Input)
{
    if(CharsAvailable(Input))
    {
        return algodalparser_utf8_read(&Input.Chars[Input.IndexOfChars]);
    }
    return 0;
}
inline static uint32_t ReadNewline(struct ParserInput Input)
{
    const int64_t rem_chars = GetRemainingChars(Input);
    if(rem_chars > 1)
    {
        if(
            Input.Chars[Input.IndexOfChars] == '\r' &&
            Input.Chars[Input.IndexOfChars + 1] == '\n'
        ) return 1;
    }
    if(rem_chars > 0)
    {
        if(Input.Chars[Input.IndexOfChars] == '\r') return 1;
        if(Input.Chars[Input.IndexOfChars] == '\n') return 1;
    }
    return 0;
}
inline static uint32_t ReadXSpace(struct ParserInput Input)
{
    if(CharsAvailable(Input))
    {
        if(Input.Chars[Input.IndexOfChars] == '\t') return 1;
        if(Input.Chars[Input.IndexOfChars] == ' ') return 1;
    }
    return 0;
}
inline static uint32_t GetSizeOfUnicode(struct ParserInput Input)
{
    if(CharsAvailable(Input))
    {
        return utf8_get_unicode_size(algodalparser_utf8_read(&Input.Chars[Input.IndexOfChars]));
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
inline static int8_t equal(uint8_t icase, uint32_t A, uint32_t B)
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
inline static uint32_t OrderByBasic
(
    struct ParserInput input,
    uint8_t icase, 
    struct AlgodalParser_Basic basic
)
{
    char temp_chars[1024] = APS_ZERO;
    struct AlgodalParser_String string = APS_ZERO;
    if(basic.current_state == 3)
    {
        memcpy(temp_chars, &input.refOfText[basic.parsed.position], basic.parsed.length);
        string.text = temp_chars;
        string.length = basic.parsed.length;
    }
    else if(basic.current_state == 1)
    {
        string.length = cwpc_sprintf(temp_chars, "%ld", basic.number);
        string.text = temp_chars;
    }
    else
    if(basic.current_state == 2)
    {
        string.text = (char*)basic.string;
        string.length = string.text ? strlen(string.text) : 0;
    }
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
            const uint32_t stringcode = algodalparser_utf8_read(&string.text[offset]);
            const uint32_t textcode = algodalparser_utf8_read(&input.Chars[input.IndexOfChars + offset]);
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
inline static uint32_t ExactByBasic
(
    struct ParserInput input,  
    uint8_t icase, 
    struct AlgodalParser_Basic basic
)
{
    char temp_chars[1024] = APS_ZERO;
    struct AlgodalParser_String string = APS_ZERO;
    if(basic.current_state == 3)
    {
        memcpy(temp_chars, &input.refOfText[basic.parsed.position], basic.parsed.length);
        string.text = temp_chars;
        string.length = basic.parsed.length;
    }
    else if(basic.current_state == 1)
    {
        string.length = cwpc_sprintf(temp_chars, "%ld", basic.number);
        string.text = temp_chars;
    }
    else
    if(basic.current_state == 2)
    {
        string.text = (char*)basic.string;
        string.length = string.text ? strlen(string.text) : 0;
    }
    if(CharsAvailableAtleast(input, string.length))
    {
        size_t offset = 0;
        while(offset < string.length && (offset + input.IndexOfChars) < input.SizeOfChars )
        {
            const uint32_t stringcode = algodalparser_utf8_read(&string.text[offset]);
            const uint32_t textcode = algodalparser_utf8_read(&input.Chars[input.IndexOfChars + offset]);
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
        const uint32_t textcode = algodalparser_utf8_read(&input.Chars[input.IndexOfChars]);
        size_t offset = 0;
        while(offset < string.length)
        {
            const uint32_t stringcode = algodalparser_utf8_read(&string.text[offset]);
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
inline static uint32_t OneofByBasic
(
    struct ParserInput input, 
    uint8_t icase, 
    struct AlgodalParser_Basic basic
)
{
    char temp_chars[1024] = APS_ZERO;
    struct AlgodalParser_String string = APS_ZERO;
    if(basic.current_state == 3)
    {
        memcpy(temp_chars, &input.refOfText[basic.parsed.position], basic.parsed.length);
        string.text = temp_chars;
        string.length = basic.parsed.length;
    }
    else if(basic.current_state == 1)
    {
        string.length = cwpc_sprintf(temp_chars, "%ld", basic.number);
        string.text = temp_chars;
    }    
    else
    if(basic.current_state == 2)
    {
        string.text = (char*)basic.string;
        string.length = string.text ? strlen(string.text) : 0;
    }
    if(CharsAvailable(input))
    {
        const uint32_t textcode = algodalparser_utf8_read(&input.Chars[input.IndexOfChars]);
        size_t offset = 0;
        while(offset < string.length)
        {
            const uint32_t stringcode = algodalparser_utf8_read(&string.text[offset]);
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
inline static uint16_t GetActionIndexByBasic(
    AlgodalParser_Program program, 
    struct ParserInput input,  
    struct AlgodalParser_Basic basic
)
{
    char temp_chars[1024] = APS_ZERO;
    struct AlgodalParser_String string = APS_ZERO;
    if(basic.current_state == 3)
    {
        memcpy(temp_chars, &input.refOfText[basic.parsed.position], basic.parsed.length);
        string.text = temp_chars;
        string.length = basic.parsed.length;
    }
    else if(basic.current_state == 1)
    {
        string.length = cwpc_sprintf(temp_chars, "%ld", basic.number);
        string.text = temp_chars;
    }
    else
    if(basic.current_state == 2)
    {
        string.text = (char*)basic.string;
        string.length = string.text ? strlen(string.text) : 0;
    }
    for(uint16_t i = 0; i < program.CountOfActions; i++)
    {
        struct AlgodalParser_Action action = program.Actions[i];
        const char* name = program.Strings[action.indexOfString].text;
        if(strcmpnc(name, string.text) == 0)
        {
            return i;
        }
    }
    return program.CountOfActions;
}
inline static uint16_t GetActionIndexOrTokenizerIdByBasic(
    AlgodalParser_Program program, 
    struct ParserInput input,  
    struct AlgodalParser_Basic basic,
    int8_t* is_tokenizer
)
{
    char temp_chars[1024] = APS_ZERO;
    struct AlgodalParser_String string = APS_ZERO;
    if(basic.current_state == 3)
    {
        memcpy(temp_chars, &input.refOfText[basic.parsed.position], basic.parsed.length);
        string.text = temp_chars;
        string.length = basic.parsed.length;
    }
    else if(basic.current_state == 1)
    {
        string.length = cwpc_sprintf(temp_chars, "%ld", basic.number);
        string.text = temp_chars;
    }
    else
    if(basic.current_state == 2)
    {
        string.text = (char*)basic.string;
        string.length = string.text ? strlen(string.text) : 0;
    }
    for(uint16_t i = 0; i < program.CountOfTokenizers; i++)
    {
        struct AlgodalParser_Tokenizer tokenizer = program.Tokenizers[i];
        const char* name = program.Strings[ program.Actions[tokenizer.indexOfAction].indexOfString].text;
        if(strcmpnc(name, string.text) == 0)
        {
            if(is_tokenizer) *is_tokenizer = 1;
            return i;
        }
    }
    for(uint16_t i = 0; i < program.CountOfActions; i++)
    {
        struct AlgodalParser_Action action = program.Actions[i];
        const char* name = program.Strings[action.indexOfString].text;
        if(strcmpnc(name, string.text) == 0)
        {
            if(is_tokenizer) *is_tokenizer = 0;
            return i;
        }
    }
    return program.CountOfActions;
}
inline static uint16_t GetTokenizerIdFromActionIndex(struct AlgodalParser_Program Program, uint16_t index)
{
    for(uint16_t i = 0; i < Program.CountOfTokenizers; i++)
    {
        if(Program.Tokenizers[i].indexOfAction == index)
        {
            return i;
        }
    }
    return Program.CountOfTokenizers;
}
inline static int IsBlankSpaceCharacter(int c)
{
    return
        c == '\r' ||
        c == '\n' ||
        c == '\t' ||
        c == ' '
    ;
}
inline static struct AlgodalParser_Basic TrimBasic
(
    const char* text,
    struct AlgodalParser_Basic basic
)
{
    if(basic.current_state == 3 && basic.parsed.length)  
    {
        const char* string = &text[basic.parsed.position];
        int16_t i;
        for(i = basic.parsed.length - 1; i > 0; i--)
        {
            if(IsBlankSpaceCharacter(string[i]))
            {
                continue;
            }
        }
        basic.parsed.length = i + 1;
    }
    return basic;
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
    const uint32_t textcode = algodalparser_utf8_read(&input.Chars[input.IndexOfChars]);
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
    const uint32_t textcode = algodalparser_utf8_read(&input.refOfText[input.IndexOfChars]);
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
#define STACK_MAX_ALLOC 8
static inline void StackAlloc(struct AlgodalParser_Stack* stack)
{
    stack->alloc_size += STACK_MAX_ALLOC;
    stack->addr = (struct AlgodalParser_Basic*)realloc(stack->addr, stack->alloc_size * sizeof(struct AlgodalParser_Basic));
}
static inline void StackReduceAllocAttempt(struct AlgodalParser_Stack* stack)
{
    if(stack->alloc_size >= (STACK_MAX_ALLOC * 2) && (stack->size < (stack->alloc_size - STACK_MAX_ALLOC)))
    {
        stack->alloc_size -= STACK_MAX_ALLOC;
        stack->addr = (struct AlgodalParser_Basic*)realloc(stack->addr, stack->alloc_size * sizeof(struct AlgodalParser_Basic));
    }
}
static inline int8_t StackSlotAvailable(struct AlgodalParser_Stack* stack)
{
    return stack->size < stack->alloc_size;
}
static inline void StackPush(struct AlgodalParser_Stack* stack, struct AlgodalParser_Basic basic)
{
    if(!StackSlotAvailable(stack)) StackAlloc(stack);
    stack->addr[stack->size ++] = basic;
}
static inline struct AlgodalParser_Basic StackPop(struct AlgodalParser_Stack* stack)
{
    if(stack->size)
    {
        struct AlgodalParser_Basic pop = stack->addr[-- stack->size];
        StackReduceAllocAttempt(stack);
        return pop;
    }
    return APS_CAST(struct AlgodalParser_Basic);
}
static inline struct AlgodalParser_Basic StackPeek(struct AlgodalParser_Stack* stack)
{
    if(stack->size)
    {
        return stack->addr[stack->size - 1];
    }
    return APS_CAST(struct AlgodalParser_Basic);
}
static inline struct ParserOutput GetArithTrueOutput(struct ParserInput input)
{
    struct ParserOutput output = 
    {
        .ID              = input.ID,
        .IndexOfChars    = input.IndexOfChars,
        .NextIndexOfCode = input.IndexOfCode,        
        .LastToken       = input.LastToken
    };
    output.ZeroCountResult = 1;
    return output;
}
static inline struct ParserOutput GetArithFalseOutput(struct ParserInput input)
{
    struct ParserOutput output = 
    {
        .ID              = input.ID,
        .IndexOfChars    = input.IndexOfChars,
        .NextIndexOfCode = input.IndexOfCode,        
        .LastToken       = input.LastToken
    };
    output.Flags = ALGODAL_PARSING_FAIL;
    return output;
}
static struct ParserOutput GetTokenizeOutput(struct AlgodalParser_Program Program, struct ParserInput Input, struct TokenizeExtra *PtrOfExtra)
{
    VMINFO("--------------------------------\n");
    VMLOG_STAT(Input);
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
                        sumOutput = AddOutputOutput(sumOutput, iterOutput);
                        Output.ErrorSize = sumOutput.Size;
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
                        Output.ErrorSize = output_and.Size;
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
                    Output.ErrorSize = output_not.Size;
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
                    else
                    {
                        Output.ErrorSize = reqOutput.Size;
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
                uint32_t unicode = GetUnicode(Input);
                Output.Size += unicode ? utf8_get_unicode_size(unicode) : 0;
                VMLOG_PROC(ALGPAR_OP_CHR, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_NLN: {
                Output.Size += ReadNewline(Input);
                VMLOG_PROC(ALGPAR_OP_NLN, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_XSP: {
                Output.Size += ReadXSpace(Input);
                VMLOG_PROC(ALGPAR_OP_XSP, Input, Output);
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
            case ALGPAR_OP_V_STO: {
                const uint16_t v_index = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                VMLOG_BRAN(ALGPAR_OP_V_STO, Input, Output);
                struct ParserOutput item = GetTokenizeOutput(Program, Input, PtrOfExtra);
                if(CanContinue(item))
                {
                    Program.Variables[v_index].basic.parsed.position = item.IndexOfChars;
                    Program.Variables[v_index].basic.parsed.length = item.Size;
                    Program.Variables[v_index].basic.current_state = 3;
                    VMLOG_PRINT_VAR(Input.refOfText, Program, v_index);
                }
                Input.IndexOfCode = item.NextIndexOfCode;
                Output = AddOutputOutput(Output, item);
                VMLOG_PROC(ALGPAR_OP_V_STO, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_V_CON:
            {
                const int8_t   type    = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const int8_t   nvari   = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t ovari   = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                struct AlgodalParser_Basic obasic = Program.Variables[ovari].basic;
                if(IsIntegerTypeForBasicConversion(type))
                {
                    Program.Variables[nvari].basic = CastIntegerAsBasic(CopyBasicAsInteger(Input.refOfText, type, obasic));
                    Output = AddOutputOutput(Output, GetArithTrueOutput(Input));
                    VMLOG_PRINT_VAR(Input.refOfText, Program, nvari); 
                    VMLOG_PRINT_VAR(Input.refOfText, Program, ovari); 
                }
                else
                if(IsCopyTypeForBasicConversion(type))
                {
                    Program.Variables[nvari].basic = obasic;
                    Output = AddOutputOutput(Output, GetArithTrueOutput(Input));
                    VMLOG_PRINT_VAR(Input.refOfText, Program, nvari); 
                    VMLOG_PRINT_VAR(Input.refOfText, Program, ovari); 
                }
                else
                {
                    Output = AddOutputOutput(Output, GetArithFalseOutput(Input));
                }
                VMLOG_PROC(ALGPAR_OP_V_CON, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_V_EXT: {
                const uint8_t flag = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t index = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const struct AlgodalParser_Variable var = Program.Variables[index];
                const uint32_t termSize = ExactByBasic(Input, flag, var.basic);
                Output.Size += termSize;
                VMLOG_PROC(ALGPAR_OP_EXT, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_V_ORD: {
                const uint8_t flag = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t index = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const struct AlgodalParser_Variable var = Program.Variables[index];
                uint32_t termSize = OrderByBasic(Input, flag, var.basic);
                Output.Size += termSize;
                VMLOG_PROC(ALGPAR_OP_ORD, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_V_ONE: {
                const uint8_t flag = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t index = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const struct AlgodalParser_Variable var = Program.Variables[index];
                Output.Size += OneofByBasic(Input, flag, var.basic);
                VMLOG_PROC(ALGPAR_OP_ONE, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_V_PNT: {
                const uint8_t flag = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode); (void)flag;
                const uint16_t index = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const struct AlgodalParser_Variable var = Program.Variables[index];
                VMLOG_PRINT_VAR(Input.refOfText, Program, index); 
                const uint16_t action_index = GetActionIndexByBasic(Program, Input, var.basic);
                VMLOG_BRAN(ALGPAR_OP_PNT, Input, Output);
                Output = AddOutputOutput(Output, GetTokenizeOutput(Program, RelateInputToAction(Program, Input, action_index), PtrOfExtra));
                VMLOG_PROC(ALGPAR_OP_PNT, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_V_CNT: {
                const uint8_t  type       = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint8_t  flag       = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                      uint32_t begin      = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint8_t  type2      = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint8_t  flag2      = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                      uint32_t begin2     = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t offsetCode = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t nextCode   = offsetCode + Input.IndexOfCode;                
                uint32_t it = begin, it2 = begin2;
                if(0 == type)
                {
                    const struct AlgodalParser_Variable var = Program.Variables[it];
                    begin = (uint32_t)CopyBasicAsInteger(Input.refOfText, flag, var.basic);
                    VMLOG_PRINT_VAR(Input.refOfText, Program, it); 
                }
                if(0 == type2)
                {
                    const struct AlgodalParser_Variable var = Program.Variables[it2];
                    begin2 = (uint32_t)CopyBasicAsInteger(Input.refOfText, flag2, var.basic);
                    VMLOG_PRINT_VAR(Input.refOfText, Program, it2); 
                }
                else
                if(3 == type2)
                {
                    begin2 = begin;
                }
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
                    else
                    {
                        Output.ErrorSize = reqOutput.Size;
                    }
                }
                Input.IndexOfCode = nextCode;
                Output.ZeroCountResult = begin == 0;                
                VMLOG_PROC(ALGPAR_OP_CNT, Input, Output);              
                continue;
            } break;
            case ALGPAR_OP_BYT: {
                Output.Size += CharsAvailable(Input) ? sizeof(uint8_t) : 0;
                VMLOG_PROC(ALGPAR_OP_BYT, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_L_IFB: {
                const uint16_t  countOfIf  = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  offsetCode = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  nextCode   = offsetCode + Input.IndexOfCode;
                struct ParserOutput item = APS_ZERO;
                for(uint16_t i = 0; i < countOfIf; i++)
                {
                    VMLOG_BRAN(ALGPAR_OP_L_IFB, Input, Output);
                    item = GetTokenizeOutput(Program, Input, PtrOfExtra);
                    if (CanContinueBySizeOnly(item))  
                    {                                               
                        break;
                    }
                    else
                    {
                        Input.IndexOfCode = item.NextIndexOfCode;
                        continue;
                    }
                }
                Output = AddOutputOutput(Output, item); 
                Input.IndexOfCode = nextCode;
                VMLOG_PROC(ALGPAR_OP_L_IFB, Input, Output);    
                continue;
            } break;
            case ALGPAR_OP_L_IF0: {
                const uint16_t  countOfItem  = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  offsetCode = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  nextCode   = offsetCode + Input.IndexOfCode;
                struct ParserOutput ifOutput = Output;
                (void) countOfItem;
                VMLOG_BRAN(ALGPAR_OP_L_IF0, Input, Output);
                struct ParserOutput condOutput = GetTokenizeOutput(Program, Input, PtrOfExtra);
                if(CanContinue(condOutput)) 
                {
                    Input.IndexOfChars += condOutput.Size;
                    Input.IndexOfCode = condOutput.NextIndexOfCode;
                    ifOutput = AddOutputOutput(ifOutput, condOutput);
                    VMLOG_BRAN(ALGPAR_OP_L_IF0, Input, Output);
                    struct ParserOutput trueItemOutput = GetTokenizeOutput(Program, Input, PtrOfExtra);
                    if(!CanContinue(trueItemOutput)) trueItemOutput.Flags |= ALGODAL_PARSING_FAIL;  
                    Input.IndexOfChars += trueItemOutput.Size;
                    Input.IndexOfCode = trueItemOutput.NextIndexOfCode;
                    ifOutput = AddOutputOutput(ifOutput, trueItemOutput);
                    Output = ifOutput;
                }
                else
                {
                    Output.ZeroCountResult = 1;
                }
                Input.IndexOfCode = nextCode;
                VMLOG_PROC(ALGPAR_OP_L_IF0, Input, Output);    
                continue;
            } break;
            case ALGPAR_OP_S_PUS:
            {
                const int8_t   type    = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const int8_t   subtype = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t value   = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                if(type)
                {
                    if(subtype)
                    {
                        const char* string = Program.Strings[value].text;
                        struct AlgodalParser_Basic basic = CastStringAsBasic(string);
                        StackPush(Program.Stack, basic);
                    }
                    else
                    {
                        struct AlgodalParser_Basic basic = CastIntegerAsBasic(value);
                        StackPush(Program.Stack, basic);
                    }
                }
                else
                {
                    struct AlgodalParser_Basic basic = Program.Variables[value].basic;
                    if(IsIntegerTypeForBasicConversion(subtype))
                    {
                        basic = CastIntegerAsBasic(CopyBasicAsInteger(Input.refOfText, type, basic));
                    }
                    StackPush(Program.Stack, basic);
                }
                Output = AddOutputOutput(Output, GetArithTrueOutput(Input));
                VMLOG_PROC(ALGPAR_OP_S_PUS, Input, Output);
                VMLOG_PRINT_STACK(Input.refOfText, Program);  
                continue;
            } break;
            case ALGPAR_OP_S_POP:
            {
                const int8_t   type    = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const int8_t   subtype = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t value   = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                (void)type;
                (void)subtype;
                struct AlgodalParser_Basic basic = StackPop(Program.Stack);
                if(IsIntegerTypeForBasicConversion(subtype))
                {
                    basic = CastIntegerAsBasic(CopyBasicAsInteger(Input.refOfText, type, basic));
                }
                Program.Variables[value].basic = basic;
                VMLOG_PRINT_VARS(Input.refOfText, Program);
                Output = AddOutputOutput(Output, GetArithTrueOutput(Input));
                VMLOG_PROC(ALGPAR_OP_S_POP, Input, Output);
                VMLOG_PRINT_STACK(Input.refOfText, Program);  
                continue;
            } break;
            case ALGPAR_OP_S_PEK:
            {
                const int8_t   type    = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const int8_t   subtype = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t value   = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                (void)type;
                struct AlgodalParser_Basic basic = StackPeek(Program.Stack);
                if(IsIntegerTypeForBasicConversion(subtype))
                {
                    basic = CastIntegerAsBasic(CopyBasicAsInteger(Input.refOfText, type, basic));
                }
                Program.Variables[value].basic = basic;
                VMLOG_PRINT_VARS(Input.refOfText, Program);
                Output = AddOutputOutput(Output, GetArithTrueOutput(Input));
                VMLOG_PROC(ALGPAR_OP_S_PEK, Input, Output);
                VMLOG_PRINT_STACK(Input.refOfText, Program);  
                continue;
            } break;
            case ALGPAR_OP_A_NE0:
            case ALGPAR_OP_A_EQ0:
            case ALGPAR_OP_A_LTE:
            case ALGPAR_OP_A_GTE:
            case ALGPAR_OP_A_LT0:
            case ALGPAR_OP_A_GT0:
            {
                const int8_t   icase    = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const int8_t   type0    = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const int8_t   subtype0 = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t value0   = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const int8_t   type1    = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const int8_t   subtype1 = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t value1   = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                struct AlgodalParser_Basic basic0 = GetBasicFromArithData(Input.refOfText, Program, type0, subtype0, value0);
                struct AlgodalParser_Basic basic1 = GetBasicFromArithData(Input.refOfText, Program, type1, subtype1, value1);
                const int cr = BasicComparison(Input.refOfText, icase, basic0, basic1);
                struct ParserOutput item = (IsArithDiffSuccessByOpcode(opcode, cr)) ? GetArithTrueOutput(Input) : GetArithFalseOutput(Input);
                Output = AddOutputOutput(Output, item);
                VMLOG_PROC(opcode, Input, Output);
                continue;
            } break;
            default: {
                Output.Flags |= ALGODAL_PARSING_ERROR;
                VMLOG_PROC(opcode, Input, Output);
                goto EXIT;
            } break;
        }
    } 
    while(!Output.Flags);
    EXIT:
    Output.NextIndexOfCode = Input.IndexOfCode;
    Output.priority = Input.priority;
    if(Output.Size > Output.ErrorSize) Output.ErrorSize = Output.Size;
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
            outputs[i] = APS_CAST(struct ParserOutput);
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
        Program.RV1[i] = outputs[i].ErrorSize;  
        if((Program.Flags->first_entry & 1) == 1) 
            if(outputs[i].Size > 0 && outputs[i].Flags == 0)
                return outputs[i];;
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
static inline void TokenizeResultAddToken(struct AlgodalParser_TokenizeResult* ptr, struct AlgodalParser_Token token, struct AlgodalParser_Token *returnLastToken)
{
    const uint32_t index = ptr->tokens.size ++;
    ptr->tokens.addr = (struct AlgodalParser_Token *)realloc(ptr->tokens.addr, sizeof(struct AlgodalParser_Token) * ptr->tokens.size);
    ptr->tokens.addr[index] = token;
    if(returnLastToken) returnLastToken[0] = token;
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
        ptr->error.eval1 = output.value_current;
        ptr->error.eval2 = output.value_duplicated;
        ptr->error.text_length = size;
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
    TokenizeResultAddToken(ptr, token, returnLastToken);
}
struct AlgodalParser_TokenizeResult AlgodalParser_GetTokenizeResult(struct AlgodalParser_Program Program, const char* text, const uint32_t size, struct AlgodalParser_OtherTokenizeParams* oparams)
{
    VMINFO("\nTOKENIZATION VIRTUAL MACHINE LOG\n");
    (void)oparams;
    struct AlgodalParser_TokenizeResult TokenizeResult = APS_ZERO;
    uint32_t index = 0;
    struct ParserInput Input =
    {
        .Chars = text, 
        .SizeOfChars = size,
        .LastToken = {.id = UINT16_MAX}, 
        .refOfText = text
    };
    VMLOG_PRINT_VARS(text, Program);  
    VMLOG_PRINT_STACK(Input.refOfText, Program);
    if(Program.Special->UseTokenphaseInitialActionCall)
    {
        struct ParserInput input = Input;
        struct TokenizeExtra extra = APS_ZERO;
        input.ID = Program.CountOfTokenizers;
        input.IndexOfCode = Program.Actions[Program.Special->TokenphaseInitialActionCallAction].indexOfCode;
        #ifdef ALGODAL_PARSER_LOGGER_DEBUG
        input.LastActionName = Program.Strings[Program.Actions[Program.Special->TokenphaseInitialActionCallAction].indexOfString].text;
        #endif
        (void)GetTokenizeOutput(Program, input, &extra);
    }
    while(index < size)
    {
        Input.IndexOfChars = index;
        struct TokenizeExtra extra = APS_ZERO;
        struct ParserOutput Output = GetMaxTokenizeOutput(Program, Input, &extra);
        TokenizeResultAddOutput(Program, &TokenizeResult, Output, index, size, &extra, &Input.LastToken);
        if(TokenizeResult.error.flags) break;
        index += Output.Size;
    }
    if(0 == TokenizeResult.error.flags && Program.Special->UseTokenphasePopTokenCreation)
    {
        while(Program.Stack->size > (uint32_t)Program.Special->TokenphasePopTokenCreationStop)
        {
            StackPop(Program.Stack);
            uint16_t id = GetTokenizerIdFromActionIndex(Program, Program.Special->TokenphasePopTokenCreationLabel);
            struct AlgodalParser_Token token = {.id = id, .index = size};
            TokenizeResultAddToken(&TokenizeResult, token, 0);
        }
        VMLOG_PRINT_STACK(text, Program);
    }
    if(0 == TokenizeResult.error.flags && Program.Special->UseTokenphasePopAll)
    {
        while(Program.Stack->size > 0) StackPop(Program.Stack);
        VMLOG_PRINT_STACK(text, Program);
    }
    TokenizeResult.error.phase = 1;
    return TokenizeResult;
}
const char * AlgodalParser_GetTokenizerString_READONLY(struct AlgodalParser_Program program, unsigned int id)
{
    return program.Strings[program.Actions[program.Tokenizers[id].indexOfAction].indexOfString].text;
}
/*static char * HorizontSpaceString(char * string)
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
}*/
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
inline static struct AlgodalParser_Node *CreateInvisibleNode(void)
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
    const uint32_t textcode = algodalparser_utf8_read(&input.refOfText[token.index]);
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
static inline uint32_t GetCharLengthOfTokensFromOutput(struct ParserInput input, struct ParserOutput output)
{
    if(output.Size)
    {
        uint32_t start_position = input.Tokens[output.IndexOfTokens].index;
        struct AlgodalParser_Token lastToken = input.Tokens[start_position + output.Size - 1];
        uint32_t end_position = (lastToken.index + lastToken.size);
        return end_position - start_position;
    }
    return 0;
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
                struct ParserOutput output_selected = APS_ZERO;
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
                        sumOutput = AddOutputOutput(sumOutput, iterOutput);
                        Output.ErrorSize = sumOutput.Size;
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
                        Output.ErrorSize = output_and.Size;
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
                    Output.ErrorSize = output_not.Size;
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
                    } 
                    else
                    {
                        Output.ErrorSize = reqOutput.Size;
                    }             
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
            case ALGPAR_OP_V_STO: {
                const uint16_t v_index = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                struct AlgodalParser_Node *node      = 0;
                VMLOG_BRAN(ALGPAR_OP_V_STO, Input, Output);
                struct ParserOutput item = GetAnalyzeOutput(Program, Input, &node, PtrOfExtra);
                if(CanContinue(item))
                {
                    Program.Variables[v_index].basic.parsed.position = Input.Tokens[item.IndexOfTokens].index;
                    Program.Variables[v_index].basic.parsed.length = GetCharLengthOfTokensFromOutput(Input, item);
                    Program.Variables[v_index].basic.current_state = 3;
                    VMLOG_PRINT_VAR(Input.refOfText, Program, v_index);
                }
                Input.IndexOfCode = item.NextIndexOfCode;
                Output = AddOutputOutput(Output, item);
                AddNodeNode(PtrOfNode, node);
                VMLOG_PROC(ALGPAR_OP_V_STO, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_V_CON:
            {
                const int8_t   type    = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const int8_t   nvari   = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t ovari   = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                struct AlgodalParser_Basic obasic = Program.Variables[ovari].basic;
                if(IsIntegerTypeForBasicConversion(type))
                {
                    Program.Variables[nvari].basic = CastIntegerAsBasic(CopyBasicAsInteger(Input.refOfText, type, obasic));
                    Output = AddOutputOutput(Output, GetArithTrueOutput(Input));
                    VMLOG_PRINT_VAR(Input.refOfText, Program, nvari); 
                    VMLOG_PRINT_VAR(Input.refOfText, Program, ovari); 
                }
                else
                if(IsCopyTypeForBasicConversion(type))
                {
                    Program.Variables[nvari].basic = obasic;
                    Output = AddOutputOutput(Output, GetArithTrueOutput(Input));
                    VMLOG_PRINT_VAR(Input.refOfText, Program, nvari); 
                    VMLOG_PRINT_VAR(Input.refOfText, Program, ovari); 
                }
                else
                {
                    Output = AddOutputOutput(Output, GetArithFalseOutput(Input));
                }
                VMLOG_PROC(ALGPAR_OP_V_CON, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_V_PNT: {
                const uint8_t flag = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode); (void)flag;
                const uint16_t index = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const struct AlgodalParser_Variable var = Program.Variables[index];
                VMLOG_PRINT_VAR(Input.refOfText, Program, index); 
                int8_t is_tokenizer = -1;
                const uint16_t code_index = GetActionIndexOrTokenizerIdByBasic(Program, Input, var.basic, &is_tokenizer);
                struct AlgodalParser_Node *nodeOfChildren = 0;
                VMLOG_BRAN(ALGPAR_OP_V_PNT, Input, Output);
                struct ParserOutput reqOutput = APS_ZERO;
                struct AlgodalParser_Node *ThisNode = 0;
                if(is_tokenizer == 0)
                {
                    reqOutput = GetAnalyzeOutput(Program, RelateInputToAction(Program, Input, code_index), &nodeOfChildren, PtrOfExtra);
                    ThisNode = CreateNode(Program, Input.IndexOfTokens, reqOutput.Size, code_index, 0);
                    Output = AddOutputOutput(Output, reqOutput);
                    AddNodeNode(PtrOfNode, AddNodeNode(&ThisNode, nodeOfChildren));
                }
                else
                if(is_tokenizer == 1)
                {
                    const uint16_t indexOfAction = Program.Tokenizers[code_index].indexOfAction;
                    const uint32_t OpSize = Term(Program, Input, code_index);
                    Output.Size += OpSize;
                    struct AlgodalParser_Node *node = CreateNode(Program, Input.IndexOfTokens, OpSize, indexOfAction, 1);
                    AddNodeNode(PtrOfNode, node);
                }
                VMLOG_PROC(ALGPAR_OP_V_PNT, Input, Output);
                continue;
            } break;
            case ALGPAR_OP_V_CNT: {
                const uint8_t  type       = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint8_t  flag       = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                      uint32_t begin      = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint8_t  type2      = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint8_t  flag2      = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                      uint32_t begin2     = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t offsetCode = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t nextCode   = offsetCode + Input.IndexOfCode;                
                uint32_t it = begin, it2 = begin2;
                if(0 == type)
                {
                    const struct AlgodalParser_Variable var = Program.Variables[it];
                    begin = (uint32_t)CopyBasicAsInteger(Input.refOfText, flag, var.basic);
                    VMLOG_PRINT_VAR(Input.refOfText, Program, it); 
                }
                if(0 == type2)
                {
                    const struct AlgodalParser_Variable var = Program.Variables[it2];
                    begin2 = (uint32_t)CopyBasicAsInteger(Input.refOfText, flag2, var.basic);
                    VMLOG_PRINT_VAR(Input.refOfText, Program, it2); 
                }
                else
                if(3 == type2)
                {
                    begin2 = begin;
                }
                const uint32_t end        = (begin2 > begin) ? begin2 - begin : 0;
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
                    } 
                    else
                    {
                        Output.ErrorSize = reqOutput.Size;
                    }             
                }
                Input.IndexOfCode = nextCode;
                Output.ZeroCountResult = begin == 0;
                UpdateAnalyzeExtraFurthestTokenQueryIndex(PtrOfExtra, Input);            
                VMLOG_PROC(ALGPAR_OP_CNT, Input, Output);              
                continue;
            } break;
            case ALGPAR_OP_L_IFB: {
                const uint16_t  countOfIf  = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  offsetCode = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  nextCode   = offsetCode + Input.IndexOfCode;
                struct ParserOutput item = APS_ZERO;
                struct AlgodalParser_Node *node = 0;
                for(uint16_t i = 0; i < countOfIf; i++)
                {
                    VMLOG_BRAN(ALGPAR_OP_L_IFB, Input, Output);
                    item = GetAnalyzeOutput(Program, Input, &node, PtrOfExtra);
                    if (CanContinueBySizeOnly(item))  
                    {                                               
                        break;
                    }
                    else
                    {
                        DestroyNode(&node);
                        Input.IndexOfCode = item.NextIndexOfCode;                        
                        continue;
                    }
                }
                AddNodeNode(PtrOfNode, node);
                Output = AddOutputOutput(Output, item); 
                Input.IndexOfCode = nextCode;
                VMLOG_PROC(ALGPAR_OP_L_IFB, Input, Output);    
                continue;
            } break;
            case ALGPAR_OP_L_IF0: {
                const uint16_t  countOfItem  = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  offsetCode = uint16_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint16_t  nextCode   = offsetCode + Input.IndexOfCode;
                struct ParserOutput ifOutput = Output;
                struct AlgodalParser_Node *node = CreateInvisibleNode();
                (void) countOfItem;
                VMLOG_BRAN(ALGPAR_OP_L_IF0, Input, Output);                
                struct ParserOutput condOutput = GetAnalyzeOutput(Program, Input, &node, PtrOfExtra);
                if(CanContinue(condOutput)) 
                {
                    Input.IndexOfTokens += condOutput.Size;
                    Input.IndexOfCode = condOutput.NextIndexOfCode;
                    ifOutput = AddOutputOutput(ifOutput, condOutput);
                    VMLOG_BRAN(ALGPAR_OP_L_IF0, Input, Output);
                    struct ParserOutput trueItemOutput = GetAnalyzeOutput(Program, Input, &node, PtrOfExtra);
                    if(!CanContinue(trueItemOutput)) trueItemOutput.Flags |= ALGODAL_PARSING_FAIL;  
                    Input.IndexOfTokens += trueItemOutput.Size;
                    Input.IndexOfCode = trueItemOutput.NextIndexOfCode;
                    ifOutput = AddOutputOutput(ifOutput, trueItemOutput);
                    Output = ifOutput;
                    AddNodeNode(PtrOfNode, node);
                }
                else
                {
                    DestroyNode(&node);
                    Output.ZeroCountResult = 1;
                }
                Input.IndexOfCode = nextCode;
                VMLOG_PROC(ALGPAR_OP_L_IF0, Input, Output);    
                continue;
            } break;
            case ALGPAR_OP_S_PUS:
            {
                const int8_t   type    = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const int8_t   subtype = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t value   = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                if(type)
                {
                    if(subtype)
                    {
                        const char* string = Program.Strings[value].text;
                        struct AlgodalParser_Basic basic = CastStringAsBasic(string);
                        StackPush(Program.Stack, basic);
                    }
                    else
                    {
                        struct AlgodalParser_Basic basic = CastIntegerAsBasic(value);
                        StackPush(Program.Stack, basic);
                    }
                }
                else
                {
                    struct AlgodalParser_Basic basic = Program.Variables[value].basic;
                    StackPush(Program.Stack, basic);
                }
                Output = AddOutputOutput(Output, GetArithTrueOutput(Input));
                VMLOG_PROC(ALGPAR_OP_S_PUS, Input, Output);
                VMLOG_PRINT_STACK(Input.refOfText, Program);  
                continue;
            } break;
            case ALGPAR_OP_S_POP:
            {
                const int8_t   type    = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const int8_t   subtype = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t value   = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                (void)type;
                (void)subtype;
                if(1)
                {
                    struct AlgodalParser_Basic basic = StackPop(Program.Stack);
                    Program.Variables[value].basic = basic;
                    VMLOG_PRINT_VARS(Input.refOfText, Program);
                }
                Output = AddOutputOutput(Output, GetArithTrueOutput(Input));
                VMLOG_PROC(ALGPAR_OP_S_POP, Input, Output);
                VMLOG_PRINT_STACK(Input.refOfText, Program);  
                continue;
            } break;
            case ALGPAR_OP_S_PEK:
            {
                const int8_t   type    = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const int8_t   subtype = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t value   = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                (void)type;
                (void)subtype;
                struct AlgodalParser_Basic basic = StackPeek(Program.Stack);
                if(IsIntegerTypeForBasicConversion(subtype))
                {
                    basic = CastIntegerAsBasic(CopyBasicAsInteger(Input.refOfText, type, basic));
                }
                Program.Variables[value].basic = basic;
                VMLOG_PRINT_VARS(Input.refOfText, Program);
                Output = AddOutputOutput(Output, GetArithTrueOutput(Input));
                VMLOG_PROC(ALGPAR_OP_S_PEK, Input, Output);
                VMLOG_PRINT_STACK(Input.refOfText, Program);  
                continue;
            } break;
            case ALGPAR_OP_A_NE0:
            case ALGPAR_OP_A_EQ0:
            case ALGPAR_OP_A_LTE:
            case ALGPAR_OP_A_GTE:
            case ALGPAR_OP_A_LT0:
            case ALGPAR_OP_A_GT0:
            {
                const int8_t   icase    = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const int8_t   type0    = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const int8_t   subtype0 = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t value0   = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const int8_t   type1    = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const int8_t   subtype1 = uint8_binread(Program.CodeOfActions, &Input.IndexOfCode);
                const uint32_t value1   = uint32_binread(Program.CodeOfActions, &Input.IndexOfCode);
                struct AlgodalParser_Basic basic0 = GetBasicFromArithData(Input.refOfText, Program, type0, subtype0, value0);
                struct AlgodalParser_Basic basic1 = GetBasicFromArithData(Input.refOfText, Program, type1, subtype1, value1);
                const int cr = BasicComparison(Input.refOfText, icase, basic0, basic1);
                struct ParserOutput item = (IsArithDiffSuccessByOpcode(opcode, cr)) ? GetArithTrueOutput(Input) : GetArithFalseOutput(Input);
                Output = AddOutputOutput(Output, item);
                VMLOG_PROC(opcode, Input, Output);
                continue;
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
    if(Output.Size > Output.ErrorSize) Output.ErrorSize = Output.Size;
    return Output;
}
inline static struct ParserOutput GetMaxOutputWithNode(struct ParserOutput addr[], uint16_t size, struct AlgodalParser_Node *arrOfNodes[], struct AlgodalParser_Node **ptrOfNode)
{
    struct ParserOutput output_selected = APS_ZERO;
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
        Program.RV1[i] = outputs[i].ErrorSize;
        entryNodes[i] = CreateNode(Program, input.IndexOfTokens, outputs[i].Size, indexOfAction, 0);
        AddNodeNode(&entryNodes[i], nodes[i]);
        if((Program.Flags->first_entry & 2) == 2)
            if(outputs[i].Size > 0 && outputs[i].Flags == 0)
            {
                AddNodeNode(PtrOfNode, entryNodes[i]);
                return outputs[i];
            } 
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
        ptr->error.eval1 = output.value_current;
        ptr->error.eval2 = output.value_duplicated;
    }
}
struct AlgodalParser_AnalyzeResult AlgodalParser_GetAnalyzeResult(struct AlgodalParser_Program Program, const char *text, struct AlgodalParser_Token *tokens, const uint32_t size, struct AlgodalParser_OtherAnalyzeParams* oparams)
{
    VMINFO("\nANALYZATION VIRTUAL MACHINE LOG\n");
    int8_t loopOnce = oparams ? oparams->loopOnce : 0;
    struct AlgodalParser_AnalyzeResult AlgodalParser_AnalyzeResult = APS_ZERO;
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
            if(AlgodalParser_AnalyzeResult.error.flags)
            {
                break;
            }
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
    AlgodalParser_AnalyzeResult.error.phase = 2;
    return AlgodalParser_AnalyzeResult;
}
static void PrintIndent(uint32_t indent)
{
    for(uint32_t i = 0; i < indent; i++) cwpc_fprintf(ALGODALPARSER_STDOUT, "\t");
}
const char *AlgodalParser_GetActionString_READONLY(struct AlgodalParser_Program program, unsigned int id)
{
    return program.Strings[program.Actions[id].indexOfString].text;
}
void AlgodalParser_PrintNode(AlgodalParser_Ast ast, struct AlgodalParser_Node *node, uint16_t indent)
{
    if(node->invisible)
    {
        for(uint32_t i = 0; i < node->children.size; i++)
        {
            AlgodalParser_PrintNode(ast, node->children.addr[i], indent);
        }
    }
    else
    {
        PrintIndent(indent);
        char lineBuffer[512];
        cwpc_fprintf(ALGODALPARSER_STDOUT, "%s ", AlgodalParser_GetLinenumber(ast.linenumber, ast.tokens.addr[node->indexOfToken].index, lineBuffer));
        char key[ast.tokens.addr[node->indexOfToken].size + 1];
        key[ast.tokens.addr[node->indexOfToken].size] = 0;
        AlgodalParser_GetNodeKey(ast, node, key);
        cwpc_fprintf(ALGODALPARSER_STDOUT, "%s ", key);
        const int showNodeValue = SHOW_NODE_VALUE;
        if(GetObjectpointFlag(ast.program, node->indexOfAction) == 0 && showNodeValue)
        {
            cwpc_fprintf(ALGODALPARSER_STDOUT, ": ");
            unsigned int size = AlgodalParser_GetNodeValueSize(ast, node);
            char value[size + 1];
            memset(value, 0, size + 1);
            AlgodalParser_GetNodeValue(ast, node, value);
            AlgodalParser_SimplifyStr(size, value);
            if(IsUTF8Malformed(value, size))
            {
                PrintHex(value, size);         
            }
            else
            {
                cwpc_fprintf(ALGODALPARSER_STDOUT, "%s", value);
            }
        }
        cwpc_fprintf(ALGODALPARSER_STDOUT, "\n");
        for(uint32_t i = 0; i < node->children.size; i++)
        {
            AlgodalParser_PrintNode(ast, node->children.addr[i], indent + 1);
        }
    }
}
void AlgodalParser_PrintNodeSelfOnly(AlgodalParser_Ast ast, struct AlgodalParser_Node *node, uint16_t indent)
{
    if(node->invisible)
    {
        for(uint32_t i = 0; i < node->children.size; i++)
        {
            AlgodalParser_PrintNode(ast, node->children.addr[i], indent);
        }
    }
    else
    {
        PrintIndent(indent);
        char lineBuffer[512];
        cwpc_fprintf(ALGODALPARSER_STDOUT, "%s ", AlgodalParser_GetLinenumber(ast.linenumber, ast.tokens.addr[node->indexOfToken].index, lineBuffer));
        char key[ast.tokens.addr[node->indexOfToken].size + 1];
        key[ast.tokens.addr[node->indexOfToken].size] = 0;
        AlgodalParser_GetNodeKey(ast, node, key);
        cwpc_fprintf(ALGODALPARSER_STDOUT, "%s ", key);
        const int showNodeValue = SHOW_NODE_VALUE;
        if(GetObjectpointFlag(ast.program, node->indexOfAction) == 0 && showNodeValue)
        {
            cwpc_fprintf(ALGODALPARSER_STDOUT, ": ");
            unsigned int size = AlgodalParser_GetNodeValueSize(ast, node);
            char value[size + 1];
            memset(value, 0, size + 1);
            AlgodalParser_GetNodeValue(ast, node, value);
            AlgodalParser_SimplifyStr(size, value);
            if(IsUTF8Malformed(value, size))
            {
                PrintHex(value, size);         
            }
            else
            {
                cwpc_fprintf(ALGODALPARSER_STDOUT, "%s", value);
            }
        }
        cwpc_fprintf(ALGODALPARSER_STDOUT, "\n");
    }
}
void AlgodalParser_PrintAnalyzeResult(AlgodalParser_Ast ast, AlgodalParser_Error error)
{
    for(uint32_t i = 0; i < ast.nodes.size; i++)
    {
        struct AlgodalParser_Node *node = ast.nodes.addr[i];
        AlgodalParser_PrintNode(ast, node, 0);
    }
    AlgodalParser_PrintAnalyzeParserError(ast, error);
}
void AlgodalParser_PrintTokenizeParserError(AlgodalParser_Ast ast, struct AlgodalParser_Error error)
{
    char lineBuffer1[64], lineBuffer2[64];
    if(error.flags & ALGODAL_PARSING_FAIL)
    {
        cwpc_fprintf(ALGODALPARSER_STDERR, "\033[31;1m%s: failed to tokenize text at %s - %s\033[0m\n", ast.program.NameOfParser, AlgodalParser_GetLinenumber(ast.linenumber, error.index, lineBuffer1), AlgodalParser_GetLinenumber(ast.linenumber, error.index2, lineBuffer2));
        char input[4] = APS_ZERO;
        memcpy(input, &ast.text[error.index], sizeof(char));
        cwpc_fprintf(ALGODALPARSER_STDERR, "\033[34;1m[%s] begins with `%s`\033[0m\n", AlgodalParser_GetLinenumber(ast.linenumber, error.index, lineBuffer1), input);
        for(uint16_t i = 0; i < ast.program.CountOfTokenizers; i++)
        {
            if(ast.program.RV1[i])
            {
                const char* text = ast.program.Strings[ast.program.Actions[ast.program.Tokenizers[i].indexOfAction].indexOfString].text;
                char input[4] = APS_ZERO;
                char parsed[256];
                memset(parsed, '.', 128);
                int length = ast.program.RV1[i] > 64 ? 64 : ast.program.RV1[i];
                memset(&parsed[length == 64 ? length+3 : length], 0, 16);
                memcpy(input, &ast.text[error.index + ast.program.RV1[i]], sizeof(char));
                memcpy(parsed, &ast.text[error.index], length);
                cwpc_fprintf(ALGODALPARSER_STDERR, "\033[35;1m[%s] parsed `%s` but not `%s`.\033[0m\n", text, parsed, input);
            }
        }
    }
    if(error.flags & ALGODAL_PARSING_DUP)
    {
        char * tok1 = ast.program.Strings[ast.program.Actions[ast.program.Tokenizers[error.eval1].indexOfAction].indexOfString].text;
        char * tok2 = ast.program.Strings[ast.program.Actions[ast.program.Tokenizers[error.eval2].indexOfAction].indexOfString].text;
        cwpc_fprintf(ALGODALPARSER_STDERR, "\033[31;1m%s: multiple non-discarded tokenizers returned equal tokens at %s - %s: `%s`, `%s`\033[0m\n", ast.program.NameOfParser, AlgodalParser_GetLinenumber(ast.linenumber, error.index, lineBuffer1), AlgodalParser_GetLinenumber(ast.linenumber, error.index2, lineBuffer2), tok1, tok2);
    }
    if(error.flags & ALGODAL_PARSING_ERROR)
    {
        cwpc_fprintf(ALGODALPARSER_STDERR, "\033[31;1m%s: undefined tokenization error occurred at %s - %s\033[0m\n", ast.program.NameOfParser, AlgodalParser_GetLinenumber(ast.linenumber, error.index, lineBuffer1), AlgodalParser_GetLinenumber(ast.linenumber, error.index2, lineBuffer2));
    }
}
void AlgodalParser_PrintAnalyzeParserError(AlgodalParser_Ast ast, AlgodalParser_Error error)
{
    char lineBuffer1[64], lineBuffer2[64];
    if(error.flags & ALGODAL_PARSING_FAIL)
    {
        cwpc_fprintf(ALGODALPARSER_STDERR, "\033[31;1m%s: failed to analyze tokens at %s - %s\033[0m\n", ast.program.NameOfParser, AlgodalParser_GetLinenumber(ast.linenumber, error.index, lineBuffer1), AlgodalParser_GetLinenumber(ast.linenumber, error.index2, lineBuffer2));
        char input[4] = APS_ZERO;
        memcpy(input, &ast.text[error.index], sizeof(char));
        cwpc_fprintf(ALGODALPARSER_STDERR, "\033[34;1m[%s] begins with `%s`\033[0m\n", AlgodalParser_GetLinenumber(ast.linenumber, error.index, lineBuffer1), input);
        if(error.index2 > error.index)
        {
            char input2[4] = APS_ZERO;
            memcpy(input2, &ast.text[error.index2], sizeof(char));
            cwpc_fprintf(ALGODALPARSER_STDERR, "\033[34;1m[%s] begins with `%s`\033[0m\n", AlgodalParser_GetLinenumber(ast.linenumber, error.index2, lineBuffer1), input2);
        }
    }
    if(error.flags & ALGODAL_PARSING_DUP)
    {
        cwpc_fprintf(ALGODALPARSER_STDERR, "\033[31;1m%s: multiple analyzers returned equal nodes at %s - %s\033[0m\n", ast.program.NameOfParser, AlgodalParser_GetLinenumber(ast.linenumber, error.index, lineBuffer1), AlgodalParser_GetLinenumber(ast.linenumber, error.index2, lineBuffer2));
    }
    if(error.flags & ALGODAL_PARSING_EOI)
    {
        cwpc_fprintf(ALGODALPARSER_STDERR, "\033[31;1m%s: not all tokens were parsed at %s - %s\033[0m\n", ast.program.NameOfParser, AlgodalParser_GetLinenumber(ast.linenumber, error.index, lineBuffer1), AlgodalParser_GetLinenumber(ast.linenumber, error.index2, lineBuffer2));
    }
    if(error.flags & ALGODAL_PARSING_ERROR)
    {
        cwpc_fprintf(ALGODALPARSER_STDERR, "\033[31;1m%s: undefined analyzation error occurred at %s - %s\033[0m\n", ast.program.NameOfParser, AlgodalParser_GetLinenumber(ast.linenumber, error.index, lineBuffer1), AlgodalParser_GetLinenumber(ast.linenumber, error.index2, lineBuffer2));
    }
}
void AlgodalParser_PrintToken(AlgodalParser_Ast ast, AlgodalParser_Token token)
{
    char lineBuffer[512] = APS_ZERO;
    cwpc_fprintf(ALGODALPARSER_STDOUT, "%s ", AlgodalParser_GetLinenumber(ast.linenumber, token.index, lineBuffer));
    char key[1024] = APS_ZERO;
    const char * readonlykey = AlgodalParser_GetTokenizerString_READONLY(ast.program, token.id);
    memcpy(key, readonlykey, strlen(readonlykey));
    AlgodalParser_SimplifyStr(strlen(key), key);
    cwpc_fprintf(ALGODALPARSER_STDOUT, "%s ", key);
    if(ast.program.Tokenizers[token.id].flag != 3 && ast.program.Tokenizers[token.id].type != 0 && token.size > 0)
    {
        cwpc_fprintf(ALGODALPARSER_STDOUT, ": ");
        char value[token.size + 1];
        memset(value, 0, token.size + 1);
        AlgodalParser_GetTokenValue(ast, token, value);
        AlgodalParser_SimplifyStr(token.size, value);
        if(IsUTF8Malformed(value, token.size))
        {
            PrintHex(value, token.size);         
        }
        else
        {
            cwpc_fprintf(ALGODALPARSER_STDOUT, "%s", value);
        }        
    }
    cwpc_fprintf(ALGODALPARSER_STDOUT, "\n");
}
void AlgodalParser_PrintTokenizeResult(AlgodalParser_Ast ast, AlgodalParser_Error error)
{
    for(uint32_t i = 0; i < ast.tokens.size; i++)
    {
        struct AlgodalParser_Token token = ast.tokens.addr[i];
        AlgodalParser_PrintToken(ast, token);
    }
    AlgodalParser_PrintTokenizeParserError(ast, error);
}
void AlgodalParser_PrintProgram(struct AlgodalParser_Program p)
{
    cwpc_fprintf(ALGODALPARSER_STDOUT, "COUNT OF STRINGS : %u\n", p.CountOfStrings);
    cwpc_fprintf(ALGODALPARSER_STDOUT, "-- STRINGS --\n");
    for(uint16_t i = 0; i < p.CountOfStrings; i++)
    {
        cwpc_fprintf(ALGODALPARSER_STDOUT, "%s, %d\n", p.Strings[i].text, p.Strings[i].length);
    }
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
struct AlgodalParser_TokenPair AlgodalParser_ExportToken(AlgodalParser_Ast ast, AlgodalParser_Token token)
{
    struct AlgodalParser_TokenPair pair = APS_ZERO;
    pair.offsetOfText = token.index;
    pair.key = cwpc_strdup(ast.program.Strings[ast.program.Actions[ast.program.Tokenizers[token.id].indexOfAction].indexOfString].text);
    if(ast.program.Tokenizers[token.id].type != 3 && token.size > 0)
    {
        char buf[token.size + 1]; buf[token.size] = 0;
        memcpy(buf, &ast.text[token.index], token.size);
        pair.value = strdup(buf);
    }
    AlgodalParser_GetLinenumberInteger(ast.linenumber, token.index, &pair.lineNumber, &pair.columnNumber);
    return pair;
}
struct AlgodalParser_TokenPairList AlgodalParser_ExportTokenizeResult(AlgodalParser_Ast ast)
{
    struct AlgodalParser_TokenPairList pairList = APS_ZERO;
    pairList.size = ast.tokens.size;
    pairList.addr = (struct AlgodalParser_TokenPair *)malloc(sizeof(struct AlgodalParser_TokenPair) * pairList.size);
    memset(pairList.addr, 0, sizeof(struct AlgodalParser_TokenPair) * pairList.size);
    for(uint32_t i = 0; i < pairList.size; i++)
    {
        pairList.addr[i] = AlgodalParser_ExportToken(ast, ast.tokens.addr[i]);
    }
    return pairList;
}
AlgodalParser_NodePair AlgodalParser_ExportNode(AlgodalParser_Ast ast, struct AlgodalParser_Node *node)
{
    struct AlgodalParser_NodePair pair = APS_ZERO;
    pair.offsetOfText = ast.tokens.addr[node->indexOfToken].index;
    pair.key = cwpc_strdup(ast.program.Strings[ast.program.Actions[node->indexOfAction].indexOfString].text);
    AlgodalParser_GetLinenumberInteger(ast.linenumber, ast.tokens.addr[node->indexOfToken].index, &pair.lineNumber, &pair.columnNumber);
    const int showNodeValue = SHOW_NODE_VALUE;
    if(showNodeValue)
    {
        uint32_t length = ast.tokens.addr[node->indexOfToken + node->size - 1].index - ast.tokens.addr[node->indexOfToken].index + ast.tokens.addr[node->indexOfToken + node->size - 1].size;
        char buf[length + 1]; buf[length] = 0;
        memcpy(buf, &ast.text[ast.tokens.addr[node->indexOfToken].index], length);
        pair.value = strdup(buf);
    }
    pair.children.size = node->children.size;
    pair.children.addr = (struct AlgodalParser_NodePair *)malloc(sizeof(struct AlgodalParser_NodePair) * pair.children.size);
    for(uint32_t i = 0; i < pair.children.size; i++)
    {
        pair.children.addr[i] = AlgodalParser_ExportNode(ast, node->children.addr[i]);
    }
    return pair;
}
struct AlgodalParser_NodePairList AlgodalParser_ExportAnalyzeResult(AlgodalParser_Ast ast)
{
    struct AlgodalParser_NodePairList pairList = APS_ZERO;
    pairList.size = ast.nodes.size;
    pairList.addr = (struct AlgodalParser_NodePair *)malloc(sizeof(struct AlgodalParser_NodePair) * pairList.size);
    memset(pairList.addr, 0, sizeof(struct AlgodalParser_NodePair) * pairList.size);
    for(uint32_t i = 0; i < pairList.size; i++)
    {
        pairList.addr[i] = AlgodalParser_ExportNode(ast, ast.nodes.addr[i]);
    }
    return pairList;
}
void AlgodalParser_DestroyTokenPair(struct AlgodalParser_TokenPair pair)
{
    free((void*)pair.key);
    if(pair.value)free((void*)pair.value);
}
void AlgodalParser_DestroyTokenPairList(struct AlgodalParser_TokenPairList pairList)
{
    for(uint32_t i = 0; i < pairList.size; i++)
    {
        AlgodalParser_DestroyTokenPair(pairList.addr[i]);
    }
    free(pairList.addr);
}
void AlgodalParser_DestroyNodePair(struct AlgodalParser_NodePair pair)
{
    free((void*)pair.key);
    free((void*)pair.value);
    for(uint32_t i = 0; i < pair.children.size; i++)
    {
        AlgodalParser_DestroyNodePair(pair.children.addr[i]);
    }
    free(pair.children.addr);
}
void AlgodalParser_DestroyNodePairList(struct AlgodalParser_NodePairList pairList)
{
    for(uint32_t i = 0; i < pairList.size; i++)
    {
        AlgodalParser_DestroyNodePair(pairList.addr[i]);
    }
    free(pairList.addr);
}
void AlgodalParser_FreeStack(struct AlgodalParser_Stack stack)
{
    if(stack.addr) free(stack.addr);
    memset(&stack, 0, sizeof(struct AlgodalParser_Stack));
}
void AlgodalParser_FreeProgramStack(struct AlgodalParser_Program Program)
{
    if(Program.Stack)
    {
        AlgodalParser_FreeStack(*Program.Stack);
        Program.Stack = 0;
    }
}
AlgodalParser_ParsedData AlgodalParser_ParseTextEx(AlgodalParser_Program in_program, const char* in_text, unsigned int in_length, AlgodalParser_ParsedParams in_params)
{
    AlgodalParser_ParsedData d = APS_ZERO;
    d.ast.program = in_program;
    d.text = in_text;
    d.ast.text = (char*)in_text;
    d.ast.linenumber = AlgodalParser_CreateParserLinenumber(in_text, in_length);
    AlgodalParser_TokenizeResult tr = AlgodalParser_GetTokenizeResult(in_program, in_text, in_length, &in_params.other_tokenize_params);
    d.ast.tr = tr;
    d.ast.tokens = tr.tokens;
    if(tr.error.flags) return d;
    AlgodalParser_AnalyzeResult ar = AlgodalParser_GetAnalyzeResult(in_program, in_text, tr.tokens.addr, tr.tokens.size, &in_params.other_analyze_params);
    d.ast.ar = ar;
    d.ast.nodes = ar.nodes;
    if(ar.error.flags) return d;
    return d;
}
AlgodalParser_ParsedData AlgodalParser_ParseText(AlgodalParser_Program in_program, const char* in_text, unsigned int in_length)
{
    AlgodalParser_ParsedParams in_params = APS_ZERO;
    return AlgodalParser_ParseTextEx(in_program, in_text, in_length, in_params);
}
#ifdef ALGODAL_GENERATED_PARSER_JSON_CONVERTER_C
AlgodalParser_ParsedData AlgodalParser_ParseTextExJson(const char* json_file, const char* in_text, unsigned int in_length, AlgodalParser_ParsedParams in_params)
{
    AlgodalParser_Program in_program = AlgodalJsonParser_GetProgramFromFile(json_file, 0, 0);
    return AlgodalParser_ParseTextEx(in_program, in_text, in_length, in_params);
}
AlgodalParser_ParsedData AlgodalParser_ParseTextExJsonStr(const char* json_str, unsigned int json_str_length, const char* in_text, unsigned int in_length, AlgodalParser_ParsedParams in_params)
{
    AlgodalParser_Program in_program = AlgodalJsonParser_GetProgramFromString(json_str, json_str_length, 0, 0);
    return AlgodalParser_ParseTextEx(in_program, in_text, in_length, in_params);
}
AlgodalParser_ParsedData AlgodalParser_ParseTextJson(const char* json_file, const char* in_text, unsigned int in_length)
{
    AlgodalParser_ParsedParams in_params = APS_ZERO;
    return AlgodalParser_ParseTextExJson(json_file, in_text, in_length, in_params);
}
AlgodalParser_ParsedData AlgodalParser_ParseTextJsonStr(const char* json_str, unsigned int json_str_length, const char* in_text, unsigned int in_length)
{
    AlgodalParser_ParsedParams in_params = APS_ZERO;
    return AlgodalParser_ParseTextExJsonStr(json_str, json_str_length, in_text, in_length, in_params);
}
#endif
void AlgodalParser_DestroyParsedData(AlgodalParser_ParsedData data)
{
    AlgodalParser_DestroyParserLinenumber(data.ast.linenumber);
    AlgodalParser_DestroyTokenizeResult(data.ast.tr);
    if(0 == data.ast.tr.error.flags)
    {
        AlgodalParser_DestroyAnalyzeResult(data.ast.ar);
    }
}
void AlgodalParser_PrintParsedData(AlgodalParser_ParsedData data)
{
    AlgodalParser_PrintTokenizeResult(data.ast, data.ast.tr.error);
    if(0 == data.ast.tr.error.flags)
    {
        AlgodalParser_PrintAnalyzeResult(data.ast, data.ast.ar.error);
    }
    else
    {
        cwpc_printf("Tokenization step contains error - Analyzation not done.\n");
    }
}
#ifdef __cplusplus
}
#endif
#endif  
#ifndef IntParser_ALGODAL_GENERATED_PARSER_PROGRAM_C
#define IntParser_ALGODAL_GENERATED_PARSER_PROGRAM_C
static struct AlgodalParser_Variable IntParser_TheVariables[]=
{
	APS_ZERO
};
enum
{
	IntParser_TheCountOfVariables=0,
	IntParser_TheCountOfActions=20
};

static struct AlgodalParser_Flags IntParser_TheFlags=
{
	.first_entry = 1

};

static struct AlgodalParser_Special IntParser_TheSpecial =
{
	.UseTokenphaseInitialActionCall = 0,
	.TokenphaseInitialActionCallAction = 0,
	.UseTokenphasePopTokenCreation = 0,
	.TokenphasePopTokenCreationLabel = 0,
	.TokenphasePopTokenCreationStop = 0,
	.UseTokenphasePopAll = 0
};

static uint32_t IntParser_TheRV1[8]=APS_ZERO;

static struct AlgodalParser_String IntParser_TheStrings[]=
{
	{(char*)" ", 1},
	{(char*)"\r", 1},
	{(char*)"\n", 1},
	{(char*)"\t", 1},
	{(char*)"(", 1},
	{(char*)")", 1},
	{(char*)"operator", 8},
	{(char*)"integer", 7},
	{(char*)"+-", 2},
	{(char*)"0123456789", 10},
	{(char*)"*/-+", 4},
	{(char*)"plus", 4},
	{(char*)"+", 1},
	{(char*)"minus", 5},
	{(char*)"-", 1},
	{(char*)"mul", 3},
	{(char*)"*", 1},
	{(char*)"div", 3},
	{(char*)"/", 1},
	{(char*)"multiply", 8},
	{(char*)"factor", 6},
	{(char*)"divide", 6},
	{(char*)"term", 4},
	{(char*)"expr", 4},
	{(char*)"add", 3},
	{(char*)"subtract", 8},
	{(char*)"line", 4},
	{0, 0}
};

enum
{
	IntParser_TheCountOfStrings=27
};

static uint8_t IntParser_TheCodeOfActions[]=
{
	ALGPAR_OP_SER, ALGPAR_PU16(2u), ALGPAR_PU16(34u),
	ALGPAR_OP_CNT, ALGPAR_PU32(0u), ALGPAR_PU32(1u), ALGPAR_PU16(5u),
	ALGPAR_OP_ONE, 0, ALGPAR_PU16(8u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_CNT, ALGPAR_PU32(1u), ALGPAR_PU32(4294967295u), ALGPAR_PU16(5u),
	ALGPAR_OP_ONE, 0, ALGPAR_PU16(9u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_ONE, 0, ALGPAR_PU16(10u),
	ALGPAR_OP_RET,
	ALGPAR_OP_EXT, 0, ALGPAR_PU16(0u),
	ALGPAR_OP_RET,
	ALGPAR_OP_EXT, 0, ALGPAR_PU16(1u),
	ALGPAR_OP_RET,
	ALGPAR_OP_EXT, 0, ALGPAR_PU16(2u),
	ALGPAR_OP_RET,
	ALGPAR_OP_EXT, 0, ALGPAR_PU16(3u),
	ALGPAR_OP_RET,
	ALGPAR_OP_EXT, 0, ALGPAR_PU16(4u),
	ALGPAR_OP_RET,
	ALGPAR_OP_EXT, 0, ALGPAR_PU16(5u),
	ALGPAR_OP_RET,
	ALGPAR_OP_ZTS, ALGPAR_PU16(6u), ALGPAR_PU16(12u), 0,
	ALGPAR_OP_RET,
	ALGPAR_OP_ZTS, ALGPAR_PU16(6u), ALGPAR_PU16(14u), 0,
	ALGPAR_OP_RET,
	ALGPAR_OP_ZTS, ALGPAR_PU16(6u), ALGPAR_PU16(16u), 0,
	ALGPAR_OP_RET,
	ALGPAR_OP_ZTS, ALGPAR_PU16(6u), ALGPAR_PU16(18u), 0,
	ALGPAR_OP_RET,
	ALGPAR_OP_SER, ALGPAR_PU16(2u), ALGPAR_PU16(8u),
	ALGPAR_OP_PNT, ALGPAR_PU16(10u),
	ALGPAR_OP_RET,
	ALGPAR_OP_PNT, ALGPAR_PU16(15u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_SER, ALGPAR_PU16(2u), ALGPAR_PU16(8u),
	ALGPAR_OP_PNT, ALGPAR_PU16(11u),
	ALGPAR_OP_RET,
	ALGPAR_OP_PNT, ALGPAR_PU16(15u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_SER, ALGPAR_PU16(2u), ALGPAR_PU16(31u),
	ALGPAR_OP_PNT, ALGPAR_PU16(15u),
	ALGPAR_OP_RET,
	ALGPAR_OP_CNT, ALGPAR_PU32(0u), ALGPAR_PU32(4294967295u), ALGPAR_PU16(15u),
	ALGPAR_OP_OPT, ALGPAR_PU16(2u), ALGPAR_PU16(8u), 0,
	ALGPAR_OP_PNT, ALGPAR_PU16(12u),
	ALGPAR_OP_RET,
	ALGPAR_OP_PNT, ALGPAR_PU16(13u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_OPT, ALGPAR_PU16(3u), ALGPAR_PU16(47u), 1,
	ALGPAR_OP_SER, ALGPAR_PU16(3u), ALGPAR_PU16(12u),
	ALGPAR_OP_TRM, ALGPAR_PU16(4u),
	ALGPAR_OP_RET,
	ALGPAR_OP_PNT, ALGPAR_PU16(18u),
	ALGPAR_OP_RET,
	ALGPAR_OP_TRM, ALGPAR_PU16(5u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_SER, ALGPAR_PU16(2u), ALGPAR_PU16(19u),
	ALGPAR_OP_OPT, ALGPAR_PU16(2u), ALGPAR_PU16(8u), 0,
	ALGPAR_OP_PNT, ALGPAR_PU16(8u),
	ALGPAR_OP_RET,
	ALGPAR_OP_PNT, ALGPAR_PU16(9u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_TRM, ALGPAR_PU16(7u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_TRM, ALGPAR_PU16(7u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_SER, ALGPAR_PU16(2u), ALGPAR_PU16(8u),
	ALGPAR_OP_PNT, ALGPAR_PU16(8u),
	ALGPAR_OP_RET,
	ALGPAR_OP_PNT, ALGPAR_PU16(14u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_SER, ALGPAR_PU16(2u), ALGPAR_PU16(8u),
	ALGPAR_OP_PNT, ALGPAR_PU16(9u),
	ALGPAR_OP_RET,
	ALGPAR_OP_PNT, ALGPAR_PU16(14u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_SER, ALGPAR_PU16(2u), ALGPAR_PU16(31u),
	ALGPAR_OP_PNT, ALGPAR_PU16(14u),
	ALGPAR_OP_RET,
	ALGPAR_OP_CNT, ALGPAR_PU32(0u), ALGPAR_PU32(4294967295u), ALGPAR_PU16(15u),
	ALGPAR_OP_OPT, ALGPAR_PU16(2u), ALGPAR_PU16(8u), 0,
	ALGPAR_OP_PNT, ALGPAR_PU16(16u),
	ALGPAR_OP_RET,
	ALGPAR_OP_PNT, ALGPAR_PU16(17u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_SER, ALGPAR_PU16(2u), ALGPAR_PU16(20u),
	ALGPAR_OP_PNT, ALGPAR_PU16(18u),
	ALGPAR_OP_RET,
	ALGPAR_OP_CNT, ALGPAR_PU32(0u), ALGPAR_PU32(1u), ALGPAR_PU16(4u),
	ALGPAR_OP_TRM, ALGPAR_PU16(2u),
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	ALGPAR_OP_RET,
	0
};

static struct AlgodalParser_Action IntParser_TheActions[]=
{
	{7, 0},
	{6, 40},
	{0, 45},
	{1, 50},
	{2, 55},
	{3, 60},
	{4, 65},
	{5, 70},
	{11, 75},
	{13, 82},
	{15, 89},
	{17, 96},
	{19, 103},
	{21, 117},
	{22, 131},
	{20, 168},
	{24, 222},
	{25, 236},
	{23, 250},
	{26, 287},
	{27, 313}
};

static struct AlgodalParser_Tokenizer IntParser_TheTokenizers[]=
{
	{2, 0, 1, 0},
	{3, 0, 1, 0},
	{4, 0, 2, 0},
	{5, 0, 1, 0},
	{6, 0, 0, 0},
	{7, 0, 0, 0},
	{1, 1, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 0, 0}
};

enum
{
	IntParser_TheCountOfTokenizers = 8

};

static struct AlgodalParser_Entrypoint IntParser_TheEntrypoints[]=
{
	{19, 0, 0, 0},
	{0, 0, 0, 0}
};

static struct AlgodalParser_Objectpoint IntParser_TheObjectpoints[]=
{
	{19, 0, 0, 0},
	{0, 1, 0, 0},
	{16, 0, 0, 0},
	{17, 0, 0, 0},
	{13, 0, 0, 0},
	{12, 0, 0, 0},
	{0, 0, 0, 0}
};

enum
{
	 IntParser_TheCountOfEntrypoints = 1
	,IntParser_TheCountOfObjectpoints = 6

};

static struct AlgodalParser_Stack IntParser_TheStack = APS_ZERO;

struct AlgodalParser_Program IntParserProgram =
{
	.NameOfParser = (char*)"IntParser",
	.Strings = IntParser_TheStrings,
	.Actions = IntParser_TheActions,
	.CodeOfActions = IntParser_TheCodeOfActions,
	.Tokenizers = IntParser_TheTokenizers,
	.Entrypoints = IntParser_TheEntrypoints,
	.Objectpoints = IntParser_TheObjectpoints,
	.CountOfTokenizers = IntParser_TheCountOfTokenizers,
	.CountOfEntrypoints = IntParser_TheCountOfEntrypoints,
	.CountOfObjectpoints = IntParser_TheCountOfObjectpoints,
	.Flags = &IntParser_TheFlags,
	.Variables = IntParser_TheVariables,
	.CountOfVariables = IntParser_TheCountOfVariables,
	.CountOfActions = IntParser_TheCountOfActions,
	.CountOfStrings = IntParser_TheCountOfStrings,
	.Stack = &IntParser_TheStack,
	.Special = &IntParser_TheSpecial,
	.RV1 = IntParser_TheRV1,

};

#endif

