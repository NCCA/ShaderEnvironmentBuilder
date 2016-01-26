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
"float" |
"int" |
"void" |
"bool" |
"true" |
"false" |
"invariant" |
"discard" |
"return" |
"mat2" |
"mat3" |
"mat4" |
"mat2x2" |
"mat2x3" |
"mat2x4" |
"mat3x2" |
"mat3x3" |
"mat3x4" |
"mat4x2" |
"mat4x3" |
"mat4x4" |
"vec2" |
"vec3" |
"vec4" |
"ivec2" |
"ivec3" |
"ivec4" |
"bvec2" |
"bvec3" |
"bvec4" |
"uint" |
"uvec2" |
"uvec3" |
"uvec4" |
"lowp" |
"mediump" |
"highp" |
"precision" |
"sampler1D" |
"sampler2D" |
"sampler3D" |
"samplerCube" |
"sampler1DShadow" |
"sampler2DShadow" |
"samplerCubeShadow" |
"sampler1DArray" |
"sampler2DArray" |
"sampler1DArrayShadow" |
"sampler2DArrayShadow" |
"isampler1D" |
"isampler2D" |
"isampler3D" |
"isamplerCube" |
"isampler1DArray" |
"isampler2DArray" |
"usampler1D" |
"usampler2D" |
"usampler3D" |
"usamplerCube" |
"usampler1DArray" |
"usampler2DArray" |
"sampler2DRect" |
"sampler2DRectShadow" |
"isampler2DRect" |
"usampler2DRect" |
"samplerBuffer" |
"isamplerBuffer" |
"usamplerBuffer" |
"struct"                            { return QsciLexerGLSL::StyleType::KEYWORD; }
"\n"                                { return QsciLexerGLSL::StyleType::NEWLINE; }
[" ""\t"]                           { return QsciLexerGLSL::StyleType::WHITESPACE; }
"*" |
"/" |
"+" |
"-" |
"=" |
"*=" |
"/=" |
"+=" |
"-="   { return QsciLexerGLSL::StyleType::OPERATOR; }
-?+?[0-9]+"."?[0-9]*f?l?u?          { return QsciLexerGLSL::StyleType::NUMBER; }
[a-zA-Z0-9]+                        { return QsciLexerGLSL::StyleType::DEFAULT; }

%%

void test(){
    std::cout<<"test\n";
}
