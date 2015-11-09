#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <fstream>
int main()
{
	
	std::ifstream m_fileIn;
	m_fileIn.open("parsingInput.txt");
	if(!m_fileIn.is_open())    ///If it can be opened
	{
		std::cerr<<"File Does Not Exist (make sure that the file is readable) \n";
		exit(EXIT_FAILURE);
	}
	
    std::string m_importString = "I musT sepArate This intO sectionS";
    std::vector<std::string> m_import;
	std::istringstream divideIt(fileIn);

	std::string a; //manually create for testing
	std::string b;
	std::string c;
	m_fileIn>>a;
	m_fileIn>>b;
	m_fileIn>>c;
    a.c_str(); //works manually
    b.c_str();
    m_importString.c_str();
	std::cout<<a<<std::endl;
	std::cout<<b<<std::endl;

	for(std::string m_token; getline(divideIt, m_token, ' '); )
	{
		m_fileIn>>m_import.push_back(m_token); //doesnt work in a for loop... 
	}
	std::copy(m_import.begin(), m_import.end(), std::ostream_iterator<std::string>(std::cout, "."));
    //m_fileIn.c_str();

    m_fileIn.close();
    /*
    
	//http://rosettacode.org/wiki/Tokenize_a_string    <- Adjusted this link Starts
    std::string m_file = "I musT sepArate This intO sectionS";
    std::string m_file2 = "DIVIDE intO sectionS";
    std::vector<std::string> m_vectorList;
    std::istringstream divide(m_file2);
    std::istringstream divide1(m_file);
    for(std::string m_token; getline(divide1, m_token, '\n'); ) //editted spacing, what gets replaced? ' '
		{m_vectorList.push_back(m_token);}
    std::copy(m_vectorList.begin(), m_vectorList.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
	//http://rosettacode.org/wiki/Tokenize_a_string    <- Adjusted this link ends

    //printf(s);
    m_file.c_str();
    
*/
    
    
    
    
    
    

    
}
