#include "Cebitor.h"
#include "CebErrors.h"

#include <iostream>
#include <QAction>
#include <QSettings>
#include <QStringList>
#include <Qsci/qscicommand.h>
#include <Qsci/qscicommandset.h>

#include <QTextStream>
#include <QFile>

//----------------------------------------------------------------------------------------------------------------------
/// @file Cebitor.cpp
/// @brief implementation of Cebitor class
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
Cebitor::Cebitor(QWidget *_parent) : QsciScintilla(_parent)
{
  setMinimumHeight(300);

  // Create and assign the lexer
  QsciLexer* lex = new QsciLexerGLSL(this);
  setLexer(lex);

  // Set the margin defaults
  setMarginType(0,MarginType::NumberMargin);
  setMarginWidth(0," 012");
  setMarginsForegroundColor(QColor(128, 128, 128));
  // Set the symbol margin defaults
  setMarginType(1,MarginType::SymbolMargin);
  setMarginWidth(1,12);
  setMarginMarkerMask(1, 1 << 0 | 1 << 1 | 1 << 2);

  // Set the caret defaults
  setCaretForegroundColor(QColor(247, 247, 241));
  setCaretWidth(2);
  // Set the brace defaults
  setBraceMatching(BraceMatch::SloppyBraceMatch);
  setMatchedBraceBackgroundColor(QColor(62, 61, 50));
  setUnmatchedBraceBackgroundColor(QColor(249, 38, 114));

  // Set auto-indent
  setAutoIndent(true);
  setIndentationsUseTabs(false);
  setIndentationWidth(2);

  // Enable scroll width tracking and set the scroll width to a low number
  // Scintilla doesn't track line length, so if we wanted automated scrollbar
  // to appear we would need to implement a line length checking
  SendScintilla(QsciScintillaBase::SCI_SETSCROLLWIDTHTRACKING, 1);
  SendScintilla(QsciScintillaBase::SCI_SETSCROLLWIDTH, 5);

  // set up line markers
  QIcon errorIcon = QIcon::fromTheme(QString("dialog-error"));
  QIcon warnIcon = QIcon::fromTheme(QString("dialog-warning"));

  markerDefine(errorIcon.pixmap(10,10), MarkerType::ERROR);
  markerDefine(warnIcon.pixmap(10,10), MarkerType::WARNING);
  markerDefine(MarkerSymbol::Background, MarkerType::FILESTART);
  SendScintilla(QsciScintillaBase::SCI_MARKERSETBACK, MarkerType::FILESTART, QColor(45,46,38));

  // unbind CTRL-/ keyboard shortcut
  standardCommands()->boundTo(Qt::Key_Slash | Qt::CTRL)->setKey(0);

  // rebind CTRL-/ to comment function
  QAction *commentAction = new QAction(this);
  commentAction->setShortcut(Qt::Key_Slash | Qt::CTRL);

  connect(commentAction, SIGNAL(triggered()), this, SLOT(comment()));
  addAction(commentAction);

  // connect signals and slots
  connect(this, SIGNAL(SCN_CHARADDED(int)), this, SLOT(charAdded(int)));
}

bool Cebitor::loadTextFiles(const std::vector<QString> _paths)
{
  int numPaths;
  numPaths = _paths.size();
  for(int i=0; i<numPaths; i++)
  {
    QString fileText;
    QFile file(_paths[i]);

    // Open the file as readonly and text and ensure it loaded correctly
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      // Raise an error if failed
      ceb_raise::QtFileError(file.error(), _paths[i]);
      return false;
    }

    // Fead the text into the tab if successful, adding to the end of the existing text
    QTextStream in(&file);
    int startingLines = text().count("\n");
    fileText = text() + in.readAll() + QString("\n");
    setText(fileText);
    int markerHandle = markerAdd(startingLines,2);
    m_fileMarkers.push_back(markerHandle);
  }
  return true;
}

//----------------------------------------------------------------------------------------------------------------------
bool Cebitor::autoClose(const QString _close)
{
  int cursorIndex;
  int cursorLine;
  int length;
  getCursorPosition(&cursorLine, &cursorIndex);
  length = lineLength(cursorLine);

  // insert closing character if cursor is at EOL or the next character is a space
  if(cursorIndex == length-1)
  {
    insert(_close);
    return true;
  }
  else if(text(cursorLine).at(cursorIndex).toLatin1() == ' ')
  {
    insert(_close);
    return true;
  }
  return false;
}

//----------------------------------------------------------------------------------------------------------------------
bool Cebitor::closing(const QString _close)
{
  int cursorIndex;
  int cursorLine;
  //int length;
  getCursorPosition(&cursorLine, &cursorIndex);
  //length = lineLength(cursorLine);

  // remove duplicate if next character is the same as _close
  if(text(cursorLine).at(cursorIndex) == _close.at(0))
  {
    setSelection(cursorLine, cursorIndex, cursorLine, cursorIndex+1);
    removeSelectedText();
    return true;
  }
  // auto unindent "}"
  if( _close == QString('}') && cursorIndex == indentation(cursorLine)+1 )
  {
    int indentSize;
    indentSize = indentation(cursorLine)-indentationWidth();
    if( indentSize < 0 )
    {
      indentSize = 0;
    }
    setIndentation(cursorLine, indentSize);
  }
  return false;
}

//----------------------------------------------------------------------------------------------------------------------
void Cebitor::comment()
{
  beginUndoAction();
  int lineFrom;
  int indexFrom;
  int lineTo;
  int indexTo;
  // get selected lines or current line if no text is selected
  if(hasSelectedText())
  {
    getSelection(&lineFrom, &indexFrom, &lineTo, &indexTo);
  }
  else
  {
    getCursorPosition(&lineFrom, &indexFrom);
    lineTo = lineFrom;
    indexTo = indexFrom;
  }

  // check if selected lines are already commented
  bool alreadyCommented = true;
  for(int i=lineFrom; i<=lineTo; i++)
  {
    QString lineText = text(i);
    if(!lineText.startsWith("//"))
    {
      alreadyCommented = false;
    }
  }

  // remove "//" from each line if they are already commented
  if(alreadyCommented)
  {
    for(int i=lineFrom; i<=lineTo; i++)
    {
      setSelection(i,0,i,2);
      removeSelectedText();
    }
    //offset original selection for reselecting text
    indexTo -= 2;
    if(indexFrom > 1)
    {
      indexFrom -= 2;
    }
  }

  // insert "//" at the start of each line
  else
  {
    for(int i=lineFrom; i<=lineTo; i++)
    {
      insertAt(QString("//"),i,0);
    }
    //offset original selection for reselecting text
    indexTo += 2;
    if(indexFrom != 0)
    {
      indexFrom += 2;
    }
  }

  // reselect to match original selection
  setSelection(lineFrom,indexFrom,lineTo,indexTo);
  endUndoAction();
}

void Cebitor::braceIndent()
{
  int cursorIndex;
  int cursorLine;
  QString currentLine;
  QString previousLine;
  getCursorPosition(&cursorLine, &cursorIndex);
  currentLine = text(cursorLine);
  previousLine = text(cursorLine-1);

  // indent if previous line ends with "{"
  if(previousLine.endsWith("{\n"))
  {
    int indentSize;
    indentSize = indentation(cursorLine-1);
    setIndentation(cursorLine, indentSize+indentationWidth());
    cursorIndex = cursorIndex+indentationWidth();
    setCursorPosition(cursorLine, cursorIndex);
    currentLine = text(cursorLine);
    // extra newline to separate "{}"
    if(currentLine.indexOf("}") == cursorIndex)
    {
      insert(QString("\n"));
    }
  }

  // unindent if "}" after cursor
  else if(currentLine.indexOf("}") == cursorIndex)
  {
    int indentSize;
    indentSize = indentation(cursorLine)-indentationWidth();
    if( indentSize < 0 )
    {
      indentSize = 0;
    }
    setIndentation(cursorLine, indentSize);
  }
}

//----------------------------------------------------------------------------------------------------------------------
void Cebitor::charAdded(int _c)
{
  switch(_c)
  {
    case (int) '(': { autoClose(QString(')')); break; }
    case (int) '{': { autoClose(QString('}')); break; }
    case (int) '[': { autoClose(QString(']')); break; }

    case (int) ')': { closing(QString(')')); break; }
    case (int) '}': { closing(QString('}')); break; }
    case (int) ']': { closing(QString(']')); break; }

    // special case since " opens and closes
    case (int) '"':

    // auto indent for braces
    case (int) '\n': { braceIndent(); break; }
    {
      if(!closing(QString('"')))
      {
        autoClose(QString('"'));
      }
      break;
    }
  }
}
