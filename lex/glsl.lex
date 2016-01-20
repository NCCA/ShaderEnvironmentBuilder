/* GLSL Flex lexr */

%option noyywrap
%option c++

%{
	#include <vector>
	#include <sstream>
	enum yytokentype {
		NUMBER = 0,
		KEYWORD = 1,
		FUNCTION = 2,
		STRING = 3,
		COMMENT = 4,
		DISABLED = 5,
		OPERATOR = 6
	};
	int yyloc=0;
	#define YY_USER_ACTION yyloc = yyloc + yyleng;
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
"struct"			{ return KEYWORD; }
.					{ printf(""); }

%%


std::vector<int> lexThis(const char *input)
{	
	FlexLexer* lexer = new yyFlexLexer;
	int tok;
	std::istringstream istr (input);

	std::vector<int> result;

    while ((tok = lexer->yylex(&istr))>0)
	{
		printf("tok=%d yytext=%s position = %d\n", tok, lexer->YYText(),yyloc-lexer->YYLeng());
		result.push_back(tok);
		result.push_back(yyloc-lexer->YYLeng());
		result.push_back(lexer->YYLeng());
	}
	return result;
}

int main()
{
	return EXIT_SUCCESS;
}
