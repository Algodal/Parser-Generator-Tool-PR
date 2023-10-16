//Add Include from Generated Parser here ...

#ifndef ALGODAL_GENERATED_PARSER_JSON_CONVERTER_C
#define ALGODAL_GENERATED_PARSER_JSON_CONVERTER_C

#ifndef ALGODAL_GENERATED_PARSER_OBJECT_FORMAT_TEXT
#define ALGODAL_GENERATED_PARSER_OBJECT_FORMAT_TEXT
char* object_format_text(char c[], uint32_t length)
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
                        char x[3] = {};
                        if(r < 256 - 2)
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
#endif//ALGODAL_GENERATED_PARSER_OBJECT_FORMAT_TEXT


static char * ExtractString(struct AlgodalParserUtility_NodeSearchInfo nsi, struct AlgodalParser_Node * node)
{
    if(nsi.tokens[node->indexOfToken].size)
    {
        char stringliteral[nsi.tokens[node->indexOfToken].size];
        AlgodalParser_GetNodeValue(nsi.text, nsi.tokens, node, nsi.tokens[node->indexOfToken].size, stringliteral);
        unsigned int length_string = nsi.tokens[node->indexOfToken].size - 2;
        char * string = malloc(length_string + 1);
        string[length_string] = 0;
        memcpy(string, &stringliteral[1], length_string);
        return object_format_text(string, nsi.tokens[node->indexOfToken].size - 2);
    }
    return 0;
}

static void ExtractString__NoAlloc(struct AlgodalParserUtility_NodeSearchInfo nsi, struct AlgodalParser_Node * node, char * ret_string)
{
    if(nsi.tokens[node->indexOfToken].size)
    {
        char stringliteral[nsi.tokens[node->indexOfToken].size];
        AlgodalParser_GetNodeValue(nsi.text, nsi.tokens, node, nsi.tokens[node->indexOfToken].size, stringliteral);
        unsigned int length_string = nsi.tokens[node->indexOfToken].size - 2;
        memcpy(ret_string, &stringliteral[1], length_string);
        object_format_text(ret_string, length_string);
        return;
    }
}

static unsigned int ExtractUint(struct AlgodalParserUtility_NodeSearchInfo nsi, struct AlgodalParser_Node * node)
{
    if(nsi.tokens[node->indexOfToken].size)
    {
        char numberliteral[nsi.tokens[node->indexOfToken].size + 1];
        numberliteral[nsi.tokens[node->indexOfToken].size] = 0;
        AlgodalParser_GetNodeValue(nsi.text, nsi.tokens, node, nsi.tokens[node->indexOfToken].size, numberliteral);
        return strtol(numberliteral, 0, 10);
    }
    return 0;
}

static unsigned int GetMatchingOffset(const char * string, const char * key)
{
    unsigned int l1 = strlen(string);
    unsigned int l2 = strlen(key);

    unsigned int i = 0;
    for(; i < l1 && i < l2; i++)
    {
        if(string[i] != key[i]) return i;
    }
    return i;
}

static int Get_Match_Offset(const char * string, const char * key, unsigned int * ret_offset)
{
    unsigned int length_key = strlen(key);
    unsigned int result_offset = GetMatchingOffset(string, key);
    if(ret_offset) ret_offset[0] = result_offset;
    return length_key == result_offset;
}

static uint8_t GetCodeFromShortString(const char * shortstring)
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
    if(strcmp(shortstring, "RNG")==0) return ALGPAR_OP_RNG;
    return 0;
}

static void ExtractCode(struct AlgodalParserUtility_NodeSearchInfo nsi, struct AlgodalParser_Node * node, uint8_t *ret_code, unsigned int * ret_length_code)
{
    if(nsi.tokens[node->indexOfToken].size)
    {
        if(strcmp("number", AlgodalParser_GetActionString_READONLY(nsi.program, node->indexOfAction)) == 0)
        {
            ret_code[0] = (uint8_t)ExtractUint(nsi, node);
            ret_length_code[0] = 1;
            return;
        }

        if(strcmp("string", AlgodalParser_GetActionString_READONLY(nsi.program, node->indexOfAction)) == 0)
        {
            char codeliteral[nsi.tokens[node->indexOfToken].size + 1];
            memset(codeliteral, 0, nsi.tokens[node->indexOfToken].size + 1);
            ExtractString__NoAlloc(nsi, node, codeliteral);
            
            unsigned int offset = 0;
            if(Get_Match_Offset(codeliteral, "ALGPAR_OP_", &offset))
            {
                ret_code[0] = GetCodeFromShortString(&codeliteral[offset]);
                ret_length_code[0] = 1;
                return;
            }

            if(Get_Match_Offset(codeliteral, "ALGPAR_PU", &offset))
            {
                if(Get_Match_Offset(&codeliteral[offset], "16", 0))
                {
                    ret_length_code[0] = 2;
                    const unsigned int value = strtol(&codeliteral[offset + 2 + 1], 0, 10);
                    char rawcode[] = {ALGPAR_PU16(value)};
                    memcpy(ret_code, rawcode, ret_length_code[0]);
                    return;
                }

                if(Get_Match_Offset(&codeliteral[offset], "32", 0))
                {
                    ret_length_code[0] = 4;
                    const unsigned int value = strtol(&codeliteral[offset + 2 + 1], 0, 10);
                    char rawcode[] = {ALGPAR_PU32(value)};
                    memcpy(ret_code, rawcode, ret_length_code[0]);
                    return;
                }
            }
        }
    }
}

struct AlgodalParser_Program AlgodalJsonParser_GetProgramFromString(const char *stringBuffer, const unsigned int stringLength, struct AlgodalParser_Error *retError)
{
    struct AlgodalParser_Program program = {};

    struct AlgodalParser_TokenizeResult tr = AlgodalParser_GetTokenizeResult(JsonProgram, stringBuffer, stringLength, 0);
    if(tr.error.flags)
    {
        if(retError) retError[0] = tr.error;
        return program;
    }
    struct AlgodalParser_AnalyzeResult ar = AlgodalParser_GetAnalyzeResult(JsonProgram, stringBuffer, tr.tokens.addr, tr.tokens.size, 0);
    if(ar.error.flags)
    {
        if(retError) retError[0] = ar.error;
        return program;
    }

    struct AlgodalParserUtility_NodeSearchInfo nsi =
    {
        nsi.program = JsonProgram,
        nsi.text = stringBuffer,
        nsi.tokens = tr.tokens.addr
    };


    struct AlgodalParser_Node * root = ar.nodes.addr[0];

    struct AlgodalParser_Node * node_information = AlgodalParserUtility_GetNextNode(nsi, root, AlgodalParserUtility_NodeSearch_VALUE, "\"information\"", 0);
    if(node_information)
    {
        struct AlgodalParser_Node * object_node_information = node_information->sibling;
        if(object_node_information)
        {
            struct AlgodalParser_Node * name = AlgodalParserUtility_GetNextNode(nsi, object_node_information, AlgodalParserUtility_NodeSearch_VALUE, "\"name\"", 0);
            program.NameOfParser = ExtractString(nsi, name->sibling);
        }
    }

    struct AlgodalParser_Node * node_strings = AlgodalParserUtility_GetNextNode(nsi, root, AlgodalParserUtility_NodeSearch_VALUE, "\"strings\"", 0);
    if(node_strings)
    {
        struct AlgodalParser_Node * array_node_strings = node_strings->sibling;
        if(array_node_strings)
        {
            unsigned int i = 0;
            for(; i < array_node_strings->children.size -1; i++)
            {
                struct AlgodalParser_Node * item = array_node_strings->children.addr[i];
                char * string = ExtractString(nsi, item->children.addr[0]);
                unsigned int number = ExtractUint(nsi, item->children.addr[1]);
                //printf("string %s, number %u\n", string, number);
                program.Strings = realloc(program.Strings, sizeof(struct AlgodalParser_String) * (i + 1));
                program.Strings[i].text = string;
                program.Strings[i].length = number;
            }
            program.Strings = realloc(program.Strings, sizeof(struct AlgodalParser_String) * (i + 1));
            program.Strings[i].text = 0;
            program.Strings[i].length = 0;
        }
    }

    struct AlgodalParser_Node * node_actions = AlgodalParserUtility_GetNextNode(nsi, root, AlgodalParserUtility_NodeSearch_VALUE, "\"actions\"", 0);
    if(node_actions)
    {
        struct AlgodalParser_Node * array_node_actions = node_actions->sibling;
        if(array_node_actions)
        {
            unsigned int i = 0;
            for(; i < array_node_actions->children.size -1; i++)
            {
                struct AlgodalParser_Node * item = array_node_actions->children.addr[i];
                unsigned int n1 = ExtractUint(nsi, item->children.addr[0]);
                unsigned int n2 = ExtractUint(nsi, item->children.addr[1]);
                program.Actions = realloc(program.Actions, sizeof(struct AlgodalParser_Action) * (i + 1));
                program.Actions[i].indexOfString = n1;
                program.Actions[i].indexOfCode = n2;
            }
            program.Actions = realloc(program.Actions, sizeof(struct AlgodalParser_Action) * (i + 1));
            program.Actions[i].indexOfString = 0;
            program.Actions[i].indexOfCode = 0;
        }
    }

    struct AlgodalParser_Node * node_tokenizers = AlgodalParserUtility_GetNextNode(nsi, root, AlgodalParserUtility_NodeSearch_VALUE, "\"tokenizers\"", 0);
    if(node_tokenizers)
    {
        struct AlgodalParser_Node * array_node_tokenizers = node_tokenizers->sibling;
        if(array_node_tokenizers)
        {
            unsigned int i = 0;
            for(; i < array_node_tokenizers->children.size -1; i++)
            {
                struct AlgodalParser_Node * item = array_node_tokenizers->children.addr[i];
                unsigned int n1 = ExtractUint(nsi, item->children.addr[0]);
                unsigned int n2 = ExtractUint(nsi, item->children.addr[1]);
                unsigned int n3 = ExtractUint(nsi, item->children.addr[2]);
                signed   int n4 = ExtractUint(nsi, item->children.addr[3]);
                program.Tokenizers = realloc(program.Tokenizers, sizeof(struct AlgodalParser_Tokenizer) * (i + 1));
                program.Tokenizers[i].indexOfAction = n1;
                program.Tokenizers[i].type = n2;
                program.Tokenizers[i].flag = n3;
                program.Tokenizers[i].priority = n4;
            }
            program.Tokenizers = realloc(program.Tokenizers, sizeof(struct AlgodalParser_Tokenizer) * (i + 1));
            program.Tokenizers[i].indexOfAction = 0;
            program.Tokenizers[i].type = 0;
            program.Tokenizers[i].flag = 0;
        }
    }

    struct AlgodalParser_Node * node_entrypoints = AlgodalParserUtility_GetNextNode(nsi, root, AlgodalParserUtility_NodeSearch_VALUE, "\"entrypoints\"", 0);
    if(node_entrypoints)
    {
        struct AlgodalParser_Node * array_node_entrypoints = node_entrypoints->sibling;
        if(array_node_entrypoints)
        {
            unsigned int i = 0;
            for(; i < array_node_entrypoints->children.size -1; i++)
            {
                struct AlgodalParser_Node * item = array_node_entrypoints->children.addr[i];
                unsigned int n1 = ExtractUint(nsi, item->children.addr[0]);
                unsigned int n2 = ExtractUint(nsi, item->children.addr[1]);
                unsigned int n3 = ExtractUint(nsi, item->children.addr[2]);
                signed   int n4 = ExtractUint(nsi, item->children.addr[3]);
                program.Entrypoints = realloc(program.Entrypoints, sizeof(struct AlgodalParser_Entrypoint) * (i + 1));
                program.Entrypoints[i].indexOfAction = n1;
                program.Entrypoints[i].type = n2;
                program.Entrypoints[i].flag = n3;
                program.Entrypoints[i].priority = n4;
            }
            program.Entrypoints = realloc(program.Entrypoints, sizeof(struct AlgodalParser_Entrypoint) * (i + 1));
            program.Entrypoints[i].indexOfAction = 0;
            program.Entrypoints[i].type = 0;
            program.Entrypoints[i].flag = 0;
        }
    }

    struct AlgodalParser_Node * node_objectpoints = AlgodalParserUtility_GetNextNode(nsi, root, AlgodalParserUtility_NodeSearch_VALUE, "\"objectpoints\"", 0);
    if(node_objectpoints)
    {
        struct AlgodalParser_Node * array_node_objectpoints = node_objectpoints->sibling;
        if(array_node_objectpoints)
        {
            unsigned int i = 0;
            for(; i < array_node_objectpoints->children.size -1; i++)
            {
                struct AlgodalParser_Node * item = array_node_objectpoints->children.addr[i];
                unsigned int n1 = ExtractUint(nsi, item->children.addr[0]);
                unsigned int n2 = ExtractUint(nsi, item->children.addr[1]);
                unsigned int n3 = ExtractUint(nsi, item->children.addr[2]);
                signed   int n4 = ExtractUint(nsi, item->children.addr[3]);
                program.Objectpoints = realloc(program.Objectpoints, sizeof(struct AlgodalParser_Objectpoint) * (i + 1));
                program.Objectpoints[i].indexOfAction = n1;
                program.Objectpoints[i].type = n2;
                program.Objectpoints[i].flag = n3;
                program.Objectpoints[i].priority = n4;
            }
            program.Objectpoints = realloc(program.Objectpoints, sizeof(struct AlgodalParser_Objectpoint) * (i + 1));
            program.Objectpoints[i].indexOfAction = 0;
            program.Objectpoints[i].type = 0;
            program.Objectpoints[i].flag = 0;
        }
    }

    struct AlgodalParser_Node * node_code = AlgodalParserUtility_GetNextNode(nsi, root, AlgodalParserUtility_NodeSearch_VALUE, "\"code\"", 0);
    if(node_code)
    {
        struct AlgodalParser_Node * point_node_code = node_code->sibling;
        if(point_node_code)
        {
            unsigned int offset = 0;
            unsigned int i = 0;
            for(; i < point_node_code->children.size -1; i++)
            {
                struct AlgodalParser_Node * item = point_node_code->children.addr[i];
                uint8_t code[4] = {};
                unsigned int length_code = 0;
                ExtractCode(nsi, item, code, &length_code);
                program.CodeOfActions = realloc(program.CodeOfActions, offset + length_code);
                memcpy(&program.CodeOfActions[offset], code, length_code);
                offset += length_code;
            }
            program.CodeOfActions = realloc(program.CodeOfActions, offset + 1);
            memcpy(&program.CodeOfActions[offset], (int8_t[]){0}, 1);
        }
    }

    struct AlgodalParser_Node * node_count_tokenizers = AlgodalParserUtility_GetNextNode(nsi, root, AlgodalParserUtility_NodeSearch_VALUE, "\"count_tokenizers\"", 0);
    if(node_count_tokenizers)
    {
        struct AlgodalParser_Node * number_node_count_tokenizers = node_count_tokenizers->sibling;
        if(number_node_count_tokenizers)
        {
            program.CountOfTokenizers = ExtractUint(nsi, number_node_count_tokenizers);
        }
    }

    struct AlgodalParser_Node * node_count_entrypoints = AlgodalParserUtility_GetNextNode(nsi, root, AlgodalParserUtility_NodeSearch_VALUE, "\"count_entrypoints\"", 0);
    if(node_count_entrypoints)
    {
        struct AlgodalParser_Node * number_node_count_entrypoints = node_count_entrypoints->sibling;
        if(number_node_count_entrypoints)
        {
            program.CountOfEntrypoints = ExtractUint(nsi, number_node_count_entrypoints);
        }
    }

    struct AlgodalParser_Node * node_count_objectpoints = AlgodalParserUtility_GetNextNode(nsi, root, AlgodalParserUtility_NodeSearch_VALUE, "\"count_objectpoints\"", 0);
    if(node_count_objectpoints)
    {
        struct AlgodalParser_Node * number_node_count_objectpoints = node_count_objectpoints->sibling;
        if(number_node_count_objectpoints)
        {
            program.CountOfObjectpoints = ExtractUint(nsi, number_node_count_objectpoints);
        }
    }

    AlgodalParser_DestroyTokenizeResult(tr);
    if(ar.nodes.size) AlgodalParser_DestroyAnalyzeResult(ar);

    program.successful_allocation_json = 1;
    
    return program;
}

struct AlgodalParser_Program AlgodalJsonParser_GetProgramFromFile(const char *filename, struct AlgodalParser_Error *retError)
{
    char *text = "";
    unsigned int length = 0;

    FILE* fp = fopen(filename, "rb");
    if(fp)
    {
        if(fp == 0) return AlgodalJsonParser_GetProgramFromString(text, length, retError);
        fseek(fp, 0, SEEK_END);
        length = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        text = malloc(length + 1);
        memset(text, 0, length + 1);
        fread(text, 1, length, fp);
        fclose(fp);
        struct AlgodalParser_Program program = AlgodalJsonParser_GetProgramFromString(text, length, retError);
        free(text);
        return program;
    }
    else
    {
        cwpc_printf("AlgodalJsonParser_GetProgramFromFile: Could not find `%s` file!\n", filename);
    }
    return (struct AlgodalParser_Program){};
}

void AlgodalJsonParser_DestroyProgram(struct AlgodalParser_Program program)
{
    unsigned int count = 0;
    while(program.Strings[count].text)
    {
        free(program.Strings[count].text);
        program.Strings[count].text = 0;
        count ++;
    }

    free(program.Strings);
    free(program.CodeOfActions);
    free(program.Actions);
    free(program.Tokenizers);
    free(program.Entrypoints);
    free(program.Objectpoints);
    free(program.NameOfParser);
}

void AlgodalJsonParser_DebugProgram(struct AlgodalParser_Program program)
{
    cwpc_printf("Successfull Allocation of JSON: %s\n", program.successful_allocation_json?"True":"False");

    unsigned int count = 0;
    do
    {
        cwpc_printf("-- STRING %2u) [%p] %32s, %4u --\n", count, program.Strings[count].text, program.Strings[count].text, program.Strings[count].length);
        count ++;
    } while(program.Strings[count].text);
}


#endif//ALGODAL_GENERATED_PARSER_JSON_CONVERTER_C
//MARKER
