#ifndef CEBITOR_H
#define CEBITOR_H

#include "QsciLexerGlsl.h"

#include <Qsci/qsciscintilla.h>

class Cebitor : public QsciScintilla
{
  Q_OBJECT;

public:
  Cebitor(QWidget *_parent);

private:
  void loadSettings();
};

#endif
