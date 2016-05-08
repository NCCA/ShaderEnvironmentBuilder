#include <cstdlib>
#include <iostream>

#include "Button.h"

//----------------------------------------------------------------------------------------------------------------------
/// @file button.cpp
/// @brief implementation of the different button classes
/// @author Jonny Lyddon
/// @date 07/05/16
//----------------------------------------------------------------------------------------------------------------------

Button::Button(QWidget *parent) : QDialog(parent)
{
  createButtonBox();
}

Button::Button(QString _buttonName, GLenum _buttonType, QLayout *_layout, GLuint _id, ButtonLib *_libParent, NGLScene *_sceneParent, QWidget *parent) : QDialog(parent)
{
  m_buttonName = _buttonName;
  m_buttonType = _buttonType;
  m_id=_id;
  createButtonBox(_buttonName);
  m_libParent=_libParent;
  m_sceneParent=_sceneParent;
  m_parent=parent;
  _layout->addWidget(m_button);
}

void Button::createButtonBox(QString _buttonName)
{
  m_button = new QPushButton();
  m_button->setText(_buttonName);
  connect(m_button, SIGNAL(clicked()), this, SLOT(openBox()));
}

void Button::printValues()
{
  qDebug()<<"Name:"<<m_buttonName<<"\nID: "<<m_id;
}

void ColourButton::printAttributes()
{
  std::cout<<"R: "<<m_colour.m_x<<"\nG: "<<m_colour.m_y<<"\nB: "<<m_colour.m_z<<std::endl;
}

void ColourButton::openBox()
{
  //these are set so when the colour picker is opened the current colour is opened
  m_colourPicked.setRedF(m_colour.m_x);
  m_colourPicked.setGreenF(m_colour.m_y);
  m_colourPicked.setBlueF(m_colour.m_z);
  m_colourPicked=m_colourGroupBox->getColor(m_colourPicked,
                                            m_parent,
                                            "Pick a colour",
                                            0);
  if(m_colourPicked.spec()!=QColor::Spec::Invalid)
  {
    m_colour.set(m_colourPicked.redF(),
                 m_colourPicked.greenF(),
                 m_colourPicked.blueF(),
                 m_colourPicked.alphaF());
    m_libParent->updateShaderValues();
    m_sceneParent->update();
  }

}

void ColourButton::setColour(QColor _col)
{
  m_colourPicked=_col;
  m_colour.set(_col.redF(),
               _col.greenF(),
               _col.blueF(),
               _col.alphaF());
}

void ColourButton::setColour(ngl::Vec4 _col)
{
  m_colour=_col;
  m_colourPicked.setRgbF(m_colour.m_x,
                         m_colour.m_y,
                         m_colour.m_z,
                         m_colour.m_w);
}

void FloatButton::openBox()
{
  double val = QInputDialog::getDouble(
        m_parent, tr("Input"), tr("Input"),m_value,-2147483647,2147483647,5);
  m_value=val;
  m_libParent->updateShaderValues();
  m_sceneParent->update();
}

void VecButton::setUpButton(ngl::Vec3 _vector)
{
  m_value.set(_vector);
  m_value.m_w=1.0f;

   m_vecWindow = new QDialog(m_parent);
   m_vecLayout = new QGridLayout(m_vecWindow);

   m_vecWindow->setWindowTitle("Input XYZ values");
   std::cout<<"My widget created\n";
   m_vecWindow->setFixedSize(200,200);
   m_vecWindow->setModal(1);
   m_xName = new QLabel("X: ");
   m_xSpinBox = new QDoubleSpinBox();
   m_xSpinBox->setSingleStep(0.1);
   m_xSpinBox->setDecimals(3);
   m_xSpinBox->setValue(m_value.m_x);
   m_xSpinBox->setRange(-100000.0f,100000.0f);
   m_yName = new QLabel("Y: ");
   m_ySpinBox = new QDoubleSpinBox();
   m_ySpinBox->setSingleStep(0.1);
   m_ySpinBox->setDecimals(3);
   m_ySpinBox->setValue(m_value.m_y);
   m_ySpinBox->setRange(-100000.0f,100000.0f);
   m_zName = new QLabel("Z: ");
   m_zSpinBox = new QDoubleSpinBox();
   m_zSpinBox->setSingleStep(0.1);
   m_zSpinBox->setDecimals(3);
   m_zSpinBox->setValue(m_value.m_z);
   m_zSpinBox->setRange(-100000.0f,100000.0f);
   m_vecLayout->addWidget(m_xName, 0, 0);
   m_vecLayout->addWidget(m_xSpinBox, 0, 1);
   m_vecLayout->addWidget(m_yName, 1, 0);
   m_vecLayout->addWidget(m_ySpinBox, 1, 1);
   m_vecLayout->addWidget(m_zName, 2, 0);
   m_vecLayout->addWidget(m_zSpinBox,2, 1);

   QDialogButtonBox *buttonBox_ok = new QDialogButtonBox(QDialogButtonBox::Ok);
   QDialogButtonBox *buttonBox_cancel = new QDialogButtonBox(QDialogButtonBox::Cancel);
   connect(buttonBox_ok, SIGNAL(accepted()), m_vecWindow, SLOT(accept()));
   connect(buttonBox_cancel, SIGNAL(rejected()), m_vecWindow, SLOT(reject()));

   m_vecLayout->addWidget(buttonBox_cancel, 3, 0);
   m_vecLayout->addWidget(buttonBox_ok, 3, 1);

}

void VecButton::openBox()
{
  m_xSpinBox->setValue(m_value.m_x);
  m_ySpinBox->setValue(m_value.m_y);
  m_zSpinBox->setValue(m_value.m_z);
  m_vecWindow->exec();
  if (m_vecWindow->result() == 1)
  {
    m_value.set(m_xSpinBox->value(),
                m_ySpinBox->value(),
                m_zSpinBox->value());
    m_libParent->updateShaderValues();
    m_sceneParent->update();
  }
}
