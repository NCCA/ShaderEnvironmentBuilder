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
    void initialize();
    void loadShader(QString vertSource, QString fragSource);
    void compileShader(ngl::Camera _cam, QString vertSource, QString fragSource);

private:
    ngl::ShaderLib *m_shaderLib = ngl::ShaderLib::instance();


};

#endif // SHADERMANAGER_H
