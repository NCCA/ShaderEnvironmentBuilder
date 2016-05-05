#include "button.h"
#include <cstdlib>
#include <iostream>

//----------------------------------------------------------------------------------------------------------------------
/// @file button.cpp
/// @brief implementation of the different button classes
/// @author Jonny Lyddon
//----------------------------------------------------------------------------------------------------------------------

Button::Button(QWidget *parent) : QDialog(parent)
{
  createButtonBox();
}

Button::Button(QString _buttonName, QLayout *_layout, unsigned int _id, ButtonLib *_libParent, NGLScene *_sceneParent, QWidget *parent) : QDialog(parent)
{
  m_buttonName = _buttonName;
  m_id=_id;
  createButtonBox(_buttonName);
  m_libParent=_libParent;
  m_sceneParent=_sceneParent;
  _layout->addWidget(m_buttonBox);
}

void Button::createButtonBox(QString _buttonName)
{
  m_buttonBox = new QDialogButtonBox;
  m_button = m_buttonBox->addButton(_buttonName,QDialogButtonBox::ActionRole);
  connect(m_button, SIGNAL(clicked()), this, SLOT(openBox()));
}

void Button::printValues()
{
  qDebug()<<"Name:"<<m_buttonName<<"\nID: "<<m_id;
}

void colourButton::printAttributes()
{
  std::cout<<"R: "<<m_colour.m_x<<"\nG: "<<m_colour.m_y<<"\nB: "<<m_colour.m_z<<std::endl;
}

void colourButton::openBox()
{
  //these are set so when the colour picker is opened the current colour is opened
  m_colourPicked.setRedF(m_colour.m_x);
  m_colourPicked.setGreenF(m_colour.m_y);
  m_colourPicked.setBlueF(m_colour.m_z);
  m_colourPicked=m_colourGroupBox->getColor(m_colourPicked);
  m_colour.set(m_colourPicked.redF(),
               m_colourPicked.greenF(),
               m_colourPicked.blueF(),
               m_colourPicked.alphaF());
  qDebug()<<"Box opened and colours set\n";
  m_libParent->updateShaderValues();
  m_sceneParent->update();
  //printValues();
}

void colourButton::setColour(QColor _col)
{
  m_colourPicked=_col;
  m_colour.set(_col.redF(),
               _col.greenF(),
               _col.blueF(),
               _col.alphaF());
}

void floatButton::openBox()
{
  m_window = new QDialog;
  double val = QInputDialog::getDouble(this, tr("Input"), tr("Input"), m_value, -5.0, 5.0, 3);
  m_value=val;
  m_libParent->updateShaderValues();
  m_sceneParent->update();
  //printValues();
}
