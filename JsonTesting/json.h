#ifndef JSON
#define JSON

#include <iostream>
#include <fstream>
#include <string.h>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"


class Json
{
public:
    Json();
    ~Json();

    void saveToFile(std::string _jsonString);

    void replaceWord(std::string _oldWord, std::string _newWord);

    //std::string shaderType(int _shaderNumber)
    std::string buildJson();

    Json *jsonInstance;

};

#endif // JSON

