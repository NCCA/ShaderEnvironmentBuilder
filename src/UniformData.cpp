#include "UniformData.h"

uniformData::uniformData()
{
  m_name=' ';
  m_loc=0;
  m_type=0;
  m_typeName=' ';
}

uniformData::~uniformData()
{

}

uniformData::uniformData(std::string _name , GLuint _loc , GLenum _type)
{
  m_name=_name;
  m_loc=_loc;
  m_type=_type;
}

void uniformData::setName(std::string _name)
{
  m_name=_name;
}
void uniformData::setLocation(GLuint _loc)
{
  m_loc=_loc;
}
void uniformData::setType(GLenum _type)
{
  m_type=_type;
}
void uniformData::setTypeName(std::string _typeName)
{
  m_typeName=_typeName;
}

void uniformDataV3::setVec3(float _value)
{
  m_vec3.m_x=_value;
  m_vec3.m_z=_value;
  m_vec3.m_y=_value;
}
void uniformDataV3::setVec3(ngl::Vec3 _value)
{
  m_vec3=_value;
}

void uniformDataV4::setVec4(float _value)
{
  m_vec4.m_x=_value;
  m_vec4.m_z=_value;
  m_vec4.m_y=_value;
  m_vec4.m_w=1;
}
void uniformDataV4::setVec4(ngl::Vec4 _value)
{
  m_vec4=_value;
}
