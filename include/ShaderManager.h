#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <string>
#include <ngl/ShaderLib.h>
#include <QString>
#include <ngl/Camera.h>

//structure containing currently active shader data
struct shaderProgramData
{
  std::string m_name;
  std::string m_vert;
  std::string m_frag;
};

class ShaderManager
{
public:
    ShaderManager();
    void createShaderProgram(std::string _name);
    void use(ngl::ShaderLib  *_shaderLib,uint shaderType);
    void initialize(ngl::Camera _cam);
    void compileShader(ngl::Camera _cam, QString vertSource, QString fragSource);
    inline bool isInit() {return m_init;}
    inline bool compileStatus() {return m_compileStatus;}
    inline QString getErrorLog() {return m_errorLog;}
    inline void setData(std::string _name, std::string _vert, std::string _frag)
    {m_data.m_name = _name; m_data.m_vert = _vert; m_data.m_frag = _frag;}

private:
    bool m_init;
    bool m_compileStatus;
    QString m_errorLog;
    bool checkCompileError(std::string _shaderProgName, QString *o_log);
    bool checkAllCompileError(QString *o_log);
    shaderProgramData m_data;


};

#endif // SHADERMANAGER_H
