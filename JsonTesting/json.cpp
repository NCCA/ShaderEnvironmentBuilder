#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "string.h"
#include "stdlib.h"
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
/*
void readFromJson()
{
    std::string m_hello;
    ifstream jsonFile("/home/i7685565/0Features-0BugsCVA3/JsonTesting/jsonString.json");
    if (jsonFile.is_open())
        std::cout<<"\nReading from file..."<<std::endl;
        std::string line;
        /*
        while (getline(jsonFile, line))
        {
            if (line.find(":") !=string::npos)
            {
                std::cout<<line[20]<<std::endl;
            }
        }
        *//*


        char word[20];
        int word_size = 0;
        int array_size = 1024;
        int position = 0;
        char * array = new char[array_size];

        while(!jsonFile.eof() && position < array_size)
        {
            jsonFile.get(array[position]);
            position++;
        }
        for (int i=0; array[i] != '\0'; i++)
        {
            for(int j = 0; word[j] != '\0' && j < 20 ; j++)
            {
                if(array[i] != word[j])
                {
                    break;
                }
                else
                {
                    i++;
                    if(word[j+1] == '\0')
                    {
                        std::cout<<"word found at file position: "<<(i-word_size)<<std::endl;

                    }
                }
            }
        }

        array[position-1]= '\0';
        //std::cout<< m_hello;
    jsonFile.close();
}
*/

void readFromJson()
{
    std::string searchWord = "Program";
    std::string line;
    std::string STRING;
    std::string nextWord;
    //ifstream jsonFile
    ifstream jsonFile("/home/i7685565/0Features-0BugsCVA3/JsonTesting/jsonString.json");
    if (jsonFile.is_open())
        std::cout<<"\nReading from file...\n"<<std::endl;
    if(!jsonFile)
    {
        std::cout<<"unable to open file"<<std::endl;
        exit(1);
    }

    char my_character;
    size_t pos;
    while (jsonFile.good())
    {
        getline(jsonFile, line);
        pos=line.find(searchWord);
        std::cout<<my_character;
        if(pos!=string::npos)
        {
            std::cout<<"Word starts at: "<<pos<<"   Line: "<<getline(jsonFile, line);
            std::cout<<"\nThe next word is    "<<line<<"    end\n";
            //jsonFile>>output;
            break;
        }
    }


    int number_of_lines = 1;
    while (!jsonFile.eof())
    {

        jsonFile.get(my_character);
        if (my_character=='\n')
        {
            ++number_of_lines;  
        }
    }

    char ch;
    char str[256];
    for (int i=0; i<3;i++)
    {
        jsonFile.get(ch);
        std::cout<<ch;
    }
    jsonFile.get(str, 255);
    std::cout<<str;
    std::string stringy = str;
    std::cout<<stringy;

}







void readAndWrite()
{
    ofstream textFile("/home/i7685565/0Features-0BugsCVA3/JsonTesting/textFile.txt");

    if (textFile.is_open())
        textFile << "Hello!";
        std::cout<<"Written to file!\n"<<std::endl;
    textFile.close();
}










std::string shaderType(int _shaderNumber)
{
    std::string shaderType;

    if (_shaderNumber==1)
    {
        shaderType = "noise3D";
    };
    if (_shaderNumber==2)
    {
        shaderType = "cloud3D";
    };

    return shaderType;
}


std::string buildJson(int _shaderNumber)
{

    std::string shaderTypeStr = shaderType(_shaderNumber);    //---------------------------------------

    std::cout<<"\nshader type: "<< shaderType(1)<<std::endl;
    char *cstr = new char[shaderTypeStr.length() +1];
    strcpy(cstr, shaderTypeStr.c_str());

    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();
    writer.Key("ShaderProgram");
        writer.StartObject();
        writer.Key(cstr);                     //---------------------------------------
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

    saveToFile(s.GetString());
    std::cout<<s.GetString()<<std::endl;

    return s.GetString();
}

int main()
{
    buildJson(1);
    readFromJson();

    readAndWrite();
}



