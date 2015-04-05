#include <vector>
#include <sstream>
#include <iostream>
#include "VertexAttribute.hpp"

using namespace rffalcon;

VertexAttribute::VertexAttribute(const std::string &name, GLint size, GLenum type, GLboolean normalized)
	: _name(name), _size(size), _type(type), _normalized(normalized)
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
