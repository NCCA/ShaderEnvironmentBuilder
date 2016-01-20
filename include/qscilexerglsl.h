#ifndef QSCILEXERGLSL_H__
#define QSCILEXERGLSL_H__

#include <Qsci/qscilexercustom.h>
#include <Qsci/qscistyle.h>

class QsciLexerGLSL: public QsciLexerCustom {
public:
    QsciLexerGLSL(QObject *parent=0);
    ~QsciLexerGLSL();

    void styleText(int start, int end);

    void highlightKeywords(const QString &source, int start);

    const char *language() const;

    QColor defaultColor(int style) const;
    QColor defaultPaper(int style) const;
    QFont defaultFont(int style) const;

    QString description(int style) const;


    enum StyleType{
        NONE,
        DEFAULT,
        NUMBER,
        KEYWORD,
        FUNCTION,
        STRING,
        COMMENT,
        DISABLED,
        OPERATOR,
        WHITESPACE
    };

private:
    QsciLexerGLSL(const QsciLexerGLSL &);
    QsciLexerGLSL &operator=(const QsciLexerGLSL &);
    QStringList keywordsList;
    QsciStyle m_keywordStyle;
};

#endif
