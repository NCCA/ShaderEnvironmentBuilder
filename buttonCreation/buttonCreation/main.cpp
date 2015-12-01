#include <QtGui/QApplication>

#include <iostream>
#include <cstdlib>

#include "button.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  Button myButton;
  myButton.show();

  return app.exec();
}
