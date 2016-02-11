#ifndef JSON
#define JSON

#include <iostream>
#include <fstream>
#include <string.h>
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "ngl/XMLSerializer.h"
#include "ngl/rapidxml/rapidxml_print.hpp"


class Json
{
public:
    Json();
    ~Json();

    void saveToFile(std::string _jsonString);

    void replaceWord(std::string _oldWord, std::string _newWord);

    std::string buildJson();
    rapidxml::xml_document<> m_doc;
    rapidxml::xml_node<> * root_node;

};

#endif

