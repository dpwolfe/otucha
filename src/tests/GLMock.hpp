#pragma once

#include <gmock/gmock.h>

#if defined(_WIN32)
  #if defined(__MINGW32__) || defined(__CYGWIN__)
    #define _GLAPI extern
  #else
    #define _GLAPI __declspec(dllexport)
  #endif
#else
  #define _GLAPI extern
#endif
#define GLAPI
#include <GL/glew.h>
#define GLAPI

#include <memory>

class GLMock {
public:
	static std::shared_ptr<GLMock> getSingleton();
	static std::shared_ptr<GLMock> _singleton;

	GLMock();
	~GLMock();
	MOCK_METHOD2(glBindTextureMock, void(GLenum target, GLuint texture));
	MOCK_METHOD1(glEnableVertexAttribArrayMock, void(GLuint arg0));
	MOCK_METHOD2(glGetAttribLocationMock, int(GLuint program, const GLchar* name));
	MOCK_METHOD2(glGetIntegervMock, void(GLenum pname, GLint* params));
	MOCK_METHOD2(glGenTexturesMock, void(GLsizei n, GLuint* textures));
	MOCK_METHOD6(glVertexAttribPointerMock, void(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer));
	MOCK_METHOD9(glTexImage2DMock, void(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels));
	MOCK_METHOD3(glTexParameteriMock, void(GLenum target, GLenum pname, GLint param));
};
