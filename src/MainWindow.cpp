#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "qscilexerglsl.h"

#include <Qsci/qsciscintilla.h>

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);

  m_gl=new  NGLScene(this);
  m_qsci = new QsciScintilla(this);
  QsciLexer* lex = new QsciLexerGLSL;
  m_qsci->setLexer(lex);
  m_qsci->setMarginType(1,QsciScintilla::MarginType::NumberMargin);

  m_ui->s_mainWindowGridLayout->addWidget(m_gl,0,0,2,1);
  m_ui->s_mainWindowGridLayout->addWidget(m_qsci,0,1,2,1);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}
