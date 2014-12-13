#include "ShaderProgram.h"

#include <fstream>
#include <iostream>

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

void ShaderProgram::initShaders()
{
	for (int i = 0; i < _shaderCount; i++)
	{
		if (loadShaderSource(_shaders[i]))
		{

		}
	}
}

bool ShaderProgram::loadShaderSource(Shader shader)
{
	bool result = false;
	std::ifstream in(shader.path, std::ios::in | std::ios::binary);
	if (in)
	{
		in.seekg(0, std::ios::end);
		shader.source.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&shader.source[0], shader.source.size());
		in.close();
		result = true;
	}
	else
	{
		std::cerr << "Could not open file for reading: " + shader.path;
		throw(errno);
	}
	return result;
}
