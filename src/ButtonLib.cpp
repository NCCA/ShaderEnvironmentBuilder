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
  for(auto uniform : m_parser->m_uniformList)
  {
    QString _uniformName = QString::fromStdString(uniform->getName());
    std::string _uniformType = uniform->getTypeName();
    if(_uniformType=="vec4")
    {
      ngl::Vec4 _uniformVec=uniform->getVec4();
      colourButton *tempButton = new colourButton(_uniformName,
                                                  _uniformType,
                                                  m_layout,
                                                  uniform->getLocation(),
                                                  this,
                                                  m_scene,
                                                  m_parent);
      tempButton->setColour(_uniformVec);
      m_buttonList.push_back(tempButton);
    }
    if(_uniformType=="float")
    {
      float _uniformFloat=uniform->getFloat();
      floatButton *tempButton = new floatButton(_uniformName,
                                                _uniformType,
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

void ButtonLib::updateButtons()
{
  if(m_buttonList.size()==0)
  {
    createButtons();
  }
  else
  {
    std::vector<Button*> _buttonDup = m_buttonList;
    m_buttonList.resize(0);
    createButtons();
    for(auto uniform: m_buttonList)
    {
      for(int i=0; i<_buttonDup.size(); ++i)
      {
        if(uniform->getName()==_buttonDup[i]->getName() && uniform->getType()==_buttonDup[i]->getType())
        {
          int uniformID=uniform->getID();
          if(uniform->getType()=="vec4")
          {
            qDebug()<<"\nUniform name:"<<uniform->getName()<<"\nTemp: "<<_buttonDup[i]->getName();
            QColor display = _buttonDup[i]->getColourQ();
            qDebug()<<"\nDuplicate vals: "<<display.redF()<<", "<<display.greenF()<<", "<<display.blueF()<<"\n";
            uniform->setColour(_buttonDup[i]->getColourQ());

          }
          if(uniform->getType()=="float")
          {
            std::cout<<"Uniform vals, being set"<<std::endl;
            uniform->setValue(_buttonDup[i]->getValue());
          }
        }
      }
    }
  }
}
void ButtonLib::updateShaderValues()
{
  for(auto uniform: m_parser->m_uniformList)
  {
    if(uniform->getTypeName()=="vec4")
    {
      for(auto button: m_buttonList)
      {
        if(uniform->getLocation()==button->getID())
        {
          ngl::Vec4 temp = button->getColour();
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
