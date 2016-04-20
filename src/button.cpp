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
  m_colour.set(_defaultVal.m_x, _defaultVal.m_y, _defaultVal.m_z, 1.0f);
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
  std::cout<<"R: "<<m_colour.m_x<<"\nG: "<<m_colour.m_y<<"\nB: "<<m_colour.m_z<<std::endl;
}

void Button::openColourBox()
{
  /*m_colourGroupBox = new QColorDialog(tr("Colour"));
  m_colourBoxLabel = new QLabel(tr("Select a colour:"));*/

  //colourBoxLayout = new QGridLayout;
  //colourGroupBox->setLayout(colourBoxLayout);
  m_colourPicked=m_colourGroupBox->getColor();

  m_colour.set(m_colourPicked.redF(),
               m_colourPicked.greenF(),
               m_colourPicked.blueF());
  //printValues();
}
