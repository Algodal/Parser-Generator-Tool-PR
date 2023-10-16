//Add Include from Generated Parser here ...

#ifndef ALGODAL_GENERATED_PARSER_JSON_CONVERTER_H
#define ALGODAL_GENERATED_PARSER_JSON_CONVERTER_H

struct AlgodalParser_Program AlgodalJsonParser_GetProgramFromString(const char *stringBuffer, const unsigned int stringLength, struct AlgodalParser_Error *retError);
struct AlgodalParser_Program AlgodalJsonParser_GetProgramFromFile(const char *filename, struct AlgodalParser_Error *retError);
void AlgodalJsonParser_DestroyProgram(struct AlgodalParser_Program program);

#endif//ALGODAL_GENERATED_PARSER_JSON_CONVERTER_H
