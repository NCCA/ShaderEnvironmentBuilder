//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
// System includes

// Engine includes

// Library  includes
#include <QTextStream>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QString>
#include <QLineEdit>

// Project includes
#include "QsciLexerGlsl.h"
#include "CebErrors.h"
#include "NewProjectWizard.h"
#include "MainWindow.h"
#include "ui_MainWindow.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
MainWindow::MainWindow(QWidget *_parent) : QMainWindow(_parent),
  m_ui(new Ui::MainWindow)
{
  m_project = new Project;
  m_camera = new Camera;

  // Setup ui from form creator (MainWindow.ui)
  m_ui->setupUi(this);

  // create parser in main window
  m_parForButton = new ParserLib;

  // Create openGl and qsci widgets, pass in the parser
  m_gl=new  NGLScene(this, m_parForButton);

  m_ui->m_sldr_cameraFov->setValue(65.0f);
  m_ui->m_nearClip->setValue(0.5f);
  m_ui->m_farClip->setValue(150.0f);

  m_gl->setSizePolicy(m_ui->m_f_gl_temp->sizePolicy());
  m_gl->setMinimumSize(m_ui->m_f_gl_temp->minimumSize());

  m_ui->m_vl_tab_camera->setAlignment(Qt::AlignTop);

  // add the openGl window to the interface
  m_ui->m_splitH_editContext->insertWidget(0, m_gl);

  // Delete the template frame from the form designer
  delete(m_ui->m_f_gl_temp);

  // Widget 1 (vertex)
  m_vertQsci = createQsciWidget(m_ui->m_tab_qsci_1);

  // Widget 2 (fragment)
  m_fragQsci = createQsciWidget(m_ui->m_tab_qsci_2);

  // Camera settings
  connect(m_ui->m_nearClip, SIGNAL(valueChanged(double)), m_gl->m_camera, SLOT(setCamNearClip(double)));
  connect(m_ui->m_farClip, SIGNAL(valueChanged(double)), m_gl->m_camera, SLOT(setCamFarClip(double)));
  connect(m_ui->m_cameraRoll, SIGNAL(valueChanged(double)), m_gl->m_camera, SLOT(cameraRoll(double)));
  connect(m_ui->m_cameraYaw, SIGNAL(valueChanged(double)), m_gl->m_camera, SLOT(cameraYaw(double)));
  connect(m_ui->m_cameraPitch, SIGNAL(valueChanged(double)), m_gl->m_camera, SLOT(cameraPitch(double)));
  connect(m_ui->m_sldr_cameraFov, SIGNAL(valueChanged(int)), m_gl->m_camera, SLOT(setCameraFocalLength(int)));
  connect(m_ui->m_comboBox_view, SIGNAL(currentTextChanged(QString)), m_gl->m_camera, SLOT(setCameraShape(QString)));
  connect(m_gl->m_camera, SIGNAL(updateSignal()), m_gl, SLOT(update()));
  connect(m_ui->m_resetCam,SIGNAL(clicked()),m_gl,SLOT(resetObjPos()));

  // Load the text files into the corresponding tabs
  loadTextFileToTab("shaders/PhongVertex.glsl", *m_vertQsci);
  loadTextFileToTab("shaders/PhongFragment.glsl", *m_fragQsci);
  m_buttonLibrary = new ButtonLib(m_parForButton, m_ui->vl_uniforms, m_gl, m_ui->m_w_uniforms);

  // switching between shapes
  connect(m_ui->m_actionLoad_Sphere,SIGNAL(triggered()),this,SLOT(shapeTriggered()));
  connect(m_ui->m_actionLoad_Cube,SIGNAL(triggered()),this,SLOT(shapeTriggered()));
  connect(m_ui->m_actionLoad_Torus,SIGNAL(triggered()),this,SLOT(shapeTriggered()));
  connect(m_ui->m_actionLoad_Teapot ,SIGNAL(triggered()),this,SLOT(shapeTriggered()));
  connect(m_ui->m_actionLoad_Troll,SIGNAL(triggered()),this,SLOT(shapeTriggered()));
  connect(m_ui->m_actionLoad_Dragon,SIGNAL(triggered()),this,SLOT(shapeTriggered()));
  connect(m_ui->m_actionLoad_Bunny,SIGNAL(triggered()),this,SLOT(shapeTriggered()));

  // switching to .obj files
  connect(m_ui->m_actionLoad_Obj,SIGNAL(triggered()),this,SLOT(objOpened()));

  // switching to .jpg files
  connect(m_ui->m_actionLoad_Texture,SIGNAL(triggered()),this,SLOT(on_m_actionLoad_Texture_triggered()));

  // Prints the active uniforms
  connect(m_ui->m_exportUniforms,SIGNAL(clicked()),m_gl,SLOT(exportUniform()));
  connect(m_ui->m_printUniforms ,SIGNAL(clicked()),this,SLOT(printUniforms()));

  // Obj features
  connect(m_ui->m_showNormals,SIGNAL(toggled(bool)),m_gl,SLOT(toggleNormals(bool)));
  connect(m_ui->m_showWireframe,SIGNAL(toggled(bool)),m_gl,SLOT(toggleWireframe(bool)));
  connect(m_ui->m_showGrid,SIGNAL(toggled(bool)),m_gl,SLOT(toggleGrid(bool)));
  connect(m_ui->m_showAxis,SIGNAL(toggled(bool)),m_gl,SLOT(toggleAxis(bool)));
  connect(m_ui->m_normalSize,SIGNAL(valueChanged(int)),m_gl,SLOT(setNormalSize(int)));

  // line marker connections
  connect(m_ui->m_btn_compileShader,SIGNAL(pressed()),m_vertQsci,SLOT(clearErrors()));
  connect(m_ui->m_btn_compileShader,SIGNAL(pressed()),m_fragQsci,SLOT(clearErrors()));
  connect(m_gl,SIGNAL(createLineMarker(QString,int)),this,SLOT(addError(QString,int)));
  connect(m_gl,SIGNAL(initializeGL()), this, SLOT(on_m_btn_compileShader_clicked()));

  update();

  this->setGeometry(
        QStyle::alignedRect(
          Qt::LeftToRight,
          Qt::AlignCenter,
          this->size(),
          qApp->desktop()->availableGeometry()
          )
        );

  m_startDialog = new StartupDialog(this);

}

//------------------------------------------------------------------------------
void MainWindow::on_m_btn_compileShader_clicked()
{
  // read new vertex and fragment source code from text editor
  QString vertSource, fragSource;
  vertSource = m_vertQsci->text();
  fragSource = m_fragQsci->text();

  // compile shader with new vertex and fragment source code
  m_gl->compileShader(vertSource,fragSource);

  // update uniform buttons
  m_buttonLibrary->updateButtons();
  m_buttonLibrary->updateShaderValues();
}

//------------------------------------------------------------------------------
void MainWindow::printUniforms()
{
  m_parForButton->printUniforms();
}

//------------------------------------------------------------------------------
Cebitor *MainWindow::createQsciWidget(QWidget *_parent)
{
  // Create the QsciScintilla widget
  Cebitor* qsci = new Cebitor(_parent);
  QBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(qsci);

  // Create search bar widget
  QWidget *searchWidget = new QWidget(_parent);
  QBoxLayout *searchLayout = new QVBoxLayout(searchWidget);
  searchLayout->setMargin(0);
  QLineEdit *qsciSearch = new QLineEdit(searchWidget);
  QPushButton *searchNextBtn = new QPushButton(QString("Find Next"),searchWidget);
  QPushButton *searchPrevBtn = new QPushButton(QString("Find Previous"),searchWidget);
  qsci->setSearchWidget(searchWidget);
  qsci->setSearchLineEdit(qsciSearch);

  // Connect search widget signals to editor slots
  connect(qsciSearch,SIGNAL(textChanged()),qsci,SLOT(highlightAllSearch()));
  connect(qsciSearch,SIGNAL(returnPressed()),qsci,SLOT(searchNext()));
  connect(searchNextBtn,SIGNAL(pressed()),qsci,SLOT(searchNext()));
  connect(searchPrevBtn,SIGNAL(pressed()),qsci,SLOT(searchPrev()));

  QAction *escAction = new QAction(this);
  escAction->setShortcut(Qt::Key_Escape);
  connect(escAction, SIGNAL(triggered()), qsci, SLOT(toggleSearchBox()));
  qsciSearch->addAction(escAction);

  searchLayout->setDirection(QBoxLayout::Direction::LeftToRight);
  searchLayout->addWidget(qsciSearch);
  searchLayout->addWidget(searchNextBtn);
  searchLayout->addWidget(searchPrevBtn);

  layout->addWidget(searchWidget);

  searchWidget->hide();

  _parent->setLayout(layout);

  return qsci;
}

//------------------------------------------------------------------------------
bool MainWindow::loadTextFileToTab(QString _path, Cebitor &_qsci)
{
  QString text;
  QFile file(_path);

  // Open the file as readonly and text and ensure it loaded correctly
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    // Raise an error if failed
    CEBRaise::QtFileError(file.error(), _path);
    return false;
  }

  // Fead the text into the tab if successful
  QTextStream in(&file);
  text = in.readAll();
  _qsci.setText(text);

  return true;
}

//------------------------------------------------------------------------------
void MainWindow::objOpened()
{
  // Open a file dialog and return a file directory
  QString fileName=QFileDialog::getOpenFileName(this,
                                                tr("Open Mesh"),
                                                "0Features-0BugsCVA3/",
                                                tr("Image Files (*.obj)"));
  std::string importName=fileName.toStdString();
  // Import the mesh
  m_gl->importMeshName(importName);
}

//------------------------------------------------------------------------------
void MainWindow::shapeTriggered()
{
  //get the action
  QAction *action = static_cast<QAction*>(sender());
  int a=0;
  // apply a different shape depending on the button clicked
  if (action==m_ui->m_actionLoad_Sphere)  {   a=1;  }
  if (action==m_ui->m_actionLoad_Cube)    {   a=2;  }
  if (action==m_ui->m_actionLoad_Torus)   {   a=3;  }
  if (action==m_ui->m_actionLoad_Teapot)  {   a=4;  }
  if (action==m_ui->m_actionLoad_Troll)   {   a=5;  }
  if (action==m_ui->m_actionLoad_Dragon)  {   a=6;  }
  if (action==m_ui->m_actionLoad_Bunny)   {   a=7;  }
  //set the shape
  m_gl->setShapeType(a);
}

//------------------------------------------------------------------------------
void MainWindow::setTerminalText(QString _txt)
{
  m_ui->m_pte_terminal->setPlainText(_txt);
}

//------------------------------------------------------------------------------
void MainWindow::clearTerminalText()
{
  m_ui->m_pte_terminal->clear();
}

//------------------------------------------------------------------------------
void MainWindow::on_actionStartup_Window_triggered()
{
  m_startDialog->show();
}

//------------------------------------------------------------------------------
void MainWindow::showStartDialog()
{
  m_startDialog->show();
}

//------------------------------------------------------------------------------
bool MainWindow::newProjectWiz(QWidget* _parent)
{
  NewProjectWizard *projectWiz = new NewProjectWizard(_parent);
  bool success = projectWiz->exec();
  if (success)
  {
    const OutputData *output = projectWiz->getOutput();
    m_project->set(output->m_projectName, output->m_projectDir, false);
    m_vertQsci->setText(output->m_vertSource);
    m_fragQsci->setText(output->m_fragSource);
    QString vertSource, fragSource;
    vertSource = m_vertQsci->text();
    fragSource = m_fragQsci->text();
    std::cout<<m_project->getName()<<std::endl;
    m_gl->setProject(m_project->getName(), vertSource,fragSource);
  }
  else
  {
    // qDebug() << "FAIL";
  }
  delete projectWiz;
  return success;
}

//------------------------------------------------------------------------------
void MainWindow::on_actionNew_triggered()
{
  newProjectWiz(this);
}

//------------------------------------------------------------------------------
void MainWindow::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  switch (_event->key())
  {
    case Qt::Key_W : {m_ui->m_showWireframe->toggle(); break;}
    case Qt::Key_N : {m_ui->m_showNormals->toggle();   break;}
    case Qt::Key_G : {m_ui->m_showGrid->toggle();      break;}
    case Qt::Key_F : {m_gl->resetObjPos();             break;}
  }
  update();
}

//------------------------------------------------------------------------------
void MainWindow::on_actionSaveProject_triggered()
{
  m_project->save(m_vertQsci->text(), m_fragQsci->text());
}

//------------------------------------------------------------------------------
void MainWindow::on_actionSaveProjectAs_triggered()
{
  m_project->saveAs(m_vertQsci->text(), m_fragQsci->text());
}

//------------------------------------------------------------------------------
void MainWindow::on_actionOpen_triggered()
{
  // read file directory from dialog
  QString fileDir=QFileDialog::getOpenFileName(this,
                                               tr("Open Project"),
                                               "0Features-0BugsCVA3/",
                                               tr("XML Files (*.xml)"));
  string fileDirectory = "";
  if( !fileDir.isEmpty() )
  {
     QString vertSource, fragSource;
     fileDirectory = fileDir.toStdString();
     // load project data
     m_project->load(fileDirectory, vertSource, fragSource);
     // set the text editor strings
     m_vertQsci->setText(vertSource);
     m_fragQsci->setText(fragSource);
     // set proect data in scene for shader manager
     m_gl->setProject(m_project->getName(), vertSource,fragSource);
  }
}

//------------------------------------------------------------------------------
void MainWindow::on_actionExport_triggered()
{
  QFileDialog dialog(this);
  dialog.setFileMode(QFileDialog::Directory);
  dialog.setOption(QFileDialog::ShowDirsOnly);
  dialog.setDirectory(QString(m_project->getDir().c_str()));
  QStringList dirNames;
  if (dialog.exec())
  {
    dirNames = dialog.selectedFiles();
    m_project->exportProject(dirNames.at(0).toStdString(),
                             m_vertQsci->text(),
                             m_fragQsci->text());
  }

}

//------------------------------------------------------------------------------
void MainWindow::on_m_actionLoad_Texture_triggered()
{
  // Open a file dialog and return a file directory
  QString fileName=QFileDialog::getOpenFileName(this,
                                              tr("Open Texture Map"),
                                              "0Features-0BugsCVA3/",
                                              tr("Image Files (*.jpg)"));
  // load texture map to OBJ
  std::string importName=fileName.toStdString();
  m_gl->importTextureMap(importName);
}

//------------------------------------------------------------------------------
void MainWindow::addError(QString _shaderName, int _lineNum)
{
  Cebitor * cebitorInstance;
  if(_shaderName==QString("Vertex"))
  {
    cebitorInstance = m_vertQsci;
  }
  if(_shaderName==QString("Fragment"))
  {
    cebitorInstance = m_fragQsci;
  }
  cebitorInstance->markerAdd(_lineNum,Cebitor::MarkerType::ERROR);
}

//------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
  delete m_ui;
}
