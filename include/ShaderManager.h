//------------------------------------------------------------------------------------------------------------------------
/// @file ShaderManager
/// @brief Class for managing and updating data for GLSL shaders in the IDE
/// @author Alexander La Tourelle
/// @author Anand Hotwani
/// @author Jonathan Flynn
/// @version 1.0
/// @date 05/05/16
//------------------------------------------------------------------------------------------------------------------------

#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <string>
#include <ngl/ShaderLib.h>
#include <QString>
#include <ngl/Camera.h>

//------------------------------------------------------------------------------------------------------------------------
/// @brief structure containing currently active shader data
//------------------------------------------------------------------------------------------------------------------------
struct shaderProgramData
{
  std::string m_name;
  std::string m_vert;
  std::string m_frag;
};

//------------------------------------------------------------------------------------------------------------------------
/// @class ShaderManager
/// @brief Handles creation and compilation of shaders via modified NGL ShaderLib.
/// @brief will check and return compile status to user whether successful or unsuccessful.
//------------------------------------------------------------------------------------------------------------------------
class ShaderManager
{
public:
  //------------------------------------------------------------------------------------------------------------------------
  /// @brief default constructor for ShaderManager class
  //------------------------------------------------------------------------------------------------------------------------
  ShaderManager();
  //------------------------------------------------------------------------------------------------------------------------
  /// @brief method to create a new shader program object
  /// @param _name the name of the shader program to create
  //------------------------------------------------------------------------------------------------------------------------
  void createShaderProgram(std::string _name);
  //------------------------------------------------------------------------------------------------------------------------
  /// @brief method to set OpenGL to use the current shader program
  /// @param shaderType int to switch to normals shader
  //------------------------------------------------------------------------------------------------------------------------
  void use(uint shaderType);
  //------------------------------------------------------------------------------------------------------------------------
  /// @brief method called when 1st opening program to initialise the default phong shader
  //------------------------------------------------------------------------------------------------------------------------
  void initialize();
  //------------------------------------------------------------------------------------------------------------------------
  /// @brief method called to compile the currently active shader
  /// @param _vertSource the source code for the vertex shader
  /// @param _fragSource the source code for the fragment shader
  //------------------------------------------------------------------------------------------------------------------------
  void compileShader(QString _vertSource, QString _fragSource);
  //------------------------------------------------------------------------------------------------------------------------
  /// @brief method to return whether the shader manager successfully initialised
  //------------------------------------------------------------------------------------------------------------------------
  inline bool isInit() {return m_init;}
  //------------------------------------------------------------------------------------------------------------------------
  /// @brief method to return whether the current shader successfully compiled
  //------------------------------------------------------------------------------------------------------------------------
  inline bool compileStatus() {return m_compileStatus;}
  //------------------------------------------------------------------------------------------------------------------------
  /// @brief method to return the most recent error log
  //------------------------------------------------------------------------------------------------------------------------
  inline QString getErrorLog() {return m_errorLog;}
  //------------------------------------------------------------------------------------------------------------------------
  /// @brief method to set the data for the current shader
  /// @param _name the name of the the shader
  /// @param _vert the name of the vertex shader object
  /// @param _frag the name of the fragment shader object
  //------------------------------------------------------------------------------------------------------------------------
  inline void setData(std::string _name, std::string _vert, std::string _frag)
    {m_data.m_name = _name;
     m_data.m_vert = _vert;
     m_data.m_frag = _frag;}

private:
  //------------------------------------------------------------------------------------------------------------------------
  /// @brief flag for success of shader manager initialisation
  //------------------------------------------------------------------------------------------------------------------------
  bool m_init;
  //------------------------------------------------------------------------------------------------------------------------
  /// @brief flag for the success of compilation of currently active shader
  //------------------------------------------------------------------------------------------------------------------------
  bool m_compileStatus;
  //------------------------------------------------------------------------------------------------------------------------
  /// @brief error log for storing compiling errors
  //------------------------------------------------------------------------------------------------------------------------
  QString m_errorLog;
  //------------------------------------------------------------------------------------------------------------------------
  /// @brief method to check compiling errors for a single shader object
  /// @param _shadeName the name of the shader object to check
  /// @param o_log the output error log
  //------------------------------------------------------------------------------------------------------------------------
  bool checkCompileError(std::string _shaderName, QString *o_log);
  //------------------------------------------------------------------------------------------------------------------------
  /// @brief method to check compiling errors for all shader objects attached
  /// @brief to currently active shader program
  /// @param o_log the output error log
  //------------------------------------------------------------------------------------------------------------------------
  bool checkAllCompileError(QString *o_log);
  //------------------------------------------------------------------------------------------------------------------------
  /// @brief structure containing names for currently actuve shader program
  //------------------------------------------------------------------------------------------------------------------------
  shaderProgramData m_data;
  //------------------------------------------------------------------------------------------------------------------------
  /// @brief variable holding the identity of the bound texture map
  //------------------------------------------------------------------------------------------------------------------------
  GLuint m_textureName;

};

#endif // SHADERMANAGER_H
