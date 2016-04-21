#include "project.h"
#include "json.h"
#include <fstream>
#include "io_xml.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "CebErrors.h"

Project::Project()
{
  m_name = "untitled";
  m_dir = "";
  m_Json  = new Json;
  m_xml = new IO_XML;
  m_saved = false;
}

Project::~Project()
{
  delete m_Json;
  delete m_xml;
}

void Project::set(std::string _name, std::string _dir)
{
  m_name = _name;
  m_dir = _dir;
}

void Project::save()
{
  m_xml->writeProject(m_name, m_dir);
  m_saved = true;
}

void Project::saveAs(string _name, string _dir)
{
   set(_name, _dir);
   save();
}

bool Project::exportProject(std::string _targetDir, QString vertSource, QString fragSource)
{


  //create path to vertex.glsl in target directory
  QString filePath = QString::fromStdString(_targetDir.append(m_name.append("Vertex.glsl")));
  qDebug() << filePath;

  //create qfile object assiciated with the file name
  QFile vertFile(filePath);

  //try to open the file for writing, if it doesnt exist the open() method will create it.
  if(!vertFile.open(QIODevice::WriteOnly | QIODevice::Text))
  {
    ceb_raise::QtFileError(vertFile.error(), filePath);
    return false;
  }

  // write vertex source into Vertex.glsl file
  QTextStream outVert(&vertFile);
  outVert << vertSource;
  vertFile.close();

  //now do the same for fragment.glsl
  filePath.clear();
  filePath = QString::fromStdString(_targetDir.append(m_name.append("Vertex.glsl")));
  qDebug() << filePath;
  QFile fragFile(filePath);

  if(!fragFile.open(QIODevice::WriteOnly | QIODevice::Text))
  {
    ceb_raise::QtFileError(fragFile.error(), filePath);
    return false;
  }

  QTextStream outFrag(&fragFile);
  outFrag << fragSource;
  fragFile.close();

  return true;
}


