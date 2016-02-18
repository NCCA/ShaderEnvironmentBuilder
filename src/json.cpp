#include <json.h>
// Only need boost for creating directories
#include <boost/filesystem.hpp>

using namespace rapidxml;
using namespace rapidjson;
using namespace std;
using json = nlohmann::json;

Json::Json()
{
  // Ensure the location of files for temp output. REMOVE IN FINAL VERSION
  boost::filesystem::path dir("./");
  boost::filesystem::create_directories(dir);
}

// ----------------------------------------------------------------------------------------------------------------------
// Writes the output Json to a file.
void Json::writeFile(std::string _fileName, std::string _stringData)
{              
    ofstream fileName("./tempFiles/"+_fileName);   // ofstream jsonFile("./tempFiles/shader.json");
    if (fileName.is_open())
        fileName << _stringData << std::endl;
    fileName.close();
}

void Json::readFile(std::string _fileName)
{
    ifstream jsonFile("./tempFiles/"+_fileName+".json");
    if(!jsonFile)
    {
        std::cout<<"Unable to open file."<<std::endl;
        exit(1);
    }
    std::cout << jsonFile;
}

// ----------------------------------------------------------------------------------------------------------------------
// (may be redundant) Reads through the Json string, finds a word and replaces with a new word.
void Json::replaceWord(std::string _oldWord, std::string _newWord)
{
    ifstream jsonFile("./tempFiles/jsonString.json");
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
    ofstream jsonFileNew("./tempFiles/jsonString.json");
    std::cout<<"\nNew file: \n"<<lineRead << std::endl;
    if (jsonFileNew.is_open())
        jsonFileNew << lineRead << std::endl;
    jsonFileNew.close();
}

// ----------------------------------------------------------------------------------------------------------------------
// This function builds the Json string by grabbing data from the XML ShaderData file.
void Json::buildJson()
{
    auto shaderProgramJson = R"(
    {
      "ShaderProgram": {
        "name": "Phong",
        "debug" : true,
      "Shaders"  : [
        {
          "type": "Vertex",
          "name": "PhongVertex",
          "path" : ["shaders/version.glsl",
                    "shaders/common.glsl",
                    "shaders/PhongVertex.glsl"]

        },
        {
          "type": "Fragment",
          "name": "PhongFragment",
          "path" : ["shaders/version.glsl",
                    "shaders/common.glsl",
                    "shaders/noise3D2.glsl",
                    "shaders/PhongFragment.glsl"]
        }
      ]
     }
    }
    )"_json;
    writeFile("jsonString.json", shaderProgramJson.dump(1));
}

void Json::addShaderData(string _name, string _type, double _value)
{
    json shaderDataJson;

    shaderDataJson[_name]={{"Name", _name}, {"Type", _value}, {"Value", _value}};
    writeFile("shaderData.json", shaderDataJson.dump(1));
}

Json::~Json()
{}





































//void Json::newBuildJson()
//{
//    auto shaderProgramJson = R"(
//    {
//      "ShaderProgram": {
//        "name": "Phong",
//        "debug" : true,
//      "Shaders"  : [
//        {
//          "type": "Vertex",
//          "name": "PhongVertex",
//          "path" : ["shaders/version.glsl",
//                    "shaders/common.glsl",
//                    "shaders/PhongVertex.glsl"]

//        },
//        {
//          "type": "Fragment",
//          "name": "PhongFragment",
//          "path" : ["shaders/version.glsl",
//                    "shaders/common.glsl",
//                    "shaders/noise3D2.glsl",
//                    "shaders/PhongFragment.glsl"]
//        }

//      ]
//     }
//    }
//        )"_json;

//    saveToFile(shaderProgramJson.dump(2));
//}



























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



///writing to json OLD:
// Building Json file
//    StringBuffer s;
//    Writer<StringBuffer> writer(s);
//    writer.StartObject();
//    writer.Key("Shader Program");
//        writer.StartObject();
//        writer.Key("noise3D");
//        writer.String(ShaderProgramName);
//        writer.Key("debug");
//        writer.Bool(true);
//        writer.Key("Shaders");
//        writer.StartArray();
//            writer.StartObject();
//            writer.Key("type");
//            writer.String("Vertex");
//            writer.Key(vertexShaderName);
//            writer.String("PhongVertex");
//            writer.Key("path");
//            writer.StartArray();
//                writer.String("shaders/version.glsl");
//                writer.String("shaders/common.glsl");
//                writer.String(vertexShaderGlsl);
//                writer.EndArray();
//                writer.EndObject();
//            writer.StartObject();
//                writer.Key("type");
//                writer.String("Fragment");
//                writer.Key("name");
//                writer.String(fragmentShaderName);
//                writer.Key("path");
//                writer.StartArray();
//                    writer.String("shaders/version.glsl");
//                    writer.String("shaders/common.glsl");
//                    writer.String("shaders/noise3D.glsl");
//                    writer.String(fragmentShaderGLSL);
//                    writer.EndArray();
//                writer.EndObject();
//            writer.EndArray();
//        writer.EndObject();
//    writer.EndObject();

//    saveToFile(s.GetString());
//    std::cout<<s.GetString()<<std::endl;

//    return s.GetString();
