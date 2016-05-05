#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "project.h"

#include <ngl/Vec4.h>
#include "NGLScene.h"
#include <QMainWindow>
#include "ParserLib.h"
#include "button.h"
#include "Cebitor.h"
#include "StartupDialog.h"
#include "NewProjectWizard.h"
#include <vector>

class NGLScene;
class StartupDialog;

//------------------------------------------------------------------------------
/// @file NGLScene.h
/// @brief the MainWindow class for our program
/// @author Jonathan Flynn
/// @version 1.0
/// @date 01/03/16
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Used to inherit the MainWindow from the generated form file ui_MainWindow.h
//------------------------------------------------------------------------------
namespace Ui {
class MainWindow;
}

//------------------------------------------------------------------------------
/// @class MainWindow
/// @brief our main window used for holding all the Qt widgets
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
  parserLib*            m_parForButton;
  //----------------------------------------------------------------------------
  /// @brief The button list for all the uniforms
  //----------------------------------------------------------------------------
  std::vector<Button*>  m_buttonList;
  //----------------------------------------------------------------------------
  /// @brief The project that is used for storing name, directory etc.
  //----------------------------------------------------------------------------
  Project*              m_project;
  //----------------------------------------------------------------------------
  /// @brief the generated widgets created from the form using ui_MainWindow.h
  //----------------------------------------------------------------------------
  Ui::MainWindow*       m_ui;
  //----------------------------------------------------------------------------
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
  void                  on_m_actionLoad_Texture_triggered();
};

#endif // _MAINWINDOW_H_
