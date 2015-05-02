#include <vector>
#include <sstream>
#include <iostream>
#include "VertexAttribute.hpp"

using namespace rffalcon;

VertexAttribute::VertexAttribute(const std::string &name, GLint size, GLenum type, GLboolean isNormalized)
	: _name(name), _size(size), _type(type), _isNormalized(isNormalized)
{
}

VertexAttribute::~VertexAttribute()
{
}

std::shared_ptr<VertexAttribute> VertexAttribute::parse(const std::string &format)
{
	std::shared_ptr<VertexAttribute> attribute = nullptr;

	std::vector<std::string> formatParts;
	std::stringstream formatStringStream(format);
	std::string formatPart;
	while (std::getline(formatStringStream, formatPart, ':'))
	{
		formatParts.push_back(formatPart);
	}

	if (formatParts.size() == 2 && formatParts[0].length() > 0 && formatParts[1].length() >= 2)
	{
		std::string name = formatParts[0];
		GLint size = formatParts[1][0] - '0';
		char typeChar = formatParts[1][1];
		GLenum type = _getType(typeChar);
		GLboolean normalized = formatParts[1].length() > 2 && formatParts[1][2] == 'n' ? 1 : 0;
		attribute = std::make_shared<VertexAttribute>(name, size, type, normalized);
	}
	else
	{
		std::cerr << "Invalid vertex attribute format: " << format << std::endl;
	}

	return attribute;
}

std::string VertexAttribute::getName()
{
	return _name;
}

GLint VertexAttribute::getSize()
{
	return _size;
}

GLenum VertexAttribute::getType()
{
	return _type;
}

GLboolean VertexAttribute::getIsNormalized()
{
	return _isNormalized;
}

int VertexAttribute::getTypeSize()
{
	switch (_type)
	{
	case GL_BOOL: return sizeof(GLboolean);
	case GL_BYTE: return sizeof(GLbyte);
	case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
	case GL_SHORT: return sizeof(GLshort);
	case GL_UNSIGNED_SHORT: return sizeof(GLushort);
	case GL_INT: return sizeof(GLint);
	case GL_UNSIGNED_INT: return sizeof(GLuint);
	case GL_FLOAT: return sizeof(GLfloat);
	default: return 0;
	}
}

void VertexAttribute::setStride(int stride)
{
	_stride = stride;
}

void VertexAttribute::setPointer(GLchar *pointer)
{
	_pointer = pointer;
}

GLenum VertexAttribute::_getType(char typeChar)
{
	switch (typeChar)
	{
	case 'b': return GL_BYTE;
	case 'B': return GL_UNSIGNED_BYTE;
	case 's': return GL_SHORT;
	case 'S': return GL_UNSIGNED_SHORT;
	case 'i': return GL_INT;
	case 'I': return GL_UNSIGNED_INT;
	case 'f': return GL_FLOAT;
	default: return 0;
	}
}

void VertexAttribute::enable()
{
	if (_index == -1)
	{
		GLint program;
		glGetIntegerv(GL_CURRENT_PROGRAM, &program);
		if (program != 0)
		{
			_index = glGetAttribLocation(program, _name.c_str());
		}
	}

	if (_index != -1)
	{
		glEnableVertexAttribArray(_index);
		glVertexAttribPointer(_index, _size, _type, _isNormalized, _stride, _pointer);
	}
}
