#ifndef UNIFORMS_H__
#define UNIFORMS_H__
#include <iostream>
#include <ngl/ShaderLib.h>
#include <ngl/Shader.h>
class uniformData
{
protected:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the name of this uniform
  //----------------------------------------------------------------------------------------------------------------------
  std::string m_name;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the location of this uniform
  //----------------------------------------------------------------------------------------------------------------------
  GLuint m_loc;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the dataType enum of this uniform, e.g. "35676"
  //----------------------------------------------------------------------------------------------------------------------
  GLenum m_type;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the dataType name of this uniform, e.g. "mat3"
  //----------------------------------------------------------------------------------------------------------------------
  std::string m_typeName;
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for the uniformData
  //----------------------------------------------------------------------------------------------------------------------
  uniformData();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor for the uniformData
  //----------------------------------------------------------------------------------------------------------------------
  ~uniformData();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for the uniformData, with input values
  /// @param[in] _name the name of the uniform
  /// @param[in] _loc the location of the uniform
  /// @param[in] _type the GLenum of the uniform, e.g. "35676"
  //----------------------------------------------------------------------------------------------------------------------
  uniformData(std::string _name , GLuint _loc , GLenum _type);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief sets the name of the uniformData
  /// @param[in] _name the name of the uniform
  //----------------------------------------------------------------------------------------------------------------------
  void setName(std::string _name);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief sets the location of the uniformData
  /// @param[in] _loc the location of the uniform
  //----------------------------------------------------------------------------------------------------------------------
  void setLocation(GLuint _loc);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief sets the enum type of the uniformData
  /// @param[in] _type the GLenum of the uniform, e.g. "35676"
  //----------------------------------------------------------------------------------------------------------------------
  void setType(GLenum _type);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief sets the string type of the uniformData
  /// @param[in] _typeName the string name of the uniform, e.g. "mat4"
  //----------------------------------------------------------------------------------------------------------------------
  void setTypeName(std::string _typeName);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this returns the name of the uniformData
  /// @return m_name
  //----------------------------------------------------------------------------------------------------------------------
  std::string getName()           {return m_name;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this returns the location of the uniformData
  /// @return m_loc
  //----------------------------------------------------------------------------------------------------------------------
  GLuint getLocation()            {return m_loc;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this returns the enum data type of the uniformData
  /// @return m_type
  //----------------------------------------------------------------------------------------------------------------------
  GLenum getTypeEnum()            {return m_type;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this returns the string data type of the uniformData
  /// @return m_typeName
  //----------------------------------------------------------------------------------------------------------------------
  std::string getTypeName()       {return m_typeName;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this pre declares the setBool() function for uniformDataBool
  /// @param[in] _value is the value to change m_bool into, from uniformDataBool
  //----------------------------------------------------------------------------------------------------------------------
  virtual void setBool(bool _value) {return;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief pre declares the getBool() function for uniformDataBool
  /// @return m_bool from uniformDataBool
  //----------------------------------------------------------------------------------------------------------------------
  virtual bool getBool() {return bool();}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this pre declares the setInt() function for uniformDataInt
  /// @param[in] _value is the value to change m_int into, from uniformDataBool
  //----------------------------------------------------------------------------------------------------------------------
  virtual void setInt(int _value){return;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief pre declares the getInt() function for uniformDataInt
  /// @return m_int from uniformDataInt
  //----------------------------------------------------------------------------------------------------------------------
  virtual int getInt() {return int();}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this pre declares the setFloat() function for uniformDataFloat
  /// @param[in] _value is the value to change m_float into, from uniformDataFloat
  //----------------------------------------------------------------------------------------------------------------------
  virtual void setFloat(float _value) {return;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief pre declares the getFloat() function for uniformDataFloat
  /// @return m_float from uniformDataFloat
  //----------------------------------------------------------------------------------------------------------------------
  virtual float getFloat() {return float();}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this pre declares the setVec3() function for uniformDataV3
  /// @param[in] _value is the value to change m_vec3 into, from uniformDataV3
  //----------------------------------------------------------------------------------------------------------------------
  virtual void setVec3(ngl::Vec3 _value) {return;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this pre declares the setVec3() function for uniformDataV3
  /// @param[in] _value is the value to change all m_vec3 components into, from uniformDataV3
  //----------------------------------------------------------------------------------------------------------------------
  virtual void setVec3(float _value) {return;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief pre declares the getVec3() function for uniformDataV3
  /// @return m_vec3 from uniformDataV3
  //----------------------------------------------------------------------------------------------------------------------
  virtual ngl::Vec3 getVec3() {return ngl::Vec3();}

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this pre declares the setVec4() function for uniformDataV4
  /// @param[in] _value is the value to change m_vec4 into, from uniformDataV4
  //----------------------------------------------------------------------------------------------------------------------
  virtual void setVec4(ngl::Vec4 _value) {return;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this pre declares the setVec4() function for uniformDataV4
  /// @param[in] _value is the value to change all m_vec4 components into, from uniformDataV4
  //----------------------------------------------------------------------------------------------------------------------
  virtual void setVec4(float _value) {return;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief pre declares the getVec4() function for uniformDataV4
  /// @return m_vec4 from uniformDataV4
  //----------------------------------------------------------------------------------------------------------------------
  virtual ngl::Vec4 getVec4() {return ngl::Vec4();}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this pre declares the setMat3() function for uniformDataM3
  /// @param[in] _value is the value to change m_mat3 into, from uniformDataM3
  //----------------------------------------------------------------------------------------------------------------------
  virtual void setMat3(ngl::Mat3 _value) {return;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief pre declares the getMat3() function for uniformDataM3
  /// @return m_mat3 from uniformDataM3
  //----------------------------------------------------------------------------------------------------------------------
  virtual ngl::Mat3 getMat3() {return ngl::Mat3();}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this pre declares the setMat4() function for uniformDataM4
  /// @param[in] _value is the value to change m_mat4 into, from uniformDataM4
  //----------------------------------------------------------------------------------------------------------------------
  virtual void setMat4(ngl::Mat4 _value) {return;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief pre declares the getMat4() function for uniformDataM4
  /// @return m_mat4 from uniformDataM4
  //----------------------------------------------------------------------------------------------------------------------
  virtual ngl::Mat4 getMat4() {return ngl::Mat4();}



};


class uniformDataM4 :public uniformData
{
private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the mat4 value
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Mat4 m_mat4;
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for the uniformDataM4
  //----------------------------------------------------------------------------------------------------------------------
  using uniformData::uniformData;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor for the uniformDataM4
  //----------------------------------------------------------------------------------------------------------------------
  ~uniformDataM4();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this assigns the _value to the uniformData m_mat4
  /// @param[in] _value is the value to change m_mat4 into
  //----------------------------------------------------------------------------------------------------------------------
  void setMat4(ngl::Mat4 _value) {m_mat4=_value;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this returns the m_mat4 value of this uniformData
  /// @return m_mat4
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Mat4 getMat4()             {return m_mat4;}
};

class uniformDataM3 :public uniformData
{
private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the mat3 value
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Mat3 m_mat3;
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for the uniformDataM3
  //----------------------------------------------------------------------------------------------------------------------
  using uniformData::uniformData;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor for the uniformDataM3
  //----------------------------------------------------------------------------------------------------------------------
  ~uniformDataM3();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this assigns the _value to the uniformData m_mat3
  /// @param[in] _value is the value to change m_mat3 into
  //----------------------------------------------------------------------------------------------------------------------
  void setMat3(ngl::Mat3 _value)    {m_mat3=_value;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this returns the m_mat3 value of this uniformData
  /// @return m_mat3
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Mat3 getMat3()               {return m_mat3;}
};

class uniformDataV4 :public uniformData
{
private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the vec4 value
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Vec4 m_vec4={0,0,0,1};
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for the uniformDataV4
  //----------------------------------------------------------------------------------------------------------------------
  using uniformData::uniformData;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor for the uniformDataV4
  //----------------------------------------------------------------------------------------------------------------------
  ~uniformDataV4();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this assigns the _value to the uniformData m_vec4
  /// @param[in] _value is the value to change m_vec4 into
  //----------------------------------------------------------------------------------------------------------------------
  void setVec4(ngl::Vec4 _value);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this assigns the _value to the uniformData m_vec4
  /// @param[in] _value is the value to change all m_vec4 componenets into
  //----------------------------------------------------------------------------------------------------------------------
  void setVec4(float _value);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this returns the m_vec4 value of this uniformData
  /// @return m_vec4
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Vec4 getVec4()            {return m_vec4;}
};

class uniformDataV3 :public uniformData
{
private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the vec3 value
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Vec3 m_vec3={0,0,0};
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for the uniformDataV3
  //----------------------------------------------------------------------------------------------------------------------
  using uniformData::uniformData;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor for the uniformDataV3
  //----------------------------------------------------------------------------------------------------------------------
  ~uniformDataV3();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this assigns the _value to the uniformData m_vec3
  /// @param[in] _value is the value to change m_vec3 into
  //----------------------------------------------------------------------------------------------------------------------
  void setVec3(ngl::Vec3 _value);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this assigns the _value to the uniformData m_vec4
  /// @param[in] _value is the value to change all m_vec3 componenets into
  //----------------------------------------------------------------------------------------------------------------------
  void setVec3(float _value);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this returns the m_vec3 value of this uniformData
  /// @return m_vec3
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Vec3 getVec3()            {return m_vec3;}
};

class uniformDataInt :public uniformData
{
private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the int value
  //----------------------------------------------------------------------------------------------------------------------
  int m_int=0;
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for the uniformDataInt
  //----------------------------------------------------------------------------------------------------------------------
  using uniformData::uniformData;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor for the uniformDataInt
  //----------------------------------------------------------------------------------------------------------------------
  ~uniformDataInt();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this assigns the _value to the uniformData m_int
  /// @param[in] _value is the value to change m_int into
  //----------------------------------------------------------------------------------------------------------------------
  void setInt(int _value) {m_int=_value;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this returns the m_int value of this uniformData
  /// @return m_int
  //----------------------------------------------------------------------------------------------------------------------
  int getInt()            {return m_int;}
};

class uniformDataFloat :public uniformData
{
private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the float value
  //----------------------------------------------------------------------------------------------------------------------
  float m_float=0.5;
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for the uniformDataFloat
  //----------------------------------------------------------------------------------------------------------------------
  using uniformData::uniformData;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor for the uniformDataFloat
  //----------------------------------------------------------------------------------------------------------------------
  ~uniformDataFloat();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this assigns the _value to the uniformData m_float
  /// @param[in] _value is the value to change m_float into
  //----------------------------------------------------------------------------------------------------------------------
  void setFloat( float _value) {m_float=_value;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this returns the m_float value of this uniformData
  /// @return m_float
  //----------------------------------------------------------------------------------------------------------------------
  float getFloat()             {return m_float;}
};

class uniformDataBool :public uniformData
{
private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the bool value
  //----------------------------------------------------------------------------------------------------------------------
  bool m_bool=false;
public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief ctor for the uniformDataBool
  //----------------------------------------------------------------------------------------------------------------------
  using uniformData::uniformData;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor for the uniformDataBool
  //----------------------------------------------------------------------------------------------------------------------
  ~uniformDataBool();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this assigns the _value to the uniformData m_bool
  /// @param[in] _value is the value to change m_bool into
  //----------------------------------------------------------------------------------------------------------------------
  void setBool( bool _value)  {m_bool=_value;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this returns the m_bool value of this this uniformData
  /// @return m_bool
  //----------------------------------------------------------------------------------------------------------------------
  bool getBool()              {return m_bool;}
};
#endif // UNIFORMS_H__


