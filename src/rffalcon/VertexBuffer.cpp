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

	for (size_t index = 0; index < MAX_VERTEX_ATTRIBUTES; ++index)
	{
		_attributes[index] = nullptr;
	}

	if (_vaoId > 0) {
		glDeleteVertexArrays(1, &_vaoId);
		_vaoId = 0;
	}

	if (_verticesId > 0) {
		glDeleteBuffers(1, &_verticesId);
	}

	if (_indicesId > 0) {
		glDeleteBuffers(1, &_indicesId);
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
	glBindVertexArray(0);

	if (_state != CLEAN)
	{
		_upload();
		_state = CLEAN;
	}

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	GLint programId;
	glGetIntegerv(GL_CURRENT_PROGRAM, &programId);
	glUseProgram(_shaderProgramId);

	rffalcon::Matrix4x4 mc_ec, ec_dc;
	_getMatrices(mc_ec, ec_dc);
	float mc_ec_cm[16];
	mc_ec.copyToColumnMajor(mc_ec_cm);
	glUniformMatrix4fv(_ppuLoc_mc_ec, 1, GL_FALSE, mc_ec_cm);
	float ec_dc_cm[16];
	ec_dc.copyToColumnMajor(ec_dc_cm);
	glUniformMatrix4fv(_ppuLoc_ec_dc, 1, GL_FALSE, ec_dc_cm);

	glUniform1i(_ppuLoc_texture, 0);

#ifndef __EMSCRIPTEN__
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif

	if (_vaoId == 0)
	{
		glGenVertexArrays(1, &_vaoId);
		glBindVertexArray(_vaoId);
		glBindBuffer(GL_ARRAY_BUFFER, _verticesId);
		for (int index = 0; index < MAX_VERTEX_ATTRIBUTES; ++index)
		{
			std::shared_ptr<VertexAttribute> attribute = _attributes[index];
			if (attribute != nullptr)
			{
				attribute->enable();
			}
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		if (_indices.size() > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesId);
		}
	}

	glBindVertexArray(_vaoId);
}

void VertexBuffer::_renderFinish()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexBuffer::_upload()
{
	if (_state != FROZEN)
	{
		if (_verticesId == 0)
		{
			glGenBuffers(1, &_verticesId);
		}

		if (_indicesId == 0)
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
	glBindVertexArray(_vaoId);
	glBindBuffer(GL_ARRAY_BUFFER, _verticesId);
	
	char* buffer = new char[vSize]();
	for (size_t index = 0; index < _vertices.size(); ++index) {
		memcpy(buffer + index * _stride, _vertices[index], _stride);
	}

	if (vSize != _gpuVSize)
	{
		glBufferData(GL_ARRAY_BUFFER, vSize, buffer, GL_DYNAMIC_DRAW);
		_gpuVSize = vSize;
	}
	else
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, vSize, buffer);
	}

	delete[] buffer;

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::_uploadIndices()
{
	size_t iSize = _indices.size() * sizeof(GLuint);
	size_t indexSize = sizeof(GLuint);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesId);

	char *buffer = new char[iSize]();
	for (size_t index = 0; index < _indices.size(); ++index) {
		memcpy(buffer + index * indexSize, &_indices[index], indexSize);
	}

	if (iSize != _gpuISize)
	{
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, iSize, buffer, GL_DYNAMIC_DRAW);
		_gpuISize = iSize;
	}
	else
	{
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, iSize, buffer);
	}

	delete[] buffer;

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
