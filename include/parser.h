#ifndef PARSER_H__
#define PARSER_H__
#include <unordered_map>
#include <iostream>
#include <ngl/ShaderLib.h>
#include <ngl/Shader.h>
#include <fstream>
class parser
{

public:
  parser();
  ~parser();
  int m_num;






  void listUniforms();
  void uniformDataTypes();
  void exportUniforms();

  typedef struct
  {
      std::string nameUniforms;
      GLuint locationUniforms;
      GLenum typeUniforms;
      std::string dataType;
  }uniformData;

  std::unordered_map <std::string, uniformData> m_registeredUniforms;

  std::vector <uniformData> m_passToGUI;


};

#endif // PARSER_H
