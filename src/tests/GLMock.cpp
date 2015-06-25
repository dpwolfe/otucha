#include "GLMock.hpp"

std::shared_ptr<GLMock> GLMock::_singleton = nullptr;

GLMock::GLMock()
{
}

GLMock::~GLMock()
{
}

std::shared_ptr<GLMock> GLMock::getSingleton()
{
	if (_singleton == nullptr)
	{
		_singleton = std::make_shared<GLMock>();
	}
	return _singleton;
}

GLAPI void GLAPIENTRY glBindTexture(GLenum target, GLuint texture)
{
	return GLMock::getSingleton()->glBindTextureMock(target, texture);
}

GLAPI void GLAPIENTRY glEnableVertexAttribArrayMock(GLuint arg0)
{
	return GLMock::getSingleton()->glEnableVertexAttribArrayMock(arg0);
}
PFNGLENABLEVERTEXATTRIBARRAYPROC __glewEnableVertexAttribArray = glEnableVertexAttribArrayMock;

GLAPI int GLAPIENTRY glGetAttribLocationMock(GLuint program, const GLchar * name)
{
	return GLMock::getSingleton()->glGetAttribLocationMock(program, name);
}
PFNGLGETATTRIBLOCATIONPROC __glewGetAttribLocation = glGetAttribLocationMock;

GLAPI void GLAPIENTRY glGetIntegerv(GLenum pname, GLint* params)
{
	return GLMock::getSingleton()->glGetIntegervMock(pname, params);
}

GLAPI void GLAPIENTRY glGenTextures(GLsizei n, GLuint* textures)
{
	return GLMock::getSingleton()->glGenTexturesMock(n, textures);
}

GLAPI void GLAPIENTRY glVertexAttribPointerMock(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer)
{
	return GLMock::getSingleton()->glVertexAttribPointerMock(index, size, type, normalized, stride, pointer);
}
PFNGLVERTEXATTRIBPOINTERPROC __glewVertexAttribPointer = glVertexAttribPointerMock;

GLAPI void GLAPIENTRY glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels)
{
	return GLMock::getSingleton()->glTexImage2DMock(target, level, internalformat, width, height, border, format, type, pixels);
}

GLAPI void GLAPIENTRY glTexParameteri(GLenum target, GLenum pname, GLint param)
{
	return GLMock::getSingleton()->glTexParameteriMock(target, pname, param);
}
