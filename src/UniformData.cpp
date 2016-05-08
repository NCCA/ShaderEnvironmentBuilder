#include "UniformData.h"

UniformData::UniformData()
{
  m_name=' ';
  m_loc=0;
  m_type=0;
  m_typeName=' ';
}

//------------------------------------------------------------------------------
UniformData::~UniformData()
{

}

//------------------------------------------------------------------------------
UniformData::UniformData(std::string _name , GLuint _loc , GLenum _type)
{
  m_name=_name;
  m_loc=_loc;
  m_type=_type;
}

//------------------------------------------------------------------------------
void UniformData::setName(std::string _name)
{
  m_name=_name;
}

//------------------------------------------------------------------------------
void UniformData::setLocation(GLuint _loc)
{
  m_loc=_loc;
}

//------------------------------------------------------------------------------
void UniformData::setType(GLenum _type)
{
  m_type=_type;
}

//------------------------------------------------------------------------------
void UniformData::setTypeName(std::string _typeName)
{
  m_typeName=_typeName;
}

//------------------------------------------------------------------------------
void UniformDataV3::setVec3(float _value)
{
  m_vec3.m_x=_value;
  m_vec3.m_z=_value;
  m_vec3.m_y=_value;
}

//------------------------------------------------------------------------------
void UniformDataV3::setVec3(ngl::Vec3 _value)
{
  m_vec3=_value;
}

//------------------------------------------------------------------------------
void UniformDataV4::setVec4(float _value)
{
  m_vec4.m_x=_value;
  m_vec4.m_z=_value;
  m_vec4.m_y=_value;
  m_vec4.m_w=1;
}

//------------------------------------------------------------------------------
void UniformDataV4::setVec4(ngl::Vec4 _value)
{
  m_vec4=_value;
}
