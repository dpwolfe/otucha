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

void VertexBuffer::push(const std::shared_ptr<std::vector<void *>> vertices, const std::shared_ptr<std::vector<GLuint>> indices)
{
	int vertexCount = vertices->size();
	int indexCount = indices->size();
	_state = FROZEN;
	// push vertices
	int vstart = _vertices.size();
	_pushVertices(vertices);
	// push indices
	int istart = _indices.size();
	_pushIndices(indices);
	// update indices based on new location in buffer
	for (int index = 0; index < indexCount; ++index)
	{
		_indices[istart + index] += static_cast<GLuint>(vstart);
	}
	// insert item
	s1::ivec4 item = { { vstart, vertexCount, istart, indexCount } };
	_items.push_back(item);
	_state = DIRTY;
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

void VertexBuffer::_pushVertices(const std::shared_ptr<std::vector<void *>> vertices)
{
	_state |= DIRTY;
}

void VertexBuffer::_pushIndices(const std::shared_ptr<std::vector<GLuint>> indices)
{
	_state |= DIRTY;
}
