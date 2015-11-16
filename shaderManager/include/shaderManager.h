#ifndef SHADERMANAGER_H__
#define SHADERMANAGER_H__

#include <ngl/ShaderLib.h>

class ShaderManager
{
    public:
    void update();
    void swap(GLint *target);

    private:

    ngl::ShaderProgram render[2];
    int render = 0;
    int edit = 1;
};
