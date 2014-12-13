#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
	: _shaderCount(2), _id(0), _shaders(new Shader[2], std::default_delete<Shader[]>())
{
	_shaders[0].path = vertexShaderPath;
	_shaders[0].type = GL_VERTEX_SHADER;
	_shaders[1].path = fragmentShaderPath;
	_shaders[1].type = GL_FRAGMENT_SHADER;
}

ShaderProgram::~ShaderProgram()
{
}