#ifndef PARSER_H__
#define PARSER_H__
#include <unordered_map>
#include <iostream>
#include <ngl/ShaderLib.h>
#include <ngl/Shader.h>
#include <fstream>
class parserLib
{

public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for our parserLib
  //----------------------------------------------------------------------------------------------------------------------
  parserLib();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor for our parserLib
  //----------------------------------------------------------------------------------------------------------------------
  ~parserLib();

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief get and store uniform data(non-values)
  //----------------------------------------------------------------------------------------------------------------------
  void assignUniformInformation();
  void assignUniformValues();
  void assignAllData();

  void sendUniformsToShader(ngl::ShaderLib *shader);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief prints the uniform location, data type and names
  //----------------------------------------------------------------------------------------------------------------------
  void printUniforms();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to translate the data type name from a number into a name. e.g. 35676 -> mat4
  //----------------------------------------------------------------------------------------------------------------------
  void uniformDataTypes();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief exports the uniformData into a .txt file ...UPDATE: is this needed or can we just extract the information via the class?
  //----------------------------------------------------------------------------------------------------------------------
  void exportUniforms();

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the number of active uniforms
  //----------------------------------------------------------------------------------------------------------------------
  int m_num;



  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the uniform Data
  //----------------------------------------------------------------------------------------------------------------------
  typedef struct
  {
      std::string m_name;     // Name of the Uniform
      GLuint m_loc;           // Location of the Uniform (you don't need this, Jonny)
      GLenum m_type;          // Data Type in GLenum form  e.g. "35676"
      std::string m_typeName; // Data Type string, easier to read e.g. "mat4"

      // Value types
      bool m_bool=NULL;
      int m_int=NULL;
      float m_float=NULL;
      ngl::Vec3 m_vec3=NULL;
      ngl::Vec4 m_vec4=NULL;
      ngl::Mat3 m_mat3=NULL;
      ngl::Mat4 m_mat4=0.0;

  /// #Lets make a template class and see if that works....or uses switches(make sure to break) using Enums to activate different values
  ///

  }uniformData;



  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store a list of pre-registered Uniform data types.
  //----------------------------------------------------------------------------------------------------------------------
  std::unordered_map <std::string, uniformData> m_registeredUniforms;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store a list of uniformData
  //----------------------------------------------------------------------------------------------------------------------
  std::vector <uniformData> m_uniformDataList;

  //-----------------------------------------------------------------------------------------------
  /// @brief
  //----------------------------------------------------------------------------------------------
  bool returnBool(int loc);
  int returnInt(int loc);
  float returnFloat(int loc);
  ngl::Vec3 returnVec3(int loc);
  ngl::Vec4 returnVec4(int loc);
  ngl::Mat3 returnMat3(int loc);
  ngl::Mat4 returnMat4(int loc);

  void setBool(int loc, bool newValue);
  void setInt(int loc, int newValue);
  void setFloat(int loc, float newValue);
  void setVec3(int loc, ngl::Vec3 newValue);
  void setVec4(int loc, ngl::Vec4 newValue);
  void setMat3(int loc, ngl::Mat3 newValue);
  void setMat4(int loc, ngl::Mat4 newValue);



};

#endif // PARSER_H
