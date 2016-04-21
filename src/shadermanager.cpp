#include "include/shadermanager.h"
#include "ngl/Light.h"
#include "ngl/Material.h"


ShaderManager::ShaderManager()
{
  m_init = false;
}

void ShaderManager::createShaderProgram(std::string _name, QString _sourceVert, QString _sourceFrag)
{
  ngl::ShaderLib *shaderLib = ngl::ShaderLib::instance();
  std::string sourceVert = _sourceVert.toStdString();
  std::string sourceFrag = _sourceFrag.toStdString();

  shaderLib->attachShader(_name+"Vertex", ngl::ShaderType::VERTEX);
  shaderLib->attachShader(_name+"Fragment", ngl::ShaderType::FRAGMENT);
  shaderLib->loadShaderSource(_name+"Vertex", sourceVert);
  shaderLib->loadShaderSource(_name+"Fragment", sourceFrag);

  shaderLib->compileShader(_name+"Vertex");
  shaderLib->compileShader(_name+"Fragment");
  shaderLib->attachShaderToProgram(_name,_name+"Vertex");
  shaderLib->attachShaderToProgram(_name,_name+"Fragment");

  // now bind the shader attributes for most NGL primitives we use the following
  // layout attribute 0 is the vertex data (x,y,z)
  shaderLib->bindAttribute(_name,0,"inVert");
  // attribute 1 is the UV data u,v (if present)
  shaderLib->bindAttribute(_name,1,"inUV");
  // attribute 2 are the normals x,y,z
  shaderLib->bindAttribute(_name,2,"inNormal");

  shaderLib->linkProgramObject(_name);

}

void ShaderManager::updateShaderProgram(std::string _name, QString _sourceVert, QString _sourceFrag)
{
  ngl::ShaderLib *shaderLib = ngl::ShaderLib::instance();

  // create a pointer to the vertex shader attached to the current shader program
  ngl::Shader* shader = shaderLib->getShader(_name+"Vertex");
  // update the shader with the QString from the text editor
  shader->loadFromString(_sourceVert.toStdString());

  // create a pointer to the fragment shader attached to the current shader program
  shader = shaderLib->getShader(_name+"Fragment");
  // update the shader with the QString from the text editor
  shader->loadFromString(_sourceFrag.toStdString());

  // compile the updated shaders
  shaderLib->compileShader(_name+"Vertex");
  shaderLib->compileShader(_name+"Fragment");

  // now link the shaderProgram
  shaderLib->linkProgramObject(_name);
}

void ShaderManager::use(std::string _name)
{
  ngl::ShaderLib *shaderLib = ngl::ShaderLib::instance();
  (*shaderLib)[_name]->use();
}

void ShaderManager::initialize(ngl::Camera _cam)
{
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

  std::vector<std::string> programs = {"PhongFragment", "PhongVertex"};

  if (!checkAllCompileError(programs, &m_errorLog))
  {
    std::cout << m_errorLog.toUtf8().constData();
    m_compileStatus = false;
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

    // set initialise flag to true
    m_init = true;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderManager::loadShader(QString vertSource, QString fragSource)
{
  ngl::ShaderLib *shaderLib=ngl::ShaderLib::instance();
  shaderLib->loadShaderSourceFromString("PhongVertex", vertSource.toStdString());
  shaderLib->loadShaderSourceFromString("PhongFragment", fragSource.toStdString());
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderManager::compileShader(ngl::Camera _cam, QString vertSource, QString fragSource)
{
  ngl::ShaderLib *shaderLib=ngl::ShaderLib::instance();

  shaderLib->loadShaderSourceFromString("PhongVertex", vertSource.toStdString());
  shaderLib->loadShaderSourceFromString("PhongFragment", fragSource.toStdString());

  // compile shaders
  shaderLib->compileShader("PhongVertex");
  shaderLib->compileShader("PhongFragment");

  std::vector<std::string> programs = {"PhongFragment", "PhongVertex"};

  if (!checkAllCompileError(programs, &m_errorLog))
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

bool ShaderManager::checkAllCompileError(std::vector<std::string> _shaderProgNames, QString *o_log)
{
  GLint isCompiled = GL_TRUE;
  QString temp_log;
  for (auto shaderProg: _shaderProgNames)
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
