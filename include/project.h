#ifndef PROJECT_H
#define PROJECT_H

#include <cstdlib>
#include <string>

class Project
{
public:
    Project();
    Project(std::string json_file);

    void save();
    void edit();
    void load(std::string json_file);

    std::string getShaderSource(std::string _path);
    std::string getShaderPath(std::string _path);

private:
    std::string m_name;

    std::string m_fragmentPath;

    std::string m_vertexPath;

    std::string m_jsonPath;

};

#endif // PROJECT_H
