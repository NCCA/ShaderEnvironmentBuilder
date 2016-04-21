#ifndef IO_XML_H
#define IO_XML_H

#include <iostream>
#include <fstream>
#include <string.h>
#include "ngl/XMLSerializer.h"
#include "ngl/rapidxml/rapidxml_print.hpp"

class IO_XML
{
public:
    IO_XML();
    //~IO_XML();

    void shaderData(const char *_shaderProgramName, const char *_vertexShaderName,
                    const char *_vertexShaderGlsl, const char *_fragmentShaderName,
                    const char *_fragmentShaderGlsl);
    void readXML(std::string _type);
    void writeXML(std::string _name, std::string _type, int _value);
    void writeProject(std::string _name, std::string _dir);
    rapidxml::xml_document<> m_doc;
    rapidxml::xml_node<> * root_node;

    //IO_XML *XMLInstance;

};

#endif // IO_XML_H
