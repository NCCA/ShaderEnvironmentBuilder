//------------------------------------------------------------------------------
/// @file NewProjectWizard
/// @brief The new Project Wizard that is used to create a new project.
/// @author Jonathan Flynn
/// @version 1.0
/// @date 18/04/16
//------------------------------------------------------------------------------
#ifndef _NEWPROJECTWIZARD_H_
#define _NEWPROJECTWIZARD_H_
//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
// System includes

// Engine includes

// Library  includes
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
class QItemSelectionModel;
class QItemSelection;
class QComboBox;
class QListWidget;
class QDir;
QT_END_NAMESPACE

// Project includes

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/// @brief The Project wizards output data stored in a struct.
/// @note Is global and not in class since it is used when getting the data when
/// the wizard is completed from MainWindow
//------------------------------------------------------------------------------
struct OutputData
{
  std::string m_projectName; ///< The projects name
  std::string m_projectDir;  ///< The projects directory
  QString     m_vertSource;  ///< The GLSL vertex source string
  QString     m_fragSource;  ///< The GLSL fragment source string
};
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
/// @class NewProjectWizard
/// @brief The main Wizard that contains all the pages for the new project.
//------------------------------------------------------------------------------
class NewProjectWizard : public QWizard
{
  Q_OBJECT // must include this if you use Qt signals/slots
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
public:
  //----------------------------------------------------------------------------
  /// @brief The vertex selection model for the vertex treeview.
  //----------------------------------------------------------------------------
  QItemSelectionModel *m_vertexSelectModel;
  //----------------------------------------------------------------------------
  /// @brief The fragment selection model for the fragment treeview.
  //----------------------------------------------------------------------------
  QItemSelectionModel *m_fragmentSelectModel;
  //----------------------------------------------------------------------------
  /// @brief The file model used for both of the vertex and fragment treeviews.
  //----------------------------------------------------------------------------
  QFileSystemModel    *m_fileModel;
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  /// @brief Constructor, passing a child of parent.
  /// @param[in] parent The parent for which this will be the child of.
  //----------------------------------------------------------------------------
  NewProjectWizard    (QWidget *parent = 0);
  //----------------------------------------------------------------------------
  /// @brief This is run when the dialog has been accepted.
  //----------------------------------------------------------------------------
  void                accept() Q_DECL_OVERRIDE;
  //----------------------------------------------------------------------------
  /// @brief Gets the output of the wizard when it has been completed
  /// @returns the output
  //----------------------------------------------------------------------------
  const OutputData*   getOutput() const {return m_output;}
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
private:
  //----------------------------------------------------------------------------
  /// @brief The output data stored on completion of the wizard
  //----------------------------------------------------------------------------
  OutputData*         m_output;
};


//------------------------------------------------------------------------------
/// @class IntroPage
/// @brief The intro wizard page. Only contains just an into label.
//------------------------------------------------------------------------------
class IntroPage : public QWizardPage
{
  Q_OBJECT // must include this if you use Qt signals/slots
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
public:
  //----------------------------------------------------------------------------
  /// @brief Constructor, passing a child of parent.
  /// @param[in] parent The parent for which this will be the child of.
  //----------------------------------------------------------------------------
  IntroPage (QWidget *parent = 0);
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
private:
  //----------------------------------------------------------------------------
  /// @brief The text label for the intro.
  //----------------------------------------------------------------------------
  QLabel* m_label;
};


//------------------------------------------------------------------------------
/// @class ProjectInfoPage
/// @brief The project wizard page with info on the project name, version,
/// directory etc.
//------------------------------------------------------------------------------
class ProjectInfoPage : public QWizardPage
{
  Q_OBJECT // must include this if you use Qt signals/slots
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
public:
  //----------------------------------------------------------------------------
  /// @brief Constructor, passing a child of parent.
  /// @param[in] parent The parent for which this will be the child of.
  //----------------------------------------------------------------------------
  ProjectInfoPage (QWidget *parent = 0);
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
private:
  //----------------------------------------------------------------------------
  /// @brief Glsl file version combo box
  //----------------------------------------------------------------------------
  QComboBox*      m_cb_glslVersion;
  //----------------------------------------------------------------------------
  /// @brief Glsl profile version combo box
  //----------------------------------------------------------------------------
  QComboBox*      m_cb_glslProfile;
  //----------------------------------------------------------------------------
  /// @brief Project name label
  //----------------------------------------------------------------------------
  QLabel*         m_l_projectName;
  //----------------------------------------------------------------------------
  /// @brief Project directory label
  //----------------------------------------------------------------------------
  QLabel*         m_l_projectDirectory;
  //----------------------------------------------------------------------------
  /// @brief Glsl version label
  //----------------------------------------------------------------------------
  QLabel*         m_l_glslVersion;
  //----------------------------------------------------------------------------
  /// @brief Glsl profile label
  //----------------------------------------------------------------------------
  QLabel*         m_l_glslProfile;
  //----------------------------------------------------------------------------
  /// @brief Project directory entry box
  //----------------------------------------------------------------------------
  QLineEdit*      m_le_projectDirectory;
  //----------------------------------------------------------------------------
  /// @brief Project name entry box
  //----------------------------------------------------------------------------
  QLineEdit*      m_le_projectName;
  //----------------------------------------------------------------------------
  /// @brief Browse directory button which opens a file dialog
  //----------------------------------------------------------------------------
  QPushButton*    m_b_browseDirectory;
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
protected:
  //----------------------------------------------------------------------------
  /// @brief Used to prepare the Wizard page before it is shown and set default
  /// values
  //----------------------------------------------------------------------------
  void            initializePage() Q_DECL_OVERRIDE;
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
private slots:
  //----------------------------------------------------------------------------
  /// @brief Used to fill the project directory line edit by opening a file
  /// dialog
  //----------------------------------------------------------------------------
  void            setProjectDirectory();
};


//------------------------------------------------------------------------------
/// @class GlslFilesPage
/// @brief The project wizard page for selecting glsl files in
/// @todo Make an inherited QWizardPage class that takes the parent (being
/// qWizard) and storing it as a member. Currenlty just repeating this for
/// GlslFilesPage and GlslOrderPage
//------------------------------------------------------------------------------
class GlslFilesPage : public QWizardPage
{
  Q_OBJECT
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
public:
  //----------------------------------------------------------------------------
  /// @brief Constructor, passing a child of parent.
  /// @param[in] parent The parent for which this will be the child of.
  //----------------------------------------------------------------------------
  GlslFilesPage     (QWidget *parent = 0);
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
private:
  //----------------------------------------------------------------------------
  /// @brief The new project wizard that this page is a part of (the parent)
  //----------------------------------------------------------------------------
  NewProjectWizard* m_wizard;
  //----------------------------------------------------------------------------
  /// @brief Group box for the glsl files
  //----------------------------------------------------------------------------
  QGroupBox*        m_gb_glslFiles;
  //----------------------------------------------------------------------------
  /// @brief Label for the fragment name
  //----------------------------------------------------------------------------
  QLabel*           m_l_fragmentName;
  //----------------------------------------------------------------------------
  /// @brief Label for the vertex name
  //----------------------------------------------------------------------------
  QLabel*           m_l_vertexName;
  //----------------------------------------------------------------------------
  /// @brief Line edit for the fragment name
  //----------------------------------------------------------------------------
  QLineEdit*        m_le_fragmentName;
  //----------------------------------------------------------------------------
  /// @brief Line edit for the vertex name
  //----------------------------------------------------------------------------
  QLineEdit*        m_le_vertexName;
  //----------------------------------------------------------------------------
  /// @brief Label for the fragment select files
  //----------------------------------------------------------------------------
  QLabel*           m_l_fragmentSelectFiles;
  //----------------------------------------------------------------------------
  /// @brief Label fro the vertex select files
  //----------------------------------------------------------------------------
  QLabel*           m_l_vertexSelectFiles;
  //----------------------------------------------------------------------------
  /// @brief Treeview for selecting fragment files
  //----------------------------------------------------------------------------
  QTreeView*        m_tv_fragmentSelectFiles;
  //----------------------------------------------------------------------------
  /// @brief Treeview for selecting vertex files
  //----------------------------------------------------------------------------
  QTreeView*        m_tv_vertexSelectFiles;
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  /// @brief Deselects selected directories so only files can be selected in the
  /// treeviews
  /// @param[in] _selected The items selected in the treeview
  /// @param[in] _selectModel The selection model used with the selections
  /// treeview
  //----------------------------------------------------------------------------
  void              deselectDir(const QItemSelection &_selected,
                                QItemSelectionModel *_selectModel);
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
protected:
  //----------------------------------------------------------------------------
  /// @brief Used to prepare the Wizard page before it is shown and set default
  /// values
  //----------------------------------------------------------------------------
  void              initializePage() Q_DECL_OVERRIDE;
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
private slots:
  //----------------------------------------------------------------------------
  /// @brief Activated when an object in the Vertex Treeview is changed
  /// @param[in] _selected the objects that have been selected in the treeview
  /// @param[in] _deselected the objects that have been deselected in the
  /// treeview
  //----------------------------------------------------------------------------
  void              vSelectChanged(const QItemSelection &_selected,
                                        const QItemSelection &_deselected);
  //----------------------------------------------------------------------------
  /// @brief Activated when an object in the Fragment Treeview is changed
  /// @param[in] _selected the objects that have been selected in the treeview
  /// @param[in] _deselected the objects that have been deselected in the
  /// treeview
  //----------------------------------------------------------------------------
  void              fSelectChanged(const QItemSelection &_selected,
                                          const QItemSelection &_deselected);
};

//------------------------------------------------------------------------------
/// @class GlslOrderPage
/// @brief The project wizard page for selecting glsl files in
//------------------------------------------------------------------------------
class GlslOrderPage : public QWizardPage
{
  Q_OBJECT
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
public:
  //----------------------------------------------------------------------------
  /// @brief Constructor, passing a child of parent.
  /// @param[in] parent The parent for which this will be the child of.
  //----------------------------------------------------------------------------
  GlslOrderPage       (QWidget *parent = 0);
  //----------------------------------------------------------------------------
  /// @brief Gets the vert list widget
  /// @returns the vert list widget from the page
  //----------------------------------------------------------------------------
  const QListWidget*  getVertListWidget() const {return m_ls_vertFilesOrder;}
  //----------------------------------------------------------------------------
  /// @brief Gets the frag list widget
  /// @returns the frag list widget from the page
  //----------------------------------------------------------------------------
  const QListWidget*  getFragListWidget() const {return m_ls_fragFilesOrder;}
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
protected:
  //----------------------------------------------------------------------------
  /// @brief Used to prepare the Wizard page before it is shown and set default
  /// values
  //----------------------------------------------------------------------------
  void                initializePage() Q_DECL_OVERRIDE;
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
private:
  //----------------------------------------------------------------------------
  /// @brief The new project wizard that this page is a part of (the parent)
  //----------------------------------------------------------------------------
  NewProjectWizard*   m_wizard;
  //----------------------------------------------------------------------------
  /// @brief Label showing vertex order
  //----------------------------------------------------------------------------
  QLabel*             m_l_vertexOrder;
  //----------------------------------------------------------------------------
  /// @brief Label showing fragment order
  //----------------------------------------------------------------------------
  QLabel*             m_l_fragmentOrder;
  //----------------------------------------------------------------------------
  /// @brief List widget for re-ordering vertex files
  //----------------------------------------------------------------------------
  QListWidget*        m_ls_vertFilesOrder;
  //----------------------------------------------------------------------------
  /// @brief List widget for re-ordering fragment files
  //----------------------------------------------------------------------------
  QListWidget*        m_ls_fragFilesOrder;
  //----------------------------------------------------------------------------
};


//------------------------------------------------------------------------------
/// @class ProjectInfoPage
/// @brief The project wizard page with info on the project name, version,
/// directory etc.
//------------------------------------------------------------------------------
class ConclusionPage : public QWizardPage
{
  Q_OBJECT
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
public:
  //----------------------------------------------------------------------------
  /// @brief Constructor, passing a child of parent.
  /// @param[in] parent The parent for which this will be the child of.
  //----------------------------------------------------------------------------
  ConclusionPage  (QWidget *parent = 0);
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
protected:
  //----------------------------------------------------------------------------
  /// @brief Used to prepare the Wizard page before it is shown and set default
  /// values
  //----------------------------------------------------------------------------
  void            initializePage() Q_DECL_OVERRIDE;
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
private:
  //----------------------------------------------------------------------------
  /// @brief The text label for the intro.
  //----------------------------------------------------------------------------
  QLabel*         m_label;
};

#endif // _NEWPROJECTWIZARD_H_
