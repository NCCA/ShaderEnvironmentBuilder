#ifndef _QSCILEXERGLSL_H__
#define _QSCILEXERGLSL_H__

#include <memory>

#include <Qsci/qscilexercustom.h>
#include <Qsci/qscistyle.h>
#include <Qsci/qsciapis.h>

//------------------------------------------------------------------------------
/// @file QsciLexerGlsl.h
/// @brief Custom QScintilla lexer for GLSL
/// @author Phil Rouse
/// @version 1.0
/// @date 07/05/2016
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// Predeclare FlexLexer class here since including GlslLexer.h in header breaks
/// flex, including in .cpp works fine though...?
//------------------------------------------------------------------------------
class FlexLexer;

//------------------------------------------------------------------------------
/// @class QsciLexerGLSL
/// @brief Custom QScintilla lexer for GLSL
///
/// Inherits from QsciLexerCustom to provide formatting specific to GLSL files
//------------------------------------------------------------------------------
class QsciLexerGLSL: public QsciLexerCustom
{
public:
  //----------------------------------------------------------------------------
  /// @brief enum for supported style types
  //----------------------------------------------------------------------------
  enum StyleType
  {
    NONE,         ///<No styling
    DEFAULT,      ///<Default
    NUMBER,       ///<Numbers
    KEYWORD,      ///<GLSL Keywords
    FUNCTION,     ///<Functions
    STRING,       ///<Strings
    COMMENT,      ///<Comments
    OPERATOR,     ///<Operators
    WHITESPACE,   ///<Whitespace
    DATATYPE,     ///<GLSL datatypes
    HASHCOMMENT,  ///<Preprocessor commands starting with #
    ILLEGAL       ///<Illegal GLSL characters
  };
  //----------------------------------------------------------------------------
  /// @brief QsciLexerGLSL constructor
  /// @param [in] _parent Parent QsciScintilla instance
  //----------------------------------------------------------------------------
  QsciLexerGLSL( QsciScintilla *_parent = 0 );
  //----------------------------------------------------------------------------
  /// @brief QsciLexerGLSL destructor.
  //----------------------------------------------------------------------------
  virtual ~QsciLexerGLSL();
  //----------------------------------------------------------------------------
  /// @brief virtual function reimplemented from QsciLexerCustom.
  ///
  /// This is called when text needs to be styled.
  /// @param [in] _start  Start position of text to be styled.
  /// @param [in] _end    End position of text to be styleed.
  //----------------------------------------------------------------------------
  virtual void styleText( const int _start, const int _end );
  //----------------------------------------------------------------------------
  /// @brief virtual function reimplemented from QsciLexer.
  /// @return lexer language.
  //----------------------------------------------------------------------------
  virtual const char* language() const;
  //----------------------------------------------------------------------------
  /// @brief virtual function reimplemented from QsciLexer.
  /// @param [in] _style  style number.
  /// @return Default colour for style \a _style.
  //----------------------------------------------------------------------------
  virtual QColor defaultColor( const int _style ) const;
  //----------------------------------------------------------------------------
  /// @brief virtual function reimplemented from QsciLexer.
  /// @param [in] _style  style number.
  /// @return Default paper colour for style \a _style.
  //----------------------------------------------------------------------------
  virtual QColor defaultPaper( const int _style ) const;
  //----------------------------------------------------------------------------
  /// @brief virtual function reimplemented from QsciLexer.
  /// @param [in] _style  style number.
  /// @return Default font for style \a _style.
  //----------------------------------------------------------------------------
  virtual QFont defaultFont( const int _style ) const;
  //----------------------------------------------------------------------------
  /// @brief virtual function reimplemented from QsciLexer.
  /// @param [in] _style  style number.
  /// @return Descriptive for style \a _style.
  //----------------------------------------------------------------------------
  virtual QString description( const int _style ) const;

protected:
  //----------------------------------------------------------------------------
  /// @brief parent QScintilla instance
  //----------------------------------------------------------------------------
  QsciScintilla *m_parent;
  //----------------------------------------------------------------------------
  /// @brief GLSL API instance
  //----------------------------------------------------------------------------
  QsciAPIs *m_API;
  //----------------------------------------------------------------------------
  /// @brief flex lexer instance
  //----------------------------------------------------------------------------
  FlexLexer *m_flexScanner;
  //----------------------------------------------------------------------------
  /// @brief copy constructor
  //----------------------------------------------------------------------------
  QsciLexerGLSL( const QsciLexerGLSL & );
  //----------------------------------------------------------------------------
  /// @brief assignment operator
  //----------------------------------------------------------------------------
  QsciLexerGLSL &operator=( const QsciLexerGLSL & );

};// end class

#endif
