#ifndef PROJECT_H
#define PROJECT_H

#include "Io_xml.h"

#include <QString>
#include <QMessageBox>
#include <cstdlib>
#include <string>

#include "Json.h"

struct projectData
{
  std::string m_projectName;
  std::string m_projectDir;
};

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
  void save(QString vertSource, QString fragSource);
  
  //method to save the current project as another project
  void saveAs(QString vertSource, QString fragSource);
  
  //method to load
  void load(string _loadedFileDirectory);
  
  //method to export the current project to accessible glsl files
  bool exportProject(std::string _targetDir, QString vertSource, QString fragSource);
  
  //get method to return the project name
  inline std::string getName(){return m_data.m_projectName;}
  
  //get method to return the project dir
  inline std::string getDir(){return m_data.m_projectDir;}

  int confirmOverwrite(QString _filePath);

private:

  //project name
  projectData m_data;

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
