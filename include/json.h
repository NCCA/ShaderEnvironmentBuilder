#ifndef JSON
#define JSON

#include <iostream>
#include <fstream>
#include <string.h>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "ngl/XMLSerializer.h"
#include "ngl/rapidxml/rapidxml_print.hpp"
#include <vector>
#include "json/json.hpp"
using namespace std;

class Json
{
public:
    Json();
    ~Json();

    void saveShaderToJson(std::string _jsonString);

    void saveShaderDataToJson(std::string _jsonString);


    void replaceWord(std::string _oldWord, std::string _newWord);

    void buildJson();

    void writeShaderData(string _name, string _type, int _value);
    //void newBuildJson();
    rapidxml::xml_document<> m_doc;
    rapidxml::xml_node<> * root_node;

};

#endif

