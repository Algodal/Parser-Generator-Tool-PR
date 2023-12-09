#include <time.h>

#include "algodal-parser-header.h"

extern AlgodalParser_Program configProgram;

/// Nothing Special.  This is something very arbitrary.  You can ignore this!!!
static int ExitParsing(long retv[], int retc)
{
    for(int i = 0; i < retc; i++)
    {
        if(retv[i] != 0) return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

static void LogNode(AlgodalParser_Ast ast, AlgodalParser_Node* node, const char* expect)
{
    const char* label = AlgodalParser_GetActionString_READONLY(ast.program, node->indexOfAction);
    unsigned int valuesize = AlgodalParser_GetNodeValueSize(ast.tokens, node);
    char* parse = malloc(valuesize+1);
    memset(parse, 0, valuesize);
    AlgodalParser_GetNodeValue(ast.text, ast.tokens, node, valuesize, parse);
    printf("Logging Node:\nExpecting `%s` At Node of key:%s and value:(next line)\n```\n%s\n```\n", expect, label, parse);
    free(parse);
}

static void LogNull(void* object, int line)
{
    if(object==NULL)printf("The object is NULL at line %d\n", line);
}

#define LOGNULL(OBJECT) LogNull(OBJECT, __LINE__)

static int GetDeviceId(const char* device)
{
    if(AlgodalParser_StrCmp(1, device, "Tablet")) return 1;
    if(AlgodalParser_StrCmp(1, device, "Desktop")) return 2;
    if(AlgodalParser_StrCmp(1, device, "PC")) return 2;
    if(AlgodalParser_StrCmp(1, device, "Mobile")) return 3;
    if(AlgodalParser_StrCmp(1, device, "Phone")) return 3;
    if(AlgodalParser_StrCmp(1, device, "Android")) return 3;
    if(AlgodalParser_StrCmp(1, device, "IPhone")) return 3;
    return 0;
}

/// @brief This is your defined struct.  The data you parse you would to treat it
///        any number of ways.  You would (if you want) create some arbitrary struct
///        to store your parse data.  In this example, I am pulling the data LINEARLY.
///        You can structure your struct and name your members any how you like.
///        You don't even have to use a struct and interpret your data immediately after
///        Pulling it from your AST.
struct MyData
{
    int window_width;
    int window_height;
    char* user_name;
    int user_age;
    char* user_address;
    char* user_foods;
    char* system_os;
    int system_device;
    struct
    {
        int year;
        int month;
        int day;
        int hour;
        int minute;
        char period[16];
    } system_time;
    
};

struct MyData* ReadAst(
    AlgodalParser_TokenizeResult tr,
    AlgodalParser_AnalyzeResult ar,
    AlgodalParser_Program program,
    const char* text,
    AlgodalParser_Linenumber *ln
)
{
    AlgodalParser_Ast ast = AlgodalParser_InitializeAst(program, tr, ar, ln, text);

    //< ast stores all the important struct we are going to need to manipulate the Node.

    // Let's get our data.
    // You can always print (AlgodalParser_PrintAnalyzeResult) it to see what it looks like in memory.

    // Normally you would start with  AlgodalParser_GetNodeByKeyOfRoots or AlgodalParser_GetNodeByValueOfRoots
    // since AlgodalParser_GetAnalyzeResult return's a list of root.  But since in this simple example
    // we know we only have one instance of a root, we will selecting it from the array and start with
    // AlgodalParser_GetNodeByKeyOfNode (or AlgodalParser_GetChildNodeByValueOfNode)

    /// Allocate space for MyData
    struct MyData* mydata = (struct MyData*)malloc(sizeof(struct MyData));
    memset(mydata, 0, sizeof(struct MyData));

    AlgodalParser_Node* section; //< NOTE: How I decide to manipulate my ast (via section, heading and keyval) is also arbitrary and based on how my nodes are generated.  You can change both manipulation and analyzation based on your preference!
    AlgodalParser_Node* heading;
    AlgodalParser_Node* keyval;

    LogNode(ast, ar.nodes.addr[0], "INI"); //For debugging 

    section = AlgodalParser_GetNodeByKeyOfNode(ast, 0, "section", ar.nodes.addr[0]); //< get the first section
    LOGNULL((void*)section); //For debugging 

    /// Once we have the first section,
    /// we are going to loop through subsequent sections
    while(section)
    {
        printf("Log: read section\n");
        //LogNode(ast, section, "SECTION"); //Logging (Debug) purposes

        heading = AlgodalParser_GetNodeByKeyOfNode(ast, 0, "heading", section);
        //LogNode(ast, heading, "HEADING"); //For debugging 
        LOGNULL(heading);  //For debugging 

        /// I put this code here for convenience.  I could have put it 
        /// inside the if statement.  But I adjusted specifically for 
        /// what I am reading.  I know that each heading MUST have atleast 1 keyval 
        /// pair.  So I get the first one here.  And since there will be a 
        /// list of keyval pairs as siblings, I can loop through the siblings.
        keyval = AlgodalParser_GetNodeByKeyOfNode(ast, 0, "setvalue", heading); 

        /// AlgodalParser_IsNodeValueSubstring is used 
        /// instead of AlgodalParser_IsNodeValue because the value of 
        /// the Node is actually `[window]` with the square brackets included.  
        /// I could have instead called 
        /// (AlgodalParser_IsNodeValue(ast, 1, "[WINDOW]", heading) and 
        /// it would haved worked the same.
        if(AlgodalParser_IsNodeValueSubstring(ast, 1, "WINDOW", heading)) //<NOTICE: 1 is passed for 1 case to tell it the comparison is CASE-INSENSITIVE.  Therefore, "window"=="WINDOW" will return TRUE.
        {
            printf("Log: read window\n");
            //I know that set value is structure like this:
            
            //setvalue
            //..name:  [value]
            //..value: [value]
            
            LOGNULL(keyval); //debugging
            //So I can ignore the KEY(LABEL) of the nodes of `Name` and `Value` and focus on the VALUE.
            while(keyval)
            {
                //LogNode(ast, keyval, "SETVALUE");

                if(AlgodalParser_IsNodeValue(ast, 1, "width", AlgodalParser_GetNodeByKeyOfNode(ast, 0, "name", keyval)))
                {
                    printf("Log: read width\n");
                    char* value = AlgodalParser_AllocNodeValue(ast, AlgodalParser_GetNodeByKeyOfNode(ast, 0, "value", keyval));
                    mydata->window_width = (int)AlgodalParser_StrToInt(value, 0);
                    free((void*)value);
                }
                if(AlgodalParser_IsNodeValue(ast, 1, "height", AlgodalParser_GetNodeByKeyOfNode(ast, 0, "name", keyval)))
                {
                    printf("Log: read height\n");
                    char* value = AlgodalParser_AllocNodeValue(ast, AlgodalParser_GetNodeByKeyOfNode(ast, 0, "value", keyval));
                    mydata->window_height = (int)AlgodalParser_StrToInt(value, 0);
                    free((void*)value);
                }


                keyval = keyval->sibling; //the next setvalue under the heading
            }
        }

        if(AlgodalParser_IsNodeValueSubstring(ast, 0, "user", heading))
        {
            printf("Log: read user\n");
            
            while(keyval)
            {
                //LogNode(ast, keyval, "SETVALUE");

                if(AlgodalParser_IsNodeValue(ast, 1, "name", AlgodalParser_GetNodeByKeyOfNode(ast, 0, "name", keyval)))
                {
                    printf("Log: read name\n");
                    char* value = AlgodalParser_AllocNodeValue(ast, AlgodalParser_GetNodeByKeyOfNode(ast, 0, "value", keyval));
                    //The name is in quotes because that's how it is parsed.
                    //You would have to manually remove the quotes, if you want to.
                    mydata->user_name = AlgodalParser_UnquoteStr(value, value);
                }
                if(AlgodalParser_IsNodeValue(ast, 1, "age", AlgodalParser_GetNodeByKeyOfNode(ast, 0, "name", keyval)))
                {
                    printf("Log: read age\n");
                    char* value = AlgodalParser_AllocNodeValue(ast, AlgodalParser_GetNodeByKeyOfNode(ast, 0, "value", keyval));
                    mydata->user_age = (int)AlgodalParser_StrToInt(value, 0);
                    free((void*)value);
                }
                if(AlgodalParser_IsNodeValue(ast, 1, "address", AlgodalParser_GetNodeByKeyOfNode(ast, 0, "name", keyval)))
                {
                    printf("Log: read address\n");
                    char* value = AlgodalParser_AllocNodeValue(ast, AlgodalParser_GetNodeByKeyOfNode(ast, 0, "value", keyval));
                    mydata->user_address = value;
                }
                if(AlgodalParser_IsNodeValue(ast, 1, "foods", AlgodalParser_GetNodeByKeyOfNode(ast, 0, "name", keyval)))
                {
                    printf("Log: read foods\n");
                    char* value = AlgodalParser_AllocNodeValue(ast, AlgodalParser_GetNodeByKeyOfNode(ast, 0, "value", keyval));
                    mydata->user_foods = value;
                }

                
                keyval = keyval->sibling; //the next setvalue under the heading
            }
        }

        if(AlgodalParser_IsNodeValueSubstring(ast, 0, "system", heading))
        {
            printf("Log: read system\n");
            
            while(keyval)
            {
                //LogNode(ast, keyval, "SETVALUE");

                if(AlgodalParser_IsNodeValue(ast, 1, "os", AlgodalParser_GetNodeByKeyOfNode(ast, 0, "name", keyval)))
                {
                    printf("Log: read os\n");
                    char* value = AlgodalParser_AllocNodeValue(ast, AlgodalParser_GetNodeByKeyOfNode(ast, 0, "value", keyval));
                    mydata->system_os = value;
                }
                /// changed around the code here just for demo
                if(AlgodalParser_IsNodeValueSubstring(ast, 0, "device", AlgodalParser_GetNodeByKeyOfNode(ast, 0, "name", keyval)))
                {
                    printf("Log: read device\n");
                    AlgodalParser_Node* other = AlgodalParser_GetNodeByKeyOfNode(ast, 0, "value", keyval);
                    char* value = AlgodalParser_AllocNodeValue(ast, other);
                    mydata->system_device = GetDeviceId(value);
                    free((void*)value);
                }
                if(AlgodalParser_IsNodeValue(ast, 1, "last_used", AlgodalParser_GetNodeByKeyOfNode(ast, 0, "name", keyval)))
                {
                    printf("Log: read time\n");
                    char* value = AlgodalParser_AllocNodeValue(ast, AlgodalParser_GetNodeByKeyOfNode(ast, 0, "value", keyval));
                    sscanf
                    (
                        value, 
                        "%d-%d-%d %d:%d %s", 
                        &mydata->system_time.year, &mydata->system_time.month,
                        &mydata->system_time.day, &mydata->system_time.hour,
                        &mydata->system_time.minute, mydata->system_time.period
                    );
                    free(value);
                }

                
                keyval = keyval->sibling; //the next setvalue under the heading
            }
        }

        section = section->sibling; //Set the next sibling section as the point of reference section.  This works because each section is a sibling to another and children of the root.  
    }

    printf("Done manipulating AST\n");

    return mydata;
}


/// @brief Demo Code demonstrating parsing text, interpreting the AST from the parse.
int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        FILE* fp = fopen(argv[1], "rb");
        if(fp)
        {
            if(fp == 0) return EXIT_FAILURE;
            fseek(fp, 0, SEEK_END);
            size_t length = ftell(fp);
            fseek(fp, 0, SEEK_SET);
            char *text = (char*)malloc(length + 1);
            text[length] = 0;
            fread(text, 1, length, fp);
            fclose(fp);
            
            
            clock_t begin = clock(), end;
            double duration;
            
            AlgodalParser_TokenizeResult TokenizeResult = AlgodalParser_GetTokenizeResult(configProgram, text, length, 0);
            AlgodalParser_AnalyzeResult AnalyzeResult = AlgodalParser_GetAnalyzeResult(configProgram, text, TokenizeResult.tokens.addr, TokenizeResult.tokens.size, 0);
            end = clock();
            duration = (double)(end - begin) / CLOCKS_PER_SEC;
            
            
            AlgodalParser_Linenumber *PLn = AlgodalParser_CreateParserLinenumber(text, length);
            cwpc_printf("\nTokenization:\n");
            AlgodalParser_PrintTokenizeResult(configProgram, TokenizeResult, text, PLn);
            
            if((configProgram).CountOfEntrypoints)
			{
				if(TokenizeResult.error.flags == 0)
		        {
		            cwpc_printf("\nAnalyzation:\n");
		            AlgodalParser_PrintAnalyzeResult(configProgram, AnalyzeResult, TokenizeResult.tokens.addr, text, PLn);
		        }
		        else
		        {
					cwpc_printf("Tokenization step contains error - Analyzation not done.\n");
		        }
			}

            struct MyData* data = ReadAst(
                TokenizeResult, 
                AnalyzeResult,
                configProgram,
                text,
                PLn
            );

            printf("\n\n--------- OUTPUT ---------\n\n");
            
            printf("window size: %dx%d\n", data->window_width, data->window_height);
            printf("user: %s; he is %d years old; he lives at %s; he loves to eat %s\n", 
                data->user_name, data->user_age,
                data->user_address, data->user_foods);
		    printf("system: os:%s, device:%d, time last used: %d-%02d-%02d %02d:%02d %s\n", 
                data->system_os, data->system_device,
                data->system_time.year, data->system_time.month,
                data->system_time.day, data->system_time.hour,
                data->system_time.minute, data->system_time.period);

            cwpc_printf("completed in %f milliseconds\n", duration * 1000);
            AlgodalParser_DestroyParserLinenumber(PLn);
            AlgodalParser_DestroyTokenizeResult(TokenizeResult);
            AlgodalParser_DestroyAnalyzeResult(AnalyzeResult);
            free(text);
            long ret[] = {TokenizeResult.error.flags, AnalyzeResult.error.flags};
            return ExitParsing(ret, sizeof(ret)/sizeof(long));
        }
        cwpc_printf("FAILED TO OPEN FILE %s\n", argv[1]);
    }
    cwpc_printf("PASS THE NAME OF THE FILE TO PARSE\n");
    return EXIT_FAILURE;
}

