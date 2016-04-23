#include "NGLScene.h"
#include "ParserLib.h"
#include "CebErrors.h"
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

bool checkCompileError(std::string _shaderProgName, QString *o_log)
{
  GLint isCompiled = 0;
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();

  GLuint shaderId = shader->getShaderID(_shaderProgName);
  //Using modified NGL to query ID of given shader


  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
  if(isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
    //Compile failed, accessing information of error

    // The maxLength includes the NULL character
    std::vector<GLchar> errorLog(maxLength);
    glGetShaderInfoLog(shaderId, maxLength, &maxLength, &errorLog[0]);

    std::string s(errorLog.begin(), errorLog.end());

    QString errLog = QString(s.c_str());
    //Convert to QString to output in IDE
    *o_log = errLog;

    // Provide the infolog in whatever manor you deem best.
    //throw ceb_error::openGL_list_error(_shaderProgName, errLog);
  }
  return isCompiled;
}

bool checkAllCompileError(std::vector<std::string> _shaderProgNames, QString *o_log)
{
  //Traverses std::vector to check compilation
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


//----------------------------------------------------------------------------------------------------------------------
NGLScene::NGLScene( QWidget *_parent, parserLib *_libParent ) : QOpenGLWidget( _parent )
{
  // re-size the widget to that of the parent (in that case the GLFrame passed in on construction)
  m_rotate=false;
  // mouse rotation values set to 0
  m_spinXFace=0.0f;
  m_spinYFace=0.0f;
  m_parser= new parserLib();
  m_shapeType=6;
  toggle=false;
  m_meshLoc="./tempFiles/strawberry.obj";

  // Store main window to send data from compile errors
  m_window = dynamic_cast<MainWindow*>(_parent);
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  this->resize(_parent->size());
  m_wireframe=false;
  m_fov=65.0;
  m_newJson= new Json();
  m_shaderManager = new ShaderManager();
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
void NGLScene::setMeshLocation(std::string _meshDirectory)
{
  m_meshLoc=_meshDirectory;
  std::cout<<"Imported file:  "<<_meshDirectory<<std::endl;
}

void NGLScene::toggleFunc()
{
  if(toggle==true)
  {
    m_mesh = std::unique_ptr<ngl::Obj> (new ngl::Obj(m_meshLoc));
    m_mesh->createVAO();
    toggle=false;
  }

}

void NGLScene::importMeshName(const std::string &name)
{
  // If the CANCEL button is clicked, then don't update the shapetype or location
  std::ifstream shaderSource(name.c_str());
  if (!shaderSource.is_open())
  {
    if(name.length()==0)
    {
      std::cerr<<"Import Cancelled"<<std::endl;
      //exit(EXIT_FAILURE);
    }
    else
    {
      std::cerr<<"File not found"<<name.c_str()<<std::endl;
      //exit(EXIT_FAILURE);
    }
  }
  else
  {
    setMeshLocation(name);
    setShapeType(0);
    toggle=true;
  }

}

//----------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------
// This virtual function is called once before the first call to paintGL() or resizeGL(),
// and then once whenever the widget has been assigned a new QGLContext.
// This function should set up any required OpenGL context rendering flags, defining display lists, etc.
//----------------------------------------------------------------------------------------------------------------------
void NGLScene::initializeGL()
{
  ngl::NGLInit::instance();
  clearAllGlErrors();

  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);

  // create our camera
  ngl::Vec3 eye(2,0.5,2);
  ngl::Vec3 look(0,0,0);
  ngl::Vec3 up(0,1,0);
  m_cam.set(eye,look,up);
  setCameraShape();
  // now to load the shader and set the values
  // grab an instance of shader manager
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  m_shaderManager->initialize(m_cam);
  if(!m_shaderManager->compileStatus())
  {
    m_window->setTerminalText(m_shaderManager->getErrorLog());
  }
  if(m_shaderManager->isInit())
  {
    //now create our light this is done after the camera so we can pass the
    //transpose of the projection matrix to the light to do correct eye space
    //transformations
    ngl::Light light(ngl::Vec3(2,2,2),ngl::Colour(1,1,1,1),ngl::Colour(1,1,1,1),ngl::LightModes::POINTLIGHT);

    ngl::Mat4 iv=m_cam.getViewMatrix();
    iv.transpose();

    light.setTransform(iv);
    light.setAttenuation(1,0,0);
    light.enable();

    //load these values to the shader as well
    light.loadToShader("light");

    m_readFromXML->shaderData("WhyHelloThere", "PhongVertex", "shaders/PhongVertex.glsl", "PhongFragment", "shaders/PhongFragment.glsl");
    m_parser->assignAllData();
    std::cerr<<"Find number of active uniforms: "<<m_parser->m_num<<std::endl;
    light.loadToShader("light");
  }


  // load these values to the shader as well

  m_readFromXML->shaderData("WhyHelloThere", "PhongVertex", "shaders/PhongVertex.glsl", "PhongFragment", "shaders/PhongFragment.glsl");
  m_parser->assignAllData();

  m_mesh = std::unique_ptr<ngl::Obj> (new ngl::Obj("./tempFiles/Frog.obj"));
  m_mesh->createVAO();

  ngl::VAOPrimitives::instance()->createSphere("sphere",0.7,20);
  ngl::VAOPrimitives::instance()->createTorus("torus",0.3,0.7,20,20);
  ngl::VAOPrimitives::instance()->createLineGrid("Grid",10,10,10);

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

void NGLScene::setShapeType(int _type)
{
  if (_type<=7)
  {
    m_shapeType=_type;
    std::cout<<"new shape type is :"<<_type<<std::endl;
  }
  else
  {
    std::cout<<"Invalid shape type"<<std::endl;
  }
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
  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();

  m_cam.setShape(m_fov, m_aspect, 0.5f, 150.0f);
  m_transform.reset();


  if (toggle)
   toggleFunc();


  loadMatricesToShader();
  drawObject(m_shapeType);
}

void NGLScene::drawObject(uint _type)
{
  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();

  enum geo {input=0,sphere=1,cube=2,torus=3,teapot=4,troll=5,dragon=6,bunny=7};
  switch(_type)
  {
    case input : m_mesh->draw();break;
    case sphere: prim->draw("sphere");break;
    case cube  : prim->draw("cube");break;
    case torus : prim->draw("torus");break;
    case teapot: prim->draw("teapot");break;
    case troll :
    {
      m_transform.setScale(1.5,1.5,1.5);
      loadMatricesToShader();
      prim->draw("troll");
      m_transform.reset();
      break;
      // Moved the troll to be the same relative shape and position as other vaoprimitive objects
    }
    case dragon:
    {
      m_transform.setScale(0.1,0.1,0.1);
      m_transform.setPosition(0,-0.5,0);
      loadMatricesToShader();
      prim->draw("dragon");
      m_transform.reset();
      break;
      // Moved the dragon to be the same relative shape and position as other vaoprimitive objects
    }
    case bunny:
    {
      m_transform.setScale(0.15,0.15,0.15);
      m_transform.setPosition(0,-0.5,0);
      loadMatricesToShader();
      prim->draw("bunny");
      m_transform.reset();
      break;
      // Moved the bunny to be the same relative shape and position as other vaoprimitive objects
    }
    default: std::cout<<"unrecognised shape type value"<<std::endl; break;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::resizeGL(QResizeEvent *_event)
{
  setCameraShape();
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::resizeGL(int _w, int _h)
{
  setCameraShape();
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

  M=m_transform.getMatrix()*m_mouseGlobalTX;
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
void NGLScene::setCameraShape()
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
  // turn on wireframe rendering
  case Qt::Key_W : m_wireframe=true; break;
  // turn off wire frame
  case Qt::Key_S : m_wireframe=false; break;
  // show full screen
  case Qt::Key_F : showFullScreen(); break;
  // show windowed
  case Qt::Key_N : showNormal(); break;
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
    ngl::Vec4 _tempVec=m_parser->m_uniformList[12]->getVec4();
    std::cout<<"\nVal:\nx: "<<_tempVec.m_x<<"\ny: "<<_tempVec.m_y<<"\nz:"<<_tempVec.m_z<<std::endl;
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
  update();
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
void NGLScene::compileShader(QString vertSource, QString fragSource)
{
  m_shaderManager->compileShader(m_cam, vertSource, fragSource);
  std::cout<<"before status: "<<m_shaderManager->compileStatus()<<std::endl;
  if(!m_shaderManager->compileStatus())
  {
    m_window->setTerminalText(parseString(m_shaderManager->getErrorLog()));
  }
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

}



//------------------------------------------------------------------
QString NGLScene::parseString(QString _string)
{

  QString outString;
  QRegExp separateLines("\n");
  QStringList lines=_string.split(separateLines);
  uint len=lines.length();
  for (uint i=0;i<len;i++)
  {
    QRegExp separateNumbers("(\\(|\\))");
    QStringList pieces=lines.value(i).split(separateNumbers);
    uint nLen=pieces.length();
    for (uint j=0;j<nLen;j++)
    {
      if(pieces[j]=="0")
      {
        outString.append("Line ");
      }
      if(pieces[j]!="0")
      {
        outString.append(pieces.value(j));
      }
    }
    if (i!=len-1)
    {
      outString.append("\n");
    }
  }
  return outString;
}

void NGLScene::resetObjPos()
{
  //reset object position back to default
  m_modelPos.m_x = 0;
  m_modelPos.m_y = 0;
  m_modelPos.m_z = 0;
  m_spinXFace = 0;
  m_spinYFace = 0;
}
