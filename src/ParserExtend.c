//Add Include from Generated Parser here ...

#ifndef ALGODAL_GENERATED_PARSER_EXTEND_C
#define ALGODAL_GENERATED_PARSER_EXTEND_C

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif



#ifndef __STACK__
#define __STACK__

enum { STACKSIZE = 16 };
struct Stack
{
    void **array;
    int max;
    int counter;
    int offset;
};

static void PushStack(struct Stack * stack, void *object) __attribute__((nonnull (1)));
static int IsEmptyStack(struct Stack * stack) __attribute__((nonnull (1)));
static void PushStack(struct Stack * stack, void *object) __attribute__((nonnull (1)));

static struct Stack * CreateStack()
{
    struct Stack * stack = malloc(sizeof(struct Stack));
    memset(stack, 0, sizeof(struct Stack));
    stack->max = STACKSIZE;
    stack->array = malloc(sizeof(void *) * stack->max);    
    stack->offset = -1;
    return stack;
}

static void DestroyStack(struct Stack * stack)
{
    free(stack->array);
    memset(stack, 0, sizeof(struct Stack));
    free(stack);
}

static int GetStackOffset(struct Stack * stack)
{
    if(stack->offset > -1) return stack->offset;
    return 0;
}

/*
    GrowStack: increases the stack by STACKSIZE elements.
          This utility function isn't part of the public interface
*/
static void GrowStack(struct Stack * stack)
{
    stack->max += STACKSIZE; /* increases the capacity */

    int i;  // for the loop
    void **tmp = malloc(sizeof(void *) * stack->max);

    /* copies the elements from the origin array in the new one. */
    for (i = 0; i < stack->max - STACKSIZE; i++)
    {
        *(tmp + i) = *(stack->array + i);
    }
    /*free the memory */
    free(stack->array);
    stack->array = tmp;
}

/* PushStack: pushs the argument onto the stack */
static void PushStack(struct Stack * stack, void *object)
{
    if (stack->counter < stack->max)
    {
        stack->offset++; /* increases the element-pointer */

        /*
            moves pointer by the offset address
            pushs the object onto stack
         */
        *(stack->array + GetStackOffset(stack)) = object;

        /* increases the inner counter */
        stack->counter++;
    }
    else /* stack is full */
    {
        GrowStack(stack);       /* lets GrowStack stack */
        PushStack(stack, object); /* recursive call */
    }
}

/*
    PopStack: pops the TopStack element of the stack from the stack.
*/
static void *PopStack(struct Stack * stack)
{
    void *TopStack = *(stack->array + GetStackOffset(stack));

    /* if use the PopStack-function, stack must not empty. */
    if(!IsEmptyStack(stack))
    {
        /* decreases the offset address for pointing of
            the new TopStack element */
        stack->offset--;

        /* decreases the inner counter */
        stack->counter--;
    }

    return TopStack;
}

/*
    size: gets the number of elements of the stack.
*/
//static int SizeStack(struct Stack * stack) { return stack->counter; }

/*
    IsEmptyStack(): returns 1 if stack is empty otherwise 0.
*/
static int IsEmptyStack(struct Stack * stack) { return stack->counter == 0; }

/*
    TopStack: returns the TopStack element from the stack without removing it.
*/
static void *TopStack(struct Stack * stack)
{
    /* offset address points to the TopStack element */
    return stack->array[GetStackOffset(stack)];
}

#endif //__STACK__

static long no_space(const char * string, unsigned int size, int dir)
{
    //index
    if(dir > 0)
    {
        unsigned int i;
        for(i = 0; i < size; i++)
        {
            int c = string[i];
            if(c == ' ' || c == '\n' || c == '\r' || c == '\t') continue;
            break;
        }
        return i;
    }
    else
    //size
    if(dir < 0)
    {
        long i;
        for(i = size-1; i > -1; i--)
        {
            int c = string[i];
            if(c == ' ' || c == '\n' || c == '\r' || c == '\t') continue;
            break;
        }
        return i + 1;
    }
    return 0;
}

struct AlgodalParser_TokenizeResult TokenPostProcessing_TrimTokens(struct AlgodalParser_TokenizeResult *tokenizeResult, const char *text)
{
    struct AlgodalParserUtility_TokenOperation * op = AlgodalParserUtility_CreateTokenOperation(tokenizeResult);
    while(AlgodalParserUtility_HasTokensRemaining(op))
    {
        struct AlgodalParser_Token token = AlgodalParserUtility_GetCurrentToken(op);
        long oi = no_space(&text[token.index], token.size,  1);
        long os = no_space(&text[token.index], token.size, -1);
        if(!(oi == token.size) && !(os == 0) && !(oi == 0 && os == token.size) && (oi < os))
        {
            token.index += oi;
            token.size   = os - oi;
            AlgodalParserUtility_TokenUpdate(op, token);
        }
        AlgodalParserUtility_GotoNextToken(op);
    }
    return AlgodalParserUtility_ProcessTokenOperation(op);
}

static unsigned int indentation_level(const char *text, struct AlgodalParser_Token token)
{
    unsigned int total = 0;
    for(unsigned int i = 0; i < token.size; i++)
    {
        int c = text[token.index + i];
        if(c == ' ')  total += 1;
        if(c == '\t') total += 8; //each tab counts as 8
        if(c == '\f') continue; //form feed is skipped
    }
    return total;
}

struct AlgodalParser_TokenizeResult TokenPostProcessing_GeneratePythonTokens(struct AlgodalParser_TokenizeResult *tokenizeResult, struct AlgodalParser_Program program, const char *text)
{
    int32_t indentID  = AlgodalParserUtility_GetTokenizerID(program, "indent"); //expected the user to create a tokenizer `@post_create indent`
    int32_t dedentID  = AlgodalParserUtility_GetTokenizerID(program, "dedent"); //expected the user to create a tokenizer `@post_create dedent`
    int32_t newlineID = AlgodalParserUtility_GetTokenizerID(program, "newline"); //expected the user to create a @action tokenizer `newline`
    int32_t spaceID   = AlgodalParserUtility_GetTokenizerID(program, "space"); //expected the user to create a @action tokenizer `space`

    if(indentID == -1)
    {
        cwpc_printf("Please @post_create an action called `indent` and add it as an tokenizer inorder to use this pre-processing.\n");
        return *tokenizeResult;
    }

    if(dedentID == -1)
    {
        cwpc_printf("Please @post_create an action called `dedent` and add it as an tokenizer inorder to use this pre-processing.\n");
        return *tokenizeResult;
    }

    if(newlineID == -1)
    {
        cwpc_printf("Please create an @action called `newline` for parsing literal-newlines and add it as a tokenizer to use this pre-processing.\n");
        return *tokenizeResult;
    }

    if(spaceID == -1)
    {
        cwpc_printf("Please create an @action called `space` for parsing literal-spaces and add it as a tokenizer to use this pre-processing.\n");
        return *tokenizeResult;
    }

    struct Stack * stack = CreateStack();
    PushStack(stack, (void*)0);

    struct AlgodalParserUtility_TokenOperation * op = AlgodalParserUtility_CreateTokenOperation(tokenizeResult);
    while(AlgodalParserUtility_HasTokensRemaining(op))
    {
        struct AlgodalParser_Token token = AlgodalParserUtility_GetCurrentToken(op);
        if(token.id == newlineID)
        {
            long IL_Current = (long)TopStack(stack);
            long IL_AfterNewline = 0;
            AlgodalParserUtility_GotoNextToken(op);
            token = AlgodalParserUtility_GetCurrentToken(op);
            if(token.id == spaceID)IL_AfterNewline = indentation_level(text, token);
            if(IL_AfterNewline > IL_Current)
            {
                PushStack(stack, (void*)IL_AfterNewline);
                AlgodalParserUtility_TokenDelete(op); //delete Space token
                AlgodalParserUtility_TokenInsert(op, AlgodalParserUtility_CreateToken(indentID, token.index, IL_AfterNewline));
            }
            else
            if(IL_AfterNewline < IL_Current)
            {
                AlgodalParserUtility_TokenDelete(op); //delete Space token
                do
                {
                    PopStack(stack);
                    IL_Current = (long)TopStack(stack);
                    AlgodalParserUtility_TokenInsert(op, AlgodalParserUtility_CreateToken(dedentID, op->last.token.index, IL_Current));
                }
                while(IL_AfterNewline < IL_Current && TopStack(stack) != 0);
            }
        }
        else
        if(token.id == spaceID)
        {
            AlgodalParserUtility_TokenDelete(op); //delete Space token
        }
        AlgodalParserUtility_GotoNextToken(op);
    }
    while(TopStack(stack) != 0)
    {
        PopStack(stack);
        AlgodalParserUtility_TokenInsert(op, AlgodalParserUtility_CreateToken(dedentID, 0, 0));
    }
    DestroyStack(stack);
    return AlgodalParserUtility_ProcessTokenOperation(op);
}

#ifdef __cplusplus
}
#endif

#endif //ALGODAL_GENERATED_PARSER_EXTEND_C

