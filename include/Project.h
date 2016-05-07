//------------------------------------------------------------------------------------------------------------------------
/// @file Project
/// @brief Class for managing saving and loading of projects
/// @author Alexander La Tourelle
/// @author Ellie Ansell
/// @author Jonathan Flynn
/// @version 1.0
/// @date 07/05/16
//------------------------------------------------------------------------------------------------------------------------
#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QMessageBox>
#include <cstdlib>
#include <string>

#include "Io_xml.h"

//------------------------------------------------------------------------------------------------------------------------
/// @class Project
/// @brief stores the name and directory of the current project as well as
/// @brief providing methods for saving and loading projects to xml files and
/// @brief exporting the porject's shaders to glsl files.
//------------------------------------------------------------------------------------------------------------------------
class Project
{

public:

  //----------------------------------------------------------------------------
  /// @brief default constructor for project class
  //----------------------------------------------------------------------------
  Project();
  //----------------------------------------------------------------------------
  /// @brief default destructor for the project class
  //----------------------------------------------------------------------------
  ~Project();
  //----------------------------------------------------------------------------
  /// @brief method to set the data for the project
  /// @param _name the name of the project
  /// @param _dir the directory of the project
  /// @param _saveState flag for whether the project has previsouly been saved
  //----------------------------------------------------------------------------
  inline void set(std::string _name, std::string _dir, bool _saveState)
  {
    m_projectName = _name;
    m_projectDir = _dir;
    m_saved = _saveState;
  }
  //----------------------------------------------------------------------------
  /// @brief method for saving the current project
  /// @param _vertSource the vertex shader source code to save
  /// @param _fragSource the fragment shader source code to save
  //----------------------------------------------------------------------------
  void save(QString _vertSource, QString _fragSource);
  //----------------------------------------------------------------------------
  /// @brief method for saving the current project as a new project
  /// @param _vertSource the vertex shader source code to save
  /// @param _fragSource the fragment shader source code to save
  //----------------------------------------------------------------------------
  void saveAs(QString _vertSource, QString _fragSource);
  //----------------------------------------------------------------------------
  /// @brief method to load in a project from an xml file
  /// @param _loadedFileDirectory the directory of the loaded file
  /// @param o_vertSource output vertex shader source code from loaded project
  /// @param o_fragSource output fragment shader source code from loaded project
  //----------------------------------------------------------------------------
  void load(std::string _loadedFileDirectory, QString &o_vertSource, QString &o_fragSource);
  //----------------------------------------------------------------------------
  /// @brief method for exporting the vertex and fragment shaders
  /// @brief from the current project for GLSL files
  /// @param _targetDir the directory to save the GLSL files in
  /// @param _vertSource the vertex shader source code to save
  /// @param _fragSource the fragment shader source code to save
  //----------------------------------------------------------------------------
  bool exportProject(std::string _targetDir, QString _vertSource, QString _fragSource);
  //----------------------------------------------------------------------------
  /// @brief method to return the name of the current project
  //----------------------------------------------------------------------------
  inline std::string getName(){return m_projectName;}
  //----------------------------------------------------------------------------
  /// @brief method to return the directory of the current project
  //----------------------------------------------------------------------------
  inline std::string getDir(){return m_projectDir;}
  //----------------------------------------------------------------------------
  /// @brief method to confirm overwriting exported files
  /// _filePath the path of the file to overwrite
  //----------------------------------------------------------------------------
  int confirmOverwrite(QString _filePath);

private:
  //----------------------------------------------------------------------------
  /// @brief the name of the current project
  //----------------------------------------------------------------------------
  std::string m_projectName;
  //----------------------------------------------------------------------------
  /// @brief the directory of the current project
  //----------------------------------------------------------------------------
  std::string m_projectDir;
  //----------------------------------------------------------------------------
  /// @brief flag storing whether the current project has been previously saved
  //----------------------------------------------------------------------------
  bool m_saved;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to save and load project information from xml file
  //----------------------------------------------------------------------------------------------------------------------
  IO_XML *m_xml;

};

#endif // PROJECT_H
