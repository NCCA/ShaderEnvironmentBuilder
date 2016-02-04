#include <json.h>
// Only need boost for creating directories
#include <boost/filesystem.hpp>

using namespace rapidxml;
using namespace rapidjson;
using namespace std;

Json::Json()
{
  // Ensure the location of files for temp output. REMOVE IN FINAL VERSION
  boost::filesystem::path dir("./tempFiles/json");
  boost::filesystem::create_directories(dir);
}

// ----------------------------------------------------------------------------------------------------------------------
// Writes the output Json to a file.
void Json::saveToFile(std::string _jsonString)
{
    ofstream jsonFile("./tempFiles/json/jsonString.json");

    if (jsonFile.is_open())
        jsonFile << _jsonString << std::endl;
        std::cout<<"Written to file: "<<std::endl;
    jsonFile.close();
}

// ----------------------------------------------------------------------------------------------------------------------
// (may be redundant) Reads through the Json string, finds a word and replaces with a new word.
void Json::replaceWord(std::string _oldWord, std::string _newWord)
{
    ifstream jsonFile("./tempFiles/json/jsonString.json");
    if(!jsonFile)
    {
        std::cout<<"Unable to open file."<<std::endl;
        exit(1);
    }
    std::string lineRead;
    size_t pos;
    std::string foundWord;
    while (jsonFile.good())
    {
        getline(jsonFile, lineRead);
        pos=lineRead.find(_oldWord);
        if(pos!=string::npos)              //reads through the line
        {
            lineRead.replace(pos, _oldWord.length(), _newWord);
            break;
        }
    }
    jsonFile.close();
    ofstream jsonFileNew("./tempFiles/json/jsonString.json");
    std::cout<<"\nNew file: \n"<<lineRead << std::endl;
    if (jsonFileNew.is_open())
        jsonFileNew << lineRead << std::endl;
    jsonFileNew.close();
}

// ----------------------------------------------------------------------------------------------------------------------
// This function builds the Json string by grabbing data from the XML ShaderData file.
std::string Json::buildJson()
{
//  Reading shaderData file.

    xml_document<> doc;
    ifstream file("/home/i7685565/0Features-0BugsCVA3/tempFiles/shaderData.xml");
    vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>( ));
    buffer.push_back('\0');
    //cout<<&buffer[0]<<endl;  //prints xml buffer
    doc.parse<0>(&buffer[0]);

    xml_node<> *current_node = doc.first_node("ShaderProgram");
    xml_node<> *vertex_node = doc.first_node("ShaderProgram")->first_node("FragmentData");
    xml_node<> *fragment_node = doc.first_node("ShaderProgram")->first_node("FragmentData");

    const char* ShaderProgramName = current_node->first_attribute("name")->value();

    const char* vertexShaderName = vertex_node->first_attribute("name")->value();
    const char* vertexShaderGlsl = vertex_node->first_attribute("vertexPath")->value();

    const char* fragmentShaderName = fragment_node->first_attribute("name")->value();
    const char* fragmentShaderGLSL = fragment_node->first_attribute("customPath")->value();    //these chars can be edited later.


// Building Json file
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();
    writer.Key("Shader Program");
        writer.StartObject();
        writer.Key("noise3D");
        writer.String(ShaderProgramName);
        writer.Key("debug");
        writer.Bool(true);
        writer.Key("Shaders");
        writer.StartArray();
            writer.StartObject();
            writer.Key("type");
            writer.String("Vertex");
            writer.Key(vertexShaderName);
            writer.String("PhongVertex");
            writer.Key("path");
            writer.StartArray();
                writer.String("shaders/version.glsl");
                writer.String("shaders/common.glsl");
                writer.String(vertexShaderGlsl);
                writer.EndArray();
                writer.EndObject();
            writer.StartObject();
                writer.Key("type");
                writer.String("Fragment");
                writer.Key("name");
                writer.String(fragmentShaderName);
                writer.Key("path");
                writer.StartArray();
                    writer.String("shaders/version.glsl");
                    writer.String("shaders/common.glsl");
                    writer.String("shaders/noise3D.glsl");
                    writer.String(fragmentShaderGLSL);
                    writer.EndArray();
                writer.EndObject();
            writer.EndArray();
        writer.EndObject();
    writer.EndObject();

    saveToFile(s.GetString());
    std::cout<<s.GetString()<<std::endl;

    return s.GetString();
}

Json::~Json()
{

}







///To be deleted
//std::string Json::shaderType(int _shaderNumber)
//{
//    std::string shaderType;

//    if (_shaderNumber==1)
//    {
//        shaderType = "noise3D";
//    };
//    if (_shaderNumber==2)
//    {
//        shaderType = "cloud3D";
//    };

//    return shaderType;
//}
//    NOTE: This is useful to input a string directly into the writer. Input parameter int_shaderNumber to use.
//    std::string shaderTypeStr = shaderType(_shaderNumber);

//    std::cout<<"\nshader type: "<< shaderType(1)<<std::endl;
//    char *cstr = new char[shaderTypeStr.length() +1];
//    strcpy(cstr, shaderTypeStr.c_str());
