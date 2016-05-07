#ifndef IO_XML_H
#define IO_XML_H

#include <iostream>
#include <ostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include "ngl/XMLSerializer.h"
#include "ngl/rapidxml/rapidxml_print.hpp"

//------------------------------------------------------------------------------------------------------------------------
/// @file io_xml.h
/// @brief Creates xml files to store project data by the user. The data can then be read for futher use.
/// @author Ellie Ansell
/// @version 1.0
/// @date 22/04/16
//------------------------------------------------------------------------------------------------------------------------

class IO_XML
{
public:
    IO_XML();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Saves the project name, vertex and fragment data in set directory
    /// @param [in] _name the name of the saved project file
    /// @param [in] _dir the directory of the saved project file
    /// @param [in] _vertSource the vertex shader source code
    /// @param [in] _fragSource the fragment shader source code
    //----------------------------------------------------------------------------------------------------------------------
    void writeProject(std::string _name, std::string _dir, std::string _vertSource, std::string _fragSource);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Saves data
    /// @param [in] _shaderProgramName Name of the shader program
    /// @param [in] _vertexShaderName Name of the vertex shader
    /// @param [in] _vertexShaderGlsl Vertex data
    /// @param [in] _fragmentShaderName Fragment data
    /// @param [in] _fragmentShaderGlsl
    //----------------------------------------------------------------------------------------------------------------------
    void shaderData(const char *_shaderProgramName, const char *_vertexShaderName,
                    const char *_vertexShaderGlsl, const char *_fragmentShaderName,
                    const char *_fragmentShaderGlsl);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Will read the project file data
    /// @param [in] &_name reference to current working file name
    /// @param [in] &_dir reference to current working directory
    /// @param [in] _loadedFileDirectory Name of loaded file directory selected by UI.
    /// @param [in] &_vertSource Reference of vertex string read then returned to project
    /// @param [in] &_fragSource Reference of fragment string read then returned to project
    //----------------------------------------------------------------------------------------------------------------------
    void readProjectXML(std::string &_name, std::string &_dir, std::string _loadedFileDirectory, std::string& _vertSource, std::string& _fragSource);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief (unused) Writes name, type and value for passed data.
    /// @param [in] _name Used to identify data
    /// @param [in] _type Material type
    /// @param [in] _value data value
    //----------------------------------------------------------------------------------------------------------------------
    void writeXML(std::string _name, std::string _type, int _value);
};

#endif // IO_XML_H
