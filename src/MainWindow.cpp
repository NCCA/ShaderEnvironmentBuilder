#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "QsciLexerGlsl.h"
#include "CebErrors.h"

#include <QTextStream>

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

  //std::cerr<<"Find number of active uniforms: "<<m_parForButton->m_num<<std::endl;

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
void MainWindow::on_m_btn_compileShader_clicked()
{
  m_gl->compileShader();
  //m_parForButton->printUniforms(1);
  createButtons();
  //TEST VAR m_parForButton->m_uniformList[12]->setVec4(ngl::Vec4(0.2f,0.8f,0.1f,1.0f));
  updateShaderValues();
}

void MainWindow::printUniforms()
{
  m_parForButton->printUniforms(1);
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
  }/*
  std::vector<Button*> _uniformsToAdd;
  for(auto uniform: m_parForButton->m_uniformList)
  {
    bool _exists=0;
    //std::cout<<uniform->getName()<<std::endl;
    for (auto button: m_buttonList)
    {
      QString _tempName = button->getName();
      std::string _temp = _tempName.toUtf8().constData();
      if(uniform->getName()==_temp)
      {
        button->setID(uniform->getLocation());
        //qDebug()<<button->getName()<<"\n"<<button->getID()<<"\n";
        _exists=1;
        break;
      }
    }
    if(_exists==0 && (uniform->getName()==_temp))
    {
      //std::cout<<"CREATING"<<std::endl;
      //qDebug()<<uniform->getName()<<"\n"<<uniform->getLocation()<<"\n";
      QString _tempName = QString::fromStdString(uniform->getName());
      Button *tempButton = new Button(_tempName,
                                      m_ui->vl_uniforms,
                                      uniform->getLocation(),
                                      uniform->getVec4(),
                                      m_ui->m_w_uniforms);
      _uniformsToAdd.push_back(tempButton);
    }
  }
  for(auto button: _uniformsToAdd)
  {
    m_buttonList.push_back(button);
  }
}
  //std::cerr<<"THIS IS THE BUTTON LIST LENGTH: "<<m_buttonList.size()<<std::endl;

*/
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

