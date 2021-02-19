//------------------------------------------------------------------------------
// INCLUDES
//------------------------------------------------------------------------------
// System includes
#include <array>
#include <iostream>
#include <typeinfo>

// Engine includes

// Library  includes
#include <QAction>

// Project includes
#include "CebApplication.h"
#include "CebErrors.h"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
bool CebApplication::notify(QObject *_reciever, QEvent *_event)
{
  try // Try to notify but will catch an exception if it fails
  {
    return QApplication::notify(_reciever, _event);
  }
  catch (std::exception &e)
  {
    // Create and show messagebox
    QMessageBox* mBox = createErrorMsgBox(&e, _reciever, _event,
                                          QMessageBox::Critical);
    mBox->exec();

    delete mBox;
  }
  catch (...)
  {
    // Create unknown error message then create and show messagebox
    CEBError::unknownError e = CEBError::unknownError();
    QMessageBox* mBox = createErrorMsgBox(&e, _reciever, _event,
                                          QMessageBox::Critical);
    mBox->exec();

    delete mBox;
  }

  return false;
}

//------------------------------------------------------------------------------
QMessageBox* CebApplication::createErrorMsgBox(std::exception *_e,
                                               QObject *_reciever,
                                               QEvent *_event,
                                               QMessageBox::Icon _errLvl)
{
  // Create text and window title message
  QString msg = QString("%1 Error").arg(m_errorLvl[static_cast<int>(_errLvl)]);
  // Create informative text message
  QString iMsg = QString(_e->what());
  // create de
  QString dMsg = QString("Sending event '%1' to object '%2' (%3)")
      .arg(typeid(*_event).name(),
           qPrintable(_reciever->objectName()),
           typeid(*_reciever).name());

  // Output to console for extra logging
  std::cerr << msg.toUtf8().constData() << std::endl
            << iMsg.toUtf8().constData() << std::endl;

  // Create the msgbox
  QMessageBox* msgBox = new QMessageBox;
  // Set values
  msgBox->setIcon(_errLvl);
  msgBox->setText(msg);
  msgBox->setWindowTitle(msg);
  msgBox->setInformativeText(iMsg);
  msgBox->setDetailedText(dMsg);

  return msgBox;
}
