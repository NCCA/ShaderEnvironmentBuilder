#ifndef JSON
#define JSON

#include <cstdlib>
#include <string>

class Json
{
public:
    Json();

private:

    std::string buildJson();
    void saveToFile(std::string _jsonString);
    void replaceWord(std::string _oldWord, std::string _newWord);
};

//int main()
//{
//    buildJson();
//    replaceWord("Shader", "CHANGED");
//}
#endif // JSON
