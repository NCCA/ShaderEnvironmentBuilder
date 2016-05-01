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

Button::Button(QString _buttonName, QLayout *_layout, unsigned int _id, QWidget *parent) : QDialog(parent)
{
  m_buttonName = _buttonName;
  m_id=_id;
  createButtonBox(_buttonName);
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
  m_colourPicked=m_colourGroupBox->getColor();
  m_colour.set(m_colourPicked.redF(),
               m_colourPicked.greenF(),
               m_colourPicked.blueF(),
               m_colourPicked.alphaF());
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
  double val = QInputDialog::getDouble(this, tr("Input"), tr("Input"));
  m_value=val;
  //printValues();
}
