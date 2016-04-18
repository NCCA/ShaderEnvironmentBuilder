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
    void loadShader(QString _text, ngl::ShaderType _type);
    void compileShader(ngl::Camera _cam);

private:
    ngl::ShaderLib *shader = ngl::ShaderLib::instance();


};

#endif // SHADERMANAGER_H
