#ifndef BUTTON_H_
#define BUTTON_H_

#include <ngl/Vec4.h>
#include <QtWidgets>
#include <ngl/Colour.h>
#include <QtWidgets>
#include <QDialogButtonBox>

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QColor>
#include <QColorDialog>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QGridLayout;
class QLabel;
class QPushButton;
class QColor;
QT_END_NAMESPACE

//----------------------------------------------------------------------------------------------------------------------
/// @file button.h
/// @brief this class creates a button with a pop up widget that can create modifiable
/// attributes
/// @author Jonny Lyddon
/// @version 1.0
/// @date 04/02/16
//----------------------------------------------------------------------------------------------------------------------

class Button : public QDialog
{
  Q_OBJECT

public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief constructor to create the button
  /// @param [in] the parent window is defaulted to nothing
  //----------------------------------------------------------------------------------------------------------------------
  Button(QWidget *parent=0);
  Button(QString _buttonName, QLayout *_layout, unsigned int _id, ngl::Vec4 _defaultVal=ngl::Vec4(0.0f,0.0f,0.0f,1.0f), QWidget *parent=0);
  QString getName(){return m_buttonName;}
  void setColour(QColor _col){m_colourPicked=_col;}
  void setID(unsigned int _id){m_id=_id;}
  unsigned int getID() {return m_id;}
  ngl::Colour getColour();
  void printValues();

private slots:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a slot to open a colour box upon event
  //----------------------------------------------------------------------------------------------------------------------
  void openColourBox();
private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function to create the button box for the colour picker
  //----------------------------------------------------------------------------------------------------------------------
  void createButtonBox(QString _buttonName="Select &Colour");
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief id to access specific buttons
  //----------------------------------------------------------------------------------------------------------------------
  unsigned int m_id;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief colour struct used to access colour attributes
  /// @brief string to hold button's name
  //----------------------------------------------------------------------------------------------------------------------
  typedef struct m_colour
  {
    qreal m_r;
    qreal m_g;
    qreal m_b;
  } m_colour;
  QString m_buttonName;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief colour structure to store colour attributes for easy accessibility
  //----------------------------------------------------------------------------------------------------------------------
  m_colour m_colourStruct;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief button box to open colour picker
  //----------------------------------------------------------------------------------------------------------------------
  QDialogButtonBox *m_buttonBox;
  QDialogButtonBox *m_buttonBox2;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief colour used to store attributes coming out from colour picker
  //----------------------------------------------------------------------------------------------------------------------
  QColor m_colourPicked;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief colour box to select colours
  //----------------------------------------------------------------------------------------------------------------------
  QColorDialog *m_colourGroupBox;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief layout for colour box to be stored within
  //----------------------------------------------------------------------------------------------------------------------
  QGridLayout *m_colourBoxLayout;
  //----------------------------------------------------------------------------------------------------------------------
  //ignore these for now
  //----------------------------------------------------------------------------------------------------------------------
  QPushButton *m_closeButton;
  QPushButton *m_helpButton;

  QLabel *m_colourBoxLabel;
  QGridLayout *m_mainLayout;


};

#endif
