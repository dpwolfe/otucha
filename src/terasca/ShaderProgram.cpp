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
	initialize();
}

ShaderProgram::~ShaderProgram()
{
}

void ShaderProgram::initialize()
{
	_id = glCreateProgram();
	for (int i = 0; i < _shaderCount; i++)
	{
		loadShaderSource(_shaders[i]);
		compileShader(_shaders[i]);
		glAttachShader(_id, _shaders[i].id);
	}
}

void ShaderProgram::link()
{
	glLinkProgram(_id);
	GLint linked;
	glGetProgramiv(_id, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		std::cerr << "Shader program failed to link." << std::endl;
		readFailLog(_id);
		dispose();
	}
}

void ShaderProgram::loadShaderSource(Shader& shader)
{
	std::ifstream in(shader.path, std::ios::in | std::ios::binary);
	if (in)
	{
		in.seekg(0, std::ios::end);
		shader.source.resize(static_cast<unsigned int>(in.tellg()));
		in.seekg(0, std::ios::beg);
		in.read(&shader.source[0], shader.source.size());
		in.close();
	}
	else
	{
		std::cerr << "Could not open file for reading: " + shader.path;
		dispose();
		throw(errno);
	}
}

void ShaderProgram::compileShader(Shader& shader)
{
	shader.id = glCreateShader(shader.type);
	const char* src = shader.source.c_str();
	glShaderSource(shader.id, 1, &src, nullptr);
	glCompileShader(shader.id);

	GLint compiled;
	glGetShaderiv(shader.id, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		std::cerr << "Failed to compile shader: " << shader.path << std::endl;
		readFailLog(shader.id);
		dispose();
		throw(errno);
	}
}

void ShaderProgram::readFailLog(GLint id)
{
	GLint logSize;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logSize);
	if (logSize <= 0)
	{
		std::cerr << "No log available." << std::endl;
	}
	else
	{
		try
		{
			std::unique_ptr<char[]> log(new char[logSize], std::default_delete<char[]>());
			glGetShaderInfoLog(id, logSize, nullptr, log.get());
			std::cerr << "Error Log: " << log.get() << "'" << std::endl;
		}
		catch (std::bad_alloc ex)
		{
			std::cerr << "Unable to allocate error log buffer of size: " << logSize << std::endl;
		}
	}
}

void ShaderProgram::dispose()
{
	for (int i = 0; i < _shaderCount; i++)
	{
		int shaderId = _shaders[i].id;
		if (shaderId > 0)
		{
			if (glIsShader(shaderId))
			{
				glDeleteShader(shaderId);
			}
			_shaders[i].id = 0;
		}
		if (_id > 0)
		{
			if (glIsProgram(_id))
			{
				glDeleteProgram(_id);
			}
			_id = 0;
		}
		_shaderCount = 0;
	}
}