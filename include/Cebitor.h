#ifndef CEBITOR_H
#define CEBITOR_H

#include "QsciLexerGlsl.h"

#include <Qsci/qsciscintilla.h>

class Cebitor : public QsciScintilla
{
  Q_OBJECT;

public:
  Cebitor(QWidget *_parent) : QsciScintilla(_parent) {loadSettings();}

private:
  void loadSettings();
};

#endif
