#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "QsciLexerGlsl.h"
#include "CebErrors.h"

#include "QString"
#include "NewProjectWizard.h"

#include <QTextStream>
#include <QFileDialog>
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *_parent) : QMainWindow(_parent),
                                           m_ui(new Ui::MainWindow)
{
  // Setup ui from form creator (MainWindow.ui)
  m_ui->setupUi(this);
  // create parser in main window
  m_parForButton = new parserLib;
  // Create openGl and qsci widgets, pass in the parser
  m_gl=new  NGLScene(this, m_parForButton);

  m_gl->setSizePolicy(m_ui->m_f_gl_temp->sizePolicy());
  m_gl->setMinimumSize(m_ui->m_f_gl_temp->minimumSize());

  // add the openGl window to the interface
  m_ui->m_splitH_editContext->insertWidget(0, m_gl);
  // Delete the template frame from the form designer
  delete(m_ui->m_f_gl_temp);

  // Widget 1 (vertex)
  m_qsci1 = createQsciWidget(m_ui->m_tab_qsci_1);

  // Widget 2 (fragment)
  m_qsci2 = createQsciWidget(m_ui->m_tab_qsci_2);


  // Set the combo box initially to VERTEX
  // Camera Settings
   connect(m_ui->m_sldr_cameraFov,SIGNAL(valueChanged(int)),m_gl,SLOT(setCameraFocalLength(int)));
   connect(m_ui->m_cameraRoll, SIGNAL(valueChanged(double)), m_gl, SLOT(setCameraRoll(double)));
   connect(m_ui->m_cameraYaw, SIGNAL(valueChanged(double)), m_gl, SLOT(setCameraYaw(double)));
   connect(m_ui->m_comboBox_view, SIGNAL(currentTextChanged(QString)), m_gl, SLOT(setCameraShape(QString)));

  // Load the text files into the corresponding tabs
  loadTextFileToTab("shaders/PhongVertex.glsl", *m_qsci1);
  loadTextFileToTab("shaders/PhongFragment.glsl", *m_qsci2);

  // switching between shapes
  connect(m_ui->m_actionLoad_Sphere,SIGNAL(triggered()),this,SLOT(on_actionLoad_shape_triggered()));
  connect(m_ui->m_actionLoad_Cube,SIGNAL(triggered()),this,SLOT(on_actionLoad_shape_triggered()));
  connect(m_ui->m_actionLoad_Torus,SIGNAL(triggered()),this,SLOT(on_actionLoad_shape_triggered()));
  connect(m_ui->m_actionLoad_Teapot ,SIGNAL(triggered()),this,SLOT(on_actionLoad_shape_triggered()));
  connect(m_ui->m_actionLoad_Troll,SIGNAL(triggered()),this,SLOT(on_actionLoad_shape_triggered()));
  connect(m_ui->m_actionLoad_Dragon,SIGNAL(triggered()),this,SLOT(on_actionLoad_shape_triggered()));
  connect(m_ui->m_actionLoad_Bunny,SIGNAL(triggered()),this,SLOT(on_actionLoad_shape_triggered()));
  // switching to .obj files
  connect(m_ui->m_actionLoad_Obj,SIGNAL(triggered()),this,SLOT(on_actionLoad_obj_opened()));

  connect(m_ui->m_exportUniforms,SIGNAL(clicked()),m_gl,SLOT(exportUniform()));
  connect(m_ui->m_printUniforms ,SIGNAL(clicked()),this,SLOT(printUniforms()));

  connect(m_ui->m_showNormals,SIGNAL(toggled(bool)),m_gl,SLOT(toggleNormals(bool)));
  connect(m_ui->m_showWireframe,SIGNAL(toggled(bool)),m_gl,SLOT(toggleWireframe(bool)));
  connect(m_ui->m_showGrid,SIGNAL(toggled(bool)),m_gl,SLOT(toggleGrid(bool)));
  connect(m_ui->m_showAxis,SIGNAL(toggled(bool)),m_gl,SLOT(toggleAxis(bool)));

  connect(m_ui->m_normalSize,SIGNAL(valueChanged(int)),m_gl,SLOT(setNormalSize(int)));


  update();
  //std::cerr<<"Find number of active uniforms: "<<m_parForButton->m_num<<std::endl;

  this->setGeometry(
      QStyle::alignedRect(
          Qt::LeftToRight,
          Qt::AlignCenter,
          this->size(),
          qApp->desktop()->availableGeometry()
      )
  );

  m_startDialog = new StartupDialog(this);

  m_project = new Project;
}

//----------------------------------------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete m_ui;
}

//----------------------------------------------------------------------------------------------------------------------
void MainWindow::on_m_btn_compileShader_clicked()
{
  QString vertSource, fragSource;
  vertSource = m_qsci1->text();
  fragSource = m_qsci2->text();
  m_gl->compileShader(vertSource,fragSource);
  createButtons();
  updateShaderValues();
}

void MainWindow::printUniforms()
{
  m_parForButton->printUniforms();
}

void MainWindow::createButtons()
{
  if(m_buttonList.size()==0)
  {
    for(unsigned int i=0;i<m_parForButton->m_num; ++i)
    {
      if(m_parForButton->m_uniformList[i]->getTypeName()=="vec4")
      {
        QString _tempName = QString::fromStdString(m_parForButton->m_uniformList[i]->getName());
        ngl::Vec4 _tempVec=m_parForButton->m_uniformList[i]->getVec4();
        colourButton *tempButton = new colourButton(_tempName, m_ui->vl_uniforms, i, m_ui->m_w_uniforms);
        tempButton->setColour(_tempVec);

        m_buttonList.push_back(tempButton);
      }
      if(m_parForButton->m_uniformList[i]->getTypeName()=="float")
      {
        QString _tempName = QString::fromStdString(m_parForButton->m_uniformList[i]->getName());
        float _tempFloat=m_parForButton->m_uniformList[i]->getFloat();
        floatButton *tempButton = new floatButton(_tempName, m_ui->vl_uniforms, i, m_ui->m_w_uniforms);
        tempButton->setValue(_tempFloat);

        m_buttonList.push_back(tempButton);
      }
    }
  }
}

void MainWindow::updateShaderValues()
{
  for(auto uniform: m_parForButton->m_uniformList)
  {
    if(uniform->getTypeName()=="vec4")
    {
      for(auto button: m_buttonList)
      {
        if(uniform->getLocation()==button->getID())
        {
          ngl::Vec4 temp = button->getColour();
          qDebug()<<temp.m_x<<", "<<temp.m_y<<", "<<temp.m_z<<"\n";
          uniform->setVec4(temp);
          break;
        }
      }

    }
    if(uniform->getTypeName()=="float")
    {
      for(auto button: m_buttonList)
      {
        if(uniform->getLocation()==button->getID())
        {
          float temp = button->getValue();
          uniform->setFloat(temp);
          break;
        }
      }

    }
  }
}

//----------------------------------------------------------------------------------------------------------------------
Cebitor *MainWindow::createQsciWidget(QWidget *_parent)
{
  // Create the QsciScintilla widget
  Cebitor* qsci = new Cebitor(_parent);
  QBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(qsci);
  _parent->setLayout(layout);

  return qsci;
}
//----------------------------------------------------------------------------------------------------------------------
bool MainWindow::loadTextFileToTab(QString _path, Cebitor &_qsci)
{
  QString text;
  QFile file(_path);

  // Open the file as readonly and text and ensure it loaded correctly
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    // Raise an error if failed
    ceb_raise::QtFileError(file.error(), _path);
    return false;
  }

  // Fead the text into the tab if successful
  QTextStream in(&file);
  text = in.readAll();
  _qsci.setText(text);

  return true;
}

//----------------------------------------------------------------------------------------------------------------------
void MainWindow::on_actionLoad_obj_opened()
{
  // Open a file dialog and return a file directory
  QString fileName=QFileDialog::getOpenFileName(this,
  tr("Open Mesh"),"0Features-0BugsCVA3/",tr("Image Files (*.obj)"));

  std::string importName=fileName.toStdString();
  // Import the mesh
  m_gl->importMeshName(importName);
}

void MainWindow::on_actionLoad_shape_triggered()
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
void MainWindow::setTerminalText(QString _txt)
{
  m_ui->m_pte_terminal->setPlainText(_txt);
}

void MainWindow::clearTerminalText()
{
  m_ui->m_pte_terminal->clear();
}

void MainWindow::on_actionStartup_Window_triggered()
{
  m_startDialog->show();
}

void MainWindow::showStartDialog()
{
  m_startDialog->show();
}

void MainWindow::on_actionNew_triggered()
{
  NewProjectWizard *projectWiz = new NewProjectWizard(this);
  if (projectWiz->exec())
  {
    m_project->set(projectWiz->m_output->m_projectName, projectWiz->m_output->m_projectDir);
    m_gl->newProject(m_project->getName());
    m_qsci1->setText(projectWiz->m_output->m_vertSource);
    m_qsci2->setText(projectWiz->m_output->m_fragSource);
  }
  else
  {
    qDebug() << "FAIL";
  }
}
void MainWindow::keyPressEvent(QKeyEvent *_event)
{
  // that method is called every time the main window recives a key event.
  switch (_event->key())
  {
    case Qt::Key_W : {m_ui->m_showWireframe->toggle(); break;}
    case Qt::Key_N : {m_ui->m_showNormals->toggle();   break;}
    case Qt::Key_G : {m_ui->m_showGrid->toggle();      break;}
  }
  update();
}


void MainWindow::on_actionSaveProject_triggered()
{
    m_project->save(m_qsci1->text(), m_qsci2->text());
}

void MainWindow::on_actionSaveProjectAs_triggered()
{
    m_project->saveAs(m_qsci1->text(), m_qsci2->text());
}

