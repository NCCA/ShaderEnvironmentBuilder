#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <fstream>
using namespace rapidjson;
using namespace std;

void saveToFile(std::string _jsonString)
{
    ofstream jsonFile("/home/i7685565/0Features-0BugsCVA3/JsonTesting/jsonString.json");

    if (jsonFile.is_open())
        jsonFile << _jsonString;
        std::cout<<"Written to file!\n"<<std::endl;
    jsonFile.close();
}




//std::string insertVertexShader()
//{

//    std::string phongVertex="shaders/PhongVertex.glsl";
//    return phongVertex;
//}

//std::string funct()
//{
//    StringBuffer s;
//    Writer<StringBuffer> writer(s);
//    writer.StartObject();
//    writer.Key("TEST");
//    writer.String("JERONIMOOOOE!");
//    writer.EndObject();
//    saveToFile(s.GetString());
//    std::cout<<s.GetString();
//    return s.GetString();
//}

std::string buildJson()
{

    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();
    writer.Key("ShaderProgram");
        writer.StartObject();
        writer.Key("name");
        writer.String("Phong");
        writer.Key("debug");
        writer.Bool(true);
        writer.Key("Shaders");  //{"ShaderProgram":{"name":"Phong","debug":true,"Shaders":true,"f":false,"n":null,"i":123,"pi":3.1416,"a":[0,1,2,3]}
        writer.StartArray();
            writer.StartObject();
            writer.Key("type");
            writer.String("Vertex");
            writer.Key("name");
            writer.String("PhongVertex");
            writer.Key("path");
            writer.StartArray();
                writer.String("shaders/version.glsl");
                writer.String("shaders/common.glsl");
                //writer.String(insertVertexShader());
                writer.String("shaders/PhongVertex.glsl");
                writer.EndArray();
                writer.EndObject();
            writer.StartObject();
                writer.Key("type");
                writer.String("Fragment");
                writer.Key("name");
                writer.String("PhongFragment");
                writer.Key("path");
                writer.StartArray();
                    writer.String("shaders/version.glsl");
                    writer.String("shaders/common.glsl");
                    writer.String("shaders/noise3D.glsl");
                    writer.String("shaders/PhongFragment.glsl");
                    writer.EndArray();
                writer.EndObject();
            writer.EndArray();
        writer.EndObject();
    writer.EndObject();

//    funct();
//    writer.StartObject();
//    std::string add;
//    std::string *stringptr1;

//    //stringptr1 = &str1;
//    writer.EndObject();
    saveToFile(s.GetString());
    //grabShaderType();
    return s.GetString();
}

int main()
{
    std::cout<<buildJson();
}



