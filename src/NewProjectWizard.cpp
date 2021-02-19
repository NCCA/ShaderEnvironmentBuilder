//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
// System includes
#include <algorithm>

// Engine includes

// Library  includes
#include <QFileDialog>
#include <QModelIndex>
#include <QFileSystemModel>
#include <QItemSelectionModel>
#include <QListWidget>
#include <QTextStream>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QTreeView>
#include <QGroupBox>
#include <QDebug>

// Project includes
#include "CebErrors.h"
#include "NewProjectWizard.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
NewProjectWizard::NewProjectWizard(QWidget *parent): QWizard(parent)
{
  // Setup file model
  m_fileModel = new QFileSystemModel;
  m_fileModel->setRootPath(QDir::currentPath() + "/shaders/files");
  m_fileModel->removeColumns(1,3);
  // Create the structr for storing output data
  m_output = new OutputData;

  // Add the pages to the wizard
  addPage(new IntroPage(this));
  addPage(new ProjectInfoPage(this));
  addPage(new GlslFilesPage(this));
  addPage(new GlslOrderPage(this));
  addPage(new ConclusionPage(this));

  setWindowTitle(tr("New Project Wizard"));

}

//------------------------------------------------------------------------------
void NewProjectWizard::accept()
{
  // get project name and directory
  m_output->m_projectName = field("projectName").toString().toStdString();
  m_output->m_projectDir = field("projectDirectory").toString().toStdString();

  // create glsl version string
  QString ver = QString("#version %1 %2\n\n")
                .arg(field("glslVersion").toString(),
                     field("glslProfile").toString());

  // get the selected rows from the vertex and fragment selection models used
  // with the treeviews
  QModelIndexList vertFiles = m_vertexSelectModel->selectedRows();
  QModelIndexList fragFiles = m_fragmentSelectModel->selectedRows();

  // Get the glsl order page
  GlslOrderPage* glslOrderPg = static_cast<GlslOrderPage*>(page(3));

  // Setup variables for getting the correct order of the files
  // ordered filenames (from the qlistwidgets)
  QStringList vertexOrderFileNames, fragmentOrderFileNames;
  // unordered filenames (from the qtreeviews)
  QStringList vertFileNames, fragFileNames;

  // get the list of ordered files from the list widgets
  const QListWidget* vertFilesOrder = glslOrderPg->getVertListWidget();
  const QListWidget* fragFilesOrder = glslOrderPg->getFragListWidget();

  // create the unordered and ordered file name lists for vertex
  for (int i=0; i<vertFilesOrder->count(); ++i)
  {
    vertFileNames.append(m_fileModel->fileInfo(vertFiles.at(i)).fileName());
    vertexOrderFileNames.append(vertFilesOrder->item(i)->text());
  }

  // create the unordered and ordered file name lists for fragment
  for (int i=0; i<fragFilesOrder->count(); ++i)
  {
    fragFileNames.append(m_fileModel->fileInfo(fragFiles.at(i)).fileName());
    fragmentOrderFileNames.append(fragFilesOrder->item(i)->text());
  }

  // the final vertex and fragment strings
  QString vertexFilesString, fragmentFilesString;

  // Now find the correct index from the ordered list using the ordered and
  // un-ordered file name lists and get the file value from the file model
  for (int i=0; i<vertFileNames.length(); ++i)
  {
    // getting the correct index from the ordered file list
    int index = vertFileNames.indexOf(vertexOrderFileNames[i]);
    // get the file at the correct index from the selected rows in the QTreeView
    QFile vFile(m_fileModel->fileInfo(vertFiles.at(index)).absoluteFilePath());
    // open the file
    if (!vFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      // Raise an error if failed
      CEBRaise::QtFileError(vFile.error(),
                            m_fileModel->fileInfo(vertFiles.at(index))
                                                           .absoluteFilePath());
    }
    // append the file to a single string
    QTextStream in(&vFile);
    vertexFilesString.append(in.readAll());
    vertexFilesString.append("\n");
  }

  // REPEAT above again
  // Now find the correct index from the ordered list using the ordered and
  // un-ordered file name lists and get the file value from the file model
  for (int i=0; i<fragFileNames.length(); ++i)
  {
    // getting the correct index from the ordered file list
    int index = fragFileNames.indexOf(fragmentOrderFileNames[i]);
    // get the file at the correct index from the selected rows in the QTreeView
    QFile fFile(m_fileModel->fileInfo(fragFiles.at(index)).absoluteFilePath());
    // open the file
    if (!fFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      // Raise an error if failed
      CEBRaise::QtFileError(fFile.error(),
                            m_fileModel->fileInfo(fragFiles.at(index))
                                                           .absoluteFilePath());
    }
    // append the file to a single string
    QTextStream in(&fFile);
    fragmentFilesString.append(in.readAll());
    fragmentFilesString.append("\n");
  }

  // check if each of the file strings already contains a version. If it doesn't
  // then push to front
  if(!vertexFilesString.contains("#version"))
  {
    vertexFilesString.push_front(ver+"\n");
  }
  // same as above
  if(!fragmentFilesString.contains("#version"))
  {
    fragmentFilesString.push_front(ver+"\n");
  }
  // store in output
  m_output->m_vertSource = vertexFilesString;
  m_output->m_fragSource = fragmentFilesString;

  // accept the dialog
  QDialog::accept();
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
IntroPage::IntroPage(QWidget *parent)
  : QWizardPage(parent)
{
  setTitle(tr("Introduction"));

  m_label = new QLabel(tr("This wizard will generate a CEB project "
                          "definition. You simply "
                          "need to specify the project name and set a few "
                          "options to produce a json project file "
                          "implementation for your new OpenGL shader."));
  m_label->setWordWrap(true);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(m_label);
  setLayout(layout);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
ProjectInfoPage::ProjectInfoPage(QWidget *parent)
  : QWizardPage(parent)
{
  setTitle(tr("Project Information"));
  setSubTitle(tr("Specify basic information about the project for which you "
                 "want to generate."));
  // project name
  m_l_projectName = new QLabel(tr("Project name:"));
  m_le_projectName = new QLineEdit();
  m_l_projectName->setBuddy(m_le_projectName);

  m_l_projectDirectory = new QLabel(tr("Project Directory:"));
  m_b_browseDirectory = new QPushButton(tr("Browse..."));
  m_le_projectDirectory = new QLineEdit();
  m_l_projectDirectory->setBuddy(m_le_projectDirectory);

  // create a sperator
  QFrame *line = new QFrame();
  line->setObjectName(QString::fromUtf8("line"));
  line->setFrameShape(QFrame::HLine);
  line->setFrameShadow(QFrame::Sunken);

  m_l_glslVersion = new QLabel(tr("GLSL Version:"));
  m_cb_glslVersion = new QComboBox();
  QStringList glslVer = {"110", "120", "130", "140", "150", "330", "400",
                         "410", "420", "430", "430", "440", "450"};
  std::reverse(glslVer.begin(), glslVer.end());
  m_cb_glslVersion->addItems(glslVer);
  m_cb_glslVersion->setEditable(true);
  m_cb_glslVersion->setInsertPolicy(QComboBox::InsertAtTop);

  m_l_glslProfile = new QLabel(tr("GLSL Profile:"));
  m_cb_glslProfile = new QComboBox();
  m_cb_glslProfile->addItems({"core", "compatibility"});

  // register the fields so that the wizard can read the values at the end
  registerField("projectName*", m_le_projectName);
  registerField("projectDirectory*", m_le_projectDirectory);
  registerField("glslVersion", m_cb_glslVersion, "currentText",
                "currentIndexChanged");
  registerField("glslProfile", m_cb_glslProfile,"currentText",
                "currentIndexChanged");

  // add all the widgets to the layout
  QGridLayout *layout = new QGridLayout;
  layout->addWidget(m_l_projectName, 0, 0);
  layout->addWidget(m_le_projectName, 0, 1, 1, 2);
  layout->addWidget(m_l_projectDirectory, 1, 0);
  layout->addWidget(m_le_projectDirectory, 1, 1);
  layout->addWidget(m_b_browseDirectory, 1, 2);
  layout->addWidget(line, 2,0,1,3);
  layout->addWidget(m_l_glslVersion, 3,0);
  layout->addWidget(m_cb_glslVersion, 3,1,1,2);
  layout->addWidget(m_l_glslProfile, 4,0);
  layout->addWidget(m_cb_glslProfile, 4,1,1,2);
  setLayout(layout);

  // connect the browse button to open file dialog
  connect(m_b_browseDirectory, SIGNAL (clicked()),this,
          SLOT(setProjectDirectory()));
}

//------------------------------------------------------------------------------
void ProjectInfoPage::initializePage()
{
  m_le_projectName->setText("Phong");
  m_le_projectDirectory->setText(QDir::homePath());

  // get the shader version and set the combobox to the highest compatible
  const unsigned char* glv = glGetString(GL_SHADING_LANGUAGE_VERSION);
  QString glVerStrConvert = QString((const char* ) glv);
  QString glVerStr = glVerStrConvert.left(1) + glVerStrConvert.mid(2,2);

  m_cb_glslVersion->setCurrentText(glVerStr);
  m_cb_glslProfile->setCurrentIndex(0);
}

//------------------------------------------------------------------------------
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

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
GlslFilesPage::GlslFilesPage(QWidget *parent)
  : QWizardPage(parent)
{
  m_wizard = static_cast<NewProjectWizard*>(parent);
  QString shadersPath = QDir::currentPath() + "/shaders/files";
  setTitle(tr("Shaders & GLSL Files"));
  setSubTitle(tr("Specify the name of the Vertex and Fragment shaders as well "
                 "what GLSL files will be linked."));

  m_l_vertexName = new QLabel(tr("Vertex Name:"));
  m_le_vertexName = new QLineEdit();
  m_l_vertexName->setBuddy(m_le_vertexName);

  m_l_fragmentName = new QLabel(tr("Fragment Name:"));
  m_le_fragmentName = new QLineEdit();
  m_l_fragmentName->setBuddy(m_le_fragmentName);

  m_l_vertexSelectFiles = new QLabel(tr("Vertex Files:"));
  m_l_fragmentSelectFiles = new QLabel(tr("Fragment Files:"));

  /// @todo Make the two tree views into a single function since a lot of values
  /// are set the same. Just done this for the time being for speed.
  m_tv_vertexSelectFiles = new QTreeView;
  m_tv_fragmentSelectFiles = new QTreeView;

  std::vector<QTreeView*> tViews = {m_tv_vertexSelectFiles,
                                    m_tv_fragmentSelectFiles};

  for (auto tv: tViews)
  {
    tv->setModel(m_wizard->m_fileModel);
    // set directory to show
    tv->setRootIndex(m_wizard->m_fileModel->index(shadersPath));
    tv->setSelectionMode(QAbstractItemView::MultiSelection);
    // show only file name
    tv->setColumnHidden(1,true);
    tv->setColumnHidden(2,true);
    tv->setColumnHidden(3,true);
  }

  // store the selection models
  m_wizard->m_vertexSelectModel = m_tv_vertexSelectFiles->selectionModel();
  m_wizard->m_fragmentSelectModel = m_tv_fragmentSelectFiles->selectionModel();

  // setup selection connections for de-selecting folders
  connect(m_wizard->m_vertexSelectModel,
          SIGNAL(selectionChanged(const QItemSelection&,
                                  const QItemSelection&)),
          this,
          SLOT(vertexSelectChanged(const QItemSelection&,
                                   const QItemSelection&)));
  connect(m_wizard->m_fragmentSelectModel,
          SIGNAL(selectionChanged(const QItemSelection&,
                                  const QItemSelection&)),
          this,
          SLOT(fragmentSelectChanged(const QItemSelection&,
                                     const QItemSelection&)));

  // register fileds for wizard
  registerField("vertexFileName*", m_le_vertexName);
  registerField("fragmentFileName*", m_le_fragmentName);

  //layouts
  m_gb_glslFiles = new QGroupBox(tr("Select GLSL Files"));
  m_gb_glslFiles->setMinimumHeight(300);
  QGridLayout *groupBoxLayout = new QGridLayout;
  groupBoxLayout->addWidget(m_l_vertexSelectFiles, 0, 0);
  groupBoxLayout->addWidget(m_l_fragmentSelectFiles, 0, 1);
  groupBoxLayout->addWidget(m_tv_vertexSelectFiles, 1, 0);
  groupBoxLayout->addWidget(m_tv_fragmentSelectFiles, 1, 1);

  m_gb_glslFiles->setLayout(groupBoxLayout);

  QGridLayout *layout = new QGridLayout;
  layout->addWidget(m_l_vertexName, 0, 0);
  layout->addWidget(m_le_vertexName, 0, 1);
  layout->addWidget(m_l_fragmentName, 1, 0);
  layout->addWidget(m_le_fragmentName, 1, 1);
  layout->addWidget(m_gb_glslFiles, 2, 0, 1, 2);
  setLayout(layout);
}

//------------------------------------------------------------------------------
void GlslFilesPage::initializePage()
{
  QString projectName = field("projectName").toString();
  m_le_vertexName->setText(projectName + "Vertex");
  m_le_fragmentName->setText(projectName + "Fragment");
}

//------------------------------------------------------------------------------
void GlslFilesPage::vertexSelectChanged(const QItemSelection &_selected,
                                        const QItemSelection &_deselected)
{
  deselectDir(_selected, m_wizard->m_vertexSelectModel);
}

//------------------------------------------------------------------------------
void GlslFilesPage::fragmentSelectChanged(const QItemSelection &_selected,
                                          const QItemSelection &_deselected)
{
  deselectDir(_selected, m_wizard->m_fragmentSelectModel);
}

//------------------------------------------------------------------------------
void GlslFilesPage::deselectDir(const QItemSelection &_selected,
                                QItemSelectionModel *_selectModel)
{
  QModelIndexList items = _selected.indexes();
  for (auto index: items)
  {
    // check if the selected item is a folder, if it is deselect it
    // we only want files
    QFileInfo info = m_wizard->m_fileModel->fileInfo(index);
    if (info.isDir())
    {
      _selectModel->select(index, QItemSelectionModel::Deselect);
    }
  }
}

//------------------------------------------------------------------------------
GlslOrderPage::GlslOrderPage(QWidget *parent)
  : QWizardPage(parent)
{
  m_wizard = static_cast<NewProjectWizard*>(parent);
  setTitle(tr("GLSL File Order"));
  setSubTitle(tr("Specify the order in which the GLSL files will be loaded "
                 "into the shader program."));

  m_l_vertexOrder = new QLabel(tr("Vertex File Order:"));
  m_l_fragmentOrder = new QLabel(tr("Fragment File Order:"));

  // create list widgets and allow dragging and dropping
  m_ls_vertFilesOrder = new QListWidget();
  m_ls_vertFilesOrder->setDragDropMode(QAbstractItemView::InternalMove);
  m_ls_fragFilesOrder = new QListWidget();
  m_ls_fragFilesOrder->setDragDropMode(QAbstractItemView::InternalMove);

  QGridLayout *layout = new QGridLayout();
  layout->addWidget(m_l_vertexOrder, 0,0);
  layout->addWidget(m_l_fragmentOrder, 0,1);
  layout->addWidget(m_ls_vertFilesOrder, 1,0);
  layout->addWidget(m_ls_fragFilesOrder, 1,1);
  setLayout(layout);
}

//------------------------------------------------------------------------------
void GlslOrderPage::initializePage()
{
  m_ls_vertFilesOrder->clear();
  m_ls_fragFilesOrder->clear();

  // fill the list widgets with the selected items from the previous pages
  // QTreeViews
  QModelIndexList indexes = m_wizard->m_vertexSelectModel->selectedRows();
  QStringList vertexNames, fragmentNames;
  for (auto i: indexes)
  {
    vertexNames.append(m_wizard->m_fileModel->fileInfo(i).fileName());
  }
  m_ls_vertFilesOrder->addItems(vertexNames);

  // fill the list widgets with the selected items from the previous pages
  // QTreeViews
  indexes = m_wizard->m_fragmentSelectModel->selectedRows();
  for (auto i: indexes)
  {
    fragmentNames.append(m_wizard->m_fileModel->fileInfo(i).fileName());
  }
  m_ls_fragFilesOrder->addItems(fragmentNames);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
ConclusionPage::ConclusionPage(QWidget *parent)
  : QWizardPage(parent)
{
  setTitle(tr("Conclusion"));

  m_label = new QLabel;
  m_label->setWordWrap(true);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(m_label);
  setLayout(layout);
}

//------------------------------------------------------------------------------
void ConclusionPage::initializePage()
{
  QString finishText = wizard()->buttonText(QWizard::FinishButton);
  finishText.remove('&');
  m_label->setText(tr("Click %1 to generate the project.")
                   .arg(finishText));
}
