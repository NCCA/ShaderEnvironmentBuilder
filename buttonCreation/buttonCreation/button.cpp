#include <QtWidgets>

#include "button.h"

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

  connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
}
