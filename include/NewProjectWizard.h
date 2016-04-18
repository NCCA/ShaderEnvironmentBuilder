#ifndef NEWPROJECTWIZARD_H
#define NEWPROJECTWIZARD_H

#include <QWizard>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QRadioButton;
class QPushButton;
class QTreeView;
class QFileSystemModel;
QT_END_NAMESPACE


class NewProjectWizard : public QWizard
{
  Q_OBJECT
public:
  NewProjectWizard(QWidget *parent = 0);
  void accept() Q_DECL_OVERRIDE;

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
private slots:
  void setProjectDirectory();
};

class GlslFilesPage : public QWizardPage
{
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
  QTreeView *m_tv_selectFiles;
  QFileSystemModel *m_fileModel;

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
