#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>

#include "project.h"
#include "Json.h"
#include "CebErrors.h"
#include "Io_xml.h"

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

  // Converts QString to const char* (These have to be separate, not .toStdString.c_str() otherwise it doesn't write the string.)
  std::string vertSourceString = vertSource.toStdString();
  std::string fragSourceString = vertSource.toStdString();
  const char * vertSource_c = vertSourceString.c_str();
  const char * fragSource_c = fragSourceString.c_str();

  m_xml->writeProject(m_data.m_projectName, m_data.m_projectDir, vertSource_c, fragSource_c);
  m_saved = true;
}

void Project::saveAs(QString vertSource, QString fragSource)
{
  m_saved = false;
  save(vertSource, fragSource);
}

int Project::confirmOverwrite(QString _filePath)
{
  QMessageBox msgBox;
  msgBox.setIcon(QMessageBox::Warning);
  msgBox.setText("The file you have specified already exists: " + _filePath);
  msgBox.setInformativeText("Do you want to overwrite the file?");
  msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::No | QMessageBox::Cancel);
  msgBox.setDefaultButton(QMessageBox::Save);
  QMessageBox::ButtonRole ret = static_cast<QMessageBox::ButtonRole>(msgBox.exec());
  return ret;
}

bool Project::exportProject(std::string _targetDir, QString vertSource, QString fragSource)
{

  _targetDir.append("/");

  QString detOutput;
  //create path to vertex.glsl in target directory
  QString vFilePath = QString::fromStdString(_targetDir + m_data.m_projectName + "Vertex.glsl");
  qDebug() << vFilePath;

  //create qfile object assiciated with the file name
  QFile vertFile(vFilePath);
  QFileInfo checkPath(vFilePath);

  int state = QMessageBox::Save;
  if (checkPath.exists() && checkPath.isFile())
  {
    state = confirmOverwrite(vFilePath);
    if (state == QMessageBox::Cancel)
    {
      return false;
    }
  }

  if (state == QMessageBox::Save)
  {
    //try to open the file for writing, if it doesnt exist the open() method will create it.
    if(!vertFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      CEBRaise::QtFileError(vertFile.error(), vFilePath);
      return false;
    }

    // write vertex source into Vertex.glsl file
    QTextStream outVert(&vertFile);
    outVert << vertSource;
    vertFile.close();
    detOutput.append("Vertex File: " + vFilePath + "\n");
  }

  //now do the same for fragment.glsl
  QString fFilePath = QString::fromStdString(_targetDir + m_data.m_projectName + "Fragment.glsl");
  qDebug() << fFilePath;
  QFile fragFile(fFilePath);
  checkPath = QFileInfo(fFilePath);

  state = QMessageBox::Save;
  if (checkPath.exists() && checkPath.isFile())
  {
    state = confirmOverwrite(fFilePath);
    if (state == QMessageBox::Cancel)
    {
      return false;
    }
  }

  if (state == QMessageBox::Save)
  {
    if(!fragFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      CEBRaise::QtFileError(fragFile.error(), fFilePath);
      return false;
    }

    QTextStream outFrag(&fragFile);
    outFrag << fragSource;
    fragFile.close();
    detOutput.append("Fragment File: " + vFilePath + "\n");
  }

  QMessageBox msgBox;
  msgBox.setText("The file(s) have been successfully saved");
  msgBox.setDetailedText(detOutput);
  msgBox.exec();
  return true;
}
// ----------------------------------------------------------------------------------------------------------------------
// Loads the xml saved project data.
void Project::load(std::string _loadedFileDirectory)
{
   m_saved = true;
   std::cout<<"Opening: "<<_loadedFileDirectory<<std::endl;

   std::string _vertSource = "";
   std::string _fragSource = "";
   std::string _fileName = "";
   std::string _fileDirectory = "";
   m_xml->readProjectXML(_fileName, _fileDirectory, _loadedFileDirectory, _vertSource, _fragSource);
   m_data.m_projectName = _fileName;
   m_data.m_projectDir = _fileDirectory;
}

