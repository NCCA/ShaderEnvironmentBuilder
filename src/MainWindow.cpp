#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "QsciLexerGlsl.h"
#include "CebErrors.h"

#include <QTextStream>
#include <QFileDialog>

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
  m_ui->m_split_mainContext->insertWidget(0, m_gl);

  // Delete the template frame from the form designer
  delete(m_ui->m_f_gl_temp);

  // Widget 1 (vertex)
  m_qsci1 = createQsciWidget(m_ui->m_tab_qsci_1);

  // Widget 2 (fragment)
  m_qsci2 = createQsciWidget(m_ui->m_tab_qsci_2);

  // Set the combo box values for the shader type
  m_ui->m_cb_shaderType->insertItem(static_cast<int>(ngl::ShaderType::VERTEX),
                                  "Vertex Shader");
  m_ui->m_cb_shaderType->insertItem(static_cast<int>(ngl::ShaderType::FRAGMENT),
                                  "Fragment Shader");
  m_ui->m_cb_shaderType->insertItem(static_cast<int>(ngl::ShaderType::COMPUTE),
                                  "Compute Shader");

  // Set the combo box initially to VERTEX
  m_ui->m_cb_shaderType->setCurrentIndex(static_cast<int>(
                                         ngl::ShaderType::VERTEX));

  // Load the text files into the corresponding tabs
  loadTextFileToTab("shaders/PhongVertex.glsl", *m_qsci1);
  loadTextFileToTab("shaders/PhongFragment.glsl", *m_qsci2);

  // switching between shapes
  connect(m_ui->actionLoad_Sphere,SIGNAL(triggered()),this,SLOT(on_actionLoad_shape_triggered()));
  connect(m_ui->actionLoad_Cube,SIGNAL(triggered()),this,SLOT(on_actionLoad_shape_triggered()));
  connect(m_ui->actionLoad_Torus,SIGNAL(triggered()),this,SLOT(on_actionLoad_shape_triggered()));
  connect(m_ui->actionLoad_Cone,SIGNAL(triggered()),this,SLOT(on_actionLoad_shape_triggered()));
  connect(m_ui->actionLoad_Teapot ,SIGNAL(triggered()),this,SLOT(on_actionLoad_shape_triggered()));
  connect(m_ui->actionLoad_Troll,SIGNAL(triggered()),this,SLOT(on_actionLoad_shape_triggered()));
  connect(m_ui->actionLoad_Dragon,SIGNAL(triggered()),this,SLOT(on_actionLoad_shape_triggered()));

  connect(m_ui->actionLoad_obj,SIGNAL(triggered()),this,SLOT(on_actionLoad_obj_triggered222()));

}

//----------------------------------------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
    delete m_ui;
}

//----------------------------------------------------------------------------------------------------------------------
void MainWindow::on_m_btn_loadShader_clicked()
{
  // Get and cast the shader type combo box value
  int cb_id = m_ui->m_cb_shaderType->currentIndex();
  ngl::ShaderType shdrChoiceId = static_cast<ngl::ShaderType>(cb_id);

  // Get the current tabid
  int tabId = m_ui->m_tabs_qsci->currentIndex();

  // Get the text from the currently selected tab
  QString text;
  switch (tabId)
  {
  case 0:
    text = m_qsci1->text();
    break;

  case 1:
    text = m_qsci2->text();
    break;

  default:
    std::cerr<< "ERROR: Tab id is not recognised\n";
  }
  // Load the text into the shader with the shader type
  m_gl->loadShader(text, shdrChoiceId);
}

//----------------------------------------------------------------------------------------------------------------------
void MainWindow::on_m_btn_compileShader_clicked2()
{
  m_gl->compileShader();
  m_parForButton->printUniforms(1);
  createButtons();
}

void MainWindow::printUniforms()
{
  m_parForButton->printUniforms(1);
}

void MainWindow::createButtons()
{
  for(unsigned int i=0;i<m_parForButton->m_num; ++i)
  {
    if(m_parForButton->m_uniformList[i]->getTypeName()=="vec4")
    {
      QString _tempName = QString::fromStdString(m_parForButton->m_uniformList[i]->getName());
      ngl::Vec4 _tempVec=m_parForButton->m_uniformList[i]->getVec4();
      Button *tempButton = new Button(_tempName, m_ui->vl_uniforms, _tempVec, m_ui->m_w_uniforms);

      m_buttonList.push_back(tempButton);
    }
  }
  std::cerr<<"THIS IS THE BUTTON LIST LENGTH: "<<m_buttonList.size()<<std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
void MainWindow::on_m_tabs_qsci_currentChanged(int _index)
{
  // On switch of tab, change the combo box value to the corresponding tab type
  switch (_index)
  {
    case 0:
      m_ui->m_cb_shaderType->setCurrentIndex(static_cast<int>(
                                               ngl::ShaderType::VERTEX));
    break;

    case 1:
      m_ui->m_cb_shaderType->setCurrentIndex(static_cast<int>(
                                               ngl::ShaderType::FRAGMENT));
    break;

    default:
      std::cerr<< "ERROR: Tab id is not recognised\n";
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
void MainWindow::on_actionLoad_obj_triggered222()
{
  QString fileName = QFileDialog::getOpenFileName(this,
      tr("Open Mesh"), "tempFiles/", tr("Image Files (*.obj)"));

  std::string importName=fileName.toStdString();
  std::cout<<"IMPORT NAME :              "<<importName<<std::endl;
  m_gl->setMeshLocation(fileName);
  m_gl->meshImport();
  m_gl->setShapeType(0);
}

void MainWindow::on_actionLoad_shape_triggered()
{
  QAction *action = static_cast<QAction*>(sender());
  int a=666;

  if (action==m_ui->actionLoad_Sphere)  {   a=1;  }
  if (action==m_ui->actionLoad_Cube)    {   a=2;  }
  if (action==m_ui->actionLoad_Torus)   {   a=3;  }
  if (action==m_ui->actionLoad_Cone)    {   a=4;  }
  if (action==m_ui->actionLoad_Teapot)  {   a=5;  }
  if (action==m_ui->actionLoad_Troll)   {   a=6;  }
  if (action==m_ui->actionLoad_Dragon)  {   a=7;  }

  std::cout<<"Print >> " <<action<<"  "<<a<<std::endl;
  m_gl->setShapeType(a);
}

void MainWindow::on_pushButton_clicked2()
{
  QPushButton *button = static_cast<QPushButton*>(sender());
  float a=0.0;
  float b=0.0;
  float c=0.0;
  if (button==m_ui->pushButtonR)    {   a=1.0;b=0.0;c=0.0;  }
  if (button==m_ui->pushButtonG)    {   a=0.0;b=1.0;c=0.0;  }
  if (button==m_ui->pushButtonB)    {   a=0.0;b=0.0;c=1.0;  }
  std::cout<<"Print >> " <<button<<"  "<<a<<std::endl;
  ngl::Vec4 abc(a,b,c,1.0);
  m_gl->m_parser->m_uniformList[0]->setVec4(abc);
}
