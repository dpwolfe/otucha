#pragma once

#include <string>
#include <memory>
#include <vector>
#include <GL/glew.h>
#include "VertexAttribute.hpp"
#include "vec.hpp"

#define CLEAN  0
#define DIRTY  1
#define FROZEN 2

namespace rffalcon {
	class VertexBuffer {
	public:
		VertexBuffer(const std::string &format);
		~VertexBuffer();

		void push(const std::shared_ptr<std::vector<void *>> vertices, const std::shared_ptr<std::vector<GLuint>> indices);

	private:
		int _parseAttributes(const std::vector<std::string> &formatParts);
		void _pushVertices(const std::shared_ptr<std::vector<void *>> vertices);
		void _pushIndices(const std::shared_ptr<std::vector<GLuint>> indices);

		std::string _format;
		std::shared_ptr<VertexAttribute> _attributes[MAX_VERTEX_ATTRIBUTES];
		std::vector<char*> _vertices;
		std::vector<GLuint> _indices;
		std::vector<s1::ivec4> _items;
		GLuint _verticesId = 0;
		int _gpuVSize = 0;
		GLuint _indicesId = 0;
		int _gpuISize = 0;
		char _state = DIRTY;
		GLenum _mode = GL_TRIANGLES;
	};
}