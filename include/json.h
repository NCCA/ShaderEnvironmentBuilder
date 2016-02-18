#ifndef JSON_H_
#define JSON_H_

#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

#include "json/json.hpp"
//#include "rapidjson/writer.h"
//#include "rapidjson/stringbuffer.h"
//#include "ngl/XMLSerializer.h"
//#include "ngl/rapidxml/rapidxml_print.hpp"
using namespace std;

class Json
{
public:

    //----------------------------------------------------------------------------------------------------------------------
    /// @brief ctor for the json class
    //----------------------------------------------------------------------------------------------------------------------
    Json();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Writes to a file
    /// @param[in] _fileName specifies the name of the file to be written
    /// @param[in] _stringData The data to be written to the file
    //----------------------------------------------------------------------------------------------------------------------
    void writeFile(string _fileName, string _stringData);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Reads from a file
    /// @param[in] _fileName specifies the name of the file to be read
    //----------------------------------------------------------------------------------------------------------------------
    void readFile(std::string _fileName);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Reads the file as a string and replaces words
    /// @param[in] _oldWord Word to be replaced
    /// @param[in] _newWord Replaced word
    //----------------------------------------------------------------------------------------------------------------------
    void replaceWord(string _oldWord, string _newWord);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Builds the default shader
    //----------------------------------------------------------------------------------------------------------------------
    void defaultShader();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Appends shader data
    /// @param[in] _name Name for data
    /// @param[in] _type Type of data
    /// @param[in] _value Value of data
    //----------------------------------------------------------------------------------------------------------------------
    void addShaderData(string _name, string _type, double _value);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief dtor for the json class
    //----------------------------------------------------------------------------------------------------------------------
    ~Json();

    //    rapidxml::xml_document<> m_doc;
    //    rapidxml::xml_node<> * root_node;
};

#endif //_JSON_H_

