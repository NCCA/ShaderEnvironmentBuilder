#include "Io_xml.h"

using namespace rapidxml;
using namespace std;
IO_XML::IO_XML()
{
}
// ----------------------------------------------------------------------------------------------------------------------
// (Unused) Organises name, type and value for shader data into an XML file. E.g. Name: light.diffuse, Type: mat4, value: 1.
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
// Reads the .xml project file vertex and fragment data, then returns this to project.cpp.
// Returns an error if an incorrect XML file is opened.
void IO_XML::readProjectXML(std::string& _fileName, std::string& _fileDirectory, std::string _loadedFileDirectory, std::string& _vertSource, std::string& _fragSource)
{
    xml_document<> doc;
    ifstream file(_loadedFileDirectory);
    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>( ));
    buffer.push_back('\0');
    doc.parse<0>(&buffer[0]);

    xml_node<> *firstNode = doc.first_node();
    if (!(doc.first_node("Shader_Data")))
    {
        std::cout<< "Error: Incorrect XML file. Open a previously saved project file and try again."<<std::endl;
    }
    else
    {
        xml_node<> *current_node = doc.first_node("Shader_Data");
        xml_node<> *vertex_node = current_node->first_node("Vertex");
        xml_node<> *fragment_node = current_node->first_node("Fragment");
        std::cout<<"Opened project '"<<current_node->first_attribute("Name")->value()<<"' at "<<current_node->first_attribute("Dir")->value()<<" successfully."<<std::endl;

        _vertSource = vertex_node->first_attribute("VtxData")->value();
        _fragSource = fragment_node->first_attribute("FragData")->value();
        _fileName = current_node->first_attribute("Name")->value();
        _fileDirectory = current_node->first_attribute("Dir")->value();
    }
    return;
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
    std::ofstream file_stored(_dir+"/"+_name+".xml");
    file_stored << saveProject;
    file_stored.close();
    saveProject.clear();

    cout<<"Written "<<_name<<".xml"<<" to "<<_dir<<std::endl;
}
