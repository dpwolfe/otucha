#pragma once

#include <string>
#include <memory>
#include <GL/glew.h>

#define MAX_VERTEX_ATTRIBUTES 16

namespace rffalcon
{
	class VertexAttribute
	{
	public:
		VertexAttribute(const std::string &name, GLint size, GLenum type, GLboolean isNormalized);
		~VertexAttribute();

		static std::shared_ptr<VertexAttribute> parse(const std::string &part);

		std::string getName();
		GLint getSize();
		GLenum getType();
		GLboolean getIsNormalized();
		int getTypeSize();
		void setStride(int stride);
		void setPointer(GLchar *pointer);
		void enable();

	private:
		static GLenum _getType(char typeChar);

		GLuint _index = -1;
		std::string _name;
		GLint _size;
		GLenum _type;
		GLboolean _isNormalized;
		GLsizei _stride = 0;
		GLchar *_pointer = 0;
	};
}