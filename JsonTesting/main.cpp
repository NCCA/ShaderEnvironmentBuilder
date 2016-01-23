#include <json.h>
#include <io_xml.h>
#include <iostream>
#include <fstream>
#include <string.h>

int main()
{
    //Json *next = new Json();
    Json *jsonInstance = new Json();
    jsonInstance->buildJson();
    jsonInstance->replaceWord("Shader", "CHANGED");

    IO_XML *XMLInstance = new IO_XML();
    XMLInstance->readXML();
    //XMLInstance->writeXML();

}
