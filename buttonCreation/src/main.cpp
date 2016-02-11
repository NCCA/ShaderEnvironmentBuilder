#include <QtGui/QApplication>

#include <iostream>
#include <cstdlib>

//#include "read.cpp"

#include "button.h"

int main(int argc, char *argv[])
{
  //readFile();
  QApplication app(argc, argv);

  QGridLayout *mainLayout_2;
  mainLayout_2 = new QGridLayout;/*
  mainLayout->addWidget(buttonBox, 0, 1);
  setLayout(mainLayout);

  mainLayout->setSizeConstraint(QLayout::SetMinimumSize);

  setWindowTitle(tr("Button Layout"));*/
  //Button myButton;
  //myButton.show();

  return app.exec();
}
