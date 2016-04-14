#include "CebErrors.h"

void clearAllGlErrors()
{
  GLenum errNo = glGetError();
  while (errNo != GL_NO_ERROR)
  {
    errNo = glGetError();
  }
}

const char *glErrorCodeToText(glErrorCodes _e)
{
  switch(_e)
  {
    case glErrorCodes::NoError: return "No Memory"; break;
    case glErrorCodes::OutOfMemory: return "Out of Memory"; break;
    case glErrorCodes::InvalidEnum: return "Invalid Enum"; break;
    case glErrorCodes::InvalidValue: return "Invalid Value"; break;
    case glErrorCodes::InvalidOperation: return "Invalid Operation"; break;
    case glErrorCodes::InvalidFramebufferOperation: return "Invalid Framebuffer Operation"; break;
    case glErrorCodes::StackOverflow: return "Stack Overflow"; break;
    case glErrorCodes::StackUnderflow: return "Stack Underflow"; break;
    case glErrorCodes::TableTooLarge: return "Table Too Large"; break;
    case glErrorCodes::ContextLost: return "Context Lost"; break;
  }
}

//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
namespace ceb_raise
{
//----------------------------------------------------------------------------------------------------------------------
  void QtFileError(QFileDevice::FileError _e, QString _path)
  {
    switch(_e)
    {
      case QFileDevice::ReadError: throw ceb_error::file_read_error(_path); break;
      case QFileDevice::WriteError: throw ceb_error::file_write_error(_path); break;
      case QFileDevice::FatalError: throw ceb_error::file_fatal_error(_path); break;
      case QFileDevice::ResourceError: throw ceb_error::file_resource_error(_path); break;
      case QFileDevice::OpenError: throw ceb_error::file_open_error(_path); break;
      case QFileDevice::AbortError: throw ceb_error::file_abort_error(_path); break;
      case QFileDevice::TimeOutError: throw ceb_error::file_time_out_error(_path); break;
      case QFileDevice::UnspecifiedError: throw ceb_error::file_unspecified_error(_path); break;
      case QFileDevice::RemoveError: throw ceb_error::file_remove_error(_path); break;
      case QFileDevice::RenameError: throw ceb_error::file_rename_error(_path); break;
      case QFileDevice::PositionError: throw ceb_error::file_position_error(_path); break;
      case QFileDevice::ResizeError: throw ceb_error::file_resize_error(_path); break;
      case QFileDevice::PermissionsError: throw ceb_error::file_permissions_error(_path); break;
      case QFileDevice::CopyError: throw ceb_error::file_copy_error(_path); break;
    default: throw ceb_error::unknown_error(); break;
    }
  }
}


//----------------------------------------------------------------------------------------------------------------------
