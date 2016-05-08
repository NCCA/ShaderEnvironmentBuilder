#ifndef BUTTON_H_
#define BUTTON_H_

#include <ngl/Vec4.h>
#include <ngl/Colour.h>
#include "ButtonLib.h"
#include "NGLScene.h"

#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QInputDialog>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QColor>
#include <QColorDialog>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QDoubleSpinBox;
class QLabel;
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
/// @version 1.1
/// @date 20/04/16
//----------------------------------------------------------------------------------------------------------------------

class ButtonLib;
class NGLScene;



class Button : public QDialog
{
  Q_OBJECT

public:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief default constructor to create the button
  /// @param [in] the parent window is defaulted to nothing
  //----------------------------------------------------------------------------------------------------------------------
  Button(QWidget *parent=0);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief constructor to create the button, custom variables can also be assigned
  /// @param [in] name of the button to be used
  /// @param [in] the layout environment for the button to be attached to
  /// @param [in] the id used to access the button information
  /// @param [in] the parent window is defaulted to nothing
  //----------------------------------------------------------------------------------------------------------------------
  Button(QString _buttonName,
         GLenum _buttonType,
         QLayout *_layout,
         GLuint _id,
         ButtonLib *_libParent,
         NGLScene *_sceneParent,
         QWidget *parent=0);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief button object to be pressed by user to open relevant widget
  //----------------------------------------------------------------------------------------------------------------------
  QPushButton *m_button;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returns the current button name
  /// @return m_buttonName
  //----------------------------------------------------------------------------------------------------------------------
  QString getName() {return m_buttonName;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returns the current button type
  /// @return m_buttonType
  //----------------------------------------------------------------------------------------------------------------------
  GLenum getTypeEnum() {return m_buttonType;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief sets the current ID for the button, from its' shader location
  /// @param [in] the location ID for the button id
  //----------------------------------------------------------------------------------------------------------------------
  void setID(unsigned int _id) {m_id=_id;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returns the button ID, this will change based on shader location
  /// @return m_id
  //----------------------------------------------------------------------------------------------------------------------
  GLuint getID() {return m_id;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief sets the colour to be used by colour buttons
  /// @param [in] the colour to be set within the colourButton class
  //----------------------------------------------------------------------------------------------------------------------
  virtual void setColour(ngl::Vec4 _col) {return;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief overloaded function to set the colour
  /// @param [in] the colour to be set within the colourButton class
  //----------------------------------------------------------------------------------------------------------------------
  virtual void setColour(QColor _col) {return;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returns the colour, stored by the button
  /// @return m_colour
  //----------------------------------------------------------------------------------------------------------------------
  virtual ngl::Vec4 getColour() {return ngl::Vec4();}
  virtual QColor getColourQ() {return QColor();}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief sets the value to be for float attributes
  /// @param [in] the value to be set within the floatButton class
  //----------------------------------------------------------------------------------------------------------------------
  virtual void setValue(float _val) {return;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returns the value, stored by the button
  /// @return m_value
  //----------------------------------------------------------------------------------------------------------------------
  virtual float getValue() {return float();}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief prints the button attribute values
  //----------------------------------------------------------------------------------------------------------------------
  virtual void printValues();
  virtual ngl::Vec4 getVec() {return ngl::Vec4();}
  virtual void setVec(ngl::Vec4 _value) {return;}

//  virtual void setVec(ngl::Vec4 _value){return;}
//  virtual ngl::Vec4 getVec(){return ngl::Vec4();}

  ButtonLib *m_libParent;

  NGLScene *m_sceneParent;

  QWidget *m_parent;

private slots:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a slot to open a widget upon button press event
  //----------------------------------------------------------------------------------------------------------------------
  virtual void openBox() {return;}

private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief string to hold button's name
  //----------------------------------------------------------------------------------------------------------------------
  QString m_buttonName;

  GLenum m_buttonType;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief id to access specific buttons and shader locations
  //----------------------------------------------------------------------------------------------------------------------
  unsigned int m_id;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief function to create the button box for the colour picker
  /// @param [in] button name
  //----------------------------------------------------------------------------------------------------------------------
  void createButtonBox(QString _buttonName="Select &Colour");
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief button box to open the necessary widget
  //----------------------------------------------------------------------------------------------------------------------
  QDialogButtonBox *m_buttonBox;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief layout for the button box to be stored within
  //----------------------------------------------------------------------------------------------------------------------
  QGridLayout *m_gridLayout;

};

class colourButton : public Button
{
    Q_OBJECT

private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief vector to store colour attributes for easy accessibility
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Vec4 m_colour;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief colour used to store attributes coming out from colour picker
  //----------------------------------------------------------------------------------------------------------------------
  QColor m_colourPicked;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief colour box to select colours
  //----------------------------------------------------------------------------------------------------------------------
  QColorDialog *m_colourGroupBox;
private slots:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a slot to open a colour widget upon button press event
  //----------------------------------------------------------------------------------------------------------------------
  void openBox();
public:
  using Button::Button;

  /*~colourButton()
  {
    delete m_libParent;
    delete m_sceneParent;
  }*/
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief sets the picked colour and colour attribute to the colour input
  /// @param [in] colour value
  //----------------------------------------------------------------------------------------------------------------------
  void setColour(QColor _col);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief sets the colour attribute to the colour input
  /// @param [in] colour value
  //----------------------------------------------------------------------------------------------------------------------
  void setColour(ngl::Vec4 _col);
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returns the colour, stored by the button
  /// @return m_colour
  //----------------------------------------------------------------------------------------------------------------------
  ngl::Vec4 getColour() {return m_colour;}
  QColor getColourQ() {return m_colourPicked;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief print the attribute data stored within the colour attriubte for debugging
  //----------------------------------------------------------------------------------------------------------------------
  void printAttributes();

  //colourButton& operator=(colourButton &_rhs);
};

class floatButton : public Button
{
    Q_OBJECT

private:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief float to store attribute for easy accessibility
  //----------------------------------------------------------------------------------------------------------------------
  float m_value;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief window to hold float slider
  //----------------------------------------------------------------------------------------------------------------------
  QDialog *m_window;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief creates a frame with a tile to hold float slider
  //----------------------------------------------------------------------------------------------------------------------
  QGroupBox *m_sliderGroupBox;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief layout to hold float slider widget
  //----------------------------------------------------------------------------------------------------------------------
  QGridLayout *m_sliderLayout;
private slots:
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief a slot to open float widget upon button press event
  //----------------------------------------------------------------------------------------------------------------------
    void openBox();
public:
  using Button::Button;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief sets the value of the float
  //----------------------------------------------------------------------------------------------------------------------
  void setValue(float _val) {m_value=_val;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief returns the value, stored by the button
  /// @return m_value
  //----------------------------------------------------------------------------------------------------------------------
  float getValue() {return m_value;}
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief print the attribute data stored within the float attriubte for debugging
  //----------------------------------------------------------------------------------------------------------------------
  void printAttributes();
  //floatButton& operator=(floatButton &_rhs);
};

class VecButton : public Button
{
  Q_OBJECT

private:

  QDialog *m_vecWindow;

  QGridLayout *m_vecLayout;

  QLabel *m_xName;
  QLabel *m_yName;
  QLabel *m_zName;

  QDoubleSpinBox *m_xSpinBox;
  QDoubleSpinBox *m_ySpinBox;
  QDoubleSpinBox *m_zSpinBox;

  QDialogButtonBox *m_buttonBox_ok;
  QDialogButtonBox *m_buttonBox_cancel;

  ngl::Vec4 m_value;

private slots:
//----------------------------------------------------------------------------------------------------------------------
/// @brief a slot to open float widget upon button press event
//----------------------------------------------------------------------------------------------------------------------
  void openBox();

public:
  using Button::Button;

  void setUpButton(ngl::Vec3 _vector);

  void setVec(ngl::Vec4 _value){m_value=_value;}
  ngl::Vec4 getVec(){return m_value;}

  void printAttributes();

};


#endif
