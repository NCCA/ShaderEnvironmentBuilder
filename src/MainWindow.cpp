#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <Qsci/qsciscintilla.h>

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);

  m_gl=new  NGLScene(this);
  m_qsci = new QsciScintilla(this);

  m_ui->s_mainWindowGridLayout->addWidget(m_gl,0,0,2,1);
  m_ui->s_mainWindowGridLayout->addWidget(m_qsci,0,1,2,1);
}

MainWindow::~MainWindow()
{
    delete m_ui;
}
