#include "NGLScene.h"
#include "ParserLib.h"
#include <iostream>
#include <ngl/Vec3.h>
#include <ngl/Camera.h>
#include <ngl/Light.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/Material.h>
#include <ngl/ShaderLib.h>
#include <iostream>
#include <typeinfo>
#include <QColorDialog>
#include <QString>

//----------------------------------------------------------------------------------------------------------------------
/// @brief the increment for x/y translation with mouse movement
//----------------------------------------------------------------------------------------------------------------------
const static float INCREMENT=0.01f;
//----------------------------------------------------------------------------------------------------------------------
/// @brief the increment for the wheel zoom
//----------------------------------------------------------------------------------------------------------------------
const static float ZOOM=0.1f;
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
NGLScene::NGLScene( QWidget *_parent ) : QOpenGLWidget( _parent )
{
  // re-size the widget to that of the parent (in that case the GLFrame passed in on construction)
  m_rotate=false;
  // mouse rotation values set to 0
  m_spinXFace=0.0f;
  m_spinYFace=0.0f;
  m_parser= new parserLib();
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  this->resize(_parent->size());
  m_wireframe=false;
  m_fov=65.0;
  m_newJson= new Json();
  // set this widget to have the initial keyboard focus
  setFocus();
}

//----------------------------------------------------------------------------------------------------------------------
NGLScene::~NGLScene()
{
  delete m_newJson;
  //delete m_readFromXML;
  delete m_parser;
}

//----------------------------------------------------------------------------------------------------------------------
// This virtual function is called once before the first call to paintGL() or resizeGL(),
// and then once whenever the widget has been assigned a new QGLContext.
// This function should set up any required OpenGL context rendering flags, defining display lists, etc.
//----------------------------------------------------------------------------------------------------------------------
void NGLScene::initializeGL()
{

  ngl::NGLInit::instance();
  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);

  // create our camera
  ngl::Vec3 eye(0,1,1);
  ngl::Vec3 look(0,0,0);
  ngl::Vec3 up(0,1,0);
  m_cam.set(eye,look,up);
  setCamShape();
  // now to load the shader and set the values
  // grab an instance of shader manager
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  // we are creating a shader called Phong
  shader->createShaderProgram("Phong"); //RENAME TO INPUT SHADER
  // now we are going to create empty shaders for Frag and Vert
  shader->attachShader("PhongVertex",ngl::ShaderType::VERTEX); //INPUTVERTEX
  shader->attachShader("PhongFragment",ngl::ShaderType::FRAGMENT); //INPUTSHADER
  // attach the source
  shader->loadShaderSource("PhongVertex","shaders/PhongVertex.glsl"); //NEEDS TO BE SHADERFROMTSTRING
  shader->loadShaderSource("PhongFragment","shaders/PhongFragment.glsl"); //NEEDS TO BE SHADERFROMSTRING
  // compile the shaders

  GLuint shaderTest= shader->getProgramID("PhongFragment");

  std::cout<<shaderTest<<std::endl;

  GLint success=0;

  glGetShaderiv(shaderTest,GL_COMPILE_STATUS, &success);


  shader->compileShader("PhongFragment");


  shader->compileShader("PhongVertex");

  shader->attachShaderToProgram("Phong","PhongVertex");
  shader->attachShaderToProgram("Phong","PhongFragment");

  // add them to the program

  // now bind the shader attributes for most NGL primitives we use the following
  // layout attribute 0 is the vertex data (x,y,z)
  shader->bindAttribute("Phong",0,"inVert");
  // attribute 1 is the UV data u,v (if present)
  shader->bindAttribute("Phong",1,"inUV");
  // attribute 2 are the normals x,y,z
  shader->bindAttribute("Phong",2,"inNormal");

  // now we have associated this data we can link the shader
  shader->linkProgramObject("Phong");
  // and make it active ready to load values
  (*shader)["Phong"]->use();
  shader->setShaderParam1i("Normalize",1);
  shader->setShaderParam3f("viewerPos",m_cam.getEye().m_x,m_cam.getEye().m_y,m_cam.getEye().m_z);
  // now pass the modelView and projection values to the shader
  // the shader will use the currently active material and light0 so set them
  ngl::Material m(ngl::STDMAT::GOLD );
  // load our material values to the shader into the structure material (see Vertex shader)
  m.loadToShader("material");
  // we need to set a base colour as the material isn't being used for all the params
  shader->setShaderParam4f("Colour",0.23125f,0.23125f,0.23125f,1);

  // now create our light this is done after the camera so we can pass the
  // transpose of the projection matrix to the light to do correct eye space
  // transformations
  ngl::Light light(ngl::Vec3(2,2,2),ngl::Colour(1,1,1,1),ngl::Colour(1,1,1,1),ngl::LightModes::POINTLIGHT);

  ngl::Mat4 iv=m_cam.getViewMatrix();
  iv.transpose();

  light.setTransform(iv);
  light.setAttenuation(1,0,0);
  light.enable();

  // load these values to the shader as well
  light.loadToShader("light");

  m_readFromXML->shaderData("WhyHelloThere", "PhongVertex", "shaders/PhongVertex.glsl", "PhongFragment", "shaders/PhongFragment.glsl");
  m_parser->assignAllData();
}
//----------------------------------------------------------------------------------------------------------------------
void NGLScene::exportUniforms()
{
  std::ofstream fileOut;
  fileOut.open("./tempFiles/ParsingOutput.txt");
  if(!fileOut.is_open())    ///If it can be opened
  {
    std::cerr<<"couldn't' open file\n";
    exit(EXIT_FAILURE);
  }
  for(uint i=0;i<m_parser->m_num;i++)
  {
    fileOut<<m_parser->m_uniformList[i]->getName()<<"\n";
    fileOut<<m_parser->m_uniformList[i]->getLocation()<<"\n";
    fileOut<<m_parser->m_uniformList[i]->getTypeName()<<"\n";
  }
  fileOut.close();
  // close files
  std::cout<<"EXPORTED\n"<<std::endl;
}



//----------------------------------------------------------------------------------------------------------------------
//This virtual function is called whenever the widget needs to be painted.
// this is our main drawing routine
//----------------------------------------------------------------------------------------------------------------------
void NGLScene::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if(m_wireframe == true)
  {
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  }
  else
  {
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  }

  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  (*shader)["Phong"]->use();

  // Rotation based on the mouse position for our global transform
  ngl::Mat4 rotX;
  ngl::Mat4 rotY;
  // create the rotation matrices
  rotX.rotateX(m_spinXFace);
  rotY.rotateY(m_spinYFace);
  // multiply the rotations
  m_mouseGlobalTX=rotY*rotX;
  // add the translations
  m_mouseGlobalTX.m_m[3][0] = m_modelPos.m_x;
  m_mouseGlobalTX.m_m[3][1] = m_modelPos.m_y;
  m_mouseGlobalTX.m_m[3][2] = m_modelPos.m_z;

  m_cam.setShape(m_fov, m_aspect, 0.5f, 150.0f);

  loadMatricesToShader();
  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
  prim->draw("teapot");


  m_text.reset(new ngl::Text(QFont ("Arial",18)));
  m_text->setScreenSize(width(),height());
  m_text->setColour(ngl::Colour (0.82,0.2,0.2));


  m_text->renderText(10,18,"Error!");
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::resizeGL(QResizeEvent *_event)
{
  setCamShape();
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::resizeGL(int _w, int _h)
{
  setCamShape();
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::loadMatricesToShader()
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  (*shader)["Phong"]->use();

  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  ngl::Mat4 M;

  M=m_mouseGlobalTX;
  MV=  M*m_cam.getViewMatrix();
  MVP= M*m_cam.getVPMatrix();
  normalMatrix=MV;
  normalMatrix.inverse();


  m_parser->sendUniformsToShader(shader);
  shader->setShaderParamFromMat4("MV",MV);
  shader->setShaderParamFromMat4("MVP",MVP);
  shader->setShaderParamFromMat3("normalMatrix",normalMatrix);
  shader->setShaderParamFromMat4("M",M);
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::setCamShape()
{
  m_aspect=(float)width()/height();
  m_cam.setShape(m_fov, m_aspect, 0.5f, 150.0f);
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // that method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quit
  //case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  // turn on wirframe rendering
  case Qt::Key_W : m_wireframe=true; break;
  // turn off wire frame
  case Qt::Key_S : m_wireframe=false; break;
  // show full screen
  case Qt::Key_F : showFullScreen(); break;
  // show windowed
  case Qt::Key_N : showNormal(); break;
  case Qt::Key_Space: m_parser->assignUniformValues();

  default : break;
  }
    update();
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseMoveEvent ( QMouseEvent * _event )
{
  if(m_rotate && _event->buttons() == Qt::LeftButton)
  {
    int diffx=_event->x()-m_origX;
    int diffy=_event->y()-m_origY;
    m_spinXFace += (float) 0.5f * diffy;
    m_spinYFace += (float) 0.5f * diffx;
    m_origX = _event->x();
    m_origY = _event->y();
    update();

  }
  // right mouse translate code
  else if(m_translate && _event->buttons() == Qt::RightButton)
  {
    int diffX = (int)(_event->x() - m_origXPos);
    int diffY = (int)(_event->y() - m_origYPos);
    m_origXPos=_event->x();
    m_origYPos=_event->y();
    m_modelPos.m_x += INCREMENT * diffX;
    m_modelPos.m_y -= INCREMENT * diffY;
    update();

   }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mousePressEvent ( QMouseEvent * _event )
{
  // that method is called when the mouse button is pressed in this case we
  // store the value where the maouse was clicked (x,y) and set the Rotate flag to true
  if(_event->button() == Qt::LeftButton)
  {
    m_origX = _event->x();
    m_origY = _event->y();
    m_rotate =true;
  }
  // right mouse translate mode
  else if(_event->button() == Qt::RightButton)
  {
    m_origXPos = _event->x();
    m_origYPos = _event->y();
    m_translate=true;
  }
  setFocus();
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseReleaseEvent ( QMouseEvent * _event )
{
  // that event is called when the mouse button is released
  // we then set Rotate to false
  if (_event->button() == Qt::LeftButton)
  {
    m_rotate=false;
  }
        // right mouse translate mode
  if (_event->button() == Qt::RightButton)
  {
    m_translate=false;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::wheelEvent ( QWheelEvent * _event )
{

  // check the diff of the wheel position (0 means no change)
  if(_event->delta() > 0)
  {
    m_modelPos.m_z+=ZOOM;
  }
  else if(_event->delta() < 0)
  {
    m_modelPos.m_z-=ZOOM;
  }
  update();
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::loadShader(QString _text, ngl::ShaderType _type)
{
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    GLuint shaderTest=shader->getProgramID("PhongFragment");
    GLint* success = new int;
    switch (_type)
    {
      case ngl::ShaderType::VERTEX:
        shader->loadShaderSourceFromString("PhongVertex", _text.toUtf8().constData());
        break;
      case ngl::ShaderType::FRAGMENT:
        shader->loadShaderSourceFromString("PhongFragment", _text.toUtf8().constData());
        break;
      default:
        std::cout << "Shader type not compatible\n";
    }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::compileShader()
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();

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
  shader->setShaderParam3f("viewerPos",m_cam.getEye().m_x,m_cam.getEye().m_y,m_cam.getEye().m_z);
  // now pass the modelView and projection values to the shader
  // the shader will use the currently active material and light0 so set them
  ngl::Material m(ngl::STDMAT::GOLD );
  // load our material values to the shader into the structure material (see Vertex shader)
  m.loadToShader("material");
  // we need to set a base colour as the material isn't being used for all the params
  shader->setShaderParam4f("Colour",0.23125f,0.23125f,0.23125f,1);

  ngl::Light light(ngl::Vec3(2,2,2),ngl::Colour(1,1,1,1),ngl::Colour(1,1,1,1),ngl::LightModes::POINTLIGHT);
  // now create our light this is done after the camera so we can pass the
  // transpose of the projection matrix to the light to do correct eye space
  // transformations
  ngl::Mat4 iv=m_cam.getViewMatrix();
  iv.transpose();

  light.setTransform(iv);
  light.setAttenuation(1,0,0);
  light.enable();
  // load these values to the shader as well
  light.loadToShader("light");

  update();
}
