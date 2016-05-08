
#include "ngl/Light.h"
#include "ngl/Material.h"
#include "ngl/Texture.h"

#include "ShaderManager.h"

//------------------------------------------------------------------------------------------------------------------------

ShaderManager::ShaderManager()
{
  m_data.m_name = "untitled";
  m_data.m_vert = "";
  m_data.m_frag = "";
  m_init = false;
}

//------------------------------------------------------------------------------------------------------------------------

void ShaderManager::createShaderProgram(std::string _name)
{
  //set our data
  setData(_name, _name+"Vertex", _name+"Fragment");
  //grab an instance of the shader lib
  ngl::ShaderLib *shaderLib = ngl::ShaderLib::instance();
  //create an empty shader program
  shaderLib->createShaderProgram(_name);
  //create empty shader objects for vertex and fragment shaders
  shaderLib->attachShader(m_data.m_vert, ngl::ShaderType::VERTEX);
  shaderLib->attachShader(m_data.m_frag, ngl::ShaderType::FRAGMENT);
  //attach empty shader objects to the shader program
  shaderLib->attachShaderToProgram(m_data.m_name, m_data.m_vert);
  shaderLib->attachShaderToProgram(m_data.m_name, m_data.m_frag);

  shaderLib->bindAttribute(m_data.m_name,0,"inVert");
  // attribute 1 is the UV data u,v (if present)
  shaderLib->bindAttribute(m_data.m_name,1,"inUV");
  // attribute 2 are the normals x,y,z
  shaderLib->bindAttribute(m_data.m_name,2,"inNormal");

  use(0);
}

//------------------------------------------------------------------------------------------------------------------------

void ShaderManager::use(uint _shaderType)
{
  //grab an instance of shaderLib
  ngl::ShaderLib *shaderLib = ngl::ShaderLib::instance(); 
  enum shader{objectShader=0,objectNormals=1};
  //choose which shader to use
  switch(_shaderType)
  {
    case objectShader :  {  shaderLib->use(m_data.m_name); break;  }
    case objectNormals:  {  (*shaderLib)["normalShader"]->use();break;  }
    default:               std::cerr<<"Invalid shaderType"<<std::endl; break;
  }
}

//------------------------------------------------------------------------------------------------------------------------

void ShaderManager::initialize()
{
  //set our data
  setData("Phong", "PhongVertex", "PhongFragment");
  //grab an instance of shader manager
  ngl::ShaderLib *shaderLib=ngl::ShaderLib::instance();
  //create an empty shader program called Phong
  shaderLib->createShaderProgram("Phong");
  // create and empty shader objects from fragment and vertex shaders
  shaderLib->attachShader("PhongVertex",ngl::ShaderType::VERTEX);
  shaderLib->attachShader("PhongFragment",ngl::ShaderType::FRAGMENT);
  // load the source code to the shader objects
  shaderLib->loadShaderSource("PhongVertex","shaders/PhongVertex.glsl");
  shaderLib->loadShaderSource("PhongFragment","shaders/PhongFragment.glsl");
  // compile the shaders
  shaderLib->compileShader("PhongFragment");
  shaderLib->compileShader("PhongVertex");

  // check if the shader compiled successfully
  if (!checkAllCompileError(&m_errorLog))
  {
    // output code errors to user
    std::cout << m_errorLog.toUtf8().constData();
    m_compileStatus = false;
    std::cout<<"Initial Program compilation fail"<<std::endl;
  }
  else
  {
    // user's code has no errors, will now be attached to program
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
    shaderLib->use(m_data.m_name);

    /// The following section is from :-
    /// Jon Macey (2016) AffineTransforms [online]. [Accessed 2016].
    /// Available from: <https://github.com/NCCA/AffineTransforms>.
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
    ///End of Citation


    // set initialise flag to true
    m_init = true;
  }
}

//----------------------------------------------------------------------------------------------------------------------

void ShaderManager::compileShader(QString _vertSource, QString _fragSource)
{
  //clear the error log
  m_errorLog.clear();
  //grab an instance of the shader lib
  ngl::ShaderLib *shaderLib=ngl::ShaderLib::instance();

  // convert from QString to std::string for compiling
  shaderLib->loadShaderSourceFromString(m_data.m_vert, _vertSource.toStdString());
  shaderLib->loadShaderSourceFromString(m_data.m_frag, _fragSource.toStdString());

  // compile shaders
  shaderLib->compileShader(m_data.m_vert);
  shaderLib->compileShader(m_data.m_frag);

  //check for compile errors
  if (!checkAllCompileError(&m_errorLog))
  {
    // output any compile errors to user
    std::cout << m_errorLog.toUtf8().constData();
    m_compileStatus = false;
  }
  else
  {
    m_compileStatus = true;
    m_errorLog.append("No Errors");
    // add them to the program
    shaderLib->attachShaderToProgram(m_data.m_name,m_data.m_vert);
    shaderLib->attachShaderToProgram(m_data.m_name,m_data.m_frag);

    // now we have associated this data we can link the shader
    shaderLib->linkProgramObject(m_data.m_name);

    // use the shader program
    (*shaderLib)[m_data.m_name]->use();
    ngl::Texture texture("textures/rustTexture.jpg");
    m_textureName=texture.setTextureGL();
  }
}

//------------------------------------------------------------------------------------------------------------------------

bool ShaderManager::checkCompileError(std::string _shaderName, QString *o_log)
{
  GLint isCompiled = 0;
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  GLuint shaderId = shader->getShaderID(_shaderName);

  // Get compile status of shader
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
  if(isCompiled == GL_FALSE)
  {
    // Receive info log
    GLint maxLength = 0;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> errorLog(maxLength);
    glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);

    //  Write error log to an std::string to be output at QString
    std::string s(errorLog.begin(), errorLog.end());

    QString errLog = QString(s.c_str());

    *o_log = errLog;

    // Provide the infolog in whatever manor you deem best.
    //throw ceb_error::openGL_list_error(_shaderProgName, errLog);
  }
  return isCompiled;
}

//------------------------------------------------------------------------------------------------------------------------

bool ShaderManager::checkAllCompileError(QString *o_log)
{
  GLint isAllCompiled = GL_TRUE;
  QString temp_log;
  std::vector <std::string> shaderPrograms = {m_data.m_vert, m_data.m_frag};

  // Iterate between vertex and fragment shaders to check compile errors
  for (auto shaderProg: shaderPrograms)
  {
    GLint isCompiled = checkCompileError(shaderProg, &temp_log);
    if (!isCompiled)
    {
      o_log->append(QString("%1:\n").arg(shaderProg.c_str()));
      o_log->append(temp_log);
    }
    isAllCompiled &= isCompiled;
  }
  return isAllCompiled;
}
