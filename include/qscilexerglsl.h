#ifndef QSCILEXERGLSL_H__
#define QSCILEXERGLSL_H__

#include <Qsci/qscilexercpp.h>

class QsciLexerGLSL: public QsciLexerCPP {
public:
    QsciLexerGLSL(QObject *parent = 0, bool caseInsensitiveKeywords = false) : QsciLexerCPP()
    {
    }
};

#endif
