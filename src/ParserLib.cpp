#include <QDir>
#include <ngl/ShaderLib.h>
#include "ParserLib.h"
#include "CebErrors.h"


//----------------------------------------------------------------------------
/// @brief ctor for our ParserLib
//----------------------------------------------------------------------------
ParserLib::ParserLib(ShaderManager* _manager)
{
  m_num=0;
  m_uniformList.resize(0);
  m_shaderManager = _manager;
}

//----------------------------------------------------------------------------
ParserLib::~ParserLib()
{
  std::cerr<<"ParserLib destroyed"<<std::endl;
}

//----------------------------------------------------------------------------
void ParserLib::initializeUniformData()
{
  //create instance of a shader
  ngl::ShaderLib *shaderLib=ngl::ShaderLib::instance();
  GLuint id=shaderLib->getProgramID(m_shaderManager->getData().m_name);

  // extract the number of uniforms active and update class data.
  GLint nUniforms;
  glGetProgramInterfaceiv(id, GL_UNIFORM, GL_ACTIVE_RESOURCES, &nUniforms);
  m_num=nUniforms;
  m_uniformList.resize(m_num);
  m_registeredUniforms.clear();

  m_ignoreUniformIDs.resize(0);

  // declare some temp variables
  char uniformName[256];
  GLsizei length;
  GLint size;
  GLenum type;

  // Permanently assign data to the class
  for (GLint i=0; i<nUniforms; i++)
  {
    // create local variables to store temp location value.
    GLint tempLoc;
    // get the active uniform data...
    glGetActiveUniform(id,i, 256, &length, &size , &type , uniformName);
    // ... store the temp data
    tempLoc=glGetUniformLocation(id,uniformName);

    // set a different data type depending on typeData
    switch(type)
    {
      case GL_BOOL:
      {
        UniformDataBool* newData= new UniformDataBool(uniformName,
                                                      tempLoc,
                                                      type);
        // Add UniformData to the currently registeredUniforms
        // m_registeredUniforms[uniformName]=newData;
        m_uniformList[i-m_ignoreUniformIDs.size()]=newData;
        break;
      }
      case GL_FLOAT:
      {
        UniformDataFloat* newData= new UniformDataFloat(uniformName,
                                                        tempLoc,
                                                        type);
        // Add UniformData to the currently registeredUniforms
        // m_registeredUniforms[uniformName]=newData;
        m_uniformList[i-m_ignoreUniformIDs.size()]=newData;
        break;
      }
      case GL_INT:
      {
        UniformDataInt* newData= new UniformDataInt(uniformName,
                                                    tempLoc,
                                                    type);
        // Add UniformData to the currently registeredUniforms
        // m_registeredUniforms[uniformName]=newData;
        m_uniformList[i-m_ignoreUniformIDs.size()]=newData;
        break;
      }
      case GL_FLOAT_VEC3:
      {
        UniformDataV3* newData= new UniformDataV3(uniformName,
                                                  tempLoc,
                                                  type);
        // Add UniformData to the currently registeredUniforms
        // m_registeredUniforms[uniformName]=newData;
        m_uniformList[i-m_ignoreUniformIDs.size()]=newData;
        break;
      }
      case GL_FLOAT_VEC4:
      {
        UniformDataV4* newData= new UniformDataV4(uniformName,
                                                  tempLoc,
                                                  type);
        // Add UniformData to the currently registeredUniforms
        // m_registeredUniforms[uniformName]=newData;
        m_uniformList[i-m_ignoreUniformIDs.size()]=newData;
        break;
      }
      case GL_FLOAT_MAT3:
      {
        UniformDataM3* newData= new UniformDataM3(uniformName,
                                                  tempLoc,
                                                  type);
        // Add UniformData to the currently registeredUniforms
        // m_registeredUniforms[uniformName]=newData;
        m_uniformList[i-m_ignoreUniformIDs.size()]=newData;
        break;
      }
      case GL_FLOAT_MAT4:
      {
        UniformDataM4* newData= new UniformDataM4(uniformName,
                                                  tempLoc,
                                                  type);
        // Add UniformData to the currently registeredUniforms
        // m_registeredUniforms[uniformName]=newData;
        m_uniformList[i-m_ignoreUniformIDs.size()]=newData;
        break;
      }
      default:
      {
        std::cout<<"unrecognised data type name"<<std::endl;
        m_uniformList.erase(m_uniformList.begin()+(i-m_ignoreUniformIDs.size()));
        m_ignoreUniformIDs.push_back(i);

      }
    }


  }
  m_num -= m_ignoreUniformIDs.size();
  uniformDataTypes();
}

//------------------------------------------------------------------------------
void ParserLib::assignAllData()
{
  initializeUniformData();
  assignUniformValues();
}

//------------------------------------------------------------------------------
void ParserLib::printUniforms()
{
  std::cout<<"\n******\nUniform Information: Starts\n";
  std::cout<<"There are "<<m_num<<" Uniforms\n";

  // print information
  for (uint i=0; i<m_num; i++)
  {
    std::cout << "Name: "<<m_uniformList[i]->getName();
    std::cout << ";  Location: "<<m_uniformList[i]->getName()<<" ("<<i<<")";
    std::cout << ";  Type: "<<m_uniformList[i]->getTypeEnum()<<"; ";
    std::cout <<m_uniformList[i]->getTypeName()<<std::endl;


    switch(m_uniformList[i]->getTypeEnum())
    {
      case GL_BOOL:
      {
        std::cout<<"m_bool: "<<m_uniformList[i]->getBool()<<std::endl;
        break;
      }
      case GL_FLOAT:
      {
        std::cout<<"m_float: "<<m_uniformList[i]->getFloat()<<std::endl;
        break;
      }
      case GL_INT:
      {
        std::cout<<"m_int: "<<m_uniformList[i]->getInt()<<std::endl;
        break;
      }
      case GL_FLOAT_VEC3:
      {
        std::cout<<"m_vec3:(x) "<<m_uniformList[i]->getVec3().m_x<<std::endl;
        std::cout<<"m_vec3:(y) "<<m_uniformList[i]->getVec3().m_y<<std::endl;
        std::cout<<"m_vec3:(z) "<<m_uniformList[i]->getVec3().m_z<<std::endl;
        break;
      }
      case GL_FLOAT_VEC4:
      {
        std::cout<<"m_vec4:(x) "<<m_uniformList[i]->getVec4().m_x<<std::endl;
        std::cout<<"m_vec4:(y) "<<m_uniformList[i]->getVec4().m_y<<std::endl;
        std::cout<<"m_vec4:(z) "<<m_uniformList[i]->getVec4().m_z<<std::endl;
        break;
      }
      case GL_FLOAT_MAT3:
      {
        break;
      }
      case GL_FLOAT_MAT4:
      {
        break;
      }
      default:
      {
        std::cout<<"unrecognised data type name"<<std::endl;
      }
    }
  }
  std::cout<<"___________________________________Uniform Information: Ends//\n";

}

//------------------------------------------------------------------------------
/// @brief Converts GLenums into const chars
/// Modified from :-
/// Jon Macey. NCCA library NGL::ShaderProgram::printRegisteredUniforms [online].
/// [Accessed 01/10/16]. Available from:
/// <https://nccastaff.bournemouth.ac.uk/jmacey/GraphicsLib/index.html>.
//------------------------------------------------------------------------------
void ParserLib::uniformDataTypes()
{
  // Uses an unordered map to map the GLenum's into const char's
  const static std::unordered_map<GLenum,const char *> types=
  {
    {GL_FLOAT,"float"},
    {GL_FLOAT_VEC2,"vec2"},
    {GL_FLOAT_VEC3,"vec3"},
    {GL_FLOAT_VEC4,"vec4"},
    {GL_DOUBLE,"double"},
    {GL_DOUBLE_VEC2,"dvec2"},
    {GL_DOUBLE_VEC3,"dvec3"},
    {GL_DOUBLE_VEC4,"dvec4"},
    {GL_INT,"int"},
    {GL_INT_VEC2,"ivec2"},
    {GL_INT_VEC3,"ivec3"},
    {GL_INT_VEC4,"ivec4"},
    {GL_UNSIGNED_INT,"unsigned int"},
    {GL_UNSIGNED_INT_VEC2,"uvec2"},
    {GL_UNSIGNED_INT_VEC3,"uvec3"},
    {GL_UNSIGNED_INT_VEC4,"uvec4"},
    {GL_BOOL,"bool"},
    {GL_BOOL_VEC2,"bvec2"},
    {GL_BOOL_VEC3,"bvec3"},
    {GL_BOOL_VEC4,"bvec4"},
    {GL_FLOAT_MAT2,"mat2"},
    {GL_FLOAT_MAT3,"mat3"},
    {GL_FLOAT_MAT4,"mat4"},
    {GL_FLOAT_MAT2x3,"mat2x3"},
    {GL_FLOAT_MAT2x4,"mat2x4"},
    {GL_FLOAT_MAT3x2,"mat3x2"},
    {GL_FLOAT_MAT3x4,"mat3x4"},
    {GL_FLOAT_MAT4x2,"mat4x2"},
    {GL_FLOAT_MAT4x3,"mat4x3"},
    {GL_DOUBLE_MAT2,"dmat2"},
    {GL_DOUBLE_MAT3,"dmat3"},
    {GL_DOUBLE_MAT4,"dmat4"},
    {GL_DOUBLE_MAT2x3,"dmat2x3"},
    {GL_DOUBLE_MAT2x4,"dmat2x4"},
    {GL_DOUBLE_MAT3x2,"dmat3x2"},
    {GL_DOUBLE_MAT3x4,"dmat3x4"},
    {GL_DOUBLE_MAT4x2,"dmat4x2"},
    {GL_DOUBLE_MAT4x3,"dmat4x3"},
    {GL_SAMPLER_1D,"sampler1D"},
    {GL_SAMPLER_2D,"sampler2D"},
    {GL_SAMPLER_3D,"sampler3D"},
    {GL_SAMPLER_CUBE,"samplerCube"},
    {GL_SAMPLER_1D_SHADOW,"sampler1DShadow"},
    {GL_SAMPLER_2D_SHADOW,"sampler2DShadow"},
    {GL_SAMPLER_1D_ARRAY,"sampler1DArray"},
    {GL_SAMPLER_2D_ARRAY,"sampler2DArray"},
    {GL_SAMPLER_1D_ARRAY_SHADOW,"sampler1DArrayShadow"},
    {GL_SAMPLER_2D_ARRAY_SHADOW,"sampler2DArrayShadow"},
    {GL_SAMPLER_2D_MULTISAMPLE,"sampler2DMS"},
    {GL_SAMPLER_2D_MULTISAMPLE_ARRAY,"sampler2DMSArray"},
    {GL_SAMPLER_CUBE_SHADOW,"samplerCubeShadow"},
    {GL_SAMPLER_BUFFER,"samplerBuffer"},
    {GL_SAMPLER_2D_RECT,"sampler2DRect"},
    {GL_SAMPLER_2D_RECT_SHADOW,"sampler2DRectShadow"},
    {GL_INT_SAMPLER_1D,"isampler1D"},
    {GL_INT_SAMPLER_2D,"isampler2D"},
    {GL_INT_SAMPLER_3D,"isampler3D"},
    {GL_INT_SAMPLER_CUBE,"isamplerCube"},
    {GL_INT_SAMPLER_1D_ARRAY,"isampler1DArray"},
    {GL_INT_SAMPLER_2D_ARRAY,"isampler2DArray"},
    {GL_INT_SAMPLER_2D_MULTISAMPLE,"isampler2DMS"},
    {GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,"isampler2DMSArray"},
    {GL_INT_SAMPLER_BUFFER,"isamplerBuffer"},
    {GL_INT_SAMPLER_2D_RECT,"isampler2DRect"},
    {GL_UNSIGNED_INT_SAMPLER_1D,"usampler1D"},
    {GL_UNSIGNED_INT_SAMPLER_2D,"usampler2D"},
    {GL_UNSIGNED_INT_SAMPLER_3D,"usampler3D"},
    {GL_UNSIGNED_INT_SAMPLER_CUBE,"usamplerCube"},
    {GL_UNSIGNED_INT_SAMPLER_1D_ARRAY,"usampler2DArray"},
    {GL_UNSIGNED_INT_SAMPLER_2D_ARRAY,"usampler2DArray"},
    {GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE,"usampler2DMS"},
    {GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY,"usampler2DMSArray"},
    {GL_UNSIGNED_INT_SAMPLER_BUFFER,"usamplerBuffer"},
    {GL_UNSIGNED_INT_SAMPLER_2D_RECT,"usampler2DRect"},
    {GL_IMAGE_1D,"image1D"},
    {GL_IMAGE_2D,"image2D"},
    {GL_IMAGE_3D,"image3D"},
    {GL_IMAGE_2D_RECT,"image2DRect"},
    {GL_IMAGE_CUBE,"imageCube"},
    {GL_IMAGE_BUFFER,"imageBuffer"},
    {GL_IMAGE_1D_ARRAY,"image1DArray"},
    {GL_IMAGE_2D_ARRAY,"image2DArray"},
    {GL_IMAGE_2D_MULTISAMPLE,"image2DMS"},
    {GL_IMAGE_2D_MULTISAMPLE_ARRAY,"image2DMSArray"},
    {GL_INT_IMAGE_1D,"iimage1D"},
    {GL_INT_IMAGE_2D,"iimage2D"},
    {GL_INT_IMAGE_3D,"iimage3D"},
    {GL_INT_IMAGE_2D_RECT,"iimage2DRect"},
    {GL_INT_IMAGE_CUBE,"iimageCube"},
    {GL_INT_IMAGE_BUFFER,"iimageBuffer"},
    {GL_INT_IMAGE_1D_ARRAY,"iimage1DArray"},
    {GL_INT_IMAGE_2D_ARRAY,"iimage2DArray"},
    {GL_INT_IMAGE_2D_MULTISAMPLE,"iimage2DMS"},
    {GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY,"iimage2DMSArray"},
    {GL_UNSIGNED_INT_IMAGE_1D,"uimage1D"},
    {GL_UNSIGNED_INT_IMAGE_2D,"uimage2D"},
    {GL_UNSIGNED_INT_IMAGE_3D,"uimage3D"},
    {GL_UNSIGNED_INT_IMAGE_2D_RECT,"uimage2DRect"},
    {GL_UNSIGNED_INT_IMAGE_CUBE,"uimageCube"},
    {GL_UNSIGNED_INT_IMAGE_BUFFER,"uimageBuffer"},
    {GL_UNSIGNED_INT_IMAGE_1D_ARRAY,"uimage1DArray"},
    {GL_UNSIGNED_INT_IMAGE_2D_ARRAY,"uimage2DArray"},
    {GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE,"uimage2DMS"},
    {GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY,"uimage2DMSArray"},
    {GL_UNSIGNED_INT_ATOMIC_COUNTER,"atomic_uint"}
  };

  ngl::ShaderLib *shaderLib=ngl::ShaderLib::instance();
  GLuint id=shaderLib->getProgramID(m_shaderManager->getData().m_name);

  GLint nUniforms;
  glGetProgramInterfaceiv(id, GL_UNIFORM, GL_ACTIVE_RESOURCES, &nUniforms);


  std::cout<<"Registered Uniforms for shader "<< id <<"\n";

  for(auto d : m_uniformList)
  {
    std::string type;
    auto value=types.find(d->getTypeEnum());
    if(value !=types.end())
    {
      d->setTypeName(value->second);
    }
    else
    {
      type="unknown type";
    }
    m_registeredUniforms[d->getName()] = d;
  }
  std::cout<<"End Uniforms"<<"\n";
}
/// end of Citation

//------------------------------------------------------------------------------
bool ParserLib::exportUniforms(QString _dir)
{
  std::ofstream fileOut;
  fileOut.open(_dir.toStdString().c_str());
  if(!fileOut.is_open())    ///If it can't be opened
  {
    throw CEBError::fileError(_dir);
    return false;
  }
  for(uint i=0;i<m_num;i++)
  {
    // Input Name, Location and Type
    fileOut<<m_uniformList[i]->getName()<<"\n";
    fileOut<<m_uniformList[i]->getLocation()<<"\n";
    fileOut<<m_uniformList[i]->getTypeName()<<"\n";
    switch(m_uniformList[i]->getTypeEnum())
    {
      case GL_BOOL:
      {
        fileOut<<m_uniformList[i]->getBool()<<"\n";
        break;
      }
      case GL_FLOAT:
      {
        fileOut<<m_uniformList[i]->getFloat()<<"\n";
        break;
      }
      case GL_INT:
      {
        fileOut<<m_uniformList[i]->getInt()<<"\n";
        break;
      }
      case GL_FLOAT_VEC3:
      {
        fileOut<<m_uniformList[i]->getVec3().m_x<<" ";
        fileOut<<m_uniformList[i]->getVec3().m_y<<" ";
        fileOut<<m_uniformList[i]->getVec3().m_z<<"\n";
        break;
      }
      case GL_FLOAT_VEC4:
      {
        fileOut<<m_uniformList[i]->getVec4().m_x<<" ";
        fileOut<<m_uniformList[i]->getVec4().m_y<<" ";
        fileOut<<m_uniformList[i]->getVec4().m_z<<" ";
        fileOut<<m_uniformList[i]->getVec4().m_w<<"\n";
        break;
      }
      case GL_FLOAT_MAT3:
      {

        fileOut<<m_uniformList[i]->getMat3().m_00<<" ";
        fileOut<<m_uniformList[i]->getMat3().m_01<<" ";
        fileOut<<m_uniformList[i]->getMat3().m_02<<" ";

        fileOut<<m_uniformList[i]->getMat3().m_10<<" ";
        fileOut<<m_uniformList[i]->getMat3().m_11<<" ";
        fileOut<<m_uniformList[i]->getMat3().m_12<<" ";

        fileOut<<m_uniformList[i]->getMat3().m_20<<" ";
        fileOut<<m_uniformList[i]->getMat3().m_21<<" ";
        fileOut<<m_uniformList[i]->getMat3().m_22<<"\n";

        break;
      }
      case GL_FLOAT_MAT4:
      {
        fileOut<<m_uniformList[i]->getMat4().m_00<<" ";
        fileOut<<m_uniformList[i]->getMat4().m_01<<" ";
        fileOut<<m_uniformList[i]->getMat4().m_02<<" ";
        fileOut<<m_uniformList[i]->getMat4().m_03<<" ";

        fileOut<<m_uniformList[i]->getMat4().m_10<<" ";
        fileOut<<m_uniformList[i]->getMat4().m_11<<" ";
        fileOut<<m_uniformList[i]->getMat4().m_12<<" ";
        fileOut<<m_uniformList[i]->getMat4().m_13<<" ";

        fileOut<<m_uniformList[i]->getMat4().m_20<<" ";
        fileOut<<m_uniformList[i]->getMat4().m_21<<" ";
        fileOut<<m_uniformList[i]->getMat4().m_22<<" ";
        fileOut<<m_uniformList[i]->getMat4().m_23<<"\n";

        break;
      }
      default:
      {
        std::cerr<<"unrecognised data type name"<<std::endl;
        break;
      }
    }
  }
  // close file
  fileOut.close();
  return true;
}

//------------------------------------------------------------------------------
void ParserLib::assignUniformValues()
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();

  // sets default values depending on it's data type
  for (uint i=0;i<m_num;i++)
  {
    if (std::find(m_ignoreUniformIDs.begin(), m_ignoreUniformIDs.end(), i) == m_ignoreUniformIDs.end() )
    {
      switch(m_uniformList[i]->getTypeEnum())
      {
        case GL_BOOL:
        {
          m_uniformList[i]->setBool(0);
          break;
        }
        case GL_FLOAT:
        {
          m_uniformList[i]->setFloat(0.5);
          break;
        }
        case GL_INT:
        {
          m_uniformList[i]->setInt(0);
          break;
        }
        case GL_FLOAT_VEC3:
        {
          m_uniformList[i]->setVec3(0.5);
          break;
        }
        case GL_FLOAT_VEC4:
        {
          m_uniformList[i]->setVec4(0.5);
          break;
        }
        case GL_FLOAT_MAT3:
        {
          ngl::Mat3 temp;
          temp= shader->getUniformBlockIndex(m_uniformList[i]->getName());
          temp.m_00=1;
          temp.m_11=1;
          temp.m_22=1;
          m_uniformList[i]->setMat3(temp);
          break;
        }
        case GL_FLOAT_MAT4:
        {
          ngl::Mat4 temp;
          temp= shader->getUniformBlockIndex(m_uniformList[i]->getName());
          temp.m_00=1;
          temp.m_11=1;
          temp.m_22=1;
          temp.m_33=1;
          m_uniformList[i]->setMat4(temp);
          break;
        }
        default:
        {
          std::cout<<"unrecognised data type name"<<std::endl;
          break;
        }
      }
    }
  }
}

//------------------------------------------------------------------------------
void ParserLib::sendUniformsToShader(ngl::ShaderLib *_shader)
{

  // set shader values depending on it's data type
  for (uint i=0;i<m_num;i++)
  {
    switch(m_uniformList[i]->getTypeEnum())
    {
      case GL_BOOL:
      {
        _shader->setShaderParam1i(m_uniformList[i]->getName(),
                                  m_uniformList[i]->getBool());
        break;
      }
      case GL_FLOAT:
      {
        _shader->setShaderParam1f(m_uniformList[i]->getName(),
                                  m_uniformList[i]->getFloat());
        break;
      }
      case GL_INT:
      {
        _shader->setShaderParam1i(m_uniformList[i]->getName(),
                                  m_uniformList[i]->getInt());
        break;
      }
      case GL_FLOAT_VEC3:
      {
        ngl::Vec4 newVec3;
        newVec3.m_x=m_uniformList[i]->getVec3().m_x;
        newVec3.m_y=m_uniformList[i]->getVec3().m_y;
        newVec3.m_z=m_uniformList[i]->getVec3().m_z;
        newVec3.m_w=1;
        _shader->setShaderParamFromVec4(m_uniformList[i]->getName(),
                                        newVec3);
        break;
      }
      case GL_FLOAT_VEC4:
      {
        _shader->setShaderParamFromVec4(m_uniformList[i]->getName(),
                                        m_uniformList[i]->getVec4());
        break;
      }
      case GL_FLOAT_MAT3:
      {
        _shader->setShaderParamFromMat3(m_uniformList[i]->getName(),
                                        m_uniformList[i]->getMat3());
        break;
      }
      case GL_FLOAT_MAT4:
      {
        _shader->setShaderParamFromMat4(m_uniformList[i]->getName(),
                                        m_uniformList[i]->getMat4());
        break;
      }
      default:
      {
        std::cerr<<"unrecognised data type name"<<std::endl;
      }
    }

  }
}
