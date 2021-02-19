/*! @file GlslLexer.lex
 * @brief Flex definitions for generating the GLSL lexer
 * @author Phil Rouse
 * @version 1.0
 * @date 07/05/2016
 */



%option c++

%{
  #include "QsciLexerGlsl.h"
%}

%%

"attribute"               |
"const"                   |
"uniform"                 |
"varying"                 |
"layout"                  |
"centroid"                |
"flat"                    |
"smooth"                  |
"noperspective"           |
"break"                   |
"continue"                |
"do"                      |
"for"                     |
"while"                   |
"switch"                  |
"case"                    |
"default"                 |
"if"                      |
"else"                    |
"in"                      |
"out"                     |
"inout"                   |
"return"                  |
"invariant"               |
["low""medium""high"]"p"  |
"discard"                 |
"precision"               |
"struct"                  { return QsciLexerGLSL::StyleType::KEYWORD; }

(?#/* "/.?" added to override function rule*/)
[iu]?sampler(([123]D)|Cube)|([12]DArray)|2DRect|Buffer/.? { return QsciLexerGLSL::StyleType::DATATYPE; }
sampler(([123]D)|Cube)|([12]DArray)|((2DRect)Shadow)/.?   { return QsciLexerGLSL::StyleType::DATATYPE; }
[ibu]?vec[234]/.?                                         { return QsciLexerGLSL::StyleType::DATATYPE; }
mat[234](x[234])?/.?                                      { return QsciLexerGLSL::StyleType::DATATYPE; }
(u?int)|"float"|"bool"|"void"/.?                          { return QsciLexerGLSL::StyleType::DATATYPE; }

"//".*                        { return QsciLexerGLSL::StyleType::COMMENT; }
^#.*                          { return QsciLexerGLSL::StyleType::HASHCOMMENT; }
[ \t\n\r]                     { return QsciLexerGLSL::StyleType::WHITESPACE; }

[\*\+\-\/\>\<\%\^\|\&\!\=]?\=? |
&&   |
\|\| |
\^\^ |
\.\= |
\?:  |
">>"|"<<"\=?                  { return QsciLexerGLSL::StyleType::OPERATOR; }

[Tt]rue |
[Ff]alse |
-?+?[0-9]+"."?[0-9]*f?l?u?    { return QsciLexerGLSL::StyleType::NUMBER; }

[a-zA-Z0-9]+/\(               { return QsciLexerGLSL::StyleType::FUNCTION; }
[\(\)\{\}\[\]] |
[#@\?:;,_\~\\] |
[a-zA-Z0-9]+   |
"."                           { return QsciLexerGLSL::StyleType::DEFAULT; }

�*                            {
                                yyleng = 1;
                                return QsciLexerGLSL::StyleType::ILLEGAL;
                              }
.                             { return QsciLexerGLSL::StyleType::ILLEGAL; }


%%

int yyFlexLexer::yywrap()   { return 1;}
