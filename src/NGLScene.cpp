#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include "parserLib.h"
#include <ngl/Camera.h>
#include <ngl/Light.h>
#include <ngl/Material.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>
#include <iostream>
#include <uniformValues.h>
#include <typeinfo>
//----------------------------------------------------------------------------------------------------------------------
/// @brief the increment for x/y translation with mouse movement
//----------------------------------------------------------------------------------------------------------------------
const static float INCREMENT=0.01f;
//----------------------------------------------------------------------------------------------------------------------
/// @brief the increment for the wheel zoom
//----------------------------------------------------------------------------------------------------------------------
const static float ZOOM=0.1f;

NGLScene::NGLScene()
{
  // re-size the widget to that of the parent (in that case the GLFrame passed in on construction)
  m_rotate=false;
  // mouse rotation values set to 0
  m_spinXFace=0.0f;
  m_spinYFace=0.0f;
  setTitle("Qt5 Simple NGL Demo");
  m_newParser= new parserLib();

}


NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}

void NGLScene::resizeGL(QResizeEvent *_event)
{
  m_width=_event->size().width()*devicePixelRatio();
  m_height=_event->size().height()*devicePixelRatio();
  // now set the camera size values as the screen size has changed
  m_cam.setShape(45.0f,(float)width()/height(),0.05f,350.0f);
}

void NGLScene::resizeGL(int _w , int _h)
{
  m_cam.setShape(45.0f,(float)_w/_h,0.05f,350.0f);
  m_width=_w*devicePixelRatio();
  m_height=_h*devicePixelRatio();
}

void NGLScene::initializeGL()
{
  // we must call that first before any other GL commands to load and link the
  // gl commands from the lib, if that is not done program will crash
  ngl::NGLInit::instance();
  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);
   // now to load the shader and set the values
  // grab an instance of shader manager
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  // we are creating a shader called Phong
  shader->createShaderProgram("Phong");
  // now we are going to create empty shaders for Frag and Vert
  shader->attachShader("PhongVertex",ngl::ShaderType::VERTEX);
  shader->attachShader("PhongFragment",ngl::ShaderType::FRAGMENT);
  // attach the source
  shader->loadShaderSource("PhongVertex","shaders/PhongVertex.glsl");
  shader->loadShaderSource("PhongFragment","shaders/PhongFragment.glsl");
  // compile the shaders
  shader->compileShader("PhongVertex");
  shader->compileShader("PhongFragment");
  // add them to the program
  shader->attachShaderToProgram("Phong","PhongVertex");
  shader->attachShaderToProgram("Phong","PhongFragment");
  // now bind the shader attributes for most NGL primitives we use the following
  // layout attribute 0 is the vertex data (x,y,z)
  shader->bindAttribute("Phong",0,"inVert");
  // attribute 1 is the UV data u,v (if present)
  shader->bindAttribute("Phong",1,"inUV");
  // attribute 2 are the normals x,y,z
  shader->bindAttribute("Phong",2,"inNormal");

  // now we have associated that data we can link the shader
  shader->linkProgramObject("Phong");
  // and make it active ready to load values
  (*shader)["Phong"]->use();
  // the shader will use the currently active material and light0 so set them
////  ngl::Material m(ngl::STDMAT::POLISHEDSILVER );
  // load our material values to the shader into the structure material (see Vertex shader)
////  m.loadToShader("material");
  // Now we will create a basic Camera from the graphics library
  // This is a static camera so it only needs to be set once
  // First create Values for the camera position
  ngl::Vec3 from(0,25,25);
  ngl::Vec3 to(0,5,0);
  ngl::Vec3 up(0,1,0);
  // now load to our new camera
  m_cam.set(from,to,up);
  // set the shape using FOV 45 Aspect Ratio based on Width and Height
  // The final two are near and far clipping planes of 0.5 and 10
  m_cam.setShape(45.0f,(float)720.0/576.0f,0.05f,350.0f);
  shader->setUniform("viewerPos",m_cam.getEye().toVec3());
  // now create our light that is done after the camera so we can pass the
  // transpose of the projection matrix to the light to do correct eye space
  // transformations
  ngl::Mat4 iv=m_cam.getViewMatrix();
  iv.transpose();
  ngl::Light light(ngl::Vec3(-2,5,2),ngl::Colour(1,1,1,1),ngl::Colour(1,1,1,1),ngl::LightModes::POINTLIGHT );
  light.setTransform(iv);
  // load these values to the shader as well
  light.loadToShader("light");
  // as re-size is not explicitly called we need to do that.
  // set the viewport for openGL we need to take into account retina display

  //shader->setUniform(




  ngl::Mat4 M=shader->getUniformBlockIndex("M");
  ngl::Mat4 MV=shader->getUniformBlockIndex("MV");
  ngl::Mat4 MVP=shader->getUniformBlockIndex("MVP");
  m_norm=shader->getUniformBlockIndex("Normalize");
  m_lightAmb=shader->getUniformBlockIndex("light.ambient");
  m_lightDif=shader->getUniformBlockIndex("light.diffuse");
  m_lightPos=shader->getUniformBlockIndex("light.position");
  m_lightSpec=shader->getUniformBlockIndex("light.specular");
// PUT THIS IN A CLASS.... or for loop.
  m_matAmb=shader->getUniformBlockIndex("material.ambient");
  m_matDif=shader->getUniformBlockIndex("material.diffuse");
  m_matShiny=shader->getUniformBlockIndex("material.shininess");
  m_matSpec=shader->getUniformBlockIndex("material.specular");

  ngl::Mat3 normalMatrix=shader->getUniformBlockIndex("normalMatrix");
  ngl::Vec3 viewerPos=shader->getUniformBlockIndex("viewerPos");

  m_newParser->listUniforms();
  m_newParser->printUniforms();

  for (int token=0; token<m_newParser->m_num;token++)
  {

    std::string b="bool";
    std::string f="float";
    std::string i="int";
    std::string m3="mat3";
    std::string m4="mat4";
    std::string v3="vec3";
    std::string v4="vec4";

    std::cout<<m_newParser->m_uniformDataList[token].dataType  <<std::endl;
    std::cout<<"dataType:  "<<typeid(b).name()<<std::endl;

    if(m_newParser->m_uniformDataList[token].dataType==b)
    {
      std::cout<<m_newParser->m_uniformDataList[token].nameUniforms<<std::endl;
    }
    if(m_newParser->m_uniformDataList[token].dataType==f)
    {
    }
    if(m_newParser->m_uniformDataList[token].dataType==i)
    {
    }
    if(m_newParser->m_uniformDataList[token].dataType==m3)
    {
    }
    if(m_newParser->m_uniformDataList[token].dataType==m4)
    {
    }
    if(m_newParser->m_uniformDataList[token].dataType==v3)
    {
    }
    if(m_newParser->m_uniformDataList[token].dataType==v4)
    {
    }





  }



//  m_matDif=materialDiffuse;
//  m_matAmb=materialAmbient;
//  m_matShiny=materialShininess;
//  m_matSpec=materialSpecular;

//  m_lightDif=lightDiffuse;
//  m_lightAmb=lightAmbient;
//  m_lightPos=lightPosition;
//  m_lightSpec=lightSpecular;

 // m_norm=Normalize;

  //  std::cout<<typeid(Normalize).name()<<std::endl;
//    std::cout<<"ad:    "<<DAD.m_00 <<" " <<DAD.m_01<<" " <<DAD.m_02<<" " <<DAD.m_03<<" " <<std::endl;
//    std::cout<<"ad:    "<<DAD.m_10 <<" " <<DAD.m_11<<" " <<DAD.m_12<<" " <<DAD.m_23<<" " <<std::endl;
//    std::cout<<"ad:    "<<DAD.m_20 <<" " <<DAD.m_21<<" " <<DAD.m_22<<" " <<DAD.m_23<<" " <<std::endl;
//    std::cout<<"ad:    "<<DAD.m_30 <<" " <<DAD.m_31<<" " <<DAD.m_32<<" " <<DAD.m_33<<" " <<std::endl;

//  std::cout<<"m_matDif:    "<<m_matDif.m_x <<" " <<m_matDif.m_y<<" " <<m_matDif.m_z<<" " <<m_matDif.m_w<<" " <<std::endl;
//  std::cout<<"m_matAmb:    "<<m_matAmb.m_x <<" " <<m_matAmb.m_y<<" " <<m_matAmb.m_z<<" " <<m_matAmb.m_w<<" " <<std::endl;
//  std::cout<<"m_matSpec:    "<<m_matSpec.m_x <<" " <<m_matSpec.m_y<<" " <<m_matSpec.m_z<<" " <<m_matSpec.m_w<<" " <<std::endl;
//  std::cout<<"m_matShiny:    "<<m_matShiny<<std::endl;

//  std::cout<<"m_lightDif:    "<<m_lightDif.m_x <<" " <<m_lightDif.m_y<<" " <<m_lightDif.m_z<<" " <<m_lightDif.m_w<<" " <<std::endl;
//  std::cout<<"m_lightAmb:    "<<m_lightAmb.m_x <<" " <<m_lightAmb.m_y<<" " <<m_lightAmb.m_z<<" " <<m_lightAmb.m_w<<" " <<std::endl;
//  std::cout<<"m_lightPos:    "<<m_lightPos.m_x <<" " <<m_lightPos.m_y<<" " <<m_lightPos.m_z<<" " <<m_lightPos.m_w<<" " <<std::endl;
//  std::cout<<"m_lightSpec:    "<<m_lightSpec.m_x <<" " <<m_lightSpec.m_y<<" " <<m_lightSpec.m_z<<" " <<m_lightSpec.m_w<<" " <<std::endl;

}



void NGLScene::loadMatricesToShader()
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();

  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  ngl::Mat4 M;
  //


  M=m_mouseGlobalTX;
  MV=  M*m_cam.getViewMatrix();
  MVP= M*m_cam.getVPMatrix();
  normalMatrix=MV;
  normalMatrix.inverse();
  shader->setShaderParamFromMat4("MV",MV);
  shader->setShaderParamFromMat4("MVP",MVP);
  shader->setShaderParamFromMat3("normalMatrix",normalMatrix);
  shader->setShaderParamFromMat4("M",M);

  //added stuff
  shader->setShaderParamFromMat4("Normalize",m_norm);

  shader->setShaderParamFromVec4("material.specular",m_matSpec);
  shader->setShaderParamFromVec4("material.diffuse", m_matDif);
  shader->setShaderParamFromVec4("material.ambient", m_matAmb);
  shader->setShaderParam1f("material.shininess", m_matShiny);

  shader->setShaderParamFromVec4("light.specular",m_lightSpec);
  shader->setShaderParamFromVec4("light.diffuse", m_lightDif);
  shader->setShaderParamFromVec4("light.ambient", m_lightAmb);
  shader->setShaderParamFromVec4("light.position", m_lightPos);

}

void NGLScene::paintGL()
{
  glViewport(0,0,m_width,m_height);
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // grab an instance of the shader manager
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

   // get the VBO instance and draw the built in teapot
  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
  // draw
  loadMatricesToShader();
  prim->draw("dragon");


}

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseMoveEvent (QMouseEvent * _event)
{
  // note the method buttons() is the button state when event was called
  // that is different from button() which is used to check which button was
  // pressed when the mousePress/Release event is generated
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
void NGLScene::mousePressEvent ( QMouseEvent * _event)
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
void NGLScene::wheelEvent(QWheelEvent *_event)
{

	// check the diff of the wheel position (0 means no change)
	if(_event->delta() > 0)
	{
		m_modelPos.m_z+=ZOOM;
	}
	else if(_event->delta() <0 )
	{
		m_modelPos.m_z-=ZOOM;
	}
	update();
}
//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // that method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quit
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  // turn on wirframe rendering
  case Qt::Key_W : glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); break;
  // turn off wire frame
  case Qt::Key_S : glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); break;
  // show full screen
  case Qt::Key_F : showFullScreen(); break;
  // show windowed
  case Qt::Key_N : showNormal(); break;
  case Qt::Key_M :
  {
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  ngl::Vec4 materialDiffuse=shader->getUniformBlockIndex("material.diffuse");
  std::cout<<materialDiffuse.m_x<<"   "<<materialDiffuse.m_y<<"   "<<materialDiffuse.m_z<<"   "<<materialDiffuse.m_w<<"   "<<std::endl;
  break;
  }
  default : break;
  }
  // finally update the GLWindow and re-draw
  //if (isExposed())
    update();
}
