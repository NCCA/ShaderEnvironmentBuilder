#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <string>
#include <ngl/ShaderLib.h>
#include <QString>
#include <ngl/Camera.h>

class ShaderManager
{
public:
    ShaderManager();
    void createShaderProgram(std::string _name, QString _sourceVert, QString _sourceFrag);
    void updateShaderProgram(std::string _name, QString _sourceVert, QString _sourceFrag);
    void use(std::string _name);
    void initialize(ngl::Camera _cam);
    void loadShader(QString vertSource, QString fragSource);
    void compileShader(ngl::Camera _cam, QString vertSource, QString fragSource);
    inline bool isInit() {return m_init;}
    inline bool compileStatus() {return m_compileStatus;}
    inline QString getErrorLog() {return m_errorLog;}

private:
    bool m_init;
    bool m_compileStatus;
    QString m_errorLog;
    bool checkCompileError(std::string _shaderProgName, QString *o_log);
    bool checkAllCompileError(std::vector<std::string> _shaderProgNames, QString *o_log);


};

#endif // SHADERMANAGER_H
