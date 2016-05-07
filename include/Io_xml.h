#ifndef IO_XML_H
#define IO_XML_H

#include <iostream>
#include <fstream>
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
    /// @param _name the name of the saved project file
    /// @param _dir the directory of the saved project file
    /// @param _vertSource the vertex shader source code
    /// @param _fragSource the fragment shader source code
    //----------------------------------------------------------------------------------------------------------------------
    void writeProject(std::string _name, std::string _dir, std::string _vertSource, std::string _fragSource);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Saves data
    /// @param The parameters are subject to change- may be deprecated.
    //----------------------------------------------------------------------------------------------------------------------
    void shaderData(const char *_shaderProgramName, const char *_vertexShaderName,
                    const char *_vertexShaderGlsl, const char *_fragmentShaderName,
                    const char *_fragmentShaderGlsl);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Will read the project file data
    /// @param _type
    //----------------------------------------------------------------------------------------------------------------------
    void readProjectXML(std::string &_name, std::string &_dir, std::string _loadedFileDirectory, std::string& _vertSource, std::string& _fragSource);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Deprecated function
    //----------------------------------------------------------------------------------------------------------------------
    void writeXML(std::string _name, std::string _type, int _value);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Destructor
    //----------------------------------------------------------------------------------------------------------------------
    //~IO_XML();

private:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Created xml document (delete)
    //----------------------------------------------------------------------------------------------------------------------
    rapidxml::xml_document<> m_doc;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Created root node (delete)
    //----------------------------------------------------------------------------------------------------------------------
    rapidxml::xml_node<> * root_node;

};

#endif // IO_XML_H
