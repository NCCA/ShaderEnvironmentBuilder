#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "qscilexerglsl.h"
#include "button.h"

#include <Qsci/qsciscintilla.h>
MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), m_ui(new Ui::MainWindow)
{


  // Setup ui from form creator (MainWindow.ui)
  m_ui->setupUi(this);
  m_parForButton = new parserLib;
  // Create openGl and qsci widgets
  m_gl=new  NGLScene(this, m_parForButton);
  m_qsci = new QsciScintilla(this);
  QsciLexer* lex = new QsciLexerGLSL(m_qsci);
  m_qsci->setLexer(lex);
  m_qsci->setMarginType(1,QsciScintilla::MarginType::NumberMargin);
  m_qsci->setMarginWidth(1," 012");
  m_qsci->setMarginsForegroundColor(QColor(128, 128, 128));
  // Enable scroll width tracking and set the scroll width to a low number
  // Scintilla doesn't track line length, so if we wanted automated scrollbar
  // to appear we would need to implement a line length checking
  m_qsci->SendScintilla(QsciScintillaBase::SCI_SETSCROLLWIDTHTRACKING, 1);
  m_qsci->SendScintilla(QsciScintillaBase::SCI_SETSCROLLWIDTH, 5);


  // add the qscintilla and openGl window to the interface
  m_ui->s_mainWindowGridLayout->addWidget(m_qsci,0, 1, 1, 1);
  m_ui->s_mainWindowGridLayout->addWidget(m_gl, 0, 0, 1, 1);

  // Set the combo box values for the shader type
  m_ui->cb_shaderType->insertItem(static_cast<int>(ngl::ShaderType::VERTEX), "Vertex Shader");
  m_ui->cb_shaderType->insertItem(static_cast<int>(ngl::ShaderType::FRAGMENT), "Fragment Shader");
  m_ui->cb_shaderType->insertItem(static_cast<int>(ngl::ShaderType::COMPUTE), "Compute Shader");
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::on_btn_loadShader_clicked()
{
    ngl::ShaderType shdrChoiceId = static_cast<ngl::ShaderType>(m_ui->cb_shaderType->currentIndex());
    QString text = m_qsci->text();
    m_gl->loadShader(text, shdrChoiceId);
}

void MainWindow::on_btn_compileShader_clicked()
{
  m_gl->compileShader();
  m_parForButton->printUniforms();
}

void MainWindow::printUniforms()
{
  m_parForButton->printUniforms();
}

void MainWindow::createButtons()
{
  for(int i=0;i<m_parForButton->m_uniformDataList.size(); ++i)
  {
    if(m_parForButton->m_uniformDataList[i].m_name=="vec3")
    {
      m_buttonList.push_back(Button myNew);
    }
  }
}
