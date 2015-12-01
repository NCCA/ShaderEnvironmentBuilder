#ifndef BUTTON_H_
#define BUTTON_H_

#include <QDialog>
#include <QQueue>

QT_BEGIN_NAMESPACE
class QComboBox;
class QDialogButtonBox;
class QGridLayout;
class QGroupBox;
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class Button : public QDialog
{
  Q_OBJECT

public:
  Button(QWidget *parent=0);
private slots:
  //void openColourBox();
private:
  void createButtonBox();

  QDialogButtonBox *buttonBox;

  QPushButton *closeButton;
  QPushButton *helpButton;

  QGridLayout *mainLayout;


};

#endif
