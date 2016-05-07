//------------------------------------------------------------------------------
/// @file NGLScene.h
/// @brief a modified Qt GL widget class for
/// @author Jonathan Macey
/// @author Jonathan Flynn
/// @author Anand Hotwani
/// @author Alexander la Tourelle
/// @version 1.0
/// @date 01/03/16
/// Revision History :
/// Initial Version 10/10/10 (Binary day ;-0 )
//------------------------------------------------------------------------------
#ifndef _NGLSCENE_H__
#define _NGLSCENE_H__
//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
// System includes
#include <memory>
#include <unordered_map>

// Engine includes

// Library  includes
#include <ngl/Camera.h>
#include <ngl/Obj.h>
#include <ngl/Transformation.h>
#include <ngl/Vec3.h>
#include <ngl/Text.h>
#include <QEvent>
#include <QResizeEvent>
#include <QOpenGLWidget>
#include <QString>

// Project includes
#include "Camera.h"
#include "Io_xml.h"
#include "Json.h"
#include "MainWindow.h"
#include "ParserLib.h"
#include "ShaderManager.h"

//------------------------------------------------------------------------------
// Forward declare of MainWindow to stop cyclic dependencies
//------------------------------------------------------------------------------
class MainWindow;
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/// @class NGLScene
/// @brief our main gl widget for NGL applications all drawing elements
/// are put in this file
//------------------------------------------------------------------------------
class NGLScene : public QOpenGLWidget
{
Q_OBJECT        // must include this if you use Qt signals/slots
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
public :
  //----------------------------------------------------------------------------
  /// @brief the parser to deal with all the uniform values stored in the shader
  /// @todo Should be private and have get method
  //----------------------------------------------------------------------------
  ParserLib*                  m_parser;
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  /// @brief Constructor for GLWindow
  /// @param [in] _parent the parent window to create the GL context in
  //----------------------------------------------------------------------------
  NGLScene                    (QWidget *_parent, ParserLib *_libParent);
  //----------------------------------------------------------------------------
  /// @brief dtor must close down ngl and release OpenGL resources
  //----------------------------------------------------------------------------
  ~NGLScene();
  //----------------------------------------------------------------------------
  /// @brief this is called everytime we want to draw the scene
  //----------------------------------------------------------------------------
  void                        paintGL();
  //----------------------------------------------------------------------------
  /// @brief this is called everytime we resize the scene
  /// note: Qt 5.5.1 must have this implemented and uses it
  /// @param [in] _event the Qt Event structure
  //----------------------------------------------------------------------------
  void                        resizeGL(QResizeEvent *_event);
  //----------------------------------------------------------------------------
  /// @brief this is called everytime we resize the scene
  /// note: Qt 5.x uses this instead!
  /// http://doc.qt.io/qt-5/qopenglwindow.html#resizeGL
  /// @param [in] _event the Qt Event structure
  //----------------------------------------------------------------------------
  void                        resizeGL(int _w, int _h);
  //----------------------------------------------------------------------------
  /// @brief loads and compiles a shader from Qstrings passed from the text
  /// editor
  /// @param[in] _vertSource the Qstring containing the vertex shader source
  /// code
  /// @param[in] _fragSource the Qstring containing the fragment shader source
  /// code
  //----------------------------------------------------------------------------
  void                        compileShader(QString _vertSource,
                                            QString _fragSource);
  //----------------------------------------------------------------------------
  /// @brief sets the file location you of a mesh
  //----------------------------------------------------------------------------
  void                        setMeshLocation(std::string _meshDirectory);
  //----------------------------------------------------------------------------
  /// @brief Creates a new project for the shader
  /// @param[in] _name the name of the project
  /// @param[in] _vertSource the text that makes of the vertex shader
  /// @param[in] _fragSource The text that makes up the fragment shader
  //----------------------------------------------------------------------------
  void                        setProject(std::string _name, QString _vertSource,
                                         QString _fragSource);
  //----------------------------------------------------------------------------
  /// @brief Changes the name of the m_mesh object directory
  /// @param[in] the new directory  used to draw m_mesh
  //----------------------------------------------------------------------------
  void                        importMeshName(const std::string &_name);
  //----------------------------------------------------------------------------
  /// @brief loads in a texture map and directly applies it to the OBJ.
  /// (Requires UVs)
  /// @param[in] the desired directory of the texture map
  //----------------------------------------------------------------------------
  void                        importTextureMap(const std::string &_name);
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
public slots:
  //----------------------------------------------------------------------------
  /// @brief the initialize class is called once when the window is created and
  /// we have a valid GL context
  /// use this to setup any default GL stuff
  //----------------------------------------------------------------------------
  void                        initGL();
  //----------------------------------------------------------------------------
  /// @brief sets the shape type
  /// @param[in] _type is the type of object drawn
  //----------------------------------------------------------------------------
  void                        setShapeType(int _type);
  //----------------------------------------------------------------------------
  /// @brief toggles the wireframe visibility
  /// @param[in] _state true=on false=off
  //----------------------------------------------------------------------------
  void                        toggleWireframe(bool _state);
  //----------------------------------------------------------------------------
  /// @brief toggles the normals visibility
  /// @param[in] _state true=on false=off
  //----------------------------------------------------------------------------
  void                        toggleNormals(bool _state);
  //----------------------------------------------------------------------------
  /// @brief toggles the axis visibility
  /// @param[in] _state true=on false=off
  //----------------------------------------------------------------------------
  void                        toggleAxis(bool _state);
  //----------------------------------------------------------------------------
  /// @brief toggles the grid visibility
  /// @param[in] _state true=on false=off
  //----------------------------------------------------------------------------
  void                        toggleGrid(bool _state);
  //----------------------------------------------------------------------------
  /// @brief sets the normal size
  /// @param[in] _size the normal size.....the normal size will be divided by
  /// 100
  //----------------------------------------------------------------------------
  void                        setNormalSize(int _size);
  //----------------------------------------------------------------------------
  /// @brief exports the uniforms and writes them to the file ParsingOutput.txt
  //----------------------------------------------------------------------------
  void                        exportUniform();
  //----------------------------------------------------------------------------
  /// @brief Function to set camera FOV
  /// @param[in] _focalLength the FOV value to set
  //----------------------------------------------------------------------------
  void                        setCameraFocalLength(int _focalLength);
  //----------------------------------------------------------------------------
  /// @brief Sets camera shape (persp, top, bottom, side)
  /// @param[in] _view the camara shape as either (persp, top, bottom, side)
  /// @todo Should change this to an ENUM instead of string
  //----------------------------------------------------------------------------
  void                        setCameraShape(QString _view);
  //----------------------------------------------------------------------------
  /// @brief Sets camera Roll
  /// @param[in] _roll the new roll value
  //----------------------------------------------------------------------------
  void                        setCameraRoll(double _roll);
  //----------------------------------------------------------------------------
  /// @brief Sets camera Yaw
  /// @param[in] _yaw the new yaw value
  //----------------------------------------------------------------------------
  void                        setCameraYaw(double _yaw);
  //----------------------------------------------------------------------------
  /// @brief Sets camera Pitch
  /// @param[in] _pitch the new pitch value
  //----------------------------------------------------------------------------
  void                        setCameraPitch(double _pitch);
  //----------------------------------------------------------------------------
  /// @brief resets the position of the active OBJ in the OpenGL context
  //----------------------------------------------------------------------------
  void                        resetObjPos();
  //----------------------------------------------------------------------------
  /// @brief Set camera near clipping plane
  /// @param[in] _nearClip the new Near Clip value
  //----------------------------------------------------------------------------
  void                        setCamNearClip(double _nearClip);
  //----------------------------------------------------------------------------
  /// @brief Set camera far clipping plane
  /// @param[in] _farClip the new Far clip value
  //----------------------------------------------------------------------------
  void                        setCamFarClip(double _farClip);
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
signals:
  //----------------------------------------------------------------------------
  /// @brief signal to create a line marker
  /// @param[in] _shaderName the shader name of the error in the GLSL file
  /// @param[in] _lineNum the line number of the error in the GLSL file
  //----------------------------------------------------------------------------
  void                        createLineMarker(QString _shaderName,
                                               int _lineNum);
  //----------------------------------------------------------------------------
  /// @brief the signal for initialize GL
  //----------------------------------------------------------------------------
  void                        initializeGL();
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
private:
  //----------------------------------------------------------------------------
  /// @brief flag to indicate if the mouse button is pressed when dragging
  //----------------------------------------------------------------------------
  bool                        m_rotate;
  //----------------------------------------------------------------------------
  /// @brief used to store the x rotation mouse value
  //----------------------------------------------------------------------------
  int                         m_spinXFace;
  //----------------------------------------------------------------------------
  /// @brief used to store the y rotation mouse value
  //----------------------------------------------------------------------------
  int                         m_spinYFace;
  //----------------------------------------------------------------------------
  /// @brief fov value for the camera
  //----------------------------------------------------------------------------
  float                       m_fov;
  //----------------------------------------------------------------------------
  /// @brief fov value for the camera
  //----------------------------------------------------------------------------
  float                       m_nearClip;
  //----------------------------------------------------------------------------
  /// @brief fov value for the camera
  //----------------------------------------------------------------------------
  float                       m_farClip;
  //----------------------------------------------------------------------------
  /// @brief aspect ratio of the camera
  //----------------------------------------------------------------------------
  float                       m_aspect;
  //----------------------------------------------------------------------------
  /// @brief rotation of the teapot
  //----------------------------------------------------------------------------
  ngl::Vec3                   m_rotation;
  //----------------------------------------------------------------------------
  /// @brief flag to indicate if the Right mouse button is pressed when dragging
  //----------------------------------------------------------------------------
  bool                        m_translate;
  //----------------------------------------------------------------------------
  /// @brief the previous x mouse value
  //----------------------------------------------------------------------------
  int                         m_origX;
  //----------------------------------------------------------------------------
  /// @brief the previous y mouse value
  //----------------------------------------------------------------------------
  int                         m_origY;
  //----------------------------------------------------------------------------
  /// @brief the previous x mouse value for Position changes
  //----------------------------------------------------------------------------
  int                         m_origXPos;
  //----------------------------------------------------------------------------
  /// @brief the previous y mouse value for Position changes
  //----------------------------------------------------------------------------
  int                         m_origYPos;
  //----------------------------------------------------------------------------
  /// @brief used to store the global mouse transforms
  //----------------------------------------------------------------------------
  ngl::Mat4                   m_mouseGlobalTX;
  //----------------------------------------------------------------------------
  /// @brief our camera
  //----------------------------------------------------------------------------
  ngl::Camera                 m_cam;
  //----------------------------------------------------------------------------
  /// @brief the model position for mouse movement
  //----------------------------------------------------------------------------
  ngl::Vec3                   m_modelPos;
  //----------------------------------------------------------------------------
  /// @brief transformation stack for the gl transformations etc
  //----------------------------------------------------------------------------
  ngl::Transformation         m_transform;
  //----------------------------------------------------------------------------
  /// @brief set the view to show wireframe
  //----------------------------------------------------------------------------
  bool                        m_wireframe;
  //----------------------------------------------------------------------------
  /// @brief read from xml file
  //----------------------------------------------------------------------------
  IO_XML*                     m_readFromXML;
  /// @brief the main window that is the GUI
  //----------------------------------------------------------------------------
  MainWindow*                 m_window;
  //----------------------------------------------------------------------------
  /// @brief defines the mesh type
  //----------------------------------------------------------------------------
  uint                        m_shapeType;
  //----------------------------------------------------------------------------
  /// @brief A toggle used to import the .obj m_mesh
  //----------------------------------------------------------------------------
  bool                        m_toggleObj;
  //----------------------------------------------------------------------------
  /// @brief A toggle used to turn axis on and off
  //----------------------------------------------------------------------------
  bool                        m_toggleAxis;
  //----------------------------------------------------------------------------
  /// @brief A toggle used to draw normals
  //----------------------------------------------------------------------------
  bool                        m_drawNormals;
  //----------------------------------------------------------------------------
  /// @brief A toggle used to draw a grid
  //----------------------------------------------------------------------------
  bool                        m_drawGrid;
  //----------------------------------------------------------------------------
  /// @brief Stores the size of the normal
  //----------------------------------------------------------------------------
  float                       m_normalSize;
  //----------------------------------------------------------------------------
  /// @brief stores the texture name
  //----------------------------------------------------------------------------
  GLuint                      m_textureName;
  //----------------------------------------------------------------------------
  /// @brief If there is a shader error or not
  //----------------------------------------------------------------------------
  bool                        m_shaderError;
  //----------------------------------------------------------------------------
  /// @brief Stores the shader manager which handles the setup and maintenance
  /// of shaders
  //----------------------------------------------------------------------------
  ShaderManager*              m_shaderManager;
  //----------------------------------------------------------------------------
  /// @brief Pointer to inherit camera class
  //----------------------------------------------------------------------------
  Camera*                     m_camera;
  //----------------------------------------------------------------------------
  /// @brief An index to access the cameras
  //----------------------------------------------------------------------------
  std::vector <ngl::Camera>   m_cameras;
  //----------------------------------------------------------------------------
  /// @brief An index to access the cameras
  //----------------------------------------------------------------------------
  int                         m_cameraIndex;
  //----------------------------------------------------------------------------
  /// @brief A string to store the .obj m_mesh directory
  //----------------------------------------------------------------------------
  std::string                 m_meshLoc;
  //----------------------------------------------------------------------------
  /// @brief Pointer to the VAO m_mesh
  //----------------------------------------------------------------------------
  std::unique_ptr<ngl::Obj>   m_mesh;
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  /// @brief this method is called every time a mouse is moved
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------
  void                        mouseMoveEvent(QMouseEvent * _event );
  //----------------------------------------------------------------------------
  /// @brief this method is called everytime the mouse button is pressed
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------
  void                        mousePressEvent(QMouseEvent *_event);
  //----------------------------------------------------------------------------
  /// @brief this method is called everytime the mouse button is released
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------
  void                        mouseReleaseEvent(QMouseEvent *_event);
  //----------------------------------------------------------------------------
  /// @brief method to load transform matrices to the shader
  //----------------------------------------------------------------------------
  void                        loadMatricesToShader();
  //----------------------------------------------------------------------------
  /// @brief set the camera shape in the scene
  //----------------------------------------------------------------------------
  void                        setCamShape();
  //----------------------------------------------------------------------------
  /// @brief this method is called everytime the mouse wheel is moved
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------
  void                        wheelEvent(QWheelEvent *_event);
  //----------------------------------------------------------------------------
  /// @brief this method should be called every time a keyboard button is
  /// pressed. Inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------
  void                        keyPressEvent(QKeyEvent *_event);
  //----------------------------------------------------------------------------
  /// @brief Set object transformations depending on the shape type
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------
  void                        objectTransform(uint _type);
  //----------------------------------------------------------------------------
  /// @brief Stores a QString. Used to edit the error log message
  //----------------------------------------------------------------------------
  QString                     parseErrorLog(QString);
  //----------------------------------------------------------------------------
  /// @brief Draw a xyz axis
  /// @param _pos is the position that the axis is drawn relative to the origin
  //----------------------------------------------------------------------------
  void                        drawAxis(ngl::Vec3 _pos);
  //----------------------------------------------------------------------------
  /// @brief draw an object based on the m_shapeType; e.g. 0=mesh, 1=sphere, etc
  //----------------------------------------------------------------------------
  void                        drawObject(uint _type);
  //----------------------------------------------------------------------------
  /// @brief Activate the m_mesh .obj
  //----------------------------------------------------------------------------
  void                        toggleObj();
  //----------------------------------------------------------------------------
  /// @brief set the camera shape in the scene
  //----------------------------------------------------------------------------
  void                        createCamera();
};
#endif // _NGLSCENE_H__
