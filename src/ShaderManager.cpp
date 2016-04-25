#include "include/ShaderManager.h"
#include "ngl/Light.h"
#include "ngl/Material.h"

ShaderManager::ShaderManager()
{
  m_data.m_name = "untitled";
  m_data.m_vert = "";
  m_data.m_frag = "";
  m_init = false;
}

void ShaderManager::createShaderProgram(std::string _name)
{
  ngl::ShaderLib *shaderLib = ngl::ShaderLib::instance();

  shaderLib->createShaderProgram(_name);
  shaderLib->attachShader(_name+"Vertex", ngl::ShaderType::VERTEX);
  shaderLib->attachShader(_name+"Fragment", ngl::ShaderType::FRAGMENT);

  setData(_name, _name.append("Vertex"), _name.append("fragment"));
}

void ShaderManager::use(ngl::ShaderLib *_shader,uint shaderType)
{
  enum shader{objectShader=0,objectNormals=1};
  switch(shaderType)
  {
    case objectShader :    (*_shader)[m_data.m_name]->use(); break;
    case objectNormals:    (*_shader)["normalShader"]->use();break;
    default:               std::cerr<<"Invalid shaderType"<<std::endl; break;
  }
}



void ShaderManager::initialize(ngl::Camera _cam)
{
  //set our data
  setData("Phong", "PhongVertex", "PhongFragment");
  //grab an instance of shader manager
  ngl::ShaderLib *shaderLib=ngl::ShaderLib::instance();
  //we are creating a shader called Phong
  shaderLib->createShaderProgram("Phong"); //RENAME TO INPUT SHADER
  // now we are going to create empty shaders for Frag and Vert
  shaderLib->attachShader("PhongVertex",ngl::ShaderType::VERTEX); //INPUTVERTEX
  shaderLib->attachShader("PhongFragment",ngl::ShaderType::FRAGMENT); //INPUTSHADER
  // attach the source
  shaderLib->loadShaderSource("PhongVertex","shaders/PhongVertex.glsl"); //NEEDS TO BE SHADERFROMTSTRING
  shaderLib->loadShaderSource("PhongFragment","shaders/PhongFragment.glsl"); //NEEDS TO BE SHADERFROMSTRING
  // compile the shaders
  shaderLib->compileShader("PhongFragment");
  shaderLib->compileShader("PhongVertex");

  if (!checkAllCompileError(&m_errorLog))
  {
    std::cout << m_errorLog.toUtf8().constData();
    m_compileStatus = false;
    std::cout<<"Initial Program compilation fail"<<std::endl;
  }
  else
  {
    m_compileStatus = true;
    shaderLib->attachShaderToProgram("Phong","PhongVertex");
    shaderLib->attachShaderToProgram("Phong","PhongFragment");
    // now bind the shader attributes for most NGL primitives we use the following
    // layout attribute 0 is the vertex data (x,y,z)
    shaderLib->bindAttribute("Phong",0,"inVert");
    // attribute 1 is the UV data u,v (if present)
    shaderLib->bindAttribute("Phong",1,"inUV");
    // attribute 2 are the normals x,y,z
    shaderLib->bindAttribute("Phong",2,"inNormal");
    // now we have associated this data we can link the shader
    shaderLib->linkProgramObject("Phong");
    // and make it active ready to load values
    (*shaderLib)["Phong"]->use();
    shaderLib->setShaderParam1i("Normalize",1);
    shaderLib->setShaderParam3f("viewerPos",_cam.getEye().m_x,_cam.getEye().m_y,_cam.getEye().m_z);
    shaderLib->setShaderParam4f("Colour",0.23125f,0.23125f,0.23125f,1);

    // Johns Code to initialise NORMALSHADER
    shaderLib->createShaderProgram("normalShader");
    constexpr auto normalVert="normalVertex";
    constexpr auto normalGeo="normalGeo";
    constexpr auto normalFrag="normalFrag";
    shaderLib->attachShader(normalVert,ngl::ShaderType::VERTEX);
    shaderLib->attachShader(normalFrag,ngl::ShaderType::FRAGMENT);
    shaderLib->loadShaderSource(normalVert,"shaders/normalVertex.glsl");
    shaderLib->loadShaderSource(normalFrag,"shaders/normalFragment.glsl");
    shaderLib->compileShader(normalVert);
    shaderLib->compileShader(normalFrag);
    shaderLib->attachShaderToProgram("normalShader",normalVert);
    shaderLib->attachShaderToProgram("normalShader",normalFrag);
    shaderLib->attachShader(normalGeo,ngl::ShaderType::GEOMETRY);
    shaderLib->loadShaderSource(normalGeo,"shaders/normalGeo.glsl");
    shaderLib->compileShader(normalGeo);
    shaderLib->attachShaderToProgram("normalShader",normalGeo);
    shaderLib->linkProgramObject("normalShader");
    shaderLib->use("normalShader");
    // now pass the modelView and projection values to the shader
    shaderLib->setUniform("normalSize",0.1f);
    shaderLib->setUniform("vertNormalColour",1.0f,1.0f,0.0f,1.0f);
    shaderLib->setUniform("faceNormalColour",.0f,1.0f,0.0f,1.0f);
    shaderLib->setShaderParam1i("drawFaceNormals",true);
    shaderLib->setShaderParam1i("drawVertexNormals",true);




    // set initialise flag to true
    m_init = true;
  }




}


//----------------------------------------------------------------------------------------------------------------------
void ShaderManager::compileShader(ngl::Camera _cam, QString vertSource, QString fragSource)
{
  ngl::ShaderLib *shaderLib=ngl::ShaderLib::instance();

  std::cout<< "name " << m_data.m_name << "\n";
  std::cout<< "vert " << m_data.m_vert << "\n";
  std::cout<< "frag " << m_data.m_frag << "\n";
  shaderLib->loadShaderSourceFromString(m_data.m_vert, vertSource.toStdString());
  shaderLib->loadShaderSourceFromString(m_data.m_frag, fragSource.toStdString());

  // compile shaders
  shaderLib->compileShader(m_data.m_vert);
  shaderLib->compileShader(m_data.m_frag);

  if (!checkAllCompileError(&m_errorLog))
  {
    std::cout << m_errorLog.toUtf8().constData();
    m_compileStatus = false;
  }
  else
  {
    m_compileStatus = false;
    // add them to the program
    shaderLib->attachShaderToProgram("Phong","PhongVertex");
    shaderLib->attachShaderToProgram("Phong","PhongFragment");

    // now we have associated this data we can link the shader
    shaderLib->linkProgramObject("Phong");

    // Load stuff. Need to remove this stuff in the next build, just used to set
    // inital values
    (*shaderLib)["Phong"]->use();
    shaderLib->setShaderParam1i("Normalize",1);
    shaderLib->setShaderParam3f("viewerPos",_cam.getEye().m_x,_cam.getEye().m_y,_cam.getEye().m_z);
    // we need to set a base colour as the material isn't being used for all the params
    shaderLib->setShaderParam4f("Colour",0.23125f,0.23125f,0.23125f,1);
  }
}


bool ShaderManager::checkCompileError(std::string _shaderProgName, QString *o_log)
{
  GLint isCompiled = 0;
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  GLuint shaderId = shader->getShaderID(_shaderProgName);

  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
  if(isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> errorLog(maxLength);
    glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);

    std::string s(errorLog.begin(), errorLog.end());

    QString errLog = QString(s.c_str());

    *o_log = errLog;

    // Provide the infolog in whatever manor you deem best.
    //throw ceb_error::openGL_list_error(_shaderProgName, errLog);
  }
  return isCompiled;
}

bool ShaderManager::checkAllCompileError(QString *o_log)
{
  GLint isCompiled = GL_TRUE;
  QString temp_log;
  std::vector <std::string> shaderPrograms = {m_data.m_vert, m_data.m_frag};
  for (auto shaderProg: shaderPrograms)
  {
    isCompiled &= checkCompileError(shaderProg, &temp_log);
    if (!isCompiled)
    {
      o_log->append(QString("%1:\n").arg(shaderProg.c_str()));
      o_log->append(temp_log);
    }
  }
  return isCompiled;
}
