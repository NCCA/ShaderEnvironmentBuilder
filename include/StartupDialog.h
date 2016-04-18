#ifndef STARTUPDIALOG_H
#define STARTUPDIALOG_H

#include <QDialog>

namespace Ui {
class StartupDialog;
}

class StartupDialog : public QDialog
{
  Q_OBJECT

public:
  explicit StartupDialog(QWidget *parent = 0);
  ~StartupDialog();

private slots:
  void on_m_b_openProj_clicked();

  void on_m_b_newProj_clicked();

private:
  Ui::StartupDialog *ui;
};

#endif // STARTUPDIALOG_H
