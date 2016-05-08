#ifndef _CEBITOR_H__
#define _CEBITOR_H__

#include <QLineEdit>
#include <Qsci/qsciscintilla.h>

#include "QsciLexerGlsl.h"


//------------------------------------------------------------------------------
/// @file Cebitor.h
/// @brief CEB text editor, implementation of QScintilla
/// @author Phil Rouse
/// @version 1.0.1
/// @date 03/03/16
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @class Cebitor
/// @brief CEB text editor class inherits from QsciScintilla
//------------------------------------------------------------------------------
class Cebitor : public QsciScintilla
{
  Q_OBJECT;

public:
  //----------------------------------------------------------------------------
  /// @brief Enum for supported marker types
  //----------------------------------------------------------------------------
  enum MarkerType
  {
    ERROR,    ///< Symbol marker for Errors
    WARNING,  ///< Symbol marker for warnings
  };
  //----------------------------------------------------------------------------
  /// @brief Cebitor constructor, initialises default values
  //----------------------------------------------------------------------------
  Cebitor( QWidget *_parent );
  //----------------------------------------------------------------------------
  /// @brief stores widget containing the searchbar
  //----------------------------------------------------------------------------
  inline void setSearchWidget( QWidget *_searchWidget )
                              {
                                m_searchWidget = _searchWidget;
                              }
  //----------------------------------------------------------------------------
  /// @brief stores QLineEdit widget from the searchbar
  //----------------------------------------------------------------------------
  inline void setSearchLineEdit( QLineEdit *_searchLineEdit )
                                {
                                  m_searchLineEdit = _searchLineEdit;
                                }
  //----------------------------------------------------------------------------

public slots:
  //----------------------------------------------------------------------------
  /// @brief Removes all error and warning line markers
  //----------------------------------------------------------------------------
  void clearErrors();
  //----------------------------------------------------------------------------
  /// @brief Search for next occurance
  //----------------------------------------------------------------------------
  void searchNext();
  //----------------------------------------------------------------------------
  /// @brief Search for previous occurance
  //----------------------------------------------------------------------------
  void searchPrev();
  //----------------------------------------------------------------------------
  /// @brief sets indicator for each search result
  //----------------------------------------------------------------------------
  void highlightAllSearch();
  //----------------------------------------------------------------------------
  /// @brief sets indicator for each search result
  /// @param[in] _text the text that has been changed
  //----------------------------------------------------------------------------
  void highlightAllSearch(const QString& _text);
  //----------------------------------------------------------------------------
protected:
  //----------------------------------------------------------------------------
  /// @brief widget containing the searchbar
  //----------------------------------------------------------------------------
  QWidget          *m_searchWidget;
  //----------------------------------------------------------------------------
  /// @brief searchbar QLineEdit widget
  //----------------------------------------------------------------------------
  QLineEdit        *m_searchLineEdit;
  //----------------------------------------------------------------------------
  /// @brief vector of all line markers
  //----------------------------------------------------------------------------
  std::vector<int>  m_fileMarkers;
  //----------------------------------------------------------------------------
  /// @brief indicator used to highlight all search terms
  //----------------------------------------------------------------------------
  int               m_searchIndicator;
  //----------------------------------------------------------------------------

  //----------------------------------------------------------------------------
  /// @brief adds closing character for braces and quotes
  /// @param [in] _close closing character
  /// @returns true if closing character is added
  //----------------------------------------------------------------------------
  bool autoClose( const QString _close );
  //----------------------------------------------------------------------------
  /// @brief removes duplicates of closing braces and quotes
  /// @param [in] _close closing character
  /// @returns true if duplicate character is replaced
  //----------------------------------------------------------------------------
  bool closing( const QString _close );
  //----------------------------------------------------------------------------
  /// @brief adds indentation after newline following a "{"
  //----------------------------------------------------------------------------
  void braceIndent();
  //----------------------------------------------------------------------------

protected slots:
  //----------------------------------------------------------------------------
  /// @brief comment out all selected lines
  //----------------------------------------------------------------------------
  void comment();
  //----------------------------------------------------------------------------
  /// @brief toggle search widget
  //----------------------------------------------------------------------------
  void toggleSearchBox();
  //----------------------------------------------------------------------------
  /// @brief called when a character is added
  //----------------------------------------------------------------------------
  void charAdded( const int _c );
  //----------------------------------------------------------------------------
  /// @brief reset the highlighting colour
  //----------------------------------------------------------------------------
  void resetHighlightColour();
  //----------------------------------------------------------------------------

}; // end class

#endif  // _CEBITOR_H__
