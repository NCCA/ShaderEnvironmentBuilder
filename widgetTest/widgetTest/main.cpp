
#include <QtGui/QApplication>

#include <iostream>
#include <cstdlib>
#include "widget.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  widget widgey;
  //widget widgey2;
  widgey.show();
  //widgey2.show();
  typedef struct m_colour
  {
    qreal m_r;
    qreal m_g;
    qreal m_b;
  } m_colour;
  //myCol=widgey.returnCol();
  std::cout<<"R: "<<widgey.returnRed()<<"\nG: "<<widgey.returnGreen()<<"\nB: "<<widgey.returnBlue()<<std::endl;

  //return app.exec();
}
