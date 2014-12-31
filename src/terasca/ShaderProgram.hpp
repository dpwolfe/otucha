#pragma once

#include <string>
#include <memory>

#include <GL/glew.h>
#ifdef _WIN32
    #include <GL/gl.h>
#elif __APPLE__
    #include <OpenGL/gl.h>
#endif

class ShaderProgram
{
public:
	ShaderProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	virtual ~ShaderProgram();

	int getId() const { return _id; }
	void link();

private:
	struct Shader
	{
		std::string path;
		GLenum type;
		std::string source;
		int id;

		Shader() : path(""), type(0), source(""), id(0) {}
	};

	int _id;
	int _shaderCount;
	std::unique_ptr<Shader[]> _shaders;

	void initialize();
	void loadShaderSource(Shader& shader);
	void dispose();
	void compileShader(Shader& shader);
	void readFailLog(GLint id);
};
