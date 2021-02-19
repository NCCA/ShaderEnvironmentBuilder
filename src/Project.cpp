#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>

#include "Project.h"
#include "CebErrors.h"
#include "Io_xml.h"

//----------------------------------------------------------------------------

Project::Project()
{
  m_projectName = "untitled";
  m_projectDir = "";
  m_xml = new IO_XML;
  m_saved = false;
  m_firstSave = true;
}

//----------------------------------------------------------------------------

Project::~Project()
{
  delete m_xml;
}

//----------------------------------------------------------------------------

bool Project::save(QString _vertSource, QString _fragSource)
{
  QString fileName;

  // if the project has not been saved before then open the QFile Dialog
  if(!m_saved)
  {
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    if (dialog.exec())
    {

      fileName = dialog.selectedFiles().at(0);
      QFileInfo finfo = QFileInfo(fileName);
      // set project data fromt eh dialog and set m_saved to true
      set(finfo.baseName().toStdString(), finfo.absolutePath().toStdString(), true, true);
    }
    else
    {
      return false;
    }
  }

  std::cout<<"Saving project..."<<std::endl;

  // convert QStrings to c strings.
  std::string vertSourceString = _vertSource.toStdString();
  std::string fragSourceString = _fragSource.toStdString();

  const char * vertSource_c = vertSourceString.c_str();
  const char * fragSource_c = fragSourceString.c_str();

  //write project to XML
  bool success = m_xml->writeProject(m_projectName, m_projectDir, vertSource_c,
                                     fragSource_c, !m_firstSave);

  if (success)
  {
    std::cout<<"Saved project: \nName: "<<m_projectName<<"  Directory: "<<m_projectDir<<std::endl;
    m_firstSave=false;
  }

  return success;
}

//----------------------------------------------------------------------------

bool Project::saveAs(QString vertSource, QString _fragSource)
{
  // set save state to false then call save function
  m_saved = false;
  return save(vertSource, _fragSource);
}

//----------------------------------------------------------------------------

int Project::confirmOverwrite(QString _filePath)
{
  QMessageBox msgBox;
  msgBox.setIcon(QMessageBox::Warning);
  msgBox.setText("The file you have specified already exists: " + _filePath);
  msgBox.setInformativeText("Do you want to overwrite the file?");
  msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::No | QMessageBox::Cancel);
  msgBox.setDefaultButton(QMessageBox::Save);
  int ret = msgBox.exec();
  return ret;
}

//----------------------------------------------------------------------------

bool Project::exportProject(std::string _targetDir, QString _vertSource, QString _fragSource)
{

  _targetDir.append("/");

  QString detOutput;
  //create path to vertex.glsl in target directory
  QString vFilePath = QString::fromStdString(_targetDir + m_projectName + "Vertex.glsl");
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
    outVert << _vertSource;
    vertFile.close();
    detOutput.append("Vertex File: " + vFilePath + "\n");
  }

  //now do the same for fragment.glsl
  QString fFilePath = QString::fromStdString(_targetDir + m_projectName + "Fragment.glsl");
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
    outFrag << _fragSource;
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

void Project::load(std::string _loadedFileDirectory, QString &o_vertSource, QString &o_fragSource)
{

  std::cout<<"Opening: "<<_loadedFileDirectory<<std::endl;
  std::string vertSource = "";
  std::string fragSource = "";
  std::string fileName = "";
  std::string fileDirectory = "";

  // read project from XML file storing data in variables.
  m_xml->readProjectXML(fileName, fileDirectory, _loadedFileDirectory, vertSource, fragSource);

  // set the project data
  set(fileName, fileDirectory, true, false);

  // set output shader source strings
  o_vertSource = QString::fromStdString(vertSource);
  o_fragSource = QString::fromStdString(fragSource);

}

