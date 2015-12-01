#ifndef BUTTON_H_
#define BUTTON_H_

#include <QDialog>
#include <QQueue>
#include <QtGui/QColorDialog>

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
  void openColourBox();
private:
  void createButtonBox();

  typedef struct m_colour
  {
    qreal m_r;
    qreal m_g;
    qreal m_b;
  } m_colour;

  m_colour colourStruct;

  QDialogButtonBox *buttonBox;

  QColor *myColor;
  QColorDialog *colourGroupBox;
  QGridLayout *colourBoxLayout;

  QPushButton *closeButton;
  QPushButton *helpButton;

  QLabel *colourBoxLabel;

  QGridLayout *mainLayout;


};

#endif
