#ifndef NEWPROJECTWIZARD_H
#define NEWPROJECTWIZARD_H

#include <QWizard>


enum GLSL_PROFILE {CORE, COMPATIBILITY};
extern QStringList GLSL_PROFILE_OUTPUT_TEXT;

QT_BEGIN_NAMESPACE
class QCheckBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QRadioButton;
class QPushButton;
class QTreeView;
class QFileSystemModel;
class QItemSelectionModel;
class QItemSelection;
class QComboBox;
class QListWidget;
class QDir;
QT_END_NAMESPACE

struct outputData
{
  std::string m_projectName;
  std::string m_projectDir;
  QString m_vertSource;
  QString m_fragSource;
};

class NewProjectWizard : public QWizard
{
  Q_OBJECT
public:
  NewProjectWizard(QWidget *parent = 0);
  void accept() Q_DECL_OVERRIDE;

  QItemSelectionModel *m_vertexSelectModel;
  QItemSelectionModel *m_fragmentSelectModel;
  QFileSystemModel *m_fileModel;
  outputData *m_output;
};

class IntroPage : public QWizardPage
{
  Q_OBJECT
public:
  IntroPage(QWidget *parent = 0);
private:
  QLabel *label;
};

class ProjectInfoPage : public QWizardPage
{
  Q_OBJECT
public:
  ProjectInfoPage(QWidget *parent = 0);
protected:
  void initializePage() Q_DECL_OVERRIDE;
private:
  QLabel *m_l_projectName;
  QLabel *m_l_projectDirectory;
  QLineEdit *m_le_projectName;
  QPushButton *m_b_browseDirectory;
  QLineEdit *m_le_projectDirectory;
  QLabel *m_l_glslVersion;
  QLabel *m_l_glslProfile;
  QComboBox *m_cb_glslVersion;
  QComboBox *m_cb_glslProfile;

private slots:
  void setProjectDirectory();
};


class GlslFilesPage : public QWizardPage
{
  /// @todo Make an inherited QWizardPage class that takes the parent (being qWizard)
  /// and storing it as a member. Currenlty just repeating this for GlslFilesPage and
  /// GlslOrderPage
  Q_OBJECT
public:
  GlslFilesPage(QWidget *parent = 0);
protected:
  void initializePage() Q_DECL_OVERRIDE;
private:
  QLabel *m_l_vertexName;
  QLabel *m_l_fragmentName;
  QLineEdit *m_le_vertexName;
  QLineEdit *m_le_fragmentName;
  QGroupBox *m_gb_glslFiles;
  QTreeView *m_tv_vertexSelectFiles;
  QLabel *m_l_vertexSelectFiles;
  QLabel *m_l_fragmentSelectFiles;
  QTreeView *m_tv_fragmentSelectFiles;
  NewProjectWizard *m_wizard;

  void deselectDirs(const QItemSelection &_selected, QItemSelectionModel *_selectModel);

private slots:
  void vertexSelectionChanged(const QItemSelection &_selected,
                              const QItemSelection &_deselected);
  void fragmentSelectionChanged(const QItemSelection &_selected,
                                const QItemSelection &_deselected);
};

class GlslOrderPage : public QWizardPage
{
  /// @todo Make an inherited QWizardPage class that takes the parent (being qWizard)
  /// and storing it as a member. Currenlty just repeating this for GlslFilesPage and
  /// GlslOrderPage
  Q_OBJECT
public:
  GlslOrderPage(QWidget *parent = 0);
  QListWidget *m_ls_vertexFilesOrder;
  QListWidget *m_ls_fragmentFilesOrder;
protected:
  void initializePage() Q_DECL_OVERRIDE;
private:
  QLabel *m_l_vertexOrder;
  QLabel *m_l_fragmentOrder;
  NewProjectWizard *m_wizard;
private slots:
};

class ConclusionPage : public QWizardPage
{
  Q_OBJECT
public:
  ConclusionPage(QWidget *parent = 0);
protected:
  void initializePage() Q_DECL_OVERRIDE;
private:
  QLabel *label;
};

#endif // NEWPROJECTWIZARD_H
