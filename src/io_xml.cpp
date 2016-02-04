
#include "io_xml.h"
#include <fstream>
#include <ostream>
#include <vector>
#include <stdio.h>
//#include "rapidxml_print.hpp"
using namespace rapidxml;
using namespace std;
IO_XML::IO_XML()
{
}

void IO_XML::readXML(std::string _type)
{
        xml_document<> doc;
        ifstream file("/home/i7685565/0Features-0BugsCVA3/tempFiles/readFrom.xml");
        vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>( ));
        buffer.push_back('\0');
        //cout<<&buffer[0]<<endl;  //prints xml buffer
        doc.parse<0>(&buffer[0]);

        xml_node<> *current_node = doc.first_node("root");

        // switching to a different node
        current_node = current_node->first_node("dataSets")->first_node("a");

        //traverse through node attributes until it finds _type
        for (current_node->first_node("dataSets"); current_node; current_node = current_node->next_sibling())
        {
            if (current_node->first_attribute("name")->value()==_type)
            {
                std::cout<<"Data for "<<_type<<": ";
                std::cout<<"\tName: "<<current_node->first_attribute("name")->value()<<"\tValue: "<< current_node->first_attribute("value")->value()<<"\tType: "<<current_node->first_attribute("type")->value()<<std::endl;
            break;
            };
        }
}

void IO_XML::writeXML(std::string _name, std::string _type, int _value)
{

        cout<<"Input name = "<<_name<<"\tInput value = "<<_type<<"\tInput value = "<<_value<<std::endl;
//        cout<<"\nWriting to XML file..."<<endl;


        xml_document<> doc;
        ifstream file("/home/i7685565/0Features-0BugsCVA3/tempFiles/readFrom.xml");
        vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>( ));
        buffer.push_back('\0');
        //cout<<&buffer[0]<<endl;  //prints xml buffer
        doc.parse<0>(&buffer[0]);
        xml_node<> *current_node = doc.first_node("root");
        current_node = current_node->first_node("dataSets");
        current_node->append_attribute(doc.allocate_attribute("NewName", "Henry"));
        current_node->append_attribute(doc.allocate_attribute("Version", "5000"));
        ofstream newfile;
        newfile.open("/home/i7685565/0Features-0BugsCVA3/tempFiles/writtenTo.xml");
        newfile << doc;
}

void IO_XML::shaderData(const char* _shaderProgramName, const char* _vertexShaderName, const char* _vertexShaderGlsl, const char* _fragmentShaderName, const char* _fragmentShaderGlsl)
{
    xml_document<> doc;
    ifstream file("/home/i7685565/0Features-0BugsCVA3/tempFiles/shaderData.xml");
    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>( ));
    buffer.push_back('\0');
//    //cout<<&buffer[0]<<endl;  //prints xml buffer
    doc.parse<0>(&buffer[0]);

    //------adding new node
//    xml_node<> *new_Node = doc.allocate_node(node_element, "ShaderProgram");
//    doc.append_node(new_Node);

//    xml_attribute<> *new_attr = doc.allocate_attribute("name", "_shaderProgramName");
//    new_Node->append_attribute(new_attr);

    xml_node<> *current_node = doc.first_node("ShaderProgram");
    xml_node<> *vertex_node = current_node->first_node("VertexData");
    xml_node<> *fragment_node = current_node->first_node("FragmentData");

    vertex_node->first_attribute("name")->value(_vertexShaderName);
    vertex_node->first_attribute("vertexPath")->value(_vertexShaderGlsl);

    fragment_node->first_attribute("name")->value(_fragmentShaderName);
    fragment_node->first_attribute("customPath")->value(_fragmentShaderGlsl);

    ofstream newfile;
    newfile.open("/home/i7685565/0Features-0BugsCVA3/tempFiles/shaderData.xml");
    newfile << doc;
}
