#include <qscilexerglsl.h>
#include <Qsci/qsciscintilla.h>

#include <iostream>

QsciLexerGLSL::QsciLexerGLSL(QObject *parent) : QsciLexerCustom(parent)
{
    //all GLSL keywords
    keywordsList <<"attribute"<<"const"<<"uniform"<<"varying"<<"layout"<<"centroid"<<"flat"<<"smooth"<<"noperspective"<<"patch"<<"sample"<<"break"<<"continue"<<"do"<<
                   "for"<<"while"<<"switch"<<"case"<<"default"<<"if"<<"else"<<"subroutine"<<"in"<<"out"<<"inout"<<"float"<<"double"<<"int"<<"void"<<"bool"<<"true"<<
                   "false"<<"invariant"<<"discard"<<"return"<<"mat2"<<"mat3"<<"mat4"<<"dmat2"<<"dmat3"<<"dmat4"<<"mat2x2"<<"mat2x3"<<"mat2x4"<<"dmat2x2"<<"dmat2x3"<<
                   "dmat2x4"<<"mat3x2"<<"mat3x3"<<"mat3x4"<<"dmat3x2"<<"dmat3x3"<<"dmat3x4"<<"mat4x2"<<"mat4x3"<<"mat4x4"<<"dmat4x2"<<"dmat4x3"<<"dmat4x4"<<"vec2"<<"vec3"<<
                   "vec4"<<"ivec2"<<"ivec3"<<"ivec4"<<"bvec2"<<"bvec3"<<"bvec4"<<"dvec2"<<"dvec3"<<"dvec4"<<"uint"<<"uvec2"<<"uvec3"<<"uvec4"<<"lowp"<<"mediump"<<"highp"<<
                   "precision"<<"sampler1D" << "sampler2D" << "sampler3D" << "samplerCube" << "sampler1DShadow" << "sampler2DShadow" << "samplerCubeShadow" << "sampler1DArray" <<
                   "sampler2DArray" << "sampler1DArrayShadow" << "sampler2DArrayShadow" << "isampler1D" << "isampler2D" << "isampler3D" << "isamplerCube" << "isampler1DArray" <<
                   "isampler2DArray" << "usampler1D" << "usampler2D" << "usampler3D" << "usamplerCube" << "usampler1DArray" << "usampler2DArray" << "sampler2DRect" <<
                   "sampler2DRectShadow" << "isampler2DRect" << "usampler2DRect" << "samplerBuffer" << "isamplerBuffer" << "usamplerBuffer" << "sampler2DMS" << "isampler2DMS" <<
                   "usampler2DMS" << "sampler2DMSArray" << "isampler2DMSArray" << "usampler2DMSArray" << "samplerCubeArray" << "samplerCubeArrayShadow" << "isamplerCubeArray" <<
                   "usamplerCubeArray" << "struct";
}

QsciLexerGLSL::~QsciLexerGLSL()
{
    return;
}

void QsciLexerGLSL::styleText(int start, int end)
{
    //return if no QsciScintilla editor
    if(!editor())
        return;

    char * data = new char[end - start +1];

    //get text to be styled
    editor()->SendScintilla(QsciScintilla::SCI_GETTEXTRANGE, start, end, data);
    QString source(data);
    delete [] data;

    //return if no text to be styled
    if(source.isEmpty())
        return;

    //style keywords
    highlightKeywords(source, start);
}

void QsciLexerGLSL::highlightKeywords(const QString &source, int start)
{
    //check for keywords in text
    for (int i = 0; i<keywordsList.size(); i++)
    {
        QString word = keywordsList.at(i);
        if (source.contains(word))
        {
            int count = source.count(word);
            int index = 0;
            //for each instance of the keyword, set styling
            for (int j = 0; j<count; j++)
            {
                int wordStart = source.indexOf(word, index);
                index = wordStart+1;

                startStyling(start + wordStart);
                printf("started styling\n");
                setStyling(word.length(), Keyword);
            }
        }
    }
}

QColor QsciLexerGLSL::defaultColor(int style) const
{
    switch(style)
    {
        case Keyword:
            return QColor(102,216,238);
    }
    return QColor(247,247,241);
}

QColor QsciLexerGLSL::defaultPaper(int style) const
{
    return QColor(39,40,34);
}

QFont QsciLexerGLSL::defaultFont(int style) const
{
    int weight=50;
    int size=12;
    switch(style)
    {
        case Keyword:
            weight = 75;
    }

    return QFont("Monospace", size,weight);
}

QString QsciLexerGLSL::description(int style) const
{
    switch(style)
    {
        case Default:
            return "Default";
        case Keyword:
            return "Keyword";
    }
    return QString(style);
}

const char *QsciLexerGLSL::language() const
{
    return "GLSL";
}
