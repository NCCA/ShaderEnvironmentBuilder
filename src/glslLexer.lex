/* GLSL Flex lexr */

%option noyywrap
%option c++

%{
	#include <vector>
	#include <sstream>
    #include "qscilexerglsl.h"
%}


%%
"attribute" |
"const" |
"uniform" |
"varying" |
"layout" |
"centroid" |
"flat" |
"smooth" |
"noperspective" |
"break" |
"continue" |
"do" |
"for" |
"while" |
"switch" |
"case" |
"default" |
"if" |
"else" |
"in" |
"out" |
"inout" |
"return"    |
"invariant" |
["low""medium""high"]"p" |
"discard" |
"precision" |
"struct"            { return QsciLexerGLSL::StyleType::KEYWORD; }

[iu]?sampler(([123]D)|Cube)|([12]DArray)|2DRect|Buffer          |
sampler(([123]D)|Cube)|([12]DArray)|((2DRect)Shadow)            |
[ibu]?vec[234]                                                  |
mat[234](x[234])?                                               |
(u?int)|"float"|"bool"|"void"        { return QsciLexerGLSL::StyleType::DATATYPE; }

"//".*[\n]                          { return QsciLexerGLSL::StyleType::COMMENT; }
[ \t\n\r]                           { return QsciLexerGLSL::StyleType::WHITESPACE; }

[\*\+\-\/\>\<]?"="?                 { return QsciLexerGLSL::StyleType::OPERATOR; }

[Tt]rue |
[Ff]alse |
-?+?[0-9]+"."?[0-9]*f?l?u?          { return QsciLexerGLSL::StyleType::NUMBER; }

[a-zA-Z0-9]+"("                     { return QsciLexerGLSL::StyleType::FUNCTION; }
[\(\)\{\}\[\]] |
[#@;,_]        |
[a-zA-Z0-9]+   |
"."                                 { return QsciLexerGLSL::StyleType::DEFAULT; }

%%

void test(){
    std::cout<<"test\n";
}
