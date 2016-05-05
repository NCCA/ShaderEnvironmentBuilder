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
#include <ngl/Texture.h>

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
  m_parser= _libParent; //DONT CHANGE THIS
  m_shapeType=6;
  m_toggleObj=false;
  m_meshLoc="./tempFiles/strawberry.obj";
  m_drawNormals=false;
  m_drawGrid=false;
  m_normalSize=0.1;
  // Store main window to send data from compile errors
  m_window = dynamic_cast<MainWindow*>(_parent);
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  this->resize(_parent->size());
  m_wireframe=false;
  m_fov=65.0;
  m_shaderManager = new ShaderManager();
  m_camera = new Camera();
  m_cameraIndex = 0;
  // set this widget to have the initial keyboard focus
  setFocus();
}

//----------------------------------------------------------------------------------------------------------------------
NGLScene::~NGLScene()
{
  //delete m_readFromXML;
  delete m_parser;
  delete m_shaderManager;
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::setMeshLocation(std::string _meshDirectory)
{
  m_meshLoc=_meshDirectory;
  std::cout<<"Imported file:  "<<_meshDirectory<<std::endl;
}

void NGLScene::toggleObj()
{
  if(m_toggleObj==true)
  {
    m_mesh = std::unique_ptr<ngl::Obj> (new ngl::Obj(m_meshLoc));
    m_mesh->createVAO();
    m_toggleObj=false;
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
    m_toggleObj=true;
  }


  //clear all loaded textures
  glDeleteTextures(1,&m_textureName);
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

  m_cameras = m_camera->createCamera();  //returns vector of cameras
  // now to load the shader and set the values
  // grab an instance of shader manager
  m_shaderManager->initialize(m_cameras[m_cameraIndex]);

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

    ngl::Mat4 iv=m_cameras[m_cameraIndex].getViewMatrix();
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

  // Create
  m_mesh = std::unique_ptr<ngl::Obj> (new ngl::Obj(m_meshLoc));
  m_mesh->createVAO();

  // Create some default shapes
  ngl::VAOPrimitives::instance()->createSphere("sphere",0.7,30);
  ngl::VAOPrimitives::instance()->createTorus("torus",0.3,0.7,20,20);
  ngl::VAOPrimitives::instance()->createLineGrid("Grid",10,10,10);

}

void NGLScene::setShapeType(int _type)
{
  if (_type<=7 && _type>=0)
  {
    m_shapeType=_type;
    std::cout<<"new shape type is :"<<_type<<std::endl;
  }
  // Don't update if
  else
  {
    std::cout<<"Invalid shape type"<<std::endl;
  }
  update();
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
  ngl::ShaderLib *shaderLib=ngl::ShaderLib::instance();

  m_shaderManager->use(shaderLib,0);

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

  m_cameras[m_cameraIndex].setShape(m_fov, m_aspect, 0.5f, 150.0f);
  m_transform.reset();
  ngl::Vec3 pos(-1,-0.5,-1);
  drawAxis(pos);
  loadMatricesToShader();

  if (m_drawGrid)
  {
    // Draw a grid
    prim->draw("Grid");
  }
  if (m_toggleObj)
  {
    // Activate Obj
    toggleObj();
  }

  // Set object transformation and draw
  objectTransform(m_shapeType);
  drawObject(m_shapeType);
  if(m_drawNormals)
  {
    // set the shader to use the normalShader
    m_shaderManager->use(shaderLib,1);
    ngl::Mat4 MV;
    ngl::Mat4 MVP;
    MV=m_transform.getMatrix()*m_mouseGlobalTX* m_cameras[m_cameraIndex].getViewMatrix();
    MVP=MV*m_cameras[m_cameraIndex].getProjectionMatrix();
    // set the uniform to use the current transformations
    shaderLib->setUniform("MVP",MVP);
    // set the normalSize
    shaderLib->setUniform("normalSize",m_normalSize);
    //draw the object normals
    drawObject(m_shapeType);
  }
}

void NGLScene::objectTransform(uint _type)
{
  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();

  enum geo {input=0,sphere=1,cube=2,torus=3,teapot=4,troll=5,dragon=6,bunny=7};

  // Transform differently depending on the object being drawn
  // Used to make all default shapes a similar size
  switch(_type)
  {
    case input : break;
    case sphere: break;
    case cube  : break;
    case torus : break;
    case teapot: break;
    case troll :
    {
      m_transform.setScale(1.5,1.5,1.5);
      loadMatricesToShader();
      break;
      // Moved the troll to be the same relative shape and position
    }
    case dragon:
    {
      m_transform.setScale(0.1,0.1,0.1);
      m_transform.setPosition(0,-0.5,0);
      loadMatricesToShader();
      break;
      // Moved the dragon to be the same relative shape and position
    }
    case bunny:
    {
      m_transform.setScale(0.15,0.15,0.15);
      m_transform.setPosition(0,-0.5,0);
      loadMatricesToShader();
      break;
      // Moved the bunny to be the same relative shape and position
    }
    default: std::cout<<"unrecognised shape type value"<<std::endl; break;
  }
}
void NGLScene::drawObject(uint _type)
{
  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
  enum geo {input=0,sphere=1,cube=2,torus=3,teapot=4,troll=5,dragon=6,bunny=7};

  // Draw different objects depending on the input value
  switch(_type)
  {
    case input : { m_mesh->draw();      break; }
    case sphere: { prim->draw("sphere");break; }
    case cube  : { prim->draw("cube");  break; }
    case torus : { prim->draw("torus"); break; }
    case teapot: { prim->draw("teapot");break; }
    case troll : { prim->draw("troll"); break; }
    case dragon: { prim->draw("dragon");break; }
    case bunny :  { prim->draw("bunny"); break; }
    default    : std::cout<<"unrecognised shape type value"<<std::endl; break;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::resizeGL(QResizeEvent *_event)
{
  setCameraShape(QString::fromStdString("Persp"));
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::resizeGL(int _w, int _h)
{
  setCameraShape(QString::fromStdString("Persp"));
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::loadMatricesToShader()
{
  ngl::ShaderLib *shaderLib=ngl::ShaderLib::instance();
  m_shaderManager->use(shaderLib,0);

  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  ngl::Mat4 M;

  M=m_transform.getMatrix()*m_mouseGlobalTX;
  MV=  M*m_cameras[m_cameraIndex].getViewMatrix();
  MVP= M*m_cameras[m_cameraIndex].getVPMatrix();
  normalMatrix=MV;
  normalMatrix.inverse();

  m_parser->sendUniformsToShader(shaderLib);
  shaderLib->setShaderParamFromMat4("MV",MV);
  shaderLib->setShaderParamFromMat4("MVP",MVP);
  shaderLib->setShaderParamFromMat3("normalMatrix",normalMatrix);
  shaderLib->setShaderParamFromMat4("M",M);
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::setCamShape()
{
  m_aspect=(float)width()/height();
  m_cameras[m_cameraIndex].setShape(m_fov, m_aspect, 0.5f, 150.0f);


}
void NGLScene::toggleWireframe(bool _value)
{
  m_wireframe=_value;
  update();
}
void NGLScene::toggleNormals(bool _value)
{
  m_drawNormals=_value;
  update();
}
void NGLScene::toggleGrid(bool _value)
{
  m_drawGrid=_value;
  update();
}

void NGLScene::setNormalSize(int _size)
{
  m_normalSize=_size/100.0f;
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
  m_shaderManager->compileShader(m_cameras[m_cameraIndex], vertSource, fragSource);
  m_window->setTerminalText(parseString(m_shaderManager->getErrorLog()));
  ngl::Light light(ngl::Vec3(2,2,2),ngl::Colour(1,1,1,1),ngl::Colour(1,1,1,1),ngl::LightModes::POINTLIGHT);
  // now create our light this is done after the camera so we can pass the
  // transpose of the projection matrix to the light to do correct eye space
  // transformations
  ngl::Mat4 iv=m_cameras[m_cameraIndex].getViewMatrix();
  iv.transpose();

  light.setTransform(iv);
  light.setAttenuation(1,0,0);
  light.enable();
  // load these values to the shader as well
  light.loadToShader("light");
  update();

}



//------------------------------------------------------------------------------

QString NGLScene::parseString(QString _string)
{
  // Declare a string to output
  // And a list of integer to be used for line error highlighting
  QString outString;
  std::vector<int> lineErrors;

  // Separate the input _string into separate lines.
  QRegExp separateLines("\n");
  QStringList lines=_string.split(separateLines);
  uint len=lines.length();

  for (uint i=0;i<len;i++)
  {
    // Split each line using braces; "(" and ")"
    QRegExp separateNumbers("(\\(|\\))");
    QStringList pieces=lines.value(i).split(separateNumbers);
    uint nLen=pieces.length();

    for (uint j=0;j<nLen;j++)
    {
      // This is the how to get the Title (Shader file)
      if (pieces.length()==1 && pieces[j]!="")
      {
        // Split the line using the "Remove Colon"
        QRegExp removeColon(":");
        QStringList title=pieces.value(j).split(removeColon);
      }
      // If the first segment of the line is 0...
      // remove it and replace it with "Line"
      if(pieces[j].length()==1 && j==0)
      {
        outString.append("Line ");
      }
      else
      {
        // Add the rest of the string to the list
        outString.append(pieces.value(j));
        // Add the second part of the line fragment as that is the line error number.
        // This can be returned as a list of integers
        if (j==1)
        {
          lineErrors.push_back(pieces.value(j).toInt());
        }
      }
    }
    // If it is the last line, add a new line to the string
    if (i!=len-1)
    {
      outString.append("\n");
    }
  }
  return outString;
  //return lineErrors;    // This wil return a list of integers
}

//------------------------------------------------------------------------------
void NGLScene::resetObjPos()
{
  //reset object position back to default
  m_modelPos.m_x = 0;
  m_modelPos.m_y = 0;
  m_modelPos.m_z = 0;
  m_spinXFace = 0;
  m_spinYFace = 0;
}

//------------------------------------------------------------------------------
void NGLScene::newProject(std::string _name)
{
  m_shaderManager->createShaderProgram(_name);
}

//------------------------------------------------------------------------------
void NGLScene::exportUniform()
{
  m_parser->exportUniforms();
}

//------------------------------------------------------------------------------
void NGLScene::drawAxis(ngl::Vec3 _pos)
{
  // Instance the Shader
  ngl::ShaderLib *shaderLib=ngl::ShaderLib::instance();
  m_shaderManager->use(shaderLib,0);
  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();

  // Move the Y AXIS geo
  m_transform.setScale(0.05,0.5,0.05);
  m_transform.setPosition(0,0.3,0);
  m_transform.addPosition(_pos);
  loadMatricesToShader();
  shaderLib->setShaderParam4f("Colour",0,1,0,1); //Not entirely sure if this is the best way, as the name "Colour" could be changed....
  prim->draw("cube");
  m_transform.reset();

  // Move the X AXIS geo
  m_transform.setScale(0.5,0.05,0.05);
  m_transform.setPosition(0.3,0,0);
  m_transform.addPosition(_pos);
  loadMatricesToShader();
  shaderLib->setShaderParam4f("Colour",1,0,0,1); //Not entirely sure if this is the best way, as the name "Colour" could be changed....
  prim->draw("cube");
  m_transform.reset();

  // Move the Z AXIS geo
  m_transform.setScale(0.05,0.05,0.5);
  m_transform.setPosition(0,0,0.3);
  m_transform.addPosition(_pos);
  loadMatricesToShader();
  shaderLib->setShaderParam4f("Colour",0,0,1,1); //Not entirely sure if this is the best way, as the name "Colour" could be changed....
  prim->draw("cube");
  m_transform.reset();
}



//----------------------------------------------------------------------------------------------------------------------
// Sets the view of the camera (persp, top, bottom, side).
void NGLScene::setCameraShape(QString _view)
{
  m_cameraIndex = m_camera->setCameraShape(_view);
//  m_modelPos.m_x=0;
//  m_modelPos.m_y=0;
//  m_modelPos.m_z=0;
//  m_spinXFace=0;
//  m_spinYFace=0;
  m_aspect=(float)width()/height();
  for(auto &cam : m_cameras)
    {
      cam.setShape(m_fov,m_aspect, 0.5f,150.0f);
    }
  update();
}

//----------------------------------------------------------------------------------------------------------------------
// Signal passed from the UI to set the camera FOV
void NGLScene::setCameraFocalLength(int _focalLength)
{
    m_fov= _focalLength;
    update();
}

//----------------------------------------------------------------------------------------------------------------------
// Signal passed from the UI to set the camera roll.
void NGLScene::setCameraRoll(double _cameraRoll)
{
    m_cameras[m_cameraIndex] = m_camera->cameraRoll(m_cameras[m_cameraIndex], _cameraRoll);
    update();
}

//----------------------------------------------------------------------------------------------------------------------
// Signal passed from the UI to set the camera yaw.
void NGLScene::setCameraYaw(double _cameraYaw)
{
    m_cameras[m_cameraIndex] = m_camera->cameraYaw(m_cameras[m_cameraIndex], _cameraYaw);
    update();
}
