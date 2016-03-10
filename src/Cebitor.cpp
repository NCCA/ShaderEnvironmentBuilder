#include "Cebitor.h"

//----------------------------------------------------------------------------------------------------------------------
/// @file Cebitor.cpp
/// @brief implementation of Cebitor class
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
Cebitor::Cebitor(QWidget *_parent) : QsciScintilla(_parent)
{
  // Create and assign the lexer
  QsciLexer* lex = new QsciLexerGLSL(this);
  this->setLexer(lex);

  // Set the margin defaults
  this->setMarginType(1,QsciScintilla::MarginType::NumberMargin);
  this->setMarginWidth(1," 012");
  this->setMarginsForegroundColor(QColor(128, 128, 128));
  // Set the caret defaults
  this->setCaretForegroundColor(QColor(247, 247, 241));
  this->setCaretWidth(2);
  // Set the brace defaults
  this->setBraceMatching(QsciScintilla::BraceMatch::SloppyBraceMatch);
  this->setMatchedBraceBackgroundColor(QColor(62, 61, 50));
  this->setUnmatchedBraceBackgroundColor(QColor(249, 38, 114));

  // Enable scroll width tracking and set the scroll width to a low number
  // Scintilla doesn't track line length, so if we wanted automated scrollbar
  // to appear we would need to implement a line length checking
  this->SendScintilla(QsciScintillaBase::SCI_SETSCROLLWIDTHTRACKING, 1);
  this->SendScintilla(QsciScintillaBase::SCI_SETSCROLLWIDTH, 5);
}
