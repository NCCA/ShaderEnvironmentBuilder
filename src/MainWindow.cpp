#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "qscilexerglsl.h"
#include "button.h"

#include <Qsci/qsciscintilla.h>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), m_ui(new Ui::MainWindow)
{


  // Setup ui from form creator (MainWindow.ui)
  m_ui->setupUi(this);
  // create parser in main window
  m_parForButton = new parserLib;
  // Create openGl and qsci widgets, pass in the parser
  m_gl=new  NGLScene(this, m_parForButton);

  // Widget 1 (vertex)
  m_qsci1 = new QsciScintilla(this);
  QsciLexer* lex1 = new QsciLexerGLSL(m_qsci1);
  m_qsci1->setLexer(lex1);
  m_qsci1->setMarginType(1,QsciScintilla::MarginType::NumberMargin);
  m_qsci1->setMarginWidth(1," 012");
  m_qsci1->setMarginsForegroundColor(QColor(128, 128, 128));
  m_qsci1->setCaretForegroundColor(QColor(247, 247, 241));
  m_qsci1->setCaretWidth(2);
  // Enable scroll width tracking and set the scroll width to a low number
  // Scintilla doesn't track line length, so if we wanted automated scrollbar
  // to appear we would need to implement a line length checking
  m_qsci1->SendScintilla(QsciScintillaBase::SCI_SETSCROLLWIDTHTRACKING, 1);
  m_qsci1->SendScintilla(QsciScintillaBase::SCI_SETSCROLLWIDTH, 5);
  m_ui->tab_qsci_1->layout();

  // Create a layout to enable filling of the widget
  QBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(m_qsci1);
  m_ui->tab_qsci_1->setLayout(layout);


  // Widget 2 (fragment)
  m_qsci2 = new QsciScintilla(this);
  QsciLexer* lex2 = new QsciLexerGLSL(m_qsci2);
  m_qsci2->setLexer(lex2);
  m_qsci2->setMarginType(1,QsciScintilla::MarginType::NumberMargin);
  m_qsci2->setMarginWidth(1," 012");
  m_qsci2->setMarginsForegroundColor(QColor(128, 128, 128));
  m_qsci2->setCaretForegroundColor(QColor(247, 247, 241));
  m_qsci2->setCaretWidth(2);
  // Enable scroll width tracking and set the scroll width to a low number
  // Scintilla doesn't track line length, so if we wanted automated scrollbar
  // to appear we would need to implement a line length checking
  m_qsci2->SendScintilla(QsciScintillaBase::SCI_SETSCROLLWIDTHTRACKING, 1);
  m_qsci2->SendScintilla(QsciScintillaBase::SCI_SETSCROLLWIDTH, 5);


  // Create a layout to enable filling of the widget
  layout = new QVBoxLayout;
  layout->addWidget(m_qsci2);
  m_ui->tab_qsci_2->setLayout(layout);


  // add the qscintilla and openGl window to the interface
  //m_ui->s_mainWindowGridLayout->addWidget(m_qsci,0, 2, 1, 1);
  m_ui->s_mainWindowGridLayout->addWidget(m_gl, 0, 0, 1, 1);


  // Set the combo box values for the shader type
  m_ui->cb_shaderType->insertItem(static_cast<int>(ngl::ShaderType::VERTEX),
                                  "Vertex Shader");
  m_ui->cb_shaderType->insertItem(static_cast<int>(ngl::ShaderType::FRAGMENT),
                                  "Fragment Shader");
  m_ui->cb_shaderType->insertItem(static_cast<int>(ngl::ShaderType::COMPUTE),
                                  "Compute Shader");
  // Set the combo box initially to VERTEX
  m_ui->cb_shaderType->setCurrentIndex(static_cast<int>(
                                         ngl::ShaderType::VERTEX));


  // Load in phong vertex to the Vertex Qsci widget
  QString text;
  QFile file("shaders/PhongVertex.glsl");

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    std::cout << "ERRORR READING Vertex FILE\n";
  QTextStream in(&file);
  text = in.readAll();
  m_qsci1->setText(text);


  // Load in phong fragment to the fragment Qsci widget
  file.setFileName("shaders/PhongFragment.glsl");
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    std::cout << "ERRORR READING Fragment FILE\n";
  in.reset();
  text = in.readAll();
  m_qsci2->setText(text);

}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::on_btn_loadShader_clicked()
{
    int cb_id = m_ui->cb_shaderType->currentIndex();
    ngl::ShaderType shdrChoiceId = static_cast<ngl::ShaderType>(cb_id);

    int tabId = m_ui->tabs_qsci->currentIndex();
    std::cout<< "TABID: " << tabId << std::endl;
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
        std::cout<< "ERROR: Tab id is not recognised\n";
    }

    m_gl->loadShader(text, shdrChoiceId);

}

void MainWindow::on_btn_compileShader_clicked()
{
  m_gl->compileShader();
  m_parForButton->printUniforms();
  createButtons();
}

void MainWindow::printUniforms()
{
  m_parForButton->printUniforms();
}

void MainWindow::createButtons()
{
  for(int i=0;i<m_parForButton->m_uniformDataList.size(); ++i)
  {
    if(m_parForButton->m_uniformDataList[i].m_typeName=="vec4")
    {
      ngl::Vec4 _tempVec=m_parForButton->returnVec4(i);
      //Button temp;
      std::cout<<"HERE: "<<i<<std::endl;
      std::cout<<"\nVal:\nx: "<<_tempVec.m_x<<"\ny: "<<_tempVec.m_y<<"\nz:"<<_tempVec.m_z<<std::endl;
      //m_buttonList.push_back(Button myNew);
    }
  }
}
void MainWindow::on_tabs_qsci_currentChanged(int index)
{
  switch (index)
  {
    case 0:
      m_ui->cb_shaderType->setCurrentIndex(static_cast<int>(ngl::ShaderType::VERTEX));
    break;

    case 1:
      m_ui->cb_shaderType->setCurrentIndex(static_cast<int>(ngl::ShaderType::FRAGMENT));
    break;

    default:
      std::cout<< "ERROR: Tab id is not recognised\n";
  }

}
