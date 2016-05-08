/*! \mainpage Welcome to the documentation!
 *
 * \section intro_sec Introduction
 * ## **Welcome to the 0Features-0BugsCVA3 wiki!**
 * For our project, we created an OpenGL Shading Language(glsl) Interactive
 * Development Environment(IDE). The user can load shaders such as 'toon',
 * 'basic metal', 'Phong' and more, then visualise and edit the vertex and
 * fragment shader data using the IDE. Below are some screenshots:
 * ![fill](http://i.imgur.com/39SAeTX.jpg)
 * _Teapot with a texture applied._
 * ![fill](http://i.imgur.com/XTPNWUe.jpg )
 * _Pre-defined shape, 'dragon', with high material shininess set._
 * ![fill](http://imgur.com/lAWgj7p.jpg )
 * _You can import any triangulated .obj mesh to visualise the shader on._
 *
 * \section author_sec Authors
 * | Name                  | GitHub Account |
 * |-----------------------|----------------|
 * | Jonathan Lyddon-Towl  | jlyddon        |
 * | Adam Ting             | yadang23       |
 * | Jonathan Flynn        | JFDesigner     |
 * | Ellie Ansell          | EllieAnsell    |
 * | Philip Rouse          | philrouse      |
 * | Anand Hotwani         | anandhotwani   |
 * | Alexander La Tourelle | mainConfetti   |
 *
 * \section howto_sec How to use
 * **HOW TO USE CEB:**
 * **Navigating the viewport.**
 * The viewport manipulation is similar to most 3D software packages. Using the
 * left mouse button you can rotate the viewport; moving the right mouse button
 * allows you to pan and you can zoom in and out by scrolling the mouse wheel.
 * If you accidentally lose focus of the object, hit 'F' or click 'reset' in
 * camera settings to revert to the default view. In the 'settings' tab, camera
 * controls include roll, yaw, pitch, a slider to set the FOV and the option to
 * change the clipping plane distance. The camera's orthographic view can be set
 * and reset, too. Below the camera settings are visibility switches which can
 * be toggled to show the axis, grid, wireframe ('w') and normals ('n'), and
 * the slider will adjust their size. Below these are the options to export and
 * print uniforms to be saved.
 *
 * ![fill](http://imgur.com/aKjgPqY.png )
 * _The default view window._
 *
 * 1) **Writing your first shader**
 * Upon opening the project, you can either choose to load fragment and vertex
 * shaders via the shader wizard window or simply press 'Esc' to skip to playing
 * with CEB.
 * The default shader in CEB is a normal material which softly reflects light.
 * To begin, load the preset shaders included in the project for both the vertex
 * and fragment shaders:
 * **File-> Import Shaders -> Import Vertex Shader / Import Fragment Shader**
 * (Or Ctrl+Shift+v / Ctrl+Shift+v)
 *
 * The library includes plastic, metal and toon shading as well as a shader with
 *  texture mapping support. Compiling any of these shaders will prompt the
 * Uniform buttons to appear. From here you can affect parameters such as
 * ambient, colour, light position to visualise the shader applied.
 *
 * ![fill](http://i.imgur.com/FCiMomG.png )
 * _The default window and with normal material._
 *
 * Use the central buttons (colour, light.ambient, light.constantAttenuation
 * etc.) to change how the object looks. You can edit the shader files directly
 * via the vertex and fragment text editors, then clicking 'compile shader' to
 * see the results. Auto-correct is incorporated into the editor, as well as
 * syntax highlighting. Errors are thrown to the error log in the compiler.
 * ![fill](http://i.imgur.com/XTPNWUe.jpg )
 * _Default shape dragon with high material shininess and a metal shader._
 *
 * 2) **Loading in custom .OBJ files**
 * CEB already contains a selection of .obj files and primitive shapes to start,
 * but you can also load in your own files provided they're triangulated
 * beforehand.
 * **Load Shapes -> Import OBJ**
 *
 * ![fill](http://i.imgur.com/3JrdyBX.png )
 * _Importing a custom obj file_
 *
 * 3) **Applying texture maps**
 * To load texture maps, first import the TextureMapVertex and
 * TextureMapFragment shaders. Then go:
 * **Load Texture -> Load Texture...**
 * _(Ctrl + T)_
 * Loading in custom texture maps for diffuse values are supported in CEB. Some
 * example texture maps are included in the project, however you are free to use
 * custom maps.
 * Note: the shader needs to support texture maps to work.
 *
 * ![fill](http://i.imgur.com/T5UVgqR.png )
 * _Texture map example._
 *
 * 4) **Loading in custom .glsl files**
 * CEB also supports loading in custom GLSL files directly in the IDE. (Note
 * that this will overwrite any text currently in the editor.) Using this you
 * can load in any presets provided or your own. By going File>Import Shaders
 * you can choose either Fragment or Vertex.
 * ![fill](http://i.imgur.com/Fe1QunC.png )
 *
 * 5) **Saving and loading files**
 * CEB supports saving and loading the shader project files in .xml format.
 * Saving and loading are both accessed via the "File" tab:
 * **File -> save project as...**
 * _(Ctrl+Shift+s)_
 *
 * **File -> Open project...**
 * _(Ctrl+O)_
 *
 * ![fill](http://i.imgur.com/j8ttSKb.png )
 * _Loading a saved project file._
 *
 * 6) **Using the Project Wizard**
 * Using the Project Wizard is designed to help the user to create shaders. By
 * setting a new project the user can specify their desired version of GLSL,
 * profile, project name as well as associated vertex and fragment shaders.
 * ![fill](http://i.imgur.com/U8AhFlc.png )
 * _The project wizard upon opening_
 * ![fill](http://i.imgur.com/N6t6xUN.png )
 * _Choosing the name of your project_
 * ![fill](http://i.imgur.com/9WsGJu1.png )
 * _Loading the phong vertex/ fragment shaders_
 *
 * 7) **Exporting Shader Uniforms**
 * If you find particular uniform set-ups that work well and you would like to
 * re-use in other projects or shaders, you have the ability to export them for
 * later use. These are saved out as text files and can also be run in the
 * Terminal to confirm the exporting.
 * ![fill](http://i.imgur.com/5JV9W8M.png )
 * _Exporting the uniforms_
 * ![fill](http://i.imgur.com/eMLQluWg.png )
 * _Exported the uniforms successfully._
 *
 * The pop-up reads "Uniform data successfully exported!", and a text editor
 * shows the written data saved as a .txt file to be used in other applications.
 * ![fill](http://i.imgur.com/PFQOU8r.png )
*/

#include <QApplication>
#include "CebApplication.h"
#include "MainWindow.h"
#include <qsurfaceformat.h>

int main(int argc, char **argv)
{
  // create an OpenGL format specifier
  QSurfaceFormat format;
  // set the number of samples for multisampling
  // will need to enable glEnable(GL_MULTISAMPLE); once we have a context
  format.setSamples(4);
  #if defined( DARWIN)
    // at present mac osx Mountain Lion only supports GL3.2
    // the new mavericks will have GL 4.x so can change
    format.setMajorVersion(4);
    format.setMinorVersion(2);
  #else
    // with luck we have the latest GL version so set to this
    format.setMajorVersion(4);
    format.setMinorVersion(3);
  #endif
  // now we are going to set to CoreProfile OpenGL so we can't use and old Immediate mode GL
  format.setProfile(QSurfaceFormat::CoreProfile);
  // now set the depth buffer to 24 bits
  format.setDepthBufferSize(24);
  // this will set the format for all widgets
  QSurfaceFormat::setDefaultFormat(format);
  // make an instance of the QApplication
  CebApplication a(argc, argv);
  // Create a new MainWindow
  MainWindow w;
  // show main window
  w.show();
  // show start dialog
  w.showStartDialog();

  // hand control over to Qt framework
  return a.exec();
}
