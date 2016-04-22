#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>

#include "project.h"
#include "json.h"
#include "CebErrors.h"
#include "io_xml.h"

Project::Project()
{
  m_data.m_projectName = "untitled";
  m_data.m_projectDir = "";
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
  m_data.m_projectName = _name;
  m_data.m_projectDir = _dir;
}

void Project::save(QString vertSource, QString fragSource)
{
  QString fileName;
  if(!m_saved)
  {
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec())
    {
      fileName = dialog.selectedFiles().at(0);
      QFileInfo finfo = QFileInfo(fileName);
      m_data.m_projectDir = finfo.absolutePath().toStdString();
      m_data.m_projectName = finfo.baseName().toStdString();
    }

  }
  std::cout<<"Name: "<<m_data.m_projectName<<"  Directory: "<<m_data.m_projectDir<<std::endl;

  // Converts QString to const char*
  const char * vertSource_c = vertSource.toStdString().c_str();
  const char * fragSource_c = fragSource.toStdString().c_str();
  m_xml->writeProject(m_data.m_projectName, m_data.m_projectDir, vertSource_c, fragSource_c);
  //m_xml->writeProject(projectName, projectDir, vertex, fragment);
  m_saved = true;
}

void Project::saveAs(QString vertSource, QString fragSource)
{
   m_saved = false;
   save(vertSource, fragSource);
}

bool Project::exportProject(std::string _targetDir, QString vertSource, QString fragSource)
{


  //create path to vertex.glsl in target directory
  QString filePath = QString::fromStdString(_targetDir.append(m_data.m_projectName.append("Vertex.glsl")));
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
  filePath = QString::fromStdString(_targetDir.append(m_data.m_projectName.append("Vertex.glsl")));
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


