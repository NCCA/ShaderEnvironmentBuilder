#ifndef NGLSCENE_H__
#define NGLSCENE_H__
#include "json.h"
#include "io_xml.h"
#include <ngl/Camera.h>
#include <ngl/Transformation.h>
#include <ngl/Vec3.h>
#include <ngl/Text.h>
#include <QEvent>
#include <QResizeEvent>
#include <QOpenGLWidget>
#include <memory>
#include <QOpenGLWindow>
#include <unordered_map>
#include "parserLib.h"

//----------------------------------------------------------------------------------------------------------------------
/// @file NGLScene.h
/// @brief a basic Qt GL window class for ngl demos
/// @author Jonathan Macey
/// @version 1.0
/// @date 10/10/10
/// Revision History :
/// Initial Version 10/10/10 (Binary day ;-0 )
/// @class GLWindow
/// @brief our main glwindow widget for NGL applications all drawing elements are
/// put in this file
class NGLScene : public QOpenGLWidget
{
Q_OBJECT        // must include this if you use Qt signals/slots
public :
  /// @brief Constructor for GLWindow
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief Constructor for GLWindow
  /// @param [in] _parent the parent window to create the GL context in
  //----------------------------------------------------------------------------------------------------------------------
  NGLScene(QWidget *_parent );

  bool m_rotate;

  int m_spinXFace;

  int m_spinYFace;

  /// @brief dtor
	~NGLScene();

private :
	/// @brief m_wireframe mode
	bool m_wireframe;
	/// @brief rotation data
  ngl::Vec3 m_rotation;
	/// @brief scale data
  ngl::Vec3 m_scale;
	/// @brief position data
  ngl::Vec3 m_position;
	/// @brief our object to draw
	int m_selectedObject;
	//----------------------------------------------------------------------------------------------------------------------
	// text for rendering
	//----------------------------------------------------------------------------------------------------------------------
	std::unique_ptr<ngl::Text> m_text;

protected:

  /// @brief  The following methods must be implimented in the sub class
  /// this is called when the window is created
  void initializeGL();

  /// @brief this is called whenever the window is re-sized
  /// @param[in] _w the width of the resized window
  /// @param[in] _h the height of the resized window
  void resizeGL(QResizeEvent *_event);
  /// @brief this is the main gl drawing routine which is called whenever the window needs to
  // be re-drawn
  void paintGL();

	/// @brief our camera
	ngl::Camera m_cam;
	/// @brief our transform for objects
	ngl::Transformation m_transform;
  ngl::Mat4 m_mouseGlobalTX;
private :
  /// @brief this method is called every time a mouse is moved
  /// @param _event the Qt Event structure
  void mouseMoveEvent (QMouseEvent * _event   );

    ///--------------------------------------------------------------------------------------------------------
    Json *Jsons;
  /// @brief this method is called everytime the mouse button is pressed
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  void keyPressEvent ( QKeyEvent *_event  );

    parserLib *m_parser;

  IO_XML *m_readFromXML;
  Json *m_newJson;


  void loadMatricesToShader( );
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief window width
  //----------------------------------------------------------------------------------------------------------------------
  int m_width;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief window height
  //----------------------------------------------------------------------------------------------------------------------
  int m_height;

};

#endif
