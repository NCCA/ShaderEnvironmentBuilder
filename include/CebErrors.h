//------------------------------------------------------------------------------
/// @file CebErrors.h
/// @brief Contains all the code for generating and handling errors for CEB.
/// @author Jonathan Flynn
/// @version 1.0
/// @date 01/03/16
//------------------------------------------------------------------------------
#ifndef _CEBERRORS_H__
#define _CEBERRORS_H__
//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
// System includes
#include <exception>

// Engine includes

// Library  includes
#include <ngl/Types.h>
#include <QFileDevice>

// Project includes

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/// @enum glErrorCodes
/// @brief All the error codes for openGl in an easy to read enum
//------------------------------------------------------------------------------
enum glErrorCodes : GLenum
{
  NoError                     = GL_NO_ERROR,
  OutOfMemory                 = GL_OUT_OF_MEMORY,
  InvalidEnum                 = GL_INVALID_ENUM,
  InvalidValue                = GL_INVALID_VALUE,
  InvalidOperation            = GL_INVALID_OPERATION,
  InvalidFramebufferOperation = GL_INVALID_FRAMEBUFFER_OPERATION,
  StackOverflow               = GL_STACK_OVERFLOW,
  StackUnderflow              = GL_STACK_UNDERFLOW,
  TableTooLarge               = GL_TABLE_TOO_LARGE,
  ContextLost                 = GL_CONTEXT_LOST
};

//------------------------------------------------------------------------------
/// @fn glErrorCodeToText
/// @brief Converts the gl erorr code to clean text output
/// @param[in] _e the openGL error code to convert
//------------------------------------------------------------------------------
const char *glErrorCodeToText(glErrorCodes _e);
//------------------------------------------------------------------------------
/// @fn clearAllGlErrors
/// @brief Clears all the error messages in the current openGL context
//------------------------------------------------------------------------------
void clearAllGlErrors();

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/// @namespace CEBError
/// @brief Inherited exceptions for errors in the program
//------------------------------------------------------------------------------
namespace CEBError
{
//------------------------------------------------------------------------------
/// @class unknown_error
/// @brief an unknown error which is raised when a throw is not based from a
/// normal exception
//------------------------------------------------------------------------------
class unknownError: public std::exception
{
  //----------------------------------------------------------------------------
  /// @brief returns an explanatory string
  //----------------------------------------------------------------------------
  virtual const char* what() const throw()
  {
    return "Unknown";
  }
};

//------------------------------------------------------------------------------
/// @class base_error
/// @brief an unknown error which is raised when a throw is not based from a
/// normal exception
//------------------------------------------------------------------------------
class baseError: public std::exception
{
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
public:
  //----------------------------------------------------------------------------
  /// @brief Constructor for file error
  /// @param [in] _path the location of the file
  //----------------------------------------------------------------------------
  baseError():
    m_txt("<NoMessage>"){;}
  //----------------------------------------------------------------------------
  /// @brief Constructor for file error
  /// @param [in] _path the location of the file
  //----------------------------------------------------------------------------
  baseError(QString _txt):
    m_txt(_txt){;}
  //----------------------------------------------------------------------------
  /// @brief returns an explanatory string
  //----------------------------------------------------------------------------
  virtual const char* what() const throw()
  {
    return generateMsg("Base Error");
  }
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
protected:
  //----------------------------------------------------------------------------
  /// @brief the file path location where the file exists
  //----------------------------------------------------------------------------
  QString m_txt;
  //----------------------------------------------------------------------------
  /// @brief generates the error message for files
  /// @param [in] _msg the reason the error has been raised
  //----------------------------------------------------------------------------
  const char *generateMsg(std::string _msg) const
  {
    std::string msg = _msg + " '" + m_txt.toUtf8().constData() + "'";
    return msg.c_str();
  }
};

//------------------------------------------------------------------------------
/// @class file_error
/// @brief base class which is raised for file errors
//------------------------------------------------------------------------------
class fileError: public baseError
{
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
public:
  //----------------------------------------------------------------------------
  /// @brief Constructor for file error
  /// @param [in] _path the location of the file
  //----------------------------------------------------------------------------
  fileError(QString _path){m_txt = _path;}
  //----------------------------------------------------------------------------
  /// @brief returns an explanatory string
  //----------------------------------------------------------------------------
  virtual const char* what() const throw()
  {
    return generateMsg("An error occured with the file");
  }
};
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @class file_read_error
/// @brief raised for file read errors
//------------------------------------------------------------------------------
class fileReadError: public fileError
{
  using fileError::fileError;
  //----------------------------------------------------------------------------
  /// @brief returns an explanatory string
  //----------------------------------------------------------------------------
  virtual const char* what() const throw()
  {
    return generateMsg("An error occurred when reading from the file");
  }
};
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @class file_write_error
/// @brief raised for file write errors
//------------------------------------------------------------------------------
class fileWriteError: public fileError
{
  using fileError::fileError;
  //----------------------------------------------------------------------------
  /// @brief returns an explanatory string
  //----------------------------------------------------------------------------
  virtual const char* what() const throw()
  {
    return generateMsg("An error occurred when writing to the file");
  }
};
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @class file_fatal_error
/// @brief raised for file fatal errors
//------------------------------------------------------------------------------
class fileFatalError: public fileError
{
  using fileError::fileError;
  //----------------------------------------------------------------------------
  /// @brief returns an explanatory string
  //----------------------------------------------------------------------------
  virtual const char* what() const throw()
  {
    return generateMsg("A fatal error occurred with the file");
  }
};
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @class file_resource_error
/// @brief raised for file resource errors
//------------------------------------------------------------------------------
class fileResourceError: public fileError
{
  using fileError::fileError;
  //----------------------------------------------------------------------------
  /// @brief returns an explanatory string
  //----------------------------------------------------------------------------
  virtual const char* what() const throw()
  {
    return generateMsg("Out of resources when accessing the file");
  }
};
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @class file_open_error
/// @brief raised for file open errors
//------------------------------------------------------------------------------
class fileOpenError: public fileError
{
  using fileError::fileError;
  //----------------------------------------------------------------------------
  /// @brief returns an explanatory string
  //----------------------------------------------------------------------------
  virtual const char* what() const throw()
  {
    return generateMsg("The file could not be opened");
  }
};
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @class file_abort_error
/// @brief raised for file abort errors
//------------------------------------------------------------------------------
class fileAbortError: public fileError
{
  using fileError::fileError;
  //----------------------------------------------------------------------------
  /// @brief returns an explanatory string
  //----------------------------------------------------------------------------
  virtual const char* what() const throw()
  {
    return generateMsg("The operation was aborted with the file");
  }
};
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @class file_time_out_error
/// @brief raised for file timeout errors
//------------------------------------------------------------------------------
class fileTimeOutError: public fileError
{
  using fileError::fileError;
  //----------------------------------------------------------------------------
  /// @brief returns an explanatory string
  //----------------------------------------------------------------------------
  virtual const char* what() const throw()
  {
    return generateMsg("A timeout occurred with the file");
  }
};
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @class file_unspecified_error
/// @brief raised for file unspecified errors
//------------------------------------------------------------------------------
class fileUnspecifiedError: public fileError
{
  using fileError::fileError;
  //----------------------------------------------------------------------------
  /// @brief returns an explanatory string
  //----------------------------------------------------------------------------
  virtual const char* what() const throw()
  {
    return generateMsg("An unspecified error occurred with the file");
  }
};
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
/// @class file_remove_error
/// @brief raised for file remove errors
//------------------------------------------------------------------------------
class fileRemoveError: public fileError
{
  using fileError::fileError;
  //----------------------------------------------------------------------------
  /// @brief returns an explanatory string
  //----------------------------------------------------------------------------
  virtual const char* what() const throw()
  {
    return generateMsg("The file could not be removed");
  }
};
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @class file_rename_error
/// @brief raised for file rename errors
//------------------------------------------------------------------------------
class fileRenameError: public fileError
{
  using fileError::fileError;
  //----------------------------------------------------------------------------
  /// @brief returns an explanatory string
  //----------------------------------------------------------------------------
  virtual const char* what() const throw()
  {
    return generateMsg("The file could not be renamed");
  }
};
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @class file_position_error
/// @brief raised for file position errors
//------------------------------------------------------------------------------
class filePositionError: public fileError
{
  using fileError::fileError;
  //----------------------------------------------------------------------------
  /// @brief returns an explanatory string
  //----------------------------------------------------------------------------
  virtual const char* what() const throw()
  {
    return generateMsg("The position in the file could not be changed");
  }
};
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @class file_write_error
/// @brief raised for file resize errors
//------------------------------------------------------------------------------
class fileResizeError: public fileError
{
  using fileError::fileError;
  //----------------------------------------------------------------------------
  /// @brief returns an explanatory string
  //----------------------------------------------------------------------------
  virtual const char* what() const throw()
  {
    return generateMsg("The file could not be resized");
  }
};
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @class file_write_error
/// @brief raised for file permission errors
//------------------------------------------------------------------------------
class filePermissionsError: public fileError
{
  using fileError::fileError;
  //----------------------------------------------------------------------------
  /// @brief returns an explanatory string
  //----------------------------------------------------------------------------
  virtual const char* what() const throw()
  {
    return generateMsg("The file could not be accessed");
  }
};
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @class file_copy_error
/// @brief raised for file copy errors
//------------------------------------------------------------------------------
class fileCopyError: public fileError
{
  using fileError::fileError;
  //----------------------------------------------------------------------------
  /// @brief returns an explanatory string
  //----------------------------------------------------------------------------
  virtual const char* what() const throw()
  {
    return generateMsg("The file could not be copied");
  }
};
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @class openGL_error
/// @brief raised for openGL errors
//------------------------------------------------------------------------------
class openGlError: protected baseError
{
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
public:
  //----------------------------------------------------------------------------
  /// @brief Constructor for file error
  /// @param [in] _path the location of the file
  //----------------------------------------------------------------------------
  openGlError(QString _type, QString _msg){m_type = _type; m_txt = _msg;}
  //----------------------------------------------------------------------------
  /// @brief returns an explanatory string
  //----------------------------------------------------------------------------
  virtual const char* what() const throw()
  {
    return generateMsg("An error occured with OpenGL");
  }
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
protected:
  //----------------------------------------------------------------------------
  /// @brief the file path location where the file exists
  //----------------------------------------------------------------------------
  QString m_type;
  //----------------------------------------------------------------------------
  /// @brief generates the error message for files
  /// @param [in] _msg the reason the error has been raised
  //----------------------------------------------------------------------------
  const char *generateMsg(std::string _msg) const
  {
    return (_msg + " '" + m_type.toUtf8().constData() + " : " +
            m_txt.toUtf8().constData() + "'").c_str();
  }
};

class openGlListError: public baseError
{
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
public:
  //----------------------------------------------------------------------------
  /// @brief Constructor for file error
  /// @param [in] _path the location of the file
  //----------------------------------------------------------------------------
  openGlListError(std::string _prog, QString _errMsg)
  {m_errMsg = _errMsg; m_program = _prog;}
  //----------------------------------------------------------------------------
  /// @brief returns an explanatory string
  //----------------------------------------------------------------------------
  virtual const char* what() const throw()
  {
    return generateMsg("Syntax error with openGL code");
  }
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
protected:
  //----------------------------------------------------------------------------
  /// @brief
  //----------------------------------------------------------------------------
  QString m_errMsg;
  //----------------------------------------------------------------------------
  /// @brief
  //----------------------------------------------------------------------------
  std::string m_program;
  //----------------------------------------------------------------------------
  /// @brief generates the error message for files
  /// @param [in] _msg the reason the error has been raised
  //----------------------------------------------------------------------------
  const char *generateMsg(std::string _msg) const
  {
    QString finalString = "";
    finalString.append(QString("Program: %1\nMessage:\n%2\n")
                       .arg(m_program.c_str())
                       .arg(m_errMsg));

    std::string msg = _msg + "\n" + finalString.toUtf8().constData();
    return msg.c_str();
  }
};

}// namespace CEBError ends

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/// @namespace CEBRaise
/// @brief Used to raise errors in the program
//------------------------------------------------------------------------------
namespace CEBRaise
{
//------------------------------------------------------------------------------
/// @fn QtFileError
/// @brief Used to throw the corresponding file error using Qt's File error enum
/// @param [in] _e the exception or error caused by the file
/// @param [in] _path the file location
//------------------------------------------------------------------------------
void QtFileError(QFileDevice::FileError _e, QString _path);
//------------------------------------------------------------------------------
/// @fn GlError
/// @brief Used to throw the corresponding openGL error using a openGL enum
/// @param [in] _e the exception or error cause by openGL
/// @param [in] _msg the corresponding message
//------------------------------------------------------------------------------
void GlError(glErrorCodes _e, QString _msg);
} // namespace CEBRaise ends
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#endif // _CEBERRORS_H_
