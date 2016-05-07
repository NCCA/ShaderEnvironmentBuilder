#ifndef _QSCILEXERGLSL_H__
#define _QSCILEXERGLSL_H__

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
/// @class QsciLexerGlsl
/// @brief Custom QScintilla lexer for GLSL
///
/// Inherits from QsciLexerCustom to provide formatting specific to GLSL files
//------------------------------------------------------------------------------
class QsciLexerGLSL: public QsciLexerCustom
{
public:
  //----------------------------------------------------------------------------
  /// @enum QsciLexerGLSL::StyleType
  /// enum for supported style types
  /// @enum QsciLexerGLSL::StyleType::NONE
  /// No styling
  /// @enum QsciLexerGLSL::StyleType::DEFAULT
  /// Default
  /// @enum QsciLexerGLSL::StyleType::NUMBER
  /// Numbers
  /// @enum QsciLexerGLSL::StyleType::KEYWORD
  /// GLSL Keywords
  /// @enum QsciLexerGLSL::StyleType::FUNCTION
  /// Functions
  /// @enum QsciLexerGLSL::StyleType::STRING
  /// Strings
  /// @enum QsciLexerGLSL::StyleType::COMMENT
  /// Comments
  /// @enum QsciLexerGLSL::StyleType::OPERATOR
  /// Operators
  /// @enum QsciLexerGLSL::StyleType::WHITESPACE
  /// Whitespace
  /// @enum QsciLexerGLSL::StyleType::DATATYPE
  /// GLSL datatypes
  /// @enum QsciLexerGLSL::StyleType::HASHCOMMENT
  /// Preprocessor commands starting with #
  /// @enum QsciLexerGLSL::StyleType::ILLEGAL
  /// Illegal GLSL characters
  //----------------------------------------------------------------------------
  enum StyleType
  {
    NONE,
    DEFAULT,
    NUMBER,
    KEYWORD,
    FUNCTION,
    STRING,
    COMMENT,
    OPERATOR,
    WHITESPACE,
    DATATYPE,
    HASHCOMMENT,
    ILLEGAL
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
  /// @brief virtual function reimplemented from qscilexercustom.
  ///
  /// This is called when text needs to be styled.
  /// @param [in] _start  Start position of text to be styled.
  /// @param [in] _end    End position of text to be styleed.
  //----------------------------------------------------------------------------
  virtual void styleText( const int _start, const int _end );
  //----------------------------------------------------------------------------
  /// @brief virtual function reimplemented from qscilexer.
  /// @return lexer language.
  //----------------------------------------------------------------------------
  virtual const char* language() const;
  //----------------------------------------------------------------------------
  /// @brief virtual function reimplemented from qscilexer.
  /// @param [in] _style  style number.
  /// @return Default colour for style \a _style.
  //----------------------------------------------------------------------------
  virtual QColor defaultColor( const int _style ) const;
  //----------------------------------------------------------------------------
  /// @brief virtual function reimplemented from qscilexer.
  /// @param [in] _style  style number.
  /// @return Default paper colour for style \a _style.
  //----------------------------------------------------------------------------
  virtual QColor defaultPaper( const int _style ) const;
  //----------------------------------------------------------------------------
  /// @brief virtual function reimplemented from qscilexer.
  /// @param [in] _style  style number.
  /// @return Default font for style \a _style.
  //----------------------------------------------------------------------------
  virtual QFont defaultFont( const int _style ) const;
  //----------------------------------------------------------------------------
  /// @brief virtual function reimplemented from qscilexer.
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
  /// @brief glsl API instance
  //----------------------------------------------------------------------------
  QsciAPIs *m_API;
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
