#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <fstream>
int main()
{
	//IMPORT FILE if it doesnt work. Delete.
	std::ifstream m_fileIn;
	m_fileIn.open("parsingInput.txt");
	if(!m_fileIn.is_open())    ///If it can be opened
	{
		std::cerr<<"File Does Not Exist (make sure that the file is readable) \n";
		exit(EXIT_FAILURE);
	}
	//Separating EXTERNAL String individually

	std::string a; //manually create for testing
	std::string b;
	std::string c;
	m_fileIn>>a;
	m_fileIn>>b;
	m_fileIn>>c;
    a.c_str(); //works manually
    b.c_str();
	std::cout<<a<<std::endl;
	std::cout<<b<<std::endl;
	

    m_fileIn.close();

    
    
    
    

    
}
