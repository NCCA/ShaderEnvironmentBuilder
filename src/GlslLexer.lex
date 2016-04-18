/*
//----------------------------------------------------------------------------------------------------------------------
/// @file GlslLexer.lex
/// @brief Flex definitions for generating the GLSL lexer
//----------------------------------------------------------------------------------------------------------------------
*/

%option c++

%{
	#include <vector>
	#include <sstream>
  #include "QsciLexerGlsl.h"
%}

%s LEXSTRING

%%
<LEXSTRING>[^"]*                    { return QsciLexerGLSL::StyleType::STRING; }
<LEXSTRING>[\"\n]                   {
                                      BEGIN(INITIAL);
                                      return QsciLexerGLSL::StyleType::STRING;
                                    }
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
"struct"                            { return QsciLexerGLSL::StyleType::KEYWORD; }

(?#/* "/." added to override function rule*/)
[iu]?sampler(([123]D)|Cube)|([12]DArray)|2DRect|Buffer/.  { return QsciLexerGLSL::StyleType::DATATYPE; }
sampler(([123]D)|Cube)|([12]DArray)|((2DRect)Shadow)/.    { return QsciLexerGLSL::StyleType::DATATYPE; }
[ibu]?vec[234]/.                                          { return QsciLexerGLSL::StyleType::DATATYPE; }
mat[234](x[234])?/.                                       { return QsciLexerGLSL::StyleType::DATATYPE; }
(u?int)|"float"|"bool"|"void"/.                           { return QsciLexerGLSL::StyleType::DATATYPE; }

"//".*                              { return QsciLexerGLSL::StyleType::COMMENT; }
[ \t\n\r]                           { return QsciLexerGLSL::StyleType::WHITESPACE; }

[\*\+\-\/\>\<\%\^\|\&\!\=]?\=? |
&&   |
\|\| |
\^\^ |
\.\= |
">>"|"<<"\=?                        { return QsciLexerGLSL::StyleType::OPERATOR; }

\"                                  {
                                      BEGIN(LEXSTRING);
                                      return QsciLexerGLSL::StyleType::STRING;
                                    }

[Tt]rue |
[Ff]alse |
-?+?[0-9]+"."?[0-9]*f?l?u?          { return QsciLexerGLSL::StyleType::NUMBER; }

[a-zA-Z0-9]+/\(                     { return QsciLexerGLSL::StyleType::FUNCTION; }
[\(\)\{\}\[\]] |
[#@;,_]        |
[a-zA-Z0-9]+   |
"."            |
à                                   { return QsciLexerGLSL::StyleType::DEFAULT; }


%%

int yyFlexLexer::yywrap()   { return 1;}
