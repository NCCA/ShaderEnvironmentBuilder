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

void IO_XML::readXML()
{

    cout<<"\nParsing file..."<<endl;
        xml_document<> doc;
        xml_node<> * root_node;
        // Read the xml file into a vector
        ifstream theFile("/home/i7685565/Desktop/lightToMaya.xml");
        vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
        buffer.push_back('\0');
        // Parse the buffer using the xml file parsing library into doc
        doc.parse<0>(&buffer[0]);
        // Find our root node
        root_node = doc.first_node("Data");
        // Iterate over the brewerys
        for (xml_node<> * data_node = root_node->first_node("Model"); data_node; data_node = data_node->next_sibling())
        {
            printf("\nName: %s \nLocation: %s \nType: %s",
                data_node->first_attribute("name")->value(),
                data_node->first_attribute("location")->value(),
                data_node->first_attribute("type")->value());
            for(xml_node<> * ExtraInfo = data_node->first_node("ExtraInfo"); ExtraInfo; ExtraInfo = ExtraInfo->next_sibling())
            {
                printf("\nExtra info:%s",
                    ExtraInfo->first_attribute("blah")->value());
            }
            cout<<"\n"<<std::endl;
        }

}

void IO_XML::writeXML()
{

//    cout<<"\nWriting to XML file..."<<endl;
//        ifstream theFile("/home/i7685565/Desktop/XMLexample.xml");
//        vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
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

