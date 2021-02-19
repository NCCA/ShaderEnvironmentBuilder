#include "ButtonLib.h"

ButtonLib::ButtonLib(ParserLib *_parser, QLayout *_layout, NGLScene *_scene, QWidget *_parent)
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
    GLenum _uniformType = uniform->getTypeEnum();
    if(_uniformType==GL_FLOAT_VEC4)
    {
      ngl::Vec4 _uniformVec=uniform->getVec4();
      ColourButton *tempButton = new ColourButton(_uniformName,
                                                  _uniformType,
                                                  m_layout,
                                                  uniform->getLocation(),
                                                  this,
                                                  m_scene,
                                                  m_parent);
      tempButton->setColour(_uniformVec);
      m_buttonList.push_back(tempButton);
    }
    if(_uniformType==GL_FLOAT)
    {
      float _uniformFloat=uniform->getFloat();
      FloatButton *tempButton = new FloatButton(_uniformName,
                                                _uniformType,
                                                m_layout,
                                                uniform->getLocation(),
                                                this,
                                                m_scene,
                                                m_parent);
      tempButton->setValue(_uniformFloat);
      m_buttonList.push_back(tempButton);
    }
    if(_uniformType==GL_FLOAT_VEC3)
    {
      ngl::Vec3 _uniformVec=uniform->getVec3();
      VecButton *tempButton = new VecButton(_uniformName,
                                                  _uniformType,
                                                  m_layout,
                                                  uniform->getLocation(),
                                                  this,
                                                  m_scene,
                                                  m_parent);
      tempButton->setUpButton(_uniformVec);
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
    for(auto uniform : m_buttonList)
    {
      delete uniform->m_button;
    }
    m_buttonList.resize(0);
    createButtons();
    for(auto uniform: m_buttonList)
    {
      for(uint i=0; i<_buttonDup.size(); ++i)
      {
        if(uniform->getName()==_buttonDup[i]->getName() && uniform->getTypeEnum()==_buttonDup[i]->getTypeEnum())
        {
          if(uniform->getTypeEnum()==GL_FLOAT_VEC4)
          {
            uniform->setColour(_buttonDup[i]->getColourQ());
            _buttonDup.erase(_buttonDup.begin()+i);
            break;
          }
          if(uniform->getTypeEnum()==GL_FLOAT)
          {
            uniform->setValue(_buttonDup[i]->getValue());
            _buttonDup.erase(_buttonDup.begin()+i);
            break;
          }
          if(uniform->getTypeEnum()==GL_FLOAT_VEC3)
          {
            uniform->setVec(_buttonDup[i]->getVec());
            _buttonDup.erase(_buttonDup.begin()+i);
            break;
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
    if(uniform->getTypeEnum()==GL_FLOAT_VEC4)
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
    if(uniform->getTypeEnum()==GL_FLOAT)
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
    if(uniform->getTypeEnum()==GL_FLOAT_VEC3)
    {
      for(auto button: m_buttonList)
      {
        if(uniform->getLocation()==button->getID())
        {
          ngl::Vec4 temp = button->getVec();
          uniform->setVec3(ngl::Vec3(temp.m_x,
                                     temp.m_y,
                                     temp.m_z));
          break;
        }
      }
    }
  }
}
