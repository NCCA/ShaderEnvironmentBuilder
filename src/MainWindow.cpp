#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "QsciLexerGlsl.h"

#include <Qsci/qsciscintilla.h>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),
                                         m_ui(new Ui::MainWindow)
{


  // Setup ui from form creator (MainWindow.ui)
  m_ui->setupUi(this);

  // Create openGl from template frame
  m_gl=new  NGLScene(this);
  m_gl->setSizePolicy(m_ui->m_f_gl_temp->sizePolicy());
  m_gl->setMinimumSize(m_ui->m_f_gl_temp->minimumSize());

  // Delete the template frame
  delete(m_ui->m_f_gl_temp);

  // Widget 1 (vertex)
  m_qsci1 = new QsciScintilla(this);
  QsciLexer* lex1 = new QsciLexerGLSL(m_qsci1);
  m_qsci1->setLexer(lex1);
  m_qsci1->setMarginType(1,QsciScintilla::MarginType::NumberMargin);
  m_qsci1->setMarginWidth(1," 012");
  m_qsci1->setMarginsForegroundColor(QColor(128, 128, 128));
  m_qsci1->setCaretForegroundColor(QColor(247, 247, 241));
  m_qsci1->setCaretWidth(2);
  m_qsci1->setBraceMatching(QsciScintilla::BraceMatch::SloppyBraceMatch);
  m_qsci1->setMatchedBraceBackgroundColor(QColor(62, 61, 50));
  m_qsci1->setUnmatchedBraceBackgroundColor(QColor(249, 38, 114));
  // Enable scroll width tracking and set the scroll width to a low number
  // Scintilla doesn't track line length, so if we wanted automated scrollbar
  // to appear we would need to implement a line length checking
  m_qsci1->SendScintilla(QsciScintillaBase::SCI_SETSCROLLWIDTHTRACKING, 1);
  m_qsci1->SendScintilla(QsciScintillaBase::SCI_SETSCROLLWIDTH, 5);
  m_ui->m_tab_qsci_1->layout();

  // Create a layout to enable filling of the widget
  QBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(m_qsci1);
  m_ui->m_tab_qsci_1->setLayout(layout);


  // Widget 2 (fragment)
  m_qsci2 = new QsciScintilla(this);
  QsciLexer* lex2 = new QsciLexerGLSL(m_qsci2);
  m_qsci2->setLexer(lex2);
  m_qsci2->setMarginType(1,QsciScintilla::MarginType::NumberMargin);
  m_qsci2->setMarginWidth(1," 012");
  m_qsci2->setMarginsForegroundColor(QColor(128, 128, 128));
  m_qsci2->setCaretForegroundColor(QColor(247, 247, 241));
  m_qsci2->setCaretWidth(2);
  m_qsci2->setBraceMatching(QsciScintilla::BraceMatch::SloppyBraceMatch);
  m_qsci2->setMatchedBraceBackgroundColor(QColor(62, 61, 50));
  m_qsci2->setUnmatchedBraceBackgroundColor(QColor(249, 38, 114));
  // Enable scroll width tracking and set the scroll width to a low number
  // Scintilla doesn't track line length, so if we wanted automated scrollbar
  // to appear we would need to implement a line length checking
  m_qsci2->SendScintilla(QsciScintillaBase::SCI_SETSCROLLWIDTHTRACKING, 1);
  m_qsci2->SendScintilla(QsciScintillaBase::SCI_SETSCROLLWIDTH, 5);


  // Create a layout to enable filling of the widget
  layout = new QVBoxLayout;
  layout->addWidget(m_qsci2);
  m_ui->m_tab_qsci_2->setLayout(layout);


  // add the qscintilla and openGl window to the interface
  //m_ui->s_mainWindowGridLayout->addWidget(m_qsci,0, 2, 1, 1);
  m_ui->m_split_mainContext->insertWidget(0, m_gl);

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

void MainWindow::on_m_btn_loadShader_clicked()
{
    int cb_id = m_ui->m_cb_shaderType->currentIndex();
    ngl::ShaderType shdrChoiceId = static_cast<ngl::ShaderType>(cb_id);

    int tabId = m_ui->m_tabs_qsci->currentIndex();
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

void MainWindow::on_m_btn_compileShader_clicked()
{
  m_gl->compileShader();
}

void MainWindow::on_m_tabs_qsci_currentChanged(int index)
{
  switch (index)
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
      std::cout<< "ERROR: Tab id is not recognised\n";
  }

}
