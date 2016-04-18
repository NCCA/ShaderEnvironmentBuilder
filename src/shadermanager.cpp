#include "include/shadermanager.h"
#include "ngl/Light.h"


ShaderManager::ShaderManager()
{

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
  shader->bindAttribute(_name,0,"inVert");
  // attribute 1 is the UV data u,v (if present)
  shader->bindAttribute(_name,1,"inUV");
  // attribute 2 are the normals x,y,z
  shader->bindAttribute(_name,2,"inNormal");

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
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
  (*shader)[_name]->use();
}

void ShaderManager::initialize(ngl::ShaderLib *shaderLib)
{
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();

  //create a default phong shader
  shader->createShaderProgram("Phong");
  //create empty default shaders
  shader->attachShader("PhongVertex",ngl::ShaderType::VERTEX);
  shader->attachShader("PhongFragment",ngl::ShaderType::FRAGMENT);
  //load shader source
  shader->loadShaderSource("PhongVertex","shaders/PhongVertex.glsl");
  shader->loadShaderSource("PhongFragment","shaders/PhongFragment.glsl");
  shader->compileShader("PhongVertex");
  shader->compileShader("PhongFragment");

  // add them to the program
  shader->attachShaderToProgram("Phong","PhongVertex");
  shader->attachShaderToProgram("Phong","PhongFragment");

  // now we have associated this data we can link the shader
  shader->linkProgramObject("Phong");
  std::cout<<"created phong default"<<std::endl;
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderManager::loadShader(QString vertSource, QString fragSource)
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  shader->loadShaderSourceFromString("PhongVertex", vertSource.toStdString());
  shader->loadShaderSourceFromString("PhongFragment", fragSource.toStdString());
}

//----------------------------------------------------------------------------------------------------------------------
void ShaderManager::compileShader(ngl::Camera _cam, QString vertSource, QString fragSource)
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();

  shader->loadShaderSourceFromString("PhongVertex", vertSource.toStdString());
  shader->loadShaderSourceFromString("PhongFragment", fragSource.toStdString());

  // compile shaders
  shader->compileShader("PhongVertex");
  shader->compileShader("PhongFragment");

  // add them to the program
  shader->attachShaderToProgram("Phong","PhongVertex");
  shader->attachShaderToProgram("Phong","PhongFragment");

  // now we have associated this data we can link the shader
  shader->linkProgramObject("Phong");

  // Load stuff. Need to remove this stuff in the next build, just used to set
  // inital values
  (*shader)["Phong"]->use();
  shader->setShaderParam1i("Normalize",1);
  shader->setShaderParam3f("viewerPos",_cam.getEye().m_x,_cam.getEye().m_y,_cam.getEye().m_z);
  // now pass the modelView and projection values to the shader
  // the shader will use the currently active material and light0 so set them
  //ngl::Material m(ngl::STDMAT::GOLD );
  // load our material values to the shader into the structure material (see Vertex shader)
  //m.loadToShader("material");
  // we need to set a base colour as the material isn't being used for all the params
  shader->setShaderParam4f("Colour",0.23125f,0.23125f,0.23125f,1);

  ngl::Light light(ngl::Vec3(2,2,2),ngl::Colour(1,1,1,1),ngl::Colour(1,1,1,1),ngl::LightModes::POINTLIGHT);
  // now create our light this is done after the camera so we can pass the
  // transpose of the projection matrix to the light to do correct eye space
  // transformations
  ngl::Mat4 iv=_cam.getViewMatrix();
  iv.transpose();

  light.setTransform(iv);
  light.setAttenuation(1,0,0);
  light.enable();
  // load these values to the shader as well
  light.loadToShader("light");
}
