#include "StartupDialog.h"
#include "ui_StartupDialog.h"
#include <QFileDialog>
#include <QDebug>
#include "NewProjectWizard.h"

StartupDialog::StartupDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::StartupDialog)
{
  ui->setupUi(this);
}

StartupDialog::~StartupDialog()
{
  delete ui;
  qDebug() << "Destroyed";
}

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

void StartupDialog::on_m_b_newProj_clicked()
{
  NewProjectWizard *projectWiz = new NewProjectWizard(this);
  if (projectWiz->exec())
  {
    qDebug() << "ACCEPT";
  }
  else
  {
    qDebug() << "FAIL";
  }
}
