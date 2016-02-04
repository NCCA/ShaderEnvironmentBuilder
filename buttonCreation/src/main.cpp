#include <QtGui/QApplication>

#include <iostream>
#include <cstdlib>

//#include "read.cpp"

#include "button.h"

int main(int argc, char *argv[])
{
  //readFile();
  QApplication app(argc, argv);
  Button myButton;
  myButton.show();

  return app.exec();
}
