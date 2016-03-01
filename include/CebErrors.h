#ifndef CEBERRORS_H
#define CEBERRORS_H

#include <exception>
#include <QFileDevice>

namespace ceb_error
{
//----------------------------------------------------------------------------------------------------------------------
class unknown_error: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Unknown";
  }
};
//----------------------------------------------------------------------------------------------------------------------
class file_error: public std::exception
{
public:
  file_error(QString _path):
    m_path(_path){;}

  virtual const char* what() const throw()
  {
    return generateMsg("An error occured with the file");
  }

protected:
  QString m_path;
  const char * generateMsg(std::string _msg) const
  {
    std::string msg = _msg + " '" + m_path.toUtf8().constData() + "'";
    return msg.c_str();
  }
};
//----------------------------------------------------------------------------------------------------------------------
class file_read_error: public file_error
{
  using file_error::file_error;
  virtual const char* what() const throw()
  {
    return generateMsg("An error occurred when reading from the file");
  }
};
//----------------------------------------------------------------------------------------------------------------------
class file_write_error: public file_error
{
  using file_error::file_error;
  virtual const char* what() const throw()
  {
    return generateMsg("An error occurred when writing to the file");
  }
};
//----------------------------------------------------------------------------------------------------------------------
class file_fatal_error: public file_error
{
  using file_error::file_error;
  virtual const char* what() const throw()
  {
    return generateMsg("A fatal error occurred with the file");
  }
};
//----------------------------------------------------------------------------------------------------------------------
class file_resource_error: public file_error
{
  using file_error::file_error;
  virtual const char* what() const throw()
  {
    return generateMsg("Out of resources when accessing the file");
  }
};
//----------------------------------------------------------------------------------------------------------------------
class file_open_error: public file_error
{
  using file_error::file_error;
  virtual const char* what() const throw()
  {
    return generateMsg("The file could not be opened");
  }
};
//----------------------------------------------------------------------------------------------------------------------
class file_abort_error: public file_error
{
  using file_error::file_error;
  virtual const char* what() const throw()
  {
    return generateMsg("The operation was aborted with the file");
  }
};
//----------------------------------------------------------------------------------------------------------------------
class file_time_out_error: public file_error
{
  using file_error::file_error;
  virtual const char* what() const throw()
  {
    return generateMsg("A timeout occurred with the file");
  }
};
//----------------------------------------------------------------------------------------------------------------------
class file_unspecified_error: public file_error
{
  using file_error::file_error;
  virtual const char* what() const throw()
  {
    return generateMsg("An unspecified error occurred with the file");
  }
};
//----------------------------------------------------------------------------------------------------------------------
class file_remove_error: public file_error
{
  using file_error::file_error;
  virtual const char* what() const throw()
  {
    return generateMsg("The file could not be removed");
  }
};
//----------------------------------------------------------------------------------------------------------------------
class file_rename_error: public file_error
{
  using file_error::file_error;
  virtual const char* what() const throw()
  {
    return generateMsg("The file could not be renamed");
  }
};
//----------------------------------------------------------------------------------------------------------------------
class file_position_error: public file_error
{
  using file_error::file_error;
  virtual const char* what() const throw()
  {
    return generateMsg("The position in the file could not be changed");
  }
};
//----------------------------------------------------------------------------------------------------------------------
class file_resize_error: public file_error
{
  using file_error::file_error;
  virtual const char* what() const throw()
  {
    return generateMsg("The file could not be resized");
  }
};
//----------------------------------------------------------------------------------------------------------------------
class file_permissions_error: public file_error
{
  using file_error::file_error;
  virtual const char* what() const throw()
  {
    return generateMsg("The file could not be accessed");
  }
};
//----------------------------------------------------------------------------------------------------------------------
class file_copy_error: public file_error
{
  using file_error::file_error;
  virtual const char* what() const throw()
  {
    return generateMsg("The file could not be copied");
  }
};

} // namespace ceb error ends
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
namespace ceb_raise
{

void QtFileError(QFileDevice::FileError _e, QString _path);

} // namespace ceb raise ends

#endif
