#include <QsciLexerGlsl.h>
#include <Qsci/qsciscintilla.h>

#include <iostream>
#include <sstream>
#include "generated/GlslLexer.h"

//------------------------------------------------------------------------------
/// @file QsciLexerGlsl.cpp
/// @brief implementation for GLSL Lexer class
/// @author Phil Rouse
/// @version 1.0
/// @date 07/05/2016
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
QsciLexerGLSL::QsciLexerGLSL(QsciScintilla *_parent) : QsciLexerCustom(_parent)
{
  m_parent = _parent;
  m_API = new QsciAPIs(this);
  QString apiPath("./src/glsl.api");
  setAPIs(m_API);
  m_API->load(apiPath);
  m_API->prepare();
  m_parent->setAutoCompletionThreshold(2);
  m_parent->setAutoCompletionFillupsEnabled(true);
  m_parent->setAutoCompletionSource(QsciScintilla::AcsAPIs);
  m_parent->setSelectionBackgroundColor(QColor(61,61,52));
  m_parent->resetSelectionForegroundColor();
}

//------------------------------------------------------------------------------
QsciLexerGLSL::~QsciLexerGLSL()
{
  return;
}

//------------------------------------------------------------------------------
void QsciLexerGLSL::styleText(const int start, const int end)
{
  m_parent->autoCompleteFromAPIs();
  //return if no QsciScintilla editor
  if(!editor())
    return;

  char * data = new char[end - start +1];

  //get text to be styled
  editor()->SendScintilla(QsciScintilla::SCI_GETTEXTRANGE, start, end, data);
  QString source(data);
  delete [] data;

  //return if no text to be styled
  if(source.isEmpty())
    return;

  //style keywords

  FlexLexer* lexer = new yyFlexLexer;
  int tok;
  int loc=0;
  std::istringstream istr (source.toStdString());

  std::vector<int> tokens;
  tok = lexer->yylex(&istr);

  while (tok>0)
  {
    tokens.push_back(tok);
    tokens.push_back(loc);
    tokens.push_back(lexer->YYLeng());
    loc = loc + lexer->YYLeng();
    tok = lexer->yylex();
  }

  int tokensCount = tokens.size();
  for (int i = 0; i<tokensCount; i=i+3)
  {
    startStyling(start+tokens[i+1]);
    setStyling(tokens[i+2],tokens[i]);
  }
}

//------------------------------------------------------------------------------
QColor QsciLexerGLSL::defaultColor(const int style) const
{
  switch(style)
  {
    case StyleType::DEFAULT:    { return QColor(247, 247, 241); }
    case StyleType::KEYWORD:    { return QColor(249, 38, 114); }
    case StyleType::DATATYPE:   { return QColor(102, 216, 238); }
    case StyleType::NUMBER:     { return QColor(174, 129, 255); }
    case StyleType::OPERATOR:   { return QColor(249, 38, 114); }
    case StyleType::STRING:     { return QColor(230, 219, 116); }
    case StyleType::FUNCTION:   { return QColor(166, 226, 46); }
    case StyleType::COMMENT:    { return QColor(117, 113, 94); }
    case StyleType::HASHCOMMENT:{ return QColor(174, 129, 255); }
    default:                    { return QColor(247,247,241); }
  }
}

//------------------------------------------------------------------------------
QColor QsciLexerGLSL::defaultPaper(const int style) const
{
  switch(style)
  {
    case StyleType::ILLEGAL:  { return QColor(249, 38, 114); }
    default:                  { return QColor(39,40,34); }
  }
}

//------------------------------------------------------------------------------
QFont QsciLexerGLSL::defaultFont(const int style) const
{
  int weight = 50;
  int size = 12;
  bool italic = 0;
  switch(style)
  {
    case StyleType::DEFAULT:
    {
      weight = 50;
      size = 12;
      break;
    }
    case StyleType::DATATYPE:
    {
      italic = true;
      break;
    }
  }

  return QFont("Monospace", size,weight,italic);
}

//------------------------------------------------------------------------------
QString QsciLexerGLSL::description(const int style) const
{
  switch(style)
  {
    case StyleType::NONE:       {return "NONE";}
    case StyleType::DEFAULT:    {return "DEFAULT";}
    case StyleType::NUMBER:     {return "NUMBER";}
    case StyleType::KEYWORD:    {return "KEYWORD";}
    case StyleType::FUNCTION:   {return "FUNCTION";}
    case StyleType::STRING:     {return "STRING";}
    case StyleType::COMMENT:    {return "COMMENT";}
    case StyleType::OPERATOR:   {return "OPERATOR";}
    case StyleType::WHITESPACE: {return "WHITESPACE";}
    case StyleType::DATATYPE:   {return "DATATYPE";}
    default:                    {return QString(style);}
  }
}

//------------------------------------------------------------------------------
const char *QsciLexerGLSL::language() const
{
  return "GLSL";
}
