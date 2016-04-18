#include "StartupDialog.h"
#include "ui_StartupDialog.h"

StartupDialog::StartupDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::StartupDialog)
{
  ui->setupUi(this);
}

StartupDialog::~StartupDialog()
{
  delete ui;
}
