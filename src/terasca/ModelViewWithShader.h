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

protected:
	static GLuint _shaderProgramId;

private:
	static std::string _vertexShaderPath, _fragmentShaderPath;
	static ShaderProgram* _shaderProgram;
	static int _instanceCount;
};