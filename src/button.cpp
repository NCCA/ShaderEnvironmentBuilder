#include <QtWidgets>

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

void Button::createButtonBox()
{
  m_buttonBox = new QDialogButtonBox;

  m_closeButton = m_buttonBox->addButton(tr("Select &Colour"),QDialogButtonBox::ActionRole);

  connect(m_closeButton, SIGNAL(clicked()), this, SLOT(openColourBox()));
}

void Button::openColourBox()
{
  m_colourGroupBox = new QColorDialog(tr("Colour"));
  m_colourBoxLabel = new QLabel(tr("Select a colour:"));

  //colourBoxLayout = new QGridLayout;
  //colourGroupBox->setLayout(colourBoxLayout);
  m_myColor=m_colourGroupBox->getColor();
  //std::cout<<"Done"<<std::endl;
  m_colourStruct.m_r = m_myColor.redF();
  m_colourStruct.m_g = m_myColor.greenF();
  m_colourStruct.m_b = m_myColor.blueF();

  std::cout<<"R: "<<m_colourStruct.m_r<<"\nG: "<<m_colourStruct.m_g<<"\nB: "<<m_colourStruct.m_b<<std::endl;

}
