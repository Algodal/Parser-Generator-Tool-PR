#include "algodal-parser-header.h"

extern AlgodalParser_Program IntParserProgram; //generated in IntParser.c

static char *ReadFile(const char *name, unsigned int *sizeOfFile)
{
    FILE* fp = fopen(name, "rb");
    if(fp)
    {
        fseek(fp, 0, SEEK_END);
        const size_t length = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        char *text = malloc(length + 1);
        text[length] = 0;
        (void)fread(text, 1, length, fp);
        fclose(fp);
        if(sizeOfFile) *sizeOfFile = length;
        return text;
    }
    cwpc_printf("FAILED TO OPEN FILE %s\n", name);
    return 0;
}

static int NodeToNumber(AlgodalParser_Ast ast, AlgodalParser_Node* node) 
{
    char buf[1024] = {0}; 
    ////alternative
    //int size = node->size;
    //char* buf = malloc(size + 1);
    //memset(buf, 0, size + 1);
    ////free before return
    AlgodalParser_GetNodeValue(ast, node, buf);
    return strtol(buf, 0, 10);
}

static int CalculateExprValue(AlgodalParser_Ast ast, AlgodalParser_Node* node)
{
    //Here we will demonstrate AST manipulation
    //At the root, we expect `line `.  The first child will always be integer
    //followed by series of one of `multiply`, `add`, `divide` or `substract`.
    //Each of which follows the same pattern for it's children.
    //Therefore, we can use a simple loop for each.

    int result = NodeToNumber(ast, node->children.addr[0]); 
    //based on AST, the first child will always be of type `integer`

    for(uint32_t i = 1; i < node->children.size; i++)
    {
        AlgodalParser_Node* child = node->children.addr[i];

        if(AlgodalParser_IsNodeKey(ast, 0, "multiply", child))
        {
            result *= CalculateExprValue(ast, child);
        }
        else
        if(AlgodalParser_IsNodeKey(ast, 0, "divide", child))
        {
            result /= CalculateExprValue(ast, child);
        }
        else
        if(AlgodalParser_IsNodeKey(ast, 0, "add", child))
        {
            result += CalculateExprValue(ast, child);
        }
        else
        if(AlgodalParser_IsNodeKey(ast, 0, "subtract", child))
        {
            result -= CalculateExprValue(ast, child);
        }
    }
    return result;
}

int main(int argc, char* argv[])
{
    if(argc > 1)
    {
        unsigned int length = 0;
        char* text = ReadFile(argv[1], &length);
        AlgodalParser_ParsedData pd = AlgodalParser_ParseText(IntParserProgram, text, length);
        //AlgodalParser_PrintParsedData(pd); //to view the tokens and AST
        for(uint32_t i = 0; i < pd.ast.nodes.size; i++)
        {
            char buf[1024] = {0}; //for demo purposes just using a big enough size but can allocate exact size
            printf(
                "%s = %d\n", 
                AlgodalParser_GetNodeValueSimplified(pd.ast, pd.ast.nodes.addr[i], buf), 
                CalculateExprValue(pd.ast, pd.ast.nodes.addr[i])
            );
        }
        AlgodalParser_DestroyParsedData(pd);
        free(text); //only free this after you are done with the parsed data
    }
    else
    {
        printf("Pass file to parse\n");
    }
    return 0;
}