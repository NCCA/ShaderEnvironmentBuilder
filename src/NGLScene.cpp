#include "NGLScene.h"
#include "parserLib.h"
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


//----------------------------------------------------------------------------------------------------------------------
NGLScene::NGLScene( QWidget *_parent ) : QOpenGLWidget( _parent )
{
  // re-size the widget to that of the parent (in that case the GLFrame passed in on construction)
  m_rotate=false;
  // mouse rotation values set to 0
  m_spinXFace=0.0f;
  m_spinYFace=0.0f;
  setTitle("Qt5 Simple NGL Demo");
  m_parser= new parserLib();


  // set this widget to have the initial keyboard focus
  setFocus();
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  this->resize(_parent->size());
	m_wireframe=false;
	m_rotation=0.0;
	m_scale=1.0;
	m_position=0.0;

	m_selectedObject=0;
}

// This virtual function is called once before the first call to paintGL() or resizeGL(),
//and then once whenever the widget has been assigned a new QGLContext.
// This function should set up any required OpenGL context rendering flags, defining display lists, etc.

//----------------------------------------------------------------------------------------------------------------------
void NGLScene::initializeGL()
{

  ngl::NGLInit::instance();
  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);			   // Grey Background
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  /// create our camera
  ngl::Vec3 eye(2,2,2);
  ngl::Vec3 look(0,0,0);
  ngl::Vec3 up(0,1,0);

  m_cam.set(eye,look,up);
  m_cam.setShape(45,float(1024/720),0.1,300);
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
  // as re-size is not explicitly called we need to do that.
  // set the viewport for openGL we need to take into account retina display

  ///---------------------------------------------------------------------------------------------------------

  m_parser->assignAllData();
//  Jsons = new Json();
//  Jsons->buildJson();

//  Json *jsonInstance = new Json();
//  jsonInstance->buildJson();
//  jsonInstance->replaceWord("Shader", "CHANGED");


}

void NGLScene::loadMatricesToShader()
{
  ngl::ShaderLib *shader=ngl::ShaderLib::instance();
  (*shader)["Phong"]->use();

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


  m_parser->sendUniformsToShader(shader);

  shader->setShaderParamFromMat4("MV",MV);
  shader->setShaderParamFromMat4("MVP",MVP);
  shader->setShaderParamFromMat3("normalMatrix",normalMatrix);
  shader->setShaderParamFromMat4("M",M);
}

//----------------------------------------------------------------------------------------------------------------------
//This virtual function is called whenever the widget needs to be painted.
// this is our main drawing routine
void NGLScene::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_width,m_height);
  ngl::VAOPrimitives *prim=ngl::VAOPrimitives::instance();
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

	m_transform.setPosition(m_position);
	m_transform.setScale(m_scale);
	m_transform.setRotation(m_rotation);
	loadMatricesToShader();
	switch(m_selectedObject)
	{
		case 0 : prim->draw("teapot"); break;
		case 1 : prim->draw("sphere"); break;
		case 2 : prim->draw("cube"); break;
	}

}





//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mouseMoveEvent ( QMouseEvent * _event )
{
  Q_UNUSED(_event);
}


//----------------------------------------------------------------------------------------------------------------------
void NGLScene::mousePressEvent (QMouseEvent * _event  )
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
//  case Qt::Key_1 : m_parser->m_uniformDataList[12].m_mat3.m_00+=0.1;std::cout<<m_parser->m_uniformDataList[12].m_mat3.m_00<<std::endl; break;
//  case Qt::Key_2 : m_parser->m_uniformDataList[12].m_mat3.m_01+=0.1;std::cout<<m_parser->m_uniformDataList[12].m_mat3.m_01<<std::endl; break;
//  case Qt::Key_3 : m_parser->m_uniformDataList[12].m_mat3.m_02+=0.1;std::cout<<m_parser->m_uniformDataList[12].m_mat3.m_02<<std::endl; break;
//  case Qt::Key_4 : m_parser->m_uniformDataList[12].m_mat3.m_10+=0.1;std::cout<<m_parser->m_uniformDataList[12].m_mat3.m_10<<std::endl; break;
//  case Qt::Key_5 : m_parser->m_uniformDataList[12].m_mat3.m_11+=0.1;std::cout<<m_parser->m_uniformDataList[12].m_mat3.m_11<<std::endl; break;
//  case Qt::Key_6 : m_parser->m_uniformDataList[12].m_mat3.m_12+=0.1;std::cout<<m_parser->m_uniformDataList[12].m_mat3.m_12<<std::endl; break;
//  case Qt::Key_7 : m_parser->m_uniformDataList[12].m_mat3.m_20+=0.1;std::cout<<m_parser->m_uniformDataList[12].m_mat3.m_20<<std::endl; break;
//  case Qt::Key_8 : m_parser->m_uniformDataList[12].m_mat3.m_21+=0.1;std::cout<<m_parser->m_uniformDataList[12].m_mat3.m_21<<std::endl; break;
//  case Qt::Key_9 : m_parser->m_uniformDataList[12].m_mat3.m_22+=0.1;std::cout<<m_parser->m_uniformDataList[12].m_mat3.m_22<<std::endl; break;
  case Qt::Key_1 : m_parser->m_uniformDataList[4].m_vec3.m_x+=0.1;std::cout<<m_parser->m_uniformDataList[4].m_vec3.m_x<<std::endl; break;
  case Qt::Key_2 : m_parser->m_uniformDataList[4].m_vec3.m_y+=0.1;std::cout<<m_parser->m_uniformDataList[4].m_vec3.m_y<<std::endl; break;
  case Qt::Key_3 : m_parser->m_uniformDataList[4].m_vec3.m_z+=0.1;std::cout<<m_parser->m_uniformDataList[4].m_vec3.m_z<<std::endl; break;
  case Qt::Key_4 : m_parser->m_uniformDataList[5].m_vec3.m_x+=0.1;std::cout<<m_parser->m_uniformDataList[5].m_vec3.m_x<<std::endl; break;
  case Qt::Key_5 : m_parser->m_uniformDataList[5].m_vec3.m_y+=0.05;std::cout<<m_parser->m_uniformDataList[5].m_vec3.m_y<<std::endl; break;
  case Qt::Key_6 : m_parser->m_uniformDataList[5].m_vec3.m_z+=0.05;std::cout<<m_parser->m_uniformDataList[5].m_vec3.m_z<<std::endl; break;
  case Qt::Key_7 : m_parser->m_uniformDataList[6].m_vec3.m_x+=0.1;std::cout<<m_parser->m_uniformDataList[6].m_vec3.m_x<<std::endl; break;
  case Qt::Key_8 : m_parser->m_uniformDataList[6].m_vec3.m_y+=0.1;std::cout<<m_parser->m_uniformDataList[6].m_vec3.m_y<<std::endl; break;
  case Qt::Key_9 : m_parser->m_uniformDataList[6].m_vec3.m_z+=0.1;std::cout<<m_parser->m_uniformDataList[6].m_vec3.m_z<<std::endl; break;
  case Qt::Key_K : m_parser->m_uniformDataList[7].m_vec3.m_x+=0.1;std::cout<<m_parser->m_uniformDataList[7].m_vec3.m_x<<std::endl; break;
  case Qt::Key_L : m_parser->m_uniformDataList[7].m_vec3.m_y+=0.1;std::cout<<m_parser->m_uniformDataList[7].m_vec3.m_y<<std::endl; break;
  case Qt::Key_O : m_parser->m_uniformDataList[7].m_vec3.m_z+=0.1;std::cout<<m_parser->m_uniformDataList[7].m_vec3.m_z<<std::endl; break;
  case Qt::Key_M : m_parser->m_uniformDataList[8].m_vec3.m_x+=0.1;std::cout<<m_parser->m_uniformDataList[8].m_vec3.m_x<<std::endl; break;
  case Qt::Key_H : m_parser->m_uniformDataList[8].m_vec3.m_y+=0.1;std::cout<<m_parser->m_uniformDataList[8].m_vec3.m_y<<std::endl; break;
  case Qt::Key_T : m_parser->m_uniformDataList[8].m_vec3.m_z+=0.1;std::cout<<m_parser->m_uniformDataList[8].m_vec3.m_z<<std::endl; break;
  case Qt::Key_R : m_parser->m_uniformDataList[9].m_vec3.m_x+=0.1;std::cout<<m_parser->m_uniformDataList[9].m_vec3.m_x<<std::endl; break;
  case Qt::Key_Y : m_parser->m_uniformDataList[9].m_vec3.m_y+=0.1;std::cout<<m_parser->m_uniformDataList[9].m_vec3.m_y<<std::endl; break;
  case Qt::Key_J : m_parser->m_uniformDataList[9].m_vec3.m_z+=0.1;std::cout<<m_parser->m_uniformDataList[9].m_vec3.m_z<<std::endl; break;
  case Qt::Key_C : m_parser->m_uniformDataList[5].m_vec3.m_y-=0.05;std::cout<<m_parser->m_uniformDataList[5].m_vec3.m_y<<std::endl; break;
  case Qt::Key_V : m_parser->m_uniformDataList[5].m_vec3.m_z-=0.05;std::cout<<m_parser->m_uniformDataList[5].m_vec3.m_z<<std::endl; break;
  case Qt::Key_Down : m_parser->m_uniformDataList[11].m_vec3.m_x-=0.05;std::cout<<m_parser->m_uniformDataList[11].m_vec3.m_z<<std::endl; break;
  default : break;
  }
  // finally update the GLWindow and re-draw
  //if (isExposed())
    update();
}




NGLScene::~NGLScene()
{;
}

