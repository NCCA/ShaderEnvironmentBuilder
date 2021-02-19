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
#include <QFileDialog>
#include <ngl/Texture.h>

//----------------------------------------------------------------------------------------------------------------------
/// @brief the increment for x/y translation with mouse movement
//----------------------------------------------------------------------------------------------------------------------
const static float INCREMENT=0.005f;
//----------------------------------------------------------------------------------------------------------------------
/// @brief the increment for the wheel zoom
//----------------------------------------------------------------------------------------------------------------------
const static float ZOOM=0.1f;
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
NGLScene::NGLScene( QWidget *_parent, ParserLib *_libParent,
                    ShaderManager *_manager )
  : QOpenGLWidget( _parent )
{
  // re-size the widget to that of the parent (in that case the GLFrame passed in on construction)
  m_rotate=false;
  // mouse rotation values set to 0
  m_spinXFace = 0.0f;
  m_spinYFace = 0.0f;
  m_spinZFace = 0.0;
  m_parser= _libParent; //DONT CHANGE THIS
  m_shapeType=6;
  m_toggleObj=false;
  m_toggleAxis=false;
  m_meshLoc="./models/Suzanne.obj";
  m_drawNormals=false;
  m_drawGrid=false;
  m_normalSize=0.1;
  // Store main window to send data from compile errors
  m_window = dynamic_cast<MainWindow*>(_parent);
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  this->resize(_parent->size());
  m_wireframe=false;
  m_shaderManager = _manager;
  m_camera = new Camera();
  m_camera->createCameras();
  m_cam = m_camera->m_mainCamera;

  // set this widget to have the initial keyboard focus
  setFocus();
  connect(this, SIGNAL(initializeGL()), this, SLOT(initGL()));
}

//----------------------------------------------------------------------------------------------------------------------
NGLScene::~NGLScene()
{
  //delete m_readFromXML;
  delete m_parser;
  delete m_shaderManager;

  //Clear any existing texture maps
  glDeleteTextures(1,&m_textureName);
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::setMeshLocation(std::string _meshDirectory)
{
  m_meshLoc=_meshDirectory;
  //std::cout<<"Imported file:  "<<_meshDirectory<<std::endl;
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
//----------------------------------------------------------------------------------------------------------------------

void NGLScene::importMeshName(const std::string &_name)
{
  // If the CANCEL button is clicked, then don't update the shapetype or location
  std::ifstream shaderSource(_name.c_str());
  if (!shaderSource.is_open())
  {
    if(_name.length()==0)
    {
      std::cerr<<"Import Cancelled"<<std::endl;
      //exit(EXIT_FAILURE);
    }
    else
    {
      std::cerr<<"File not found"<<_name.c_str()<<std::endl;
      //exit(EXIT_FAILURE);
    }
  }
  else
  {
    setMeshLocation(_name);
    setShapeType(0);
    m_toggleObj=true;
  }


}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::importTextureMap(const std::string &_name)
{
  std::ifstream textureSource(_name.c_str());
  ngl::Texture texture (_name);
  m_textureName=texture.setTextureGL();
  update();
}
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// This virtual function is called once before the first call to paintGL() or resizeGL(),
// and then once whenever the widget has been assigned a new QGLContext.
// This function should set up any required OpenGL context rendering flags, defining display lists, etc.
//----------------------------------------------------------------------------------------------------------------------
void NGLScene::initGL()
{
  ngl::NGLInit::instance();
  clearAllGlErrors();

  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);

  // now to load the shader and set the values
  // grab an instance of shader manager
  m_shaderManager->initialize();

  ngl::Texture texture ("textures/metalTexture.jpg");
  m_textureName=texture.setTextureGL();


  if(!m_shaderManager->compileStatus())
  {
    m_window->setTerminalText(parseErrorLog(m_shaderManager->getErrorLog()));
  }
  if(m_shaderManager->isInit())
  {
    ngl::Mat4 iv=m_cam.getViewMatrix();
    iv.transpose();
    //m_parser->assignAllData();
  }

  // Create mesh VAO
  m_mesh = std::unique_ptr<ngl::Obj> (new ngl::Obj(m_meshLoc));
  m_mesh->createVAO();

  // Create some default shapes
  ngl::VAOPrimitives::instance()->createSphere("sphere",0.7,30);
  ngl::VAOPrimitives::instance()->createTorus("torus",0.3,0.7,20,20);
  ngl::VAOPrimitives::instance()->createLineGrid("Grid",10,10,10);

}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::setShapeType(int _type)
{
  if (_type<=7 && _type>=0)
  {
    m_shapeType=_type;
  }
  else
  {
    //std::cout<<"Invalid shape type"<<std::endl;
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
    //glBindTexture(GL_TEXTURE_2D, m_textureName);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  }
  ngl::ShaderLib *shaderLib=ngl::ShaderLib::instance();

  m_shaderManager->use(0);

  // Rotation based on the mouse position for our global transform
  ngl::Mat4 rotX;
  ngl::Mat4 rotY;
  ngl::Mat4 rotZ;
  // create the rotation matrices
  rotX.rotateX(m_spinXFace);
  rotY.rotateY(m_spinYFace);
  rotZ.rotateZ(m_spinZFace);
  // multiply the rotations
  m_mouseGlobalTX=rotY*rotX*rotZ;
  // add the translations
  m_mouseGlobalTX.m_m[3][0] = m_modelPos.m_x;
  m_mouseGlobalTX.m_m[3][1] = m_modelPos.m_y;
  m_mouseGlobalTX.m_m[3][2] = m_modelPos.m_z;

  //draw initial texture map
  glBindTexture(GL_TEXTURE_2D, m_textureName);
  m_shaderManager->use(0);

  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();

  m_camera->m_aspect = (float)width()/height();
  m_camera->setShapeCam();
  m_cam = m_camera->m_mainCamera;
  m_cameraIndex = m_camera->m_cameraIndex;

  m_transform.reset();

  if (m_toggleAxis)
  {
    ngl::Vec3 pos={-1,-0.5,-1};
    drawAxis(pos);
  }
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
    m_shaderManager->use(1);
    ngl::Mat4 MV;
    ngl::Mat4 MVP;
    MV=m_transform.getMatrix()*m_mouseGlobalTX*m_cam.getViewMatrix();
    MVP=MV*m_cam.getProjectionMatrix();
    // set the uniform to use the current transformations
    shaderLib->setUniform("MVP",MVP);
    // set the normalSize
    shaderLib->setUniform("normalSize",m_normalSize);
    //draw the object normals
    drawObject(m_shapeType);
  }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::objectTransform(uint _type)
{
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
    m_transform.setRotation(0,90,0);
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
  default: std::cerr<<"unrecognised shape type value\n"; break;
  }
}

//----------------------------------------------------------------------------------------------------------------------
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
  case bunny : { prim->draw("bunny"); break; }
  default    : std::cerr<<"unrecognised shape type value\n"; break;
  }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::resizeGL(QResizeEvent *_event)
{
  m_camera->m_aspect = (float)width()/height();
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::resizeGL(int _w, int _h)
{
  m_camera->m_aspect = (float)width()/height();
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::loadMatricesToShader()
{
  ngl::ShaderLib *shaderLib=ngl::ShaderLib::instance();
  m_shaderManager->use(0);

  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  ngl::Mat4 M;

  M=m_transform.getMatrix()*m_mouseGlobalTX;
  MV=  M*m_cam.getViewMatrix();
  MVP= M*m_cam.getVPMatrix();
  normalMatrix=MV;
  normalMatrix.inverse();

  m_parser->sendUniformsToShader(shaderLib);
  shaderLib->setShaderParamFromMat4("MV",MV);
  shaderLib->setShaderParamFromMat4("MVP",MVP);
  shaderLib->setShaderParamFromMat3("normalMatrix",normalMatrix);
  shaderLib->setShaderParamFromMat4("M",M);
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::toggleWireframe(bool _state)
{
  m_wireframe=_state;
  update();
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::toggleNormals(bool _state)
{
  m_drawNormals=_state;
  update();
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::toggleGrid(bool _state)
{
  m_drawGrid=_state;
  update();
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::toggleAxis(bool _state)
{
  m_toggleAxis=_state;
  update();
}

//----------------------------------------------------------------------------------------------------------------------
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
    m_origX = _event->x();
    m_origY = _event->y();

    // Changes viewport rotation depending on camera view.
    switch(m_cameraIndex){
      case 0:
        m_spinZFace -= (float) 0.5f * diffy;
        m_spinXFace += (float) 0.5f * diffy;
        m_spinYFace += (float) 1.0f * diffx;
        break;
      case 1:
        m_spinXFace -= diffy;
        m_spinZFace += diffx; break;
      case 2:
        m_spinXFace += diffy;
        m_spinZFace += diffx; break;
      case 3:
        m_spinXFace -= diffy;
        m_spinYFace += diffx; break;
      case 4:
        m_spinXFace += diffy;
        m_spinYFace += diffx; break;
    }
    update();
  }
  else if(m_translate && _event->buttons() == Qt::RightButton)
  {
    int diffX = (int)(_event->x() - m_origXPos);
    int diffY = (int)(_event->y() - m_origYPos);
    m_origXPos=_event->x();
    m_origYPos=_event->y();

    // Switch used to change how modelPos translates depending on camera.
    switch(m_cameraIndex){
    case 0:
        m_modelPos.m_y -= INCREMENT * diffY;
        m_modelPos.m_x += INCREMENT * diffY/2;
        m_modelPos.m_z += INCREMENT * diffY/2;

        m_modelPos.m_x += INCREMENT * diffX/2;
        m_modelPos.m_z -= INCREMENT * diffX/2; break;
    case 1:
        m_modelPos.m_z -= INCREMENT * diffY;
        m_modelPos.m_x -= INCREMENT * diffX;break;
    case 2:
        m_modelPos.m_z -= INCREMENT * diffY;
        m_modelPos.m_x += INCREMENT * diffX;break;
    case 3:
        m_modelPos.m_x -= INCREMENT * diffX;
        m_modelPos.m_y -= INCREMENT * diffY;break;
    case 4:
        m_modelPos.m_x += INCREMENT * diffX;
        m_modelPos.m_y -= INCREMENT * diffY;break;
    }
    update();
  }
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mousePressEvent ( QMouseEvent * _event )
{
  // left mouse rotate mode
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
  update();
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseReleaseEvent(QMouseEvent * _event)
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
    switch(m_cameraIndex){
    case 0:
      m_modelPos.m_z+=ZOOM;
      m_modelPos.m_x+=ZOOM; break;
    case 1:
      m_modelPos.m_y+=ZOOM; break;
    case 2:
      m_modelPos.m_y-=ZOOM; break;
    case 3:
      m_modelPos.m_z-=ZOOM; break;
    case 4:
      m_modelPos.m_z+=ZOOM; break;
    }
  }
  else if(_event->delta() < 0)
  {
    switch(m_cameraIndex){
    case 0:
      m_modelPos.m_z-=ZOOM;
      m_modelPos.m_x-=ZOOM; break;
    case 1:
      m_modelPos.m_y-=ZOOM; break;
    case 2:
      m_modelPos.m_y+=ZOOM; break;
    case 3:
      m_modelPos.m_z+=ZOOM; break;
    case 4:
      m_modelPos.m_z-=ZOOM; break;
    }
  }
  update();
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  switch (_event->key())
  {
  default : break ;
  }
  update();
}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::compileShader(QString _vertSource, QString _fragSource)
{
  m_shaderManager->compileShader(_vertSource, _fragSource);
  m_window->setTerminalText(parseErrorLog(m_shaderManager->getErrorLog()));
  update();
  m_parser->assignAllData();
}

//------------------------------------------------------------------------------

QString NGLScene::parseErrorLog(QString _string)
{
  // Declare a string to output
  // And a list of integer to be used for line error highlighting
  QString outputErrors;

  QString shaderName;

  // Separate the input _string into separate lines.
  QRegExp separateLines("\n");
  QStringList lines=_string.split(separateLines);

  for (int i=0;i<lines.length();i++)
  {
    // Split each line using braces; "(" and ")"
    QRegExp separateNumbers("(\\(|\\))");
    QStringList pieces=lines.value(i).split(separateNumbers);

    for (int j=0;j<pieces.length();j++)
    {
      // This is the how to get the Title (Shader file)
      if (pieces.length()==1 && pieces[j]!="")
      {
        // Split the line using the "Remove Colon"
        if(pieces.value(j).endsWith("Vertex:"))
        {
          shaderName=QString("Vertex");
        }
        if(pieces.value(j).endsWith("Fragment:"))
        {
          shaderName=QString("Fragment");
        }
      }
      // If the first segment of the line is 0...
      // remove it and replace it with "Line"
      if(pieces[j].length()==1 && j==0)
      {
        outputErrors.append("Line ");
      }

      // Add the rest of the string to the list
      else
      {
        outputErrors.append(pieces.value(j));


        // Add the second part of the line fragment as that is the line error number.
        // This can be returned as a list of integers
        if (j==1)
        {
          int lineNumber = pieces.value(j).toInt();
          emit createLineMarker(shaderName,lineNumber-1);
        }
      }
    }
    // If it is the last line, add a new line to the string
    int finalLine =lines.length()-1;
    if (i!=finalLine)
    {
      outputErrors.append("\n");
    }
  }

  return outputErrors;
}

//------------------------------------------------------------------------------
void NGLScene::resetObjPos()
{
  //move camera back to default
  m_modelPos.m_x = 0;
  m_modelPos.m_y = 0;
  m_modelPos.m_z = 0;
  m_spinXFace = 0;
  m_spinYFace = 0;
  m_spinZFace = 0;

  m_camera->cameraRoll(0.00);
  m_camera->cameraYaw(0.00);
  m_camera->cameraPitch(0.00);
  m_camera->m_fov = 60.0;
  m_camera->m_nearClip = 0.5;
  m_camera->m_farClip = 150.0;

  update();
}

//------------------------------------------------------------------------------

void NGLScene::setProject(std::string _name, QString _vertSource, QString _fragSource)
{
  m_shaderManager->createShaderProgram(_name);
  compileShader(_vertSource, _fragSource);
}

//------------------------------------------------------------------------------
void NGLScene::exportUniform()
{
  QString fileName = QFileDialog::getSaveFileName(m_window,
                                                  tr("Export Uniforms"),
                                                  QDir::homePath(),
                                                  tr("Text File (*.txt)"));
  if (fileName != "")
  {
    if (m_parser->exportUniforms(fileName))
    {
      QMessageBox msgBox;
      msgBox.setText("Uniforms successfully exported");
      msgBox.setWindowTitle("Successfully Exported");
      msgBox.exec();
    }
  }
}

//------------------------------------------------------------------------------
void NGLScene::drawAxis(ngl::Vec3 _pos)
{
  // Instance the Shader
  ngl::ShaderLib *shaderLib=ngl::ShaderLib::instance();
  m_shaderManager->use(0);
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
