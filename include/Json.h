#ifndef JSON_H_
#define JSON_H_

#include <iostream>
#include <fstream>
#include <string.h>
#include <json/json.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <rapidjson/document.h>

//------------------------------------------------------------------------------------------------
/// @file Json.h
/// @brief Creates a json file to then load shader data to the shader manager.
/// @author Ellie Ansell
/// @version 1.0
/// @date 22/04/16
//------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------
/// This class isn't used in the final IDE for two reasons: firstly XML was chosen instead to load the vertex and
/// fragment shader data because it was easily customisable with sets of tags to support schemas and namespaces; and
/// secondly, the loadShaderFromJson() wasn't used in the ShaderManager as an alternate method was used. The aim was to
/// use the Json file to load whichever shader chosen, by replacing the name of the shader in the json file to direct to
/// the correct vertex and fragment shaders.
//------------------------------------------------------------------------------------------------
using namespace std;

class Json
{
public:
    //------------------------------------------------------------------------------
    /// @brief ctor for the json class
    //------------------------------------------------------------------------------
    Json();
    //------------------------------------------------------------------------------
    /// @brief Uses auto Json to build a default json structure to be read.
    //------------------------------------------------------------------------------
    void defaultShader();
    //------------------------------------------------------------------------------
    /// @brief Reads the file as a string and replaces a word. This would have been used to replace the shader's name
    /// (e.g. 'Phong') with another shader, such as toon, in the json file which would then redirect to the vertex and fragment
    /// shader.
    /// @param[in] _oldWord Word to be replaced
    /// @param[in] _newWord Replaced word
    //------------------------------------------------------------------------------
    void replaceWord(string _oldWord, string _newWord);
    //------------------------------------------------------------------------------
    /// @brief Writes to a file (This was replaces by an XML method).
    /// @param[in] _fileName specifies the name of the file to be written
    /// @param[in] _stringData The data to be written to the file
    //------------------------------------------------------------------------------
    void writeFile(string _fileName, string _stringData);
    //------------------------------------------------------------------------------
    /// @brief Reads from a file
    /// @param[in] _fileName specifies the name of the file to be read
    //------------------------------------------------------------------------------
    void readFile(std::string _fileName);
    //------------------------------------------------------------------------------
    /// @brief Appends shader data. (This was replaced by an XML method)
    /// @param[in] _name Name for data
    /// @param[in] _type Type of data
    /// @param[in] _value Value of data
    //------------------------------------------------------------------------------
    void addShaderData(string _name, string _type, double _value);
    //------------------------------------------------------------------------------
    /// @brief Destructor
    //------------------------------------------------------------------------------
    ~Json();

};

#endif //_JSON_H_

