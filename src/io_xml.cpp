
#include "io_xml.h"
#include <fstream>
#include <ostream>
#include <vector>
#include <stdio.h>
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

//        ifstream file("/home/i7685565/0Features-0BugsCVA3/tempFiles/readFrom.xml");
//        //vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
//        //std::string input_xml = file;
//        std::string input_xml((std::istreambuf_iterator<char>(file)),
//                         std::istreambuf_iterator<char>());
//        std::vector<char> xml_copy(input_xml.begin(), input_xml.end());
//        xml_copy.push_back('\0');


//        //buffer.push_back('\0');
//        ////cout<<&buffer[0]<<endl;
//        xml_document<> doc;
//        //doc.parse<0>(&buffer[0]);

//        doc.parse<rapidxml::parse_no_data_nodes>(&xml_copy[0]); // Notice the flag here
//        rapidxml::xml_node<>* root_node = doc.first_node("root");


//        std::string s = "test";
//        const char * text = doc.allocate_string(s.c_str(), strlen(s.c_str()));

//        root_node->first_node("data")->value(text);

//        std::string data;
//        print(std::back_inserter(data), doc);

//        std::ofstream file;
//        file.open(filename.c_str());
//        file << data;
//        file.close();




//        xml_node<> *current_node = doc.first_node("root");
//        current_node = current_node->first_node("dataSets");

//        xml_node<> *new_node;
//        new_node = doc.allocate_node(node_element, "d", "New node");
//        doc.append_node(new_node);
//        xml_attribute<> *attr = doc.allocate_attribute("new atttribute", "value here");
//        current_node->append_attribute(attr);

//        cout<<&buffer[0]<<endl;


//        std::string data = std::string(xml_copy.begin(), xml_copy.end());

//        std::ofstream openFile;
//        openFile.open(filename.c_str());
//        openFile << data;
//        openFile.close();

      //  std::ofstream file;
//        buffer.push_back('\0');

//        rapidxml::xml_document<> doc;

//        doc.parse<rapidxml::parse_no_data_nodes>(&buffer[0]); // Notice the flag here
//        rapidxml::xml_node<>* root_node = doc.first_node("Data");

//        root_node->first_node("Model")->value(std::string("Edited!").c_str());

//        //std::string data = std::string(buffer.begin(), buffer.end());

//        std::ofstream file;
//        file.open("/home/i7685565/Desktop/XMLexample.xml");
//        file << std::string("AOIJOSIJIJIJIJIJI").c_str();
//        file.close();
}
