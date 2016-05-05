//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
// System includes

// Engine includes

// Library  includes
#include <QFileDialog>
#include <QDebug>

// Project includes
#include "NewProjectWizard.h"
#include "StartupDialog.h"
#include "ui_StartupDialog.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
StartupDialog::StartupDialog(QWidget *parent) :
  QDialog(parent),
  m_ui(new Ui::StartupDialog)
{
  m_ui->setupUi(this);
  m_mainWin = static_cast<MainWindow*>(parent);
}

//------------------------------------------------------------------------------
StartupDialog::~StartupDialog()
{
  delete m_ui;
  qDebug() << "Destroyed";
}

//------------------------------------------------------------------------------
void StartupDialog::on_m_b_openProj_clicked()
{
  QFileDialog dialog(this, tr("Open Project"), "~/",
                     tr("Project Files (*.json);; All Files (*.*)"));
  dialog.setFileMode(QFileDialog::AnyFile);
  QStringList fileNames;
  if (dialog.exec())
  {
    fileNames = dialog.selectedFiles();
    this->hide();
  }
}

//------------------------------------------------------------------------------
void StartupDialog::on_m_b_newProj_clicked()
{
  if (m_mainWin->newProjectWiz(this))
  {
    this->hide();
  }
}
