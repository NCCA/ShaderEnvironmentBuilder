#include "button.h"
#include <cstdlib>
#include <iostream>

Button::Button(QWidget *parent) : QDialog(parent)
{
  createButtonBox();


  /*mainLayout = new QGridLayout;
  mainLayout->addWidget(buttonBox, 0, 1);
  setLayout(mainLayout);

  mainLayout->setSizeConstraint(QLayout::SetMinimumSize);

  setWindowTitle(tr("Button Layout"));*/

}

Button::Button(QString _buttonName, QLayout *_layout, unsigned int _id, ngl::Vec4 _defaultVal, QWidget *parent) : QDialog(parent)
{
  m_buttonName = _buttonName;
  m_id=_id;
  createButtonBox(_buttonName);
  _layout->addWidget(m_buttonBox);
  m_colour.m_r = _defaultVal.m_x;
  m_colour.m_g = _defaultVal.m_y;
  m_colour.m_b = _defaultVal.m_z;
}

void Button::createButtonBox(QString _buttonName)
{
  m_buttonBox = new QDialogButtonBox;

  m_closeButton = m_buttonBox->addButton(_buttonName,QDialogButtonBox::ActionRole);

  connect(m_closeButton, SIGNAL(clicked()), this, SLOT(openColourBox()));
}

void Button::printValues()
{
  qDebug()<<"Name:"<<m_buttonName<<"\nID: "<<m_id;
  std::cout<<"R: "<<m_colour.m_r<<"\nG: "<<m_colour.m_g<<"\nB: "<<m_colour.m_b<<std::endl;
}

void Button::openColourBox()
{
  /*m_colourGroupBox = new QColorDialog(tr("Colour"));
  m_colourBoxLabel = new QLabel(tr("Select a colour:"));*/

  //colourBoxLayout = new QGridLayout;
  //colourGroupBox->setLayout(colourBoxLayout);
  m_colourPicker=m_colourGroupBox->getColor();

  m_colour.m_r = m_colourPicker.redF();
  m_colour.m_g = m_colourPicker.greenF();
  m_colour.m_b = m_colourPicker.blueF();
  printValues();
}
