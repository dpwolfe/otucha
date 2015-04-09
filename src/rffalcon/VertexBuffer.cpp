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
	_parseAttributes(formatParts);
	_vertices = std::vector<char*>();
	_indices = std::vector<GLuint>();
	_items = std::vector<rffalcon::ivec4>();
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

void VertexBuffer::push(const std::shared_ptr<std::vector<void*>> vertices, const std::shared_ptr<std::vector<GLuint>> indices)
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
	rffalcon::ivec4 item = { { vstart, vertexCount, istart, indexCount } };
	_items.push_back(item);
	_state = DIRTY;
}

void VertexBuffer::_parseAttributes(const std::vector<std::string> &formatParts)
{
	GLchar *pointer = 0;
	for (size_t index = 0; index < MAX_VERTEX_ATTRIBUTES && index < formatParts.size(); ++index)
	{
		std::shared_ptr<VertexAttribute> attribute = VertexAttribute::parse(formatParts[index]);
		attribute->setPointer(pointer);
		int typeSizeDelta = attribute->getSize() * attribute->getTypeSize();
		_stride += typeSizeDelta;
		pointer += typeSizeDelta;
		_attributes[index] = attribute;
	}
	for (size_t index = 0; index < MAX_VERTEX_ATTRIBUTES && index < formatParts.size(); ++index)
	{
		_attributes[index]->setStride(_stride);
	}
}

void VertexBuffer::_pushVertices(const std::shared_ptr<std::vector<void*>> vertices)
{
	for (size_t index = 0; index < vertices->size(); ++index)
	{
		char *vertex = new char[_stride];
		memcpy(vertex, (*vertices)[index], _stride);
		_vertices.push_back(vertex);
	}
	_state |= DIRTY;
}

void VertexBuffer::_pushIndices(const std::shared_ptr<std::vector<GLuint>> indices)
{
	for (size_t index = 0; index < indices->size(); ++index)
	{
		_indices.push_back((*indices)[index]);
	}
	_state |= DIRTY;
}

void VertexBuffer::render()
{
	size_t vCount = _vertices.size();
	size_t iCount = _indices.size();
	_renderSetup();
	if (iCount > 0)
	{
		glDrawElements(_mode, iCount, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(_mode, 0, vCount);
	}
	_renderFinish();
}

void VertexBuffer::_renderSetup()
{
	if (_state != CLEAN)
	{
		_upload();
		_state = CLEAN;
	}

	glBindBuffer(GL_ARRAY_BUFFER, _verticesId);
	for (int index = 0; index < MAX_VERTEX_ATTRIBUTES; ++index)
	{
		std::shared_ptr<VertexAttribute> attribute = _attributes[index];
		if (attribute != nullptr)
		{
			attribute->enable();
		}
	}

	if (_indices.size() > 0)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesId);
	}
}

void VertexBuffer::_renderFinish()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexBuffer::_upload()
{
	if (_state != FROZEN)
	{
		if (!_verticesId)
		{
			glGenBuffers(1, &_verticesId);
		}

		if (!_indicesId)
		{
			glGenBuffers(1, &_indicesId);
		}

		// Upload vertices first to guarantee indices always point to valid data
		_uploadVertices();
		_uploadIndices();
	}
}

void VertexBuffer::_uploadVertices()
{
	size_t vSize = _vertices.size() * _stride;
	glBindBuffer(GL_ARRAY_BUFFER, _verticesId);
	if (vSize != _gpuVSize)
	{
		glBufferData(GL_ARRAY_BUFFER, vSize, _vertices.data(), GL_DYNAMIC_DRAW);
		_gpuVSize = vSize;
	}
	else
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, vSize, _vertices.data());
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::_uploadIndices()
{
	size_t iSize = _indices.size() * sizeof(GLuint);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesId);
	if (iSize != _gpuISize)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize, _indices.data(), GL_DYNAMIC_DRAW);
		_gpuISize = iSize;
	}
	else
	{
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, iSize, _indices.data());
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexBuffer::getMCBoundingBox(double *xyzBounds) const
{
	xyzBounds[0] = 0;
	xyzBounds[1] = 512;
	xyzBounds[2] = 0;
	xyzBounds[3] = 512;
	xyzBounds[4] = -1;
	xyzBounds[5] = 1;
}