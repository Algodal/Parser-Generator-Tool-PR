//Add Include from Generated Parser here ...

#ifndef ALGODAL_GENERATED_PARSER_UTILITY_C
#define ALGODAL_GENERATED_PARSER_UTILITY_C

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

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
#endif//ALGODAL_GENERATED_PARSER_FUNC_STRCMPNC

struct ProcessedFilterKeys
{
    char unfilteredString[64];
    unsigned int lengthProcessed;
    bool filterOut;
};

static inline unsigned int GetUnicodeSize(const char *string)
{
    char byte1 = string[0];
	return
		(byte1 & 128) == 0 ? 1u :
		(byte1 & (128 + 64 + 32)) == (128 + 64) ? 2u :
		(byte1 & (128 + 64 + 32 + 16)) == (128 + 64 + 32) ? 3u :
		(byte1 & (128 + 64 + 32 + 16 + 8)) == (128 + 64 + 32 + 16) ? 4u :
		0; 
}

struct ProcessedFilterKeys GetProcessedFilterKeys(unsigned int index, const char *refString, unsigned int refLength, const char *filterKeys[], const unsigned int *filterKeysLength, unsigned int filterKeysCount)
{
    (void)refLength;
    struct ProcessedFilterKeys result = {0};
    char compareBuffer[1024] = {0};
    for(unsigned int i = 0; i < filterKeysCount; i++)
    {
        memcpy(compareBuffer, &refString[index], filterKeysLength[i]);
        compareBuffer[filterKeysLength[i]] = 0;
        if(strcmp(filterKeys[i], compareBuffer) == 0)
        {
            result.filterOut = true;
            result.lengthProcessed = filterKeysLength[i];
            return result;
        }
    }
    result.lengthProcessed = GetUnicodeSize(&refString[index]);
    memcpy(result.unfilteredString, &refString[index], result.lengthProcessed);
    return result;
}

char *AlgodalParserUtility_CreateFilteredOutString(const char *refString, size_t refLength, const char *filterKeys[], unsigned int filterKeysCount, size_t *retFilteredStringLength)
{
    char *filteredString = malloc(refLength);
    memset(filteredString, 0, refLength);
    size_t filteredLength = 0;

    unsigned int *filterKeysLength = malloc(sizeof(unsigned int) * filterKeysCount);
    /// Gather Length of Filter Keys
    for(unsigned int i = 0; i < filterKeysCount; i++) filterKeysLength[i] = strlen(filterKeys[i]);

    size_t processedLength = 0;
    while(processedLength < refLength)
    {
        struct ProcessedFilterKeys processedFilterKeys = GetProcessedFilterKeys(processedLength, refString, refLength, filterKeys, filterKeysLength, filterKeysCount);
        if(!processedFilterKeys.filterOut)
        {
            strcat(filteredString, processedFilterKeys.unfilteredString);
            filteredLength += processedFilterKeys.lengthProcessed;
        }
        processedLength += processedFilterKeys.lengthProcessed;
    }
    filteredString = realloc(filteredString, filteredLength + 1);
    filteredString[filteredLength] = 0;
    if(retFilteredStringLength) retFilteredStringLength[0] = filteredLength;
    return filteredString;
}

//=========================================================================================================

enum TokenOperationAction
{
    AlgodalParserUtility_DELETE = 101,
    AlgodalParserUtility_INSERT = 201,
    AlgodalParserUtility_UPDATE = 301
};

struct TokenOperationState
{
    enum TokenOperationAction action;
    unsigned int index;
    struct AlgodalParser_Token token;
};

struct TokenOperationIterator
{
    unsigned int index;
};


struct AlgodalParserUtility_TokenOperation
{
    struct TokenOperationState *                   addr;
    unsigned int                                   size;
    struct AlgodalParser_TokenizeResult *          ptrOfTokenizeResult;
    struct TokenOperationIterator                  iterator;
    struct AlgodalParserUtility_LastTokenOperation last;
    
};

static unsigned int ClampStateIndices(long index, long size)
{
    if(index < 0) return 0;
    if(index >= size) return size ? size - 1 : 0;
    return (unsigned int)index;
}
static void UpdateStateIndices(struct AlgodalParserUtility_TokenOperation *op, struct TokenOperationState current)
{
    for(unsigned int i = 0; i < op->size; i++)
    {
        if(op->addr[i].index > current.index)
        {
            int dir = current.action == AlgodalParserUtility_INSERT ? +1 : current.action == AlgodalParserUtility_DELETE ? -1 : 0;
            op->addr[i].index = ClampStateIndices(op->addr[i].index + dir, op->ptrOfTokenizeResult->tokens.size);
        }
    }
}

struct AlgodalParserUtility_TokenOperation * AlgodalParserUtility_CreateTokenOperation(struct AlgodalParser_TokenizeResult * ptrOfTokenizeResult)
{
    struct AlgodalParserUtility_TokenOperation * op = malloc(sizeof(struct AlgodalParserUtility_TokenOperation));
    memset(op, 0, sizeof(struct AlgodalParserUtility_TokenOperation));
    op->ptrOfTokenizeResult = ptrOfTokenizeResult;
    op->last.deleted.id = -1;
    op->last.inserted.id = -1;
    op->last.updated.id = -1;
    op->last.token.id = -1;
    return op;
}

int32_t AlgodalParserUtility_GetTokenizerID(struct AlgodalParser_Program program, const char* tokenName)
{
    for(uint16_t i = 0; i < program.CountOfTokenizers; i++)
    {
        struct AlgodalParser_Tokenizer tokenizer = program.Tokenizers[i];
        if(strcmpnc(program.Strings[program.Actions[tokenizer.indexOfAction].indexOfString].text, tokenName)==0)
        {
            return i;
        }        
    }
    return -1;
}

int AlgodalParserUtility_IsTokenValueNameEqual(struct AlgodalParser_Program program, struct AlgodalParser_Token token, const char* name)
{
    if(strcmpnc(program.Strings[program.Actions[program.Tokenizers[token.id].indexOfAction].indexOfString].text, name)==0)
    {
        return 1;
    }
    return 0;
}

int AlgodalParserUtility_IsTokenizerNameEqual(struct AlgodalParser_Program program, struct AlgodalParser_Token token, const char* name)
{
    if(strcmpnc(program.Strings[program.Actions[program.Tokenizers[token.id].indexOfAction].indexOfString].text, name)==0)
    {
        return 1;
    }
    return 0;
}

int AlgodalParserUtility_IsTokenValueStringEqual(const char* text, struct AlgodalParser_Token token, const char* name)
{
    char value[token.size + 1];
    memcpy(value, &text[token.index], token.size);
    value[token.size] = 0;
    if(strcmpnc(value, name)==0)
    {
        return 1;
    }
    return 0;
}

struct AlgodalParser_Token AlgodalParserUtility_CreateToken(uint16_t tokenizerID, uint32_t index, uint32_t size)
{
    return (struct AlgodalParser_Token)
    {
        .id = tokenizerID,
        .index = index,
        .size = size
    };
}

int AlgodalParserUtility_HasTokensRemaining(struct AlgodalParserUtility_TokenOperation *op)
{
    return op->iterator.index < op->ptrOfTokenizeResult->tokens.size;
}

struct AlgodalParser_Token AlgodalParserUtility_GetCurrentToken(struct AlgodalParserUtility_TokenOperation *op)
{
    return (op->iterator.index < op->ptrOfTokenizeResult->tokens.size) ? op->ptrOfTokenizeResult->tokens.addr[op->iterator.index] : (struct AlgodalParser_Token){};
}

void AlgodalParserUtility_GotoNextToken(struct AlgodalParserUtility_TokenOperation *op)
{
    if(op->iterator.index < op->ptrOfTokenizeResult->tokens.size) op->iterator.index ++;
}

void AlgodalParserUtility_GotoPreviousToken(struct AlgodalParserUtility_TokenOperation *op)
{
    if(op->iterator.index > 0) op->iterator.index --;
}

void AlgodalParserUtility_TokenInsert(struct AlgodalParserUtility_TokenOperation *op, struct AlgodalParser_Token token)
{
    if(op)
    {
        struct TokenOperationState state =
        {
            .action = AlgodalParserUtility_INSERT,
            .index  = op->iterator.index,
            .token  = token
        };
        const unsigned iter = op->size ++;
        op->addr = realloc(op->addr, op->size * sizeof(struct TokenOperationState));
        op->addr[iter] = state;
        op->last.inserted = token;
        op->last.token = token;
        op->last.indexUsed = op->iterator.index;

        //AlgodalParserUtility_GotoNextToken(op);
    }
}

void AlgodalParserUtility_TokenDelete(struct AlgodalParserUtility_TokenOperation *op)
{
    if(op)
    {
        struct TokenOperationState state =
        {
            .action = AlgodalParserUtility_DELETE,
            .index  = op->iterator.index
        };
        const unsigned iter = op->size ++;
        op->addr = realloc(op->addr, op->size * sizeof(struct TokenOperationState));
        op->addr[iter] = state;
        op->last.deleted = op->ptrOfTokenizeResult->tokens.addr[op->iterator.index];
        op->last.token = op->ptrOfTokenizeResult->tokens.addr[op->iterator.index];
        op->last.indexUsed = op->iterator.index;
    }
}

void AlgodalParserUtility_TokenUpdate(struct AlgodalParserUtility_TokenOperation *op, struct AlgodalParser_Token token)
{
    if(op)
    {
        struct TokenOperationState state =
        {
            .action = AlgodalParserUtility_UPDATE,
            .index  = op->iterator.index,
            .token  = token
        };
        const unsigned iter = op->size ++;
        op->addr = realloc(op->addr, op->size * sizeof(struct TokenOperationState));
        op->addr[iter] = state;
        op->last.updated = token;
        op->last.token = token;
        op->last.indexUsed = op->iterator.index;
    }
}

static int SumOfTokenOperation(struct AlgodalParserUtility_TokenOperation *op)
{
    int sum = 0;
    for(unsigned int i =0; i < op->size; i++)
    {
        switch(op->addr[i].action)
        {
            case AlgodalParserUtility_UPDATE: break;
            case AlgodalParserUtility_INSERT: sum ++; break;
            case AlgodalParserUtility_DELETE: sum --; break;
        }
    }
    return sum;
}

static void RealignTokens(struct AlgodalParser_Token *tokens, int dir, unsigned int steps, unsigned int index, unsigned int size)
{
    unsigned int i = index;

    while(steps > 0)
    {
        if(dir < 0)
        {
            for(i = index; i < size - 1; i++)
                tokens[i] = tokens[i + 1];
        }
        else 
        if(dir > 0)
        {
            for(i = size - 1; i > index; i--)
                tokens[i] = tokens[i - 1];
        }

        steps--;
    }
}

static void ProcessState(struct AlgodalParserUtility_TokenOperation *op, struct TokenOperationState state)
{
    switch(state.action)
    {
        case AlgodalParserUtility_UPDATE:
        {
            op->ptrOfTokenizeResult->tokens.addr[state.index] = state.token;
        } break;

        case AlgodalParserUtility_INSERT:
        {
            RealignTokens(op->ptrOfTokenizeResult->tokens.addr, 1, 1, state.index, op->ptrOfTokenizeResult->tokens.size);
            op->ptrOfTokenizeResult->tokens.addr[state.index] = state.token;
            UpdateStateIndices(op, state);
        } break;

        case AlgodalParserUtility_DELETE:
        {
            RealignTokens(op->ptrOfTokenizeResult->tokens.addr, -1, 1, state.index, op->ptrOfTokenizeResult->tokens.size);
            UpdateStateIndices(op, state);
        } break;
    }
}

struct AlgodalParser_TokenizeResult AlgodalParserUtility_ProcessTokenOperation(struct AlgodalParserUtility_TokenOperation *op)
{
    int sum = SumOfTokenOperation(op);
    if(sum > 0){
        op->ptrOfTokenizeResult->tokens.size += sum;
        op->ptrOfTokenizeResult->tokens.addr = realloc(op->ptrOfTokenizeResult->tokens.addr, sizeof(struct AlgodalParser_Token) * op->ptrOfTokenizeResult->tokens.size);
    }
    
    for(unsigned int i =0; i < op->size; i++)
    {
        unsigned int size = op->ptrOfTokenizeResult->tokens.size;
        struct TokenOperationState state = op->addr[i];
        if(!(state.index < size)) continue; //TODO: error report
        ProcessState(op, state);
    }

    if(sum < 0){
        op->ptrOfTokenizeResult->tokens.size += sum;
        op->ptrOfTokenizeResult->tokens.addr = realloc(op->ptrOfTokenizeResult->tokens.addr, sizeof(struct AlgodalParser_Token) * op->ptrOfTokenizeResult->tokens.size);
    }

    op->ptrOfTokenizeResult->postProcessed = 1;
    struct AlgodalParser_TokenizeResult processedTokenizeResult = *(op->ptrOfTokenizeResult);

    free(op->addr);
    op->addr = 0;
    op->size = 0;
    free(op);

    return processedTokenizeResult;
}

struct AlgodalParserUtility_LastTokenOperation AlgodalParserUtility_GetLastOperation(struct AlgodalParserUtility_TokenOperation *op)
{
    return op->last;
}

#define ALGPU_STRCMP(i,x,y) i?strcmpnc(x, y)==0:strcmp(x, y)==0

struct AlgodalParser_Node * AlgodalParserUtility_GetNextSiblingNode(struct AlgodalParserUtility_NodeSearchInfo info, struct AlgodalParser_Node * node, enum AlgodalParserUtility_NodeSearchType type, const char *name, int icase)
{
    switch(type)
    {
        case AlgodalParserUtility_NodeSearch_KEY: 
        {
            while(node->sibling)
            {
                if(ALGPU_STRCMP(icase, name, AlgodalParser_GetActionString_READONLY(info.program, node->indexOfAction))) return node->sibling;
                node = node->sibling;
            }
        } break;

        case AlgodalParserUtility_NodeSearch_VALUE: 
        {
            while(node->sibling)
            {
                unsigned int size = AlgodalParser_GetNodeValueMinimumSize(info.tokens, node);
                char value[size + 1];
                value[size] = 0;
                AlgodalParser_GetNodeValue(info.text, info.tokens, node->sibling, size, value);
                if(ALGPU_STRCMP(icase, name, value)) return node->sibling;
                node = node->sibling;
            }
        } break;
    }

    return 0;
}

struct AlgodalParser_Node * AlgodalParserUtility_GetNextChildNode(struct AlgodalParserUtility_NodeSearchInfo info, struct AlgodalParser_Node * node, enum AlgodalParserUtility_NodeSearchType type, const char *name, int icase)
{
    switch(type)
    {
        case AlgodalParserUtility_NodeSearch_KEY: 
        {
            for(unsigned int i = 0; i < node->children.size; i++)
            {
                if(ALGPU_STRCMP(icase, name, AlgodalParser_GetActionString_READONLY(info.program, node->children.addr[i]->indexOfAction))) return node->children.addr[i];
                for(unsigned int i = 0; i < node->children.size; i++)
                {
                    struct AlgodalParser_Node * nn = AlgodalParserUtility_GetNextChildNode(info, node->children.addr[i], type, name, icase);
                    if(nn) return nn;
                }
            }
        } break;

        case AlgodalParserUtility_NodeSearch_VALUE: 
        {
            for(unsigned int i = 0; i < node->children.size; i++)
            {
                unsigned int size = AlgodalParser_GetNodeValueMinimumSize(info.tokens, node->children.addr[i]);
                char value[size + 1];
                memset(value, 0, size + 1);
                AlgodalParser_GetNodeValue(info.text, info.tokens, node->children.addr[i], size, value);
                //printf("Compare %s, %s\n", name, value);
                if(ALGPU_STRCMP(icase, name, value)) return node->children.addr[i];
                for(unsigned int i = 0; i < node->children.size; i++)
                {
                    struct AlgodalParser_Node * nn = AlgodalParserUtility_GetNextChildNode(info, node->children.addr[i], type, name, icase);
                    if(nn) return nn;
                }
            }
        } break;
    }

    return 0;
}

struct AlgodalParser_Node * AlgodalParserUtility_GetNextNode(struct AlgodalParserUtility_NodeSearchInfo info, struct AlgodalParser_Node * node, enum AlgodalParserUtility_NodeSearchType type, const char *name, int icase)
{
    struct AlgodalParser_Node * nn = AlgodalParserUtility_GetNextSiblingNode(info, node, type, name, icase);
    if(nn) return nn;
    return AlgodalParserUtility_GetNextChildNode(info, node, type, name, icase);
}

#ifdef __cplusplus
}
#endif

#endif //ALGODAL_GENERATED_PARSER_UTILITY_C

