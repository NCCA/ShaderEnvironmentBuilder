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
    for(auto uniform : m_parser->m_uniformList)
    {
      if(uniform->getTypeName()=="vec4")
      {
        QString _uniformName = QString::fromStdString(uniform->getName());
        ngl::Vec4 _uniformVec=uniform->getVec4();
        colourButton *tempButton = new colourButton(_uniformName,
                                                    m_layout,
                                                    uniform->getLocation(),
                                                    this,
                                                    m_scene,
                                                    m_parent);
        tempButton->setColour(_uniformVec);
        m_buttonList.push_back(tempButton);
      }
      if(uniform->getTypeName()=="float")
      {
        QString _uniformName = QString::fromStdString(uniform->getName());
        float _uniformFloat=uniform->getFloat();
        floatButton *tempButton = new floatButton(_uniformName,
                                                  m_layout,
                                                  uniform->getLocation(),
                                                  this,
                                                  m_scene,
                                                  m_parent);
        tempButton->setValue(_uniformFloat);
        m_buttonList.push_back(tempButton);
      }
    }
  }
  /*std::cout<<"These are the active uniforms:\n";
  for(auto uniform : m_parser->m_uniformList)
  {
    std::cout<<"Uniform name: "<<uniform->getName()<<"\nID: "<<uniform->getLocation()<<"\n";
  }*/

  /*else
  {
    std::vector<Button*> _buttonDup = m_buttonList;
    for (auto but: m_buttonList)
    {
      delete but;
    }
    //m_buttonList.clear();
    //qDebug()<<"My button list length is "<<m_buttonList.size();
    //_buttonDup.pop_back();
  }*/
}
void ButtonLib::updateShaderValues()
{
  //qDebug()<<"Function ran\n";
  for(auto uniform: m_parser->m_uniformList)
  {
    if(uniform->getTypeName()=="vec4")
    {
      for(auto button: m_buttonList)
      {
        if(uniform->getLocation()==button->getID())
        {
          ngl::Vec4 temp = button->getColour();
          //qDebug()<<temp.m_x<<", "<<temp.m_y<<", "<<temp.m_z<<"\n";
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
