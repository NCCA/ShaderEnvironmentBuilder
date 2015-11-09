#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <fstream>
int main()
{
	
	std::ofstream m_fileOut;
	m_fileOut.open("ParsingInput.txt");
	if(!m_fileOut.is_open())    ///If it can be opened
	{
		std::cerr<<"couldn't' open file\n";
		exit(EXIT_FAILURE);
	}
	

	std::vector<std::string> m_import;
	
	//m_fileOut<<



	//http://rosettacode.org/wiki/Tokenize_a_string    <- Adjusted this link Starts
    std::string m_file = "I musT sepArate This intO sectionS";
    std::string m_file2 = "DIVIDE intO sectionS";
    std::vector<std::string> m_vectorList;
    std::istringstream divide(m_file2);
    std::istringstream divide1(m_file);
    for(std::string m_token; getline(divide1, m_token, ' '); ) //editted spacing, what gets replaced? ' '
        m_vectorList.push_back(m_token);
    std::copy(m_vectorList.begin(), m_vectorList.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
	//http://rosettacode.org/wiki/Tokenize_a_string    <- Adjusted this link ends

    //printf(s);
    m_file.c_str();
    
    
    
    
    
    
    
    
    m_fileOut.close();
    
}
