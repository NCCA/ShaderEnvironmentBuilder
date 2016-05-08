//------------------------------------------------------------------------------
/// @file CebAppplication.h
/// @brief the CEB implementation of QApplication to allow for error handling
/// @author Jonathan Flynn
/// @version 1.0
/// @date 01/03/16
//------------------------------------------------------------------------------
#ifndef _CEB_APPLICATION_H__
#define _CEB_APPLICATION_H__
//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
// System includes

// Engine includes

// Library  includes
#include <QApplication>
#include <QMessageBox>
#include <QStringList>

// Project includes

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/// @class CebApplication
/// @brief used to handle all the gui's application control flow and errors for
/// the program
//------------------------------------------------------------------------------
class CebApplication : public QApplication
{
  Q_OBJECT        // must include this if you use Qt signals/slots
  using QApplication::QApplication; // Inherit constructors from QApplication
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
public:
  //----------------------------------------------------------------------------
  QStringList   m_errorLvl = {"Message", "Information", "Warning",
                              "Critical", "Question"};
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
  /// @brief Sends event to receiver and handles errors. Returns the value
  /// that is returned from the receiver's event handler or false if error
  /// @param [in] _reciever the object that recieves the event
  /// @param [in] _event the event that is being sent to the reciever
  /// @returns true if the notify was successful else false
  //----------------------------------------------------------------------------
  bool          notify(QObject *_reciever, QEvent *_event);
  //----------------------------------------------------------------------------
  //----------------------------------------------------------------------------
private:
  //----------------------------------------------------------------------------
  /// @brief creates an error msg created from an exception
  /// @param [in] _e pointer to the exception raised
  /// @param [in] _reciever the object that recieves the event
  /// @param [in] _event the event that is being sent to the reciever
  /// @param [in] _errLvl the error level for the message
  //----------------------------------------------------------------------------
  QMessageBox*  createErrorMsgBox(std::exception *_e, QObject *_reciever,
                                  QEvent *_event, QMessageBox::Icon _errLvl);
  //----------------------------------------------------------------------------
};

#endif // _CEB_APPLICATION_H_
