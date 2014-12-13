#pragma once

#include <string>
#include <GL/glew.h>
#include <GL/gl.h>

#include "ModelView.h"
#include "ShaderProgram.h"

class ModelViewWithShader : public ModelView
{
public:
	ModelViewWithShader();
	virtual ~ModelViewWithShader();

	static void setShaderSources(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

private:
	static std::string _vertexShaderPath, _fragmentShaderPath;
	static ShaderProgram* _shaderProgram;
	static GLuint _shaderProgramId;
	static int _instanceCount;
};