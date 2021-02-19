#include <Json.h>

//------------------------------------------------------------------------------
// Writes an input string into to a file
//------------------------------------------------------------------------------
void Json::writeFile(std::string _fileName, std::string _stringData)
{              
    std::ofstream fileName("./tempFiles/"+_fileName);   // ofstream jsonFile("./tempFiles/shader.json");
    if (fileName.is_open())
        fileName << _stringData << std::endl;
    fileName.close();
}

//------------------------------------------------------------------------------
// Reads an input file name and prints the file contents.
//------------------------------------------------------------------------------
void Json::readFile(std::string _fileName)
{
    std::ifstream jsonFile("./tempFiles/"+_fileName+".json");
    if(!jsonFile)
    {
        std::cout<<"Unable to open file."<<std::endl;
        exit(1);
    }
    std::cout << "File contents \n " << jsonFile;
}

//------------------------------------------------------------------------------
// Builds the shader in a default json format.
//------------------------------------------------------------------------------
void Json::defaultShader()
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

//------------------------------------------------------------------------------
// Appends shader data (name, type, value).
//------------------------------------------------------------------------------
void Json::addShaderData(std::string _name, std::string _type, double _value)
{
    nlohmann::json shaderDataJson;

    shaderDataJson[_name]={{"Name", _name}, {"Type", _value}, {"Value", _value}};
    writeFile("shaderData.json", shaderDataJson.dump(1));
}

//------------------------------------------------------------------------------
// Reads through the Json string, finds a word and replaces with a new word.
//------------------------------------------------------------------------------
void Json::replaceWord(std::string _oldWord, std::string _newWord)
{
    std::ifstream jsonFile("./tempFiles/jsonString.json");
    std::string lineRead;
    size_t pos;
    std::string foundWord;
    while (jsonFile.good())
    {
        getline(jsonFile, lineRead);
        pos=lineRead.find(_oldWord);
        if(pos!=std::string::npos)              //reads through the line
        {
            lineRead.replace(pos, _oldWord.length(), _newWord);
            break;
        }
    }
    jsonFile.close();
    std::ofstream jsonFileNew("./tempFiles/jsonString.json");
    std::cout<<"\nNew file: \n"<<lineRead << std::endl;
    if (jsonFileNew.is_open())
        jsonFileNew << lineRead << std::endl;
    jsonFileNew.close();
}


Json::~Json()
{}
