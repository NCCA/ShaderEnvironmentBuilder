#ifndef PROJECT_H
#define PROJECT_H

#include <cstdlib>
#include <string>
#include "json.h"
#include "io_xml.h"
#include <QString>

class Project
{
public:
  
  //default constructor creating "untitled" project
  Project();

  //destructor
  ~Project();
  
  //method to edit the project information
  void set(std::string _name, std::string _dir);
  
  //method to save the current project  
  void save();
  
  //method to save the current project as another project
  void saveAs(std::string _name, std::string _dir);
  
  //method to load a project from json
  void load(std::string _pathToXML);
  
  //method to export the current project to accessible glsl files
  bool exportProject(std::string _targetDir, QString vertSource, QString fragSource);
  
  //get method to return the project name
  inline std::string getName(){return m_name;}
  
  //get method to return the project dir
  inline std::string getDir(){return m_dir;}



private:
  //project name
  std::string m_name;
  
  //project directory
  std::string m_dir;
  
  //flag to say if the current project has alerady been saved
  bool m_saved;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to save shaders to a json file
  //----------------------------------------------------------------------------------------------------------------------
  Json *m_Json;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to save and load project information from xml file
  //----------------------------------------------------------------------------------------------------------------------
  IO_XML *m_xml;
};

#endif // PROJECT_H
