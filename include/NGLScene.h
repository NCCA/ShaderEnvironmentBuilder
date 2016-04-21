#ifndef NGLSCENE_H__
#define NGLSCENE_H__
#include <memory>
#include <unordered_map>
#include <ngl/Camera.h>
#include <ngl/Transformation.h>
#include <ngl/Vec3.h>
#include <ngl/Text.h>
#include <QEvent>
#include <QResizeEvent>
#include <QOpenGLWidget>
#include <QString>
#include "io_xml.h"
#include "json.h"
#include "ParserLib.h"
#include "ngl/Obj.h"
//------------------------------------------------------------------------------------------------------------------------
/// @file NGLScene.h
/// @brief a basic Qt GL widget class for ngl demos
/// @author Jonathan Macey
/// @author Jonathan Flynn
/// @version 1.0
/// @date 01/03/16
/// Revision History :
/// Initial Version 10/10/10 (Binary day ;-0 )
//------------------------------------------------------------------------------------------------------------------------
/// @class NGLScene
/// @brief our main gl widget for NGL applications all drawing elements
/// are put in this file
//------------------------------------------------------------------------------------------------------------------------
class NGLScene : public QOpenGLWidget
{
Q_OBJECT        // must include this if you use Qt signals/slots
  //----------------------------------------------------------------------------------------------------------------------
  //----------------------------------------------------------------------------------------------------------------------
public :
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Constructor for GLWindow
  /// @param [in] _parent the parent window to create the GL context in
  //----------------------------------------------------------------------------------------------------------------------
  NGLScene(QWidget *_parent, parserLib *_libParent );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief dtor must close down ngl and release OpenGL resources
  //----------------------------------------------------------------------------------------------------------------------
  ~NGLScene();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the initialize class is called once when the window is created and
  /// we have a valid GL context
  /// use this to setup any default GL stuff
  //----------------------------------------------------------------------------------------------------------------------
  void initializeGL();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this is called everytime we want to draw the scene
  //----------------------------------------------------------------------------------------------------------------------
  void paintGL();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this is called everytime we resize the scene
  /// note: Qt 5.5.1 must have this implemented and uses it
  /// @param [in] _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void resizeGL(QResizeEvent *_event);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this is called everytime we resize the scene
  /// note: Qt 5.x uses this instead!
  /// http://doc.qt.io/qt-5/qopenglwindow.html#resizeGL
  /// @param [in] _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void resizeGL(int _w, int _h);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief load a shader from a text string
  /// @param [in] _text the string that contains the glsl shader
  /// @param [in] _type the shader type to be stored
  //----------------------------------------------------------------------------------------------------------------------
  void loadShader(QString _text, ngl::ShaderType _type);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief compiles the shader
  //----------------------------------------------------------------------------------------------------------------------
  void compileShader();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief sets the file location you of a mesh
  //----------------------------------------------------------------------------------------------------------------------
  void setMeshLocation(std::string _meshDirectory);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the parser to deal with all the uniform values stored in the shader
  //----------------------------------------------------------------------------------------------------------------------
  parserLib *m_parser;
  //----------------------------------------------------------------------------------------------------------------------

  void importMeshName(const std::string &);

public slots:
  void setShapeType(int _type);
private:
  //----------------------------------------------------------------------------------------------------------------------
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief flag to indicate if the mouse button is pressed when dragging
  //----------------------------------------------------------------------------------------------------------------------
  bool m_rotate;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the x rotation mouse value
  //----------------------------------------------------------------------------------------------------------------------
  int m_spinXFace;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the y rotation mouse value
  //----------------------------------------------------------------------------------------------------------------------
  int m_spinYFace;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief fov value for the camera
  //----------------------------------------------------------------------------------------------------------------------
  float m_fov;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief aspect ratio of the camera
  //----------------------------------------------------------------------------------------------------------------------
  float m_aspect;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief rotation of the teapot
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Vec3 m_rotation;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief flag to indicate if the Right mouse button is pressed when dragging
  //----------------------------------------------------------------------------------------------------------------------
  bool m_translate;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the previous x mouse value
  //----------------------------------------------------------------------------------------------------------------------
  int m_origX;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the previous y mouse value
  //----------------------------------------------------------------------------------------------------------------------
  int m_origY;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the previous x mouse value for Position changes
  //----------------------------------------------------------------------------------------------------------------------
  int m_origXPos;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the previous y mouse value for Position changes
  //----------------------------------------------------------------------------------------------------------------------
  int m_origYPos;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to store the global mouse transforms
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Mat4 m_mouseGlobalTX;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief our camera
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Camera m_cam;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief the model position for mouse movement
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Vec3 m_modelPos;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief transformation stack for the gl transformations etc
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Transformation m_transform;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the view to show wireframe
  //----------------------------------------------------------------------------------------------------------------------
  bool m_wireframe;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief used to load shader files stored in a json file
  //----------------------------------------------------------------------------------------------------------------------
  Json *m_newJson;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief read from xml file
  //----------------------------------------------------------------------------------------------------------------------
  IO_XML *m_readFromXML;

  //----------------------------------------------------------------------------------------------------------------------
  /// @brief method to load transform matrices to the shader
  //----------------------------------------------------------------------------------------------------------------------
  void loadMatricesToShader();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief set the camera shape in the scene
  //----------------------------------------------------------------------------------------------------------------------
  void setCamShape();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Qt Event called when a key is pressed
  /// @param [in] _event the Qt event to query for size etc
  //----------------------------------------------------------------------------------------------------------------------
  void keyPressEvent(QKeyEvent *_event);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called every time a mouse is moved
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void mouseMoveEvent (QMouseEvent * _event );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called everytime the mouse button is pressed
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void mousePressEvent ( QMouseEvent *_event);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called everytime the mouse button is released
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void mouseReleaseEvent ( QMouseEvent *_event );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called everytime the mouse wheel is moved
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void wheelEvent( QWheelEvent *_event);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief export the current uniforms to a file in tempFiles/ParsingOutput
  //----------------------------------------------------------------------------------------------------------------------
  void exportUniforms();
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief defines the mesh type
  //----------------------------------------------------------------------------------------------------------------------
  uint m_shapeType;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief A toggle used to import the .obj m_mesh
  //----------------------------------------------------------------------------------------------------------------------
  bool toggle;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief A string to store the .obj m_mesh directory
  //----------------------------------------------------------------------------------------------------------------------
  std::string m_meshLoc;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Pointer to the VAO m_mesh
  //----------------------------------------------------------------------------------------------------------------------
  std::unique_ptr<ngl::Obj> m_mesh;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief draw an object based on the m_shapeType; e.g. 0=mesh, 1=sphere, etc;
  //----------------------------------------------------------------------------------------------------------------------
  void drawObject(uint _type);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Activate the m_mesh .obj
  //----------------------------------------------------------------------------------------------------------------------
  void toggleFunc();

};

#endif
