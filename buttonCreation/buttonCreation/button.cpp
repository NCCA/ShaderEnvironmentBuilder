#include <QtWidgets>

#include "button.h"
#include <cstdlib>
#include <iostream>

Button::Button(QWidget *parent) : QDialog(parent)
{
  createButtonBox();

  mainLayout = new QGridLayout;
  mainLayout->addWidget(buttonBox, 0, 0);
  setLayout(mainLayout);

  mainLayout->setSizeConstraint(QLayout::SetMinimumSize);

  setWindowTitle(tr("Button Layout"));

}

void Button::createButtonBox()
{
  buttonBox = new QDialogButtonBox;

  closeButton = buttonBox->addButton(tr("Select &Colour"),QDialogButtonBox::ActionRole);

  connect(closeButton, SIGNAL(clicked()), this, SLOT(openColourBox()));
}

void Button::openColourBox()
{
  colourGroupBox = new QColorDialog(tr("Colour"));
  colourBoxLabel = new QLabel(tr("Select a colour:"));

  //colourBoxLayout = new QGridLayout;
  //colourGroupBox->setLayout(colourBoxLayout);
  colourGroupBox->getColor();
  std::cout<<"Done"<<std::endl;
  /*colourStruct.m_r = myColor->redF();
  colourStruct.m_g = myColor->greenF();
  colourStruct.m_b = myColor->blueF();*/
}
