
#include <QtGui/QApplication>

#include <iostream>
#include <cstdlib>
#include "widget.h"

extern "C"
{
  #include <unistd.h>
}

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  widget widgey;
  //widget widgey2;
  sleep(2);
  widgey.show();
  sleep(2);
  //widgey2.show();
  typedef struct m_colour
  {
    qreal m_r;
    qreal m_g;
    qreal m_b;
  } m_colour;
  //myCol=widgey.returnCol();
  sleep(2);
  std::cout<<"R: "<<widgey.returnRed()<<"\nG: "<<widgey.returnGreen()<<"\nB: "<<widgey.returnBlue()<<std::endl;

  //return app.exec();
}
