#include "parserLib.h"

parserLib::parserLib()
{


}


parserLib::~parserLib()
{

}


void parserLib::listUniforms()
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  //shader->printRegisteredUniforms("Phong");
  GLuint id=shader->getProgramID("Phong");

  GLint nUniforms;
  glGetProgramInterfaceiv(id, GL_UNIFORM, GL_ACTIVE_RESOURCES, &nUniforms);
  m_num=nUniforms;
  m_passToGUI.resize(m_num);

  // declare some temp variables
  char UniformName[256];
  GLsizei length;
  GLint size;
  GLenum type;

  std::cout<<"#Adam's Uniforms#####Starts##########################################"<<std::endl;
  std::cout<<"---------------------------------------------------------------------"<<std::endl;
  std::cout<<"There are "<<m_num<<" Uniforms"<<std::endl;
  uniformData newData;
  for (GLuint i=0; i<nUniforms; i++)
  {
    glGetActiveUniform(id,i, 256, &length, &size , &type , UniformName);

    newData.locationUniforms= glGetUniformLocation(id,UniformName);
    newData.nameUniforms=UniformName ;
    newData.typeUniforms= type;
    m_registeredUniforms[UniformName]=newData;
    m_passToGUI[i]=newData;
    //    std::cout << "Name: "<<UniformName;
    //    std::cout << ";  Location: "<<m_passToGUI[i].locationUniforms<<" ("<<i<<")";
    //    std::cout << ";  Type: "<<m_passToGUI[i].typeUniforms<<std::endl;
    std::string str;
    const char * c = m_passToGUI[i].nameUniforms.c_str();
    GLenum newLoc;
    GLint newPosition=glGetProgramResourceLocation(id, GL_LOCATION,"phong") ;
    std::cout<<newPosition<<std::endl;
  }
  uniformDataTypes();

  for (uint i=0; i<nUniforms; i++)
  {

    std::cout << "Name: "<<m_passToGUI[i].nameUniforms;
    std::cout << ";  Location: "<<m_passToGUI[i].locationUniforms<<" ("<<i<<")";
    std::cout << ";  Type: "<<m_passToGUI[i].typeUniforms<<"; "<<m_passToGUI[i].dataType<<std::endl;



  }


    std::cout<<"-------------------------------------------------------------------"<<std::endl;
    std::cout<<"#Adam's Uniforms#####Ends##########################################"<<std::endl;


}

//JONS CODE!  //JONS CODE!  //JONS CODE!  //JONS CODE!

void parserLib::uniformDataTypes()
{
  std::cout<<"Started Uniforms" <<"\n";

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

  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  GLuint id=shader->getProgramID("Phong");

  GLint nUniforms;
  glGetProgramInterfaceiv(id, GL_UNIFORM, GL_ACTIVE_RESOURCES, &nUniforms);


  std::cout<<"Registered Uniforms for shader "<< id <<"\n";


  for(auto d : m_registeredUniforms)
  {
    std::string type;
    auto value=types.find(d.second.typeUniforms);
    if(value !=types.end())
    {
      type=value->second;
    }
    else
    {
      type="unknown type";
    }
    m_passToGUI[d.second.locationUniforms].dataType=type;
  }
  std::cout<<"End Uniforms" <<"\n";
}
//JONS CODE!  //JONS CODE!  //JONS CODE!  //JONS CODE!





void parserLib::exportUniforms()
{
  std::ofstream fileOut;
  fileOut.open("ParsingOutput.txt");
  if(!fileOut.is_open())    ///If it can be opened
  {
    std::cerr<<"couldn't' open file\n";
    exit(EXIT_FAILURE);
  }
  for(int i=0;i<m_num;i++)
  {
    fileOut<<m_passToGUI[i].nameUniforms<<"\n";
    fileOut<<m_passToGUI[i].locationUniforms<<"\n";
    fileOut<<m_passToGUI[i].dataType<<"\n";
  }
  fileOut.close();
  // close files
  std::cout<<"EXPORTED\n"<<std::endl;
}

