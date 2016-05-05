#include "ButtonLib.h"

ButtonLib::ButtonLib(parserLib *_parser, QLayout *_layout, NGLScene *_scene, QWidget *_parent)
{
  m_parser=_parser;
  m_layout=_layout;
  m_parent=_parent;
  m_scene=_scene;
  createButtons();
  updateShaderValues();
}

void ButtonLib::createButtons()
{
  if(m_buttonList.size()==0)
  {
    std::cerr<<"CHECKING BUTTON LIST\n";
    for(auto uniform : m_parser->m_uniformList)
    {

      if(uniform->getTypeName()=="vec4")
      {
        QString _tempName = QString::fromStdString(uniform->getName());
        ngl::Vec4 _tempVec=uniform->getVec4();
        colourButton *tempButton = new colourButton(_tempName,
                                                    m_layout,
                                                    uniform->getLocation(),
                                                    this,
                                                    m_scene,
                                                    m_parent);
        tempButton->setColour(_tempVec);
        m_buttonList.push_back(tempButton);
      }
      if(uniform->getTypeName()=="float")
      {
        QString _tempName = QString::fromStdString(uniform->getName());
        float _tempFloat=uniform->getFloat();
        floatButton *tempButton = new floatButton(_tempName,
                                                  m_layout,
                                                  uniform->getLocation(),
                                                  this,
                                                  m_scene,
                                                  m_parent);
        tempButton->setValue(_tempFloat);
        m_buttonList.push_back(tempButton);
      }
    }
  }
}

void ButtonLib::updateShaderValues()
{
  qDebug()<<"Function ran\n";
  for(auto uniform: m_parser->m_uniformList)
  {
    if(uniform->getTypeName()=="vec4")
    {
      for(auto button: m_buttonList)
      {
        if(uniform->getLocation()==button->getID())
        {
          ngl::Vec4 temp = button->getColour();
          qDebug()<<temp.m_x<<", "<<temp.m_y<<", "<<temp.m_z<<"\n";
          uniform->setVec4(temp);
          break;
        }
      }

    }
    if(uniform->getTypeName()=="float")
    {
      for(auto button: m_buttonList)
      {
        if(uniform->getLocation()==button->getID())
        {
          float temp = button->getValue();
          uniform->setFloat(temp);
          break;
        }
      }
    }
  }
}
