
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
// ----------------------------------------------------------------------------------------------------------------------
// Organises name, type and value for shader data into an XML file. E.g. Name: light.diffuse, Type: mat4, value: 1
void IO_XML::writeXML(std::string _name, std::string _type, int _value)
{

        cout<<"Input name = "<<_name<<"\tInput value = "<<_type<<"\tInput value = "<<_value<<std::endl;
        xml_document<> doc;
        ifstream file("./XMLfiles/readFrom.xml");
        vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>( ));
        buffer.push_back('\0');
        //cout<<&buffer[0]<<endl;  //prints xml buffer
        doc.parse<0>(&buffer[0]);
        xml_node<> *current_node = doc.first_node("root");
        current_node = current_node->first_node("dataSets");
        current_node->append_attribute(doc.allocate_attribute("NewName", "Henry"));
        current_node->append_attribute(doc.allocate_attribute("Version", "5000"));
        ofstream newfile;
        newfile.open("./XMLfiles/writtenTo.xml");
        newfile << doc;
}

//----------------------------------------------------------------------------------------------------------------------
// This function organises the shaderData from NGLScene into an XML file, which will then be read in json.cpp to build a json string.
void IO_XML::shaderData(const char* _shaderProgramName, const char* _vertexShaderName, const char* _vertexShaderGlsl, const char* _fragmentShaderName, const char* _fragmentShaderGlsl)
{
    xml_document<> doc;
    ifstream file("./shaders/shaderData.xml");
    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>( ));
    buffer.push_back('\0');
    doc.parse<0>(&buffer[0]);

    xml_node<> *current_node = doc.first_node("ShaderProgram");
    xml_node<> *vertex_node = current_node->first_node("VertexData");
    xml_node<> *fragment_node = current_node->first_node("FragmentData");

    vertex_node->first_attribute("name")->value(_vertexShaderName);
    vertex_node->first_attribute("vertexPath")->value(_vertexShaderGlsl);

    fragment_node->first_attribute("name")->value(_fragmentShaderName);
    fragment_node->first_attribute("customPath")->value(_fragmentShaderGlsl);

    ofstream newfile;
    newfile.open("./shaders/shaderData.xml");
    newfile << doc;
}


// ----------------------------------------------------------------------------------------------------------------------
// (May be omitted) Reading from an XML file.
void IO_XML::readXML(std::string _type)
{
        xml_document<> doc;
        ifstream file("./XMLfiles/readFrom.xml");
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

//------------------------------------------------------------------------------------------------------------------------
// Saves project file to user's directory
void IO_XML::writeProject(std::string _name, std::string _dir, std::string _vertSource, std::string _fragSource)
{
    // Converts strings to type const char* for rapidXML functions
    const char * projectName =_name.c_str();
    const char * projectDir = _dir.c_str();
    const char * vertSource = _vertSource.c_str();
    const char * fragSource = _fragSource.c_str();

    // Creating XML document
    xml_document<> saveProject;
    // Set default version and encoding
    xml_node<>* decl = saveProject.allocate_node(node_declaration);
    decl->append_attribute(saveProject.allocate_attribute("version", "1.0"));
    decl->append_attribute(saveProject.allocate_attribute("encoding", "utf-8"));
    saveProject.append_node(decl);

    // Creating root node with name and directory
    xml_node<>* root = saveProject.allocate_node(node_element, "Shader_Data");
    root->append_attribute(saveProject.allocate_attribute("Name", projectName));
    root->append_attribute(saveProject.allocate_attribute("Dir",projectDir));
    saveProject.append_node(root);

    // Creating child nodes containing input vertex and fragment shader data
    xml_node<>* child = saveProject.allocate_node(node_element, "Vertex");
    root->append_node(child);
    child->append_attribute(saveProject.allocate_attribute("VtxData", vertSource));

    xml_node<>* child2 = saveProject.allocate_node(node_element, "Fragment");
    root->append_node(child2);
    child2->append_attribute(saveProject.allocate_attribute("FragData", fragSource));

    // Save to file
    std::ofstream file_stored(_dir+"/"+_name);
    file_stored << saveProject;
    file_stored.close();
    saveProject.clear();

    cout<<"Written "<<_name<<".xml"<<" to "<<_dir<<std::endl;
}
