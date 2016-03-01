#ifndef PARSER_H__
#define PARSER_H__
#include <unordered_map>
#include <iostream>
#include <ngl/ShaderLib.h>
#include <ngl/Shader.h>
#include <fstream>
#include <UniformData.h>
class parserLib
{

public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for our ParserLib
  //----------------------------------------------------------------------------------------------------------------------
  parserLib();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor for our ParserLib
  //----------------------------------------------------------------------------------------------------------------------
  ~parserLib();

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief finds number of active uniforms and stores the data in blocks called uniformData.
  ///  This then stores it in a list m_uniformList
  //----------------------------------------------------------------------------------------------------------------------
  void initializeUniformData();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief sets default values for the active uniforms
  //----------------------------------------------------------------------------------------------------------------------
  void assignUniformValues();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief assigns all appropriate values, locations, data types, names
  //----------------------------------------------------------------------------------------------------------------------
  void assignAllData();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief takes the list of uniforms and updates them onto the shader, depending on the data type.
  /// @param[in] _shader an instance of the current shader
  //----------------------------------------------------------------------------------------------------------------------
  void sendUniformsToShader(ngl::ShaderLib *shader);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief prints the uniform location, data type and names
  /// @param[in] _printValues is whether or not you want to print out values.
  //----------------------------------------------------------------------------------------------------------------------
  void printUniforms(bool _printValues);

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to translate the data type name from a number into a name. e.g. 35676 -> mat4
  /// The following section was originally written by Jon Macey:-
  /// Jon Macey. NCCA library NGL::ShaderProgram::printRegisteredUniforms [online]. [Accessed 01/10/16].
  /// Available from: <https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/index.html>.
  //----------------------------------------------------------------------------------------------------------------------
  void uniformDataTypes();

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief exports the uniformData into a .txt file
  //----------------------------------------------------------------------------------------------------------------------
  void exportUniforms();

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the number of active uniforms
  //----------------------------------------------------------------------------------------------------------------------
  uint m_num;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the uniform Data
  //----------------------------------------------------------------------------------------------------------------------
//  typedef struct
//  {
//      std::string m_name;     // Name of the Uniform
//      GLuint m_loc;           // Location of the Uniform (you don't need this, Jonny)
//      GLenum m_type;          // Data Type in GLenum form  e.g. "35676"
//      std::string m_typeName; // Data Type string, easier to read e.g. "mat4"

//      // Value types
//      bool m_bool=0;
//      int m_int=0;
//      float m_float=0;
//      ngl::Vec3 m_vec3=0;
//      ngl::Vec4 m_vec4=0;
//      ngl::Mat3 m_mat3=0;
//      ngl::Mat4 m_mat4=0.0;
//  }uniformData;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store a list of pre-registered Uniform data types.
  //----------------------------------------------------------------------------------------------------------------------
  std::unordered_map <std::string, uniformData*> m_registeredUniforms;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store a list of uniformData
  //----------------------------------------------------------------------------------------------------------------------
  std::vector <uniformData*> m_uniformList;

//  //----------------------------------------------------------------------------------------------------------------------
//  /// @brief this returns the m_bool value of uniformData in the m_uniformList
//  /// @param[in] _loc the location of the uniform in the m_uniformList
//  /// @return m_uniformList[i].uniformData.m_bool
//  //----------------------------------------------------------------------------------------------------------------------
//  bool getBool(int _loc);
//  //----------------------------------------------------------------------------------------------------------------------
//  /// @brief this returns the m_int value of uniformData in the m_uniformList
//  /// @param[in] _loc the location of the uniform in the m_uniformList
//  /// @return m_uniformList[i].uniformData.m_int
//  //----------------------------------------------------------------------------------------------------------------------
//  int getInt(int _loc);
//  //----------------------------------------------------------------------------------------------------------------------
//  /// @brief this returns the m_float value of uniformData in the m_uniformList
//  /// @param[in] _loc the location of the uniform in the m_uniformList
//  /// @return m_uniformList[i].uniformData.m_float
//  //----------------------------------------------------------------------------------------------------------------------
//  float getFloat(int _loc);
//  //----------------------------------------------------------------------------------------------------------------------
//  /// @brief this returns the m_vec3 value of uniformData in the m_uniformList
//  /// @param[in] _loc the location of the uniform in the m_uniformList
//  /// @return m_uniformList[i].uniformData.m_vec3
//  //----------------------------------------------------------------------------------------------------------------------
//  ngl::Vec3 getVec3(int _loc);
//  //----------------------------------------------------------------------------------------------------------------------
//  /// @brief this returns the m_vec4 value of uniformData in the m_uniformList
//  /// @param[in] _loc the location of the uniform in the m_uniformList
//  /// @return m_uniformList[i].uniformData.m_vec4
//  //----------------------------------------------------------------------------------------------------------------------
//  ngl::Vec4 getVec4(int _loc);
//  //----------------------------------------------------------------------------------------------------------------------
//  /// @brief this returns the m_mat3 value of uniformData in the m_uniformList
//  /// @param[in] _loc the location of the uniform in the m_uniformList
//  /// @return m_uniformList[i].uniformData.m_mat3
//  //----------------------------------------------------------------------------------------------------------------------
//  ngl::Mat3 getMat3(int _loc);
//  //----------------------------------------------------------------------------------------------------------------------
//  /// @brief this returns the m_mat4 value of uniformData in the m_uniformList
//  /// @param[in] _loc the location of the uniform in the m_uniformList
//  /// @return m_uniformList[i].uniformData.m_mat4
//  //----------------------------------------------------------------------------------------------------------------------
//  ngl::Mat4 getMat4(int _loc);
//  //----------------------------------------------------------------------------------------------------------------------
//  /// @brief this assigns the _value to the uniformData m_bool
//  /// @param[in] _loc is the location of the uniform in the list
//  /// @param[in] _value is the value to change m_bool to
//  //----------------------------------------------------------------------------------------------------------------------
//  void setBool(int _loc, bool _value);
//  //----------------------------------------------------------------------------------------------------------------------
//  /// @brief this assigns the _value to the uniformData m_int
//  /// @param[in] _loc is the location of the uniform in the list
//  /// @param[in] _value is the value to change m_int to
//  //----------------------------------------------------------------------------------------------------------------------
//  void setInt(int _loc, int _value);
//  //----------------------------------------------------------------------------------------------------------------------
//  /// @brief this assigns the _value to the uniformData m_float
//  /// @param[in] _loc is the location of the uniform in the list
//  /// @param[in] _value is the value to change m_float to
//  //----------------------------------------------------------------------------------------------------------------------
//  void setFloat(int _loc, float _value);
//  //----------------------------------------------------------------------------------------------------------------------
//  /// @brief this assigns the _value to the uniformData m_vec3
//  /// @param[in] _loc is the location of the uniform in the list
//  /// @param[in] _value is the value to change m_vec3 to
//  //----------------------------------------------------------------------------------------------------------------------
//  void setVec3(int _loc, ngl::Vec3 _value);
//  //----------------------------------------------------------------------------------------------------------------------
//  /// @brief this assigns the _value to the uniformData m_vec4
//  /// @param[in] _loc is the location of the uniform in the list
//  /// @param[in] _value is the value to change m_vec4 to
//  //----------------------------------------------------------------------------------------------------------------------
//  void setVec4(int _loc, ngl::Vec4 _value);
//  //----------------------------------------------------------------------------------------------------------------------
//  /// @brief this assigns the _value to the uniformData m_mat3
//  /// @param[in] _loc is the location of the uniform in the list
//  /// @param[in] _value is the value to change m_mat3 to
//  //----------------------------------------------------------------------------------------------------------------------
//  void setMat3(int _loc, ngl::Mat3 _value);
//  //----------------------------------------------------------------------------------------------------------------------
//  /// @brief this assigns the _value to the uniformData m_mat4
//  /// @param[in] _loc is the location of the uniform in the list
//  /// @param[in] _value is the value to change m_mat4 to
//  //----------------------------------------------------------------------------------------------------------------------
//  void setMat4(int _loc, ngl::Mat4 _value);

};

#endif // PARSER_H
