#include <QtWidgets>
#include "NewProjectWizard.h"
#include <QFileDialog>

NewProjectWizard::NewProjectWizard(QWidget *parent): QWizard(parent)
{
    addPage(new IntroPage);
    addPage(new ProjectInfoPage);
    addPage(new GlslFilesPage);
    addPage(new ConclusionPage);

    setWindowTitle(tr("New Project Wizard"));
}

void NewProjectWizard::accept()
{
  QDialog::accept();
}


IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Introduction"));

    label = new QLabel(tr("This wizard will generate a CEB project "
                          "definition. You simply "
                          "need to specify the project name and set a few "
                          "options to produce a json project file "
                          "implementation for your new OpenGL shader."));
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

ProjectInfoPage::ProjectInfoPage(QWidget *parent)
    : QWizardPage(parent)
{
  setTitle(tr("Project Information"));
  setSubTitle(tr("Specify basic information about the project for which you "
                 "want to generate."));

  m_l_projectName = new QLabel(tr("Project name:"));
  m_le_projectName = new QLineEdit();
  m_l_projectName->setBuddy(m_le_projectName);

  m_l_projectDirectory = new QLabel(tr("Project Directory:"));
  m_b_browseDirectory = new QPushButton(tr("Browse..."));
  m_le_projectDirectory = new QLineEdit(QDir::homePath());
  m_l_projectDirectory->setBuddy(m_le_projectDirectory);

  registerField("projectName*", m_le_projectName);
  registerField("projectDirectory", m_le_projectDirectory);

  QGridLayout *layout = new QGridLayout;
  layout->addWidget(m_l_projectName, 0, 0);
  layout->addWidget(m_le_projectName, 0, 1, 1, 2);
  layout->addWidget(m_l_projectDirectory, 1, 0);
  layout->addWidget(m_le_projectDirectory, 1, 1);
  layout->addWidget(m_b_browseDirectory, 1, 2);
  setLayout(layout);

  connect(m_b_browseDirectory, SIGNAL (clicked()),this, SLOT(setProjectDirectory()));
}

void ProjectInfoPage::initializePage()
{
  m_le_projectName->setText("Phong");
}


void ProjectInfoPage::setProjectDirectory()
{
  QFileDialog dialog(this);
  dialog.setFileMode(QFileDialog::Directory);
  dialog.setOption(QFileDialog::ShowDirsOnly, true);
  QStringList folderNames;
  if (dialog.exec())
  {
      folderNames = dialog.selectedFiles();
      qDebug() << folderNames;
  }
  m_le_projectDirectory->setText(folderNames.first());
}


GlslFilesPage::GlslFilesPage(QWidget *parent)
  : QWizardPage(parent)
{
  setTitle(tr("Shaders & GLSL Files"));
  setSubTitle(tr("Specify the name of the Vertex and Fragment shaders as well "
                 "what GLSL files will be linked."));

  m_l_vertexName = new QLabel(tr("Vertex Name:"));
  m_le_vertexName = new QLineEdit();
  m_l_vertexName->setBuddy(m_le_vertexName);

  m_l_fragmentName = new QLabel(tr("Fragment Name:"));
  m_le_fragmentName = new QLineEdit();
  m_l_fragmentName->setBuddy(m_le_fragmentName);

  QString shadersPath = QDir::currentPath() + "/shaders/files";

  m_fileModel = new QFileSystemModel;
  m_fileModel->setRootPath(shadersPath);

  m_tv_selectFiles = new QTreeView;
  m_tv_selectFiles->setModel(m_fileModel);
  m_tv_selectFiles->setRootIndex(m_fileModel->index(shadersPath));
  m_tv_selectFiles->setSelectionMode(QAbstractItemView::MultiSelection);
  m_tv_selectFiles->setColumnHidden(1,true);
  m_tv_selectFiles->setColumnHidden(2,true);
  m_tv_selectFiles->setColumnHidden(3,true);

  //connect(m_tv_selectFiles, SIGNAL)

  registerField("vertexFileName*", m_le_vertexName);
  registerField("fragmentFileName*", m_le_fragmentName);

  m_gb_glslFiles = new QGroupBox(tr("Select GLSL Files"));
  m_gb_glslFiles->setMinimumHeight(300);
  QVBoxLayout *groupBoxLayout = new QVBoxLayout;
  groupBoxLayout->addWidget(m_tv_selectFiles);

  m_gb_glslFiles->setLayout(groupBoxLayout);

  QGridLayout *layout = new QGridLayout;
  layout->addWidget(m_l_vertexName, 0, 0);
  layout->addWidget(m_le_vertexName, 0, 1);
  layout->addWidget(m_l_fragmentName, 1, 0);
  layout->addWidget(m_le_fragmentName, 1, 1);
  layout->addWidget(m_gb_glslFiles, 2, 0, 1, 2);
  setLayout(layout);
}

void GlslFilesPage::initializePage()
{
  QString projectName = field("projectName").toString();
  m_le_vertexName->setText(projectName + "Vertex.glsl");
  m_le_fragmentName->setText(projectName + "Fragment.glsl");
}

ConclusionPage::ConclusionPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Conclusion"));

    label = new QLabel;
    label->setWordWrap(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    setLayout(layout);
}

void ConclusionPage::initializePage()
{
    QString finishText = wizard()->buttonText(QWizard::FinishButton);
    finishText.remove('&');
    label->setText(tr("Click %1 to generate the class skeleton.")
                   .arg(finishText));
}
