//------------------------------------------------------------------------------
/// @file MainWindow.h
/// @brief the MainWindow, GUI for our program
/// @author Jonathan Flynn
/// @author Alexander la Tourelle
/// @author Anand Hotwani
/// @author Ellie Ansell
/// @author Adam Ting
/// @author Phil Rouse
/// @author Jonathan Lyddon
/// @version 1.0
/// @date 01/03/16
//------------------------------------------------------------------------------
#ifndef _MAINWINDOW_H__
#define _MAINWINDOW_H__
//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
// System includes
#include <vector>

// Library  includes
#include <ngl/Vec4.h>
#include <QMainWindow>

// Project includes
#include "ButtonLib.h"
#include "Button.h"
#include "Cebitor.h"
#include "NewProjectWizard.h"
#include "NGLScene.h"
#include "ParserLib.h"
#include "Project.h"
#include "Camera.h"
#include "StartupDialog.h"

//------------------------------------------------------------------------------
// Forward declaring some classes to stop cyclic dependencies
//------------------------------------------------------------------------------
class NGLScene;
class StartupDialog;
class ButtonLib;
//------------------------------------------------------------------------------
// Used to inherit the MainWindow from the generated form file ui_MainWindow.h
//------------------------------------------------------------------------------
namespace Ui {
class MainWindow;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/// @class MainWindow
/// @brief our main window class used for holding all the GUI Qt widgets
//------------------------------------------------------------------------------
class MainWindow : public QMainWindow
{
  Q_OBJECT      // must include this if you use Qt signals/slots
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
public:
  //----------------------------------------------------------------------------
  /// @brief Create buttons for the uniforms
  //----------------------------------------------------------------------------
  void                  createButtons();
  //----------------------------------------------------------------------------
  /// @brief Update shader values from the buttons
  //----------------------------------------------------------------------------
  void                  updateShaderValues();
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  /// @brief Constructor for the MainWindow
  /// @param [in] _parent the parent window to create the MainWindow in
  //----------------------------------------------------------------------------
  explicit MainWindow   (QWidget *_parent = 0);
  //----------------------------------------------------------------------------
  /// @brief dtor must close down ngl and release OpenGL resources
  //----------------------------------------------------------------------------
  ~MainWindow();
  //----------------------------------------------------------------------------
  /// @brief set terminal text
  /// @param[in] _txt the text to set in the terminal
  //----------------------------------------------------------------------------
  void                  setTerminalText(QString _txt);
  //----------------------------------------------------------------------------
  /// @brief clear terminal text
  //----------------------------------------------------------------------------
  void                  clearTerminalText();
  //----------------------------------------------------------------------------
  /// @brief show startup dialog
  //----------------------------------------------------------------------------
  void                  showStartDialog();
  //----------------------------------------------------------------------------
  /// @brief Creates a new project wizard
  //----------------------------------------------------------------------------
  bool                  newProjectWiz(QWidget* _parent=0);
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
public slots:
  //----------------------------------------------------------------------------
  /// @brief adds line marker to text editor for _shaderName at lineNum
  /// @param [in] _shaderName Name of the shader type
  /// @param [in] _lineNum line to add error symbol at
  //----------------------------------------------------------------------------
  void                  addError(QString _shaderName, int _lineNum);
  //----------------------------------------------------------------------------
  /// @brief Called when Open button is triggered in File Menu bar
  //----------------------------------------------------------------------------
  void                  on_actionOpen_triggered();
  //----------------------------------------------------------------------------
  /// @brief Called when Export button is triggered in File Menu bar
  //----------------------------------------------------------------------------
  void                  on_actionExport_triggered();
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
private:
  //----------------------------------------------------------------------------
  /// @brief our QScintilla widget1 (vertex)
  //----------------------------------------------------------------------------
  Cebitor*              m_vertQsci;
  //----------------------------------------------------------------------------
  /// @brief our QScintilla widget2 (fragment)
  //----------------------------------------------------------------------------
  Cebitor*              m_fragQsci;
  //----------------------------------------------------------------------------
  /// @brief our openGL widget using NGLScene
  //----------------------------------------------------------------------------
  NGLScene*             m_gl;
  //----------------------------------------------------------------------------
  /// @brief startup Dialog
  //----------------------------------------------------------------------------
  StartupDialog*        m_startDialog;
  //----------------------------------------------------------------------------
  /// @brief The parser library used for the uniform buttons
  //----------------------------------------------------------------------------
  ParserLib*            m_parForButton;
  //----------------------------------------------------------------------------
  /// @brief The project that is used for storing name, directory etc.
  //----------------------------------------------------------------------------
  Project*              m_project;
  //----------------------------------------------------------------------------
  /// @brief The camera settings
  //----------------------------------------------------------------------------
  Camera*               m_camera;
  //----------------------------------------------------------------------------
  /// @brief the generated widgets created from the form using ui_MainWindow.h
  //----------------------------------------------------------------------------
  Ui::MainWindow*       m_ui;
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  ButtonLib*            m_buttonLibrary;
  //----------------------------------------------------------------------------
  /// @brief create QsciScintilla widget in the style of sublime defaults
  /// @param [in] _parent the parent widget to fill with the new Qsci Widget
  //----------------------------------------------------------------------------
  Cebitor*              createQsciWidget(QWidget *_parent = 0);
  //----------------------------------------------------------------------------
  /// @brief loads a text file from a path to a tab
  /// @param [in] _path the location of the file
  /// @param [in] _qsci the QsciScintilla tab to be filled with the file
  //----------------------------------------------------------------------------
  bool                  loadTextFileToTab(QString _path, Cebitor &_qsci);
  //----------------------------------------------------------------------------
  /// @brief Qt Event called when a key is pressed
  /// @param [in] _event the Qt event to query for size etc
  //----------------------------------------------------------------------------
  void                  keyPressEvent(QKeyEvent *_event);
  //----------------------------------------------------------------------------
  /// @brief Centres the window to the monitor's resolution
  //----------------------------------------------------------------------------
  void                  centreWindow();
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
private slots:
  //----------------------------------------------------------------------------
  /// @brief activated when Compile Shader button is clicked
  //----------------------------------------------------------------------------
  void                  on_m_btn_compileShader_clicked();
  //----------------------------------------------------------------------------
  /// @brief Called when a shape action has been triggered to change the render
  /// mesh
  //----------------------------------------------------------------------------
  void                  shapeTriggered();
  //----------------------------------------------------------------------------
  /// @brief Called when Import Mesh is called to change the render mesh
  //----------------------------------------------------------------------------
  void                  objOpened();
  //----------------------------------------------------------------------------
  /// @brief Called when Startup Window button is triggered in File Menu bar
  //----------------------------------------------------------------------------
  void                  on_actionStartup_Window_triggered();
  //----------------------------------------------------------------------------
  /// @brief Called when New button is triggered in File Menu bar
  //----------------------------------------------------------------------------
  void                  on_actionNew_triggered();
  //----------------------------------------------------------------------------
  /// @brief Called when Save Project button is triggered in File Menu bar
  //----------------------------------------------------------------------------
  void                  on_actionSaveProject_triggered();
  //----------------------------------------------------------------------------
  /// @brief Called when Startup Project as button is triggered in File Menu bar
  //----------------------------------------------------------------------------
  void                  on_actionSaveProjectAs_triggered();
  //----------------------------------------------------------------------------
  /// @brief Prints the uniforms and their current values to the terminal
  //----------------------------------------------------------------------------
  void                  printUniforms();
  //----------------------------------------------------------------------------
  /// @brief Called when Load Texture is clicked
  //----------------------------------------------------------------------------
  void                  on_m_actionLoad_Tex_triggered();
  //----------------------------------------------------------------------------
  /// @brief Called when Import Vertex Shader is clicked
  //----------------------------------------------------------------------------
  void                  on_actionImport_Vertex_Shader_triggered();
  //----------------------------------------------------------------------------
  /// @brief Called when Import Fragment Shader is clicked
  //----------------------------------------------------------------------------
  void                  on_actionImport_Fragment_Shader_triggered();
  
};

#endif // _MAINWINDOW_H_
