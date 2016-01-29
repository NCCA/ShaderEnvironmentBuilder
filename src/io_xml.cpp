
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

        cout<<&buffer[0]<<endl; /*test the buffer */

        doc.parse<0>(&buffer[0]);

        cout << "Name of my first node is: " << doc.first_node()->name() << "\n";  /*test the xml_document */ //returns root

        xml_node<> *current_node = doc.first_node("root");
        std::cout<<"current_node value 1:"<<current_node->first_attribute("name")->value()<<std::endl;
        // switching to a different node
        current_node = current_node->first_node("dataSets")->first_node("a");
        std::cout<<"current node value:"<<current_node->first_attribute("name")->value()<<std::endl;


        //traverse through node attributes until it finds m_type
        for (current_node->first_node("dataSets"); current_node; current_node = current_node->next_sibling())
        {
            if (current_node->first_attribute("name")->value()==_type)
            {
                std::cout<<"Data for "<<_type<<": ";
                std::cout<<"Name: "<<current_node->first_attribute("name")->value()<<"\tValue: "<< current_node->first_attribute("value")->value()<<"\tType: "<<current_node->first_attribute("type")->value()<<std::endl;
            break;
            };
        }





        //std::cout<<"type:"<<m_type<<std::endl;
        //std::cout<<"Name: "<<current_node->first_attribute("name")->value()<<"          Value: "<< current_node->first_attribute("value")->value()<<"          Type: "<<current_node->first_attribute("type")->value()<<std::endl;
         //search and print




//        while (current_node->first_attribute("name")->value()!=m_type)
//        {

//            std::cout<<"Data for "<<_type<<"..."<<std::endl;
//            if (current_node->first_attribute("name")->value()==m_type)
//            {
//                std::cout<<"------->Name: "<<current_node->first_attribute("name")->value()<<"          Value: "<< current_node->first_attribute("value")->value()<<"          Type: "<<current_node->first_attribute("type")->value()<<std::endl;
//            };
//            current_node = current_node->next_sibling();
//        }

















//        string rootnode_type = node->first_attribute("name")->value();

//        std::cout<<"Root node name: "<<rootnode_type;
//        for (xml_attribute<> *attr = node->first_attribute();
//             attr; attr = attr->next_attribute())
//        {
//            cout << "/nNode foobar has attribute " << attr->name() << " ";
//            cout << "with value " << attr->value() << "\n";
//        }
//        string nextNode = node->next_sibling("dataSets")->value();
//        std::cout<<"sibling:"<<nextNode;
////        cout << "Finding datasets:"<<attr->name()<<"<-value"<<std::endl;
////        cout << "Finding datasets2:"<<node->next_sibling()<<"<-value"<<std::endl;
////        cout << "Finding datasets3:"<<node->name()<<"<-value"<<std::endl;
//        root_node = doc.first_node("root");
////        // Iterate over the brewerys

//        for (xml_node<> * data_node = root_node->first_node("dataSets"); data_node; data_node = data_node->next_sibling())
//        {
//            printf("\nName: %s \nLocation: %s \nType: %s",
//                data_node->first_attribute("name")->value(),
//                data_node->first_attribute("b")->value(),
//                data_node->first_attribute("c")->value());
////            for(xml_node<> * ExtraInfo = data_node->first_node("ExtraInfo"); ExtraInfo; ExtraInfo = ExtraInfo->next_sibling())
////            {
////                printf("\nExtra info:%s",
////                    ExtraInfo->first_attribute("blah")->value());
////            }
////            cout<<"\n"<<std::endl;
//        }

////        xml_node<> *node;
////        for (xml_node<> *child = node->first_node(); child; child = child->next_sibling())
////        {
////            printf("Node: %s",
////                   node->first_node()->value());
////        }

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
