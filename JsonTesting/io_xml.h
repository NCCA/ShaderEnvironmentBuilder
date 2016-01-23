#ifndef IO_XML_H
#define IO_XML_H

#include <iostream>
#include <fstream>
#include <string.h>
#include "ngl/XMLSerializer.h"



class IO_XML
{
public:
    IO_XML();
    ~IO_XML();

    void readXML();
    void writeXML();
    rapidxml::xml_document<> m_doc;
    rapidxml::xml_node<> * root_node;

    IO_XML *XMLInstance;



};

#endif // IO_XML_H
