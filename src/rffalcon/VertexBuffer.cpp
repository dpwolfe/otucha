#include "VertexBuffer.hpp"

#include <vector>
#include <sstream>

using namespace rffalcon;

VertexBuffer::VertexBuffer(const std::string &format) : _format(format)
{
	for (int index = 0; index < MAX_VERTEX_ATTRIBUTES; ++index)
	{
		_attributes[index] = nullptr;
	}

	std::vector<std::string> formatParts;
	std::stringstream formatStringStream(format);
	std::string formatPart;
	while (std::getline(formatStringStream, formatPart, ','))
	{
		formatParts.push_back(formatPart);
	}
	int stride = _parseAttributes(formatParts);
	_vertices = std::vector<char*>();
	_indices = std::vector<GLuint>();
	_items = std::vector<s1::ivec4>();
}

VertexBuffer::~VertexBuffer()
{
	while (_vertices.size() > 0)
	{
		char *vertex = _vertices.back();
		_vertices.pop_back();
		delete[] vertex;
	}
}

int VertexBuffer::_parseAttributes(const std::vector<std::string> &formatParts)
{
	int stride = 0;
	int pointer = 0;
	for (int index = 0; index < MAX_VERTEX_ATTRIBUTES && index < static_cast<int>(formatParts.size()); ++index)
	{
		std::shared_ptr<VertexAttribute> attribute = VertexAttribute::parse(formatParts[index]);
		int typeSizeDelta = attribute->getSize() * attribute->getTypeSize();
		stride += typeSizeDelta;
		pointer += typeSizeDelta;
		_attributes[index] = attribute;
	}
	for (int index = 0; index < MAX_VERTEX_ATTRIBUTES && index < static_cast<int>(formatParts.size()); ++index)
	{
		_attributes[index]->setStride(stride);
	}
	return stride;
}