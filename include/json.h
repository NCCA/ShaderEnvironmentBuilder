#ifndef JSON_H_
#define JSON_H_

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

    void writeFile(string _fileName, string _stringData);
    void readFile(std::string _fileName);

    void replaceWord(string _oldWord, string _newWord);

    void buildJson();

    void addShaderData(string _name, string _type, double _value);
    //void newBuildJson();
    rapidxml::xml_document<> m_doc;
    rapidxml::xml_node<> * root_node;

};

#endif //_JSON_H_

