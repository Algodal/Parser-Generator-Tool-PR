
//Add Include from Generated Parser here ...

#ifndef ALGODAL_GENERATED_PARSER_UTILITY_H
#define ALGODAL_GENERATED_PARSER_UTILITY_H

#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Filter out characters out of string before passing the string to the tokenizer.
 * Main purpose is to filter out CR (\r) from CRLF (\r\n) on Windows platform.
 * This is because Algodal Parser does not treat CRLF as LF.  Therefore, if you
 * write your parser on Linux platform and only take in account LF, it will fail on
 * Windows, because Windows add in CR in text files.  Using this utility function
 * on Strings before passing it to your parser will ensure you don't need to worry
 * about CRLF compatibility in your parser code.  Just write your parser targetting
 * only LF.
 * 
 * The string produced is allocated and different from the one passed in.
 * You are resposible for free-ing both.
 * 
 * @param refString The string read from the file.  Can not be null.  (Will have EOL as CRLF on Windows and LF on Linux)
 * @param refLength The length of the string read from file. Must be non-zero.
 * @param filterKeys The list of keys being filtered out.  Must be atleast one non-empty string. For example, ["\r"] for CR
 * @param filterKeysCount The number of keys in the list.  Must atleast be 1.
 * @param retFilteredStringLength The length of the final string produced.  Can be null if not needed.
 * @return The resulting string after filtering out the unwanted characters
*/
char *AlgodalParserUtility_CreateFilteredOutString
(
    const char *refString, 
    size_t refLength, 
    const char *filterKeys[], 
    unsigned int filterKeysCount, 
    size_t *retFilteredStringLength
);

struct AlgodalParserUtility_TokenOperation; ///Operation Handle Type

struct AlgodalParserUtility_LastTokenOperation
{
    struct AlgodalParser_Token             deleted;  /// last token that was deleted
    struct AlgodalParser_Token             inserted; /// last token that was inserted
    struct AlgodalParser_Token             updated;  /// last token that was updated
    struct AlgodalParser_Token             token;    /// last token that was processed
    unsigned int                           indexUsed;/// last index that was processed
};

/**
 * This is one of a suite of *operation* functions used for handling the tokens array returned in TokenizeResult.
 * This creates an operation handle.
*/
struct AlgodalParserUtility_TokenOperation * AlgodalParserUtility_CreateTokenOperation(struct AlgodalParser_TokenizeResult * ptrOfTokenizeResult)__attribute__((nonnull (1)));
int32_t AlgodalParserUtility_GetTokenizerID(struct AlgodalParser_Program program, const char* tokenName);
/**
 * Creates a token.
 * @param tokenizerID the id of the tokenizer that *generated* this token.
 * @param index the offset in the text where the token begins.
 * @param size the length of the token.
*/
struct AlgodalParser_Token AlgodalParserUtility_CreateToken(uint16_t tokenizerID, uint32_t index, uint32_t size);
/**
 * This is one of a suite of *operation* functions used for handling the tokens array returned in TokenizeResult.
 * This inserts a token into the array at the current index position. Previous token in the position is shift to the right.
*/
void AlgodalParserUtility_TokenInsert(struct AlgodalParserUtility_TokenOperation *op, struct AlgodalParser_Token token);
/**
 * This is one of a suite of *operation* functions used for handling the tokens array returned in TokenizeResult.
 * This deletes the token at the current index position.  Token on the right is shift to the left to fill the position.
*/
void AlgodalParserUtility_TokenDelete(struct AlgodalParserUtility_TokenOperation *op);
/**
 * This is one of a suite of *operation* functions used for handling the tokens array returned in TokenizeResult.
 * This updates the token at the current position.
*/
void AlgodalParserUtility_TokenUpdate(struct AlgodalParserUtility_TokenOperation *op, struct AlgodalParser_Token token);
/**
 * This is one of a suite of *operation* functions used for handling the tokens array returned in TokenizeResult.
 * This applies the operation processes on the token array.  Before, the processes were being cached.
 * The handle is also deleted.  Once you call this function on an operation handle, you must create a new handle
 * if you want to do more operation.
*/
struct AlgodalParser_TokenizeResult AlgodalParserUtility_ProcessTokenOperation(struct AlgodalParserUtility_TokenOperation *op);
/**
 * This is one of a suite of *operation* functions used for handling the tokens array returned in TokenizeResult.
 * This checks if the current index is less than the array of tokens size.
*/
int AlgodalParserUtility_HasTokensRemaining(struct AlgodalParserUtility_TokenOperation *op);
/**
 * This is one of a suite of *operation* functions used for handling the tokens array returned in TokenizeResult.
 * This gets the token at the current index.
*/
struct AlgodalParser_Token AlgodalParserUtility_GetCurrentToken(struct AlgodalParserUtility_TokenOperation *op);
/**
 * This is one of a suite of *operation* functions used for handling the tokens array returned in TokenizeResult.
 * This updates the index to move 1 step to the right of the array.
*/
void AlgodalParserUtility_GotoNextToken(struct AlgodalParserUtility_TokenOperation *op);
/**
 * This is one of a suite of *operation* functions used for handling the tokens array returned in TokenizeResult.
 * This updates the index to move 1 step to the left of the array.
*/
void AlgodalParserUtility_GotoPreviousToken(struct AlgodalParserUtility_TokenOperation *op);
/**
 * This is one of a suite of *operation* functions used for handling the tokens array returned in TokenizeResult.
 * This returns data on the last process that was cached by the operation.
*/
struct AlgodalParserUtility_LastTokenOperation AlgodalParserUtility_GetLastOperation(struct AlgodalParserUtility_TokenOperation *op);
/**
 * Compares the name of the tokenizer.
 * This can be thought of as the key in the key-value pair.
*/
int AlgodalParserUtility_IsTokenizerNameEqual(struct AlgodalParser_Program program, struct AlgodalParser_Token token, const char* name);
/**
 * Compares the string of the token.
 * This can be thought of as the value in the key-value pair.
*/
int AlgodalParserUtility_IsTokenValueStringEqual(const char* text, struct AlgodalParser_Token token, const char* name);

enum AlgodalParserUtility_NodeSearchFlags
{
    AlgodalParserUtility_NodeSearchFlag_STRIP_QUOTES = 1
};

enum AlgodalParserUtility_NodeSearchType
{
    AlgodalParserUtility_NodeSearch_KEY,
    AlgodalParserUtility_NodeSearch_VALUE
};

struct AlgodalParserUtility_NodeSearchInfo
{
    struct AlgodalParser_Program program;
    const char *text;
    struct AlgodalParser_Token *tokens;
};

struct AlgodalParser_Node * AlgodalParserUtility_GetNextSiblingNode(struct AlgodalParserUtility_NodeSearchInfo info, struct AlgodalParser_Node * node, enum AlgodalParserUtility_NodeSearchType type, const char *name, int icase);
struct AlgodalParser_Node * AlgodalParserUtility_GetNextChildNode(struct AlgodalParserUtility_NodeSearchInfo info, struct AlgodalParser_Node * node, enum AlgodalParserUtility_NodeSearchType type, const char *name, int icase);
struct AlgodalParser_Node * AlgodalParserUtility_GetNextNode(struct AlgodalParserUtility_NodeSearchInfo info, struct AlgodalParser_Node * node, enum AlgodalParserUtility_NodeSearchType type, const char *name, int icase);

#ifdef __cplusplus
}
#endif

#endif //ALGODAL_GENERATED_PARSER_UTILITY_H

