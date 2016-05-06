//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
// System includes

// Engine includes

// Library  includes

// Project includes
#include "CebErrors.h"
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void clearAllGlErrors()
{
  GLenum errNo = glGetError();
  while (errNo != GL_NO_ERROR)
  {
    errNo = glGetError();
  }
}

//------------------------------------------------------------------------------
const char *glErrorCodeToText(glErrorCodes _e)
{
  switch(_e)
  {
    case glErrorCodes::NoError:
    {
      return "No Memory";
      break;
    }
    case glErrorCodes::OutOfMemory:
    {
      return "Out of Memory";
      break;
    }
    case glErrorCodes::InvalidEnum:
    {
      return "Invalid Enum";
      break;
    }
    case glErrorCodes::InvalidValue:
    {
      return "Invalid Value";
      break;
    }
    case glErrorCodes::InvalidOperation:
    {
      return "Invalid Operation";
      break;
    }
    case glErrorCodes::InvalidFramebufferOperation:
    {
      return "Invalid Framebuffer Operation";
      break;
    }
    case glErrorCodes::StackOverflow:
    {
      return "Stack Overflow";
      break;
    }
    case glErrorCodes::StackUnderflow:
    {
      return "Stack Underflow";
      break;
    }
    case glErrorCodes::TableTooLarge:
    {
      return "Table Too Large";
      break;
    }
    case glErrorCodes::ContextLost:
    {
      return "Context Lost";
      break;
    }
    default:
    {
      return "Unknown Gl Error Code";
      break;
    }
  }
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
namespace CEBRaise
{
//------------------------------------------------------------------------------
void QtFileError(QFileDevice::FileError _e, QString _path)
{
  switch(_e)
  {
    case QFileDevice::ReadError:
    {
      throw CEBError::fileReadError(_path);
      break;
    }
    case QFileDevice::WriteError:
    {
      throw CEBError::fileWriteError(_path);
      break;
    }
    case QFileDevice::FatalError:
    {
      throw CEBError::fileFatalError(_path);
      break;
    }
    case QFileDevice::ResourceError:
    {
      throw CEBError::fileResourceError(_path);
      break;
    }
    case QFileDevice::OpenError:
    {
      throw CEBError::fileOpenError(_path);
      break;
    }
    case QFileDevice::AbortError:
    {
      throw CEBError::fileAbortError(_path);
      break;
    }
    case QFileDevice::TimeOutError:
    {
      throw CEBError::fileTimeOutError(_path);
      break;
    }
    case QFileDevice::UnspecifiedError:
    {
      throw CEBError::fileUnspecifiedError(_path);
      break;
    }
    case QFileDevice::RemoveError:
    {
      throw CEBError::fileRemoveError(_path);
      break;
    }
    case QFileDevice::RenameError:
    {
      throw CEBError::fileRenameError(_path); break;
    }
    case QFileDevice::PositionError:
    {
      throw CEBError::filePositionError(_path); break;
    }
    case QFileDevice::ResizeError:
    {
      throw CEBError::fileResizeError(_path); break;
    }
    case QFileDevice::PermissionsError:
    {
      throw CEBError::filePermissionsError(_path); break;
    }
    case QFileDevice::CopyError:
    {
      throw CEBError::fileCopyError(_path); break;
    }
    default:
    {
      throw CEBError::unknownError();
      break;
    }
  }
}
}
//----------------------------------------------------------------------------------------------------------------------
