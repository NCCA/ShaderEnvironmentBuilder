
#include <QtWidgets>

#include "widget.h"


widget::widget(QWidget *parent) : QDialog(parent)
{
  createColourPanel();
  mainLayout = new QGridLayout;
  mainLayout->addWidget(colourGroupBox, 0, 0);
  setLayout(mainLayout);

  mainLayout->setSizeConstraint(QLayout::SetMinimumSize);
  setWindowTitle(tr("My Test Layout"));
}

void widget::colChange()
{
  //*myColor = colourGroupBox->getColor();
  //std::cout<<"Colours are: "<<std::endl;
}

void widget::createColourPanel()
{
  colourGroupBox = new QColorDialog(tr("Colour"));
  colourBoxLabel = new QLabel(tr("Select a colour:"));

  //colourBoxLayout = new QGridLayout;
  //colourGroupBox->setLayout(colourBoxLayout);
  *myColor = colourGroupBox->getColor();

  colourStruct.m_r = myColor->redF();
  colourStruct.m_g = myColor->greenF();
  colourStruct.m_b = myColor->blueF();
  //connect(colourGroupBox, SIGNAL(colorSelected(QColor)), this, SLOT(colChange()));
}

qreal widget::returnRed()
{
  return colourStruct.m_r;
}

qreal widget::returnGreen()
{
  return colourStruct.m_g;
}

qreal widget::returnBlue()
{
  return colourStruct.m_b;
}

void widget::assignCol(m_colour* a)
{
  *a = colourStruct;
}
