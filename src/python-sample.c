//Add Header from Generated parser here ...
//Add Utility header
//Add Extend header



extern char *TestDataReadFile(const char *name, unsigned int *sizeOfFile); //Create this

void void()
{
	struct AlgodalParser_Program program = TestDataParserProgram; //Comes from Generated Parser
	unsigned int length = 0;
	char *text = TestDataReadFile("sample.py", &length);
	struct AlgodalParser_TokenizeResult tresult = AlgodalParser_GetTokenizeResult(program, text, length, 0);
	tresult = TokenPostProcessing_GeneratePythonTokens(&tresult, program, text); //Generates INDENT and DEDENT tokens
	AlgodalParser_PrintTokenizeResult(program, tresult, text, 0); //check result
}
