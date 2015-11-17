#ifndef WIDGET_H_
#define WIDGET_H_

#include <QDialog>
#include <QQueue>
#include <QtGui/QColorDialog>

QT_BEGIN_NAMESPACE
//class QComboBox;
class QGridLayout;
class QGroupBox;
class QLabel;
QT_END_NAMESPACE

class widget : public QDialog
{
  Q_OBJECT

private:
  void createColourPanel();

  typedef struct m_colour
  {
    qreal m_r;
    qreal m_g;
    qreal m_b;
  } m_colour;

  m_colour colourStruct;
  QColor *myColor;
  QColorDialog *colourGroupBox;
  QLabel *colourBoxLabel;
  QColorDialog *dialogBox;
  QGridLayout *colourBoxLayout;
  QGridLayout *mainLayout;

public:
  widget(QWidget *parent = 0);
  qreal returnRed();
  qreal returnGreen();
  qreal returnBlue();
  void assignCol(m_colour* a);

private slots:
  void colChange();
};

#endif
