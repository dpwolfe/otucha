#include "ModelViewWithShader.h"

std::string ModelViewWithShader::_vertexShaderPath = "";
std::string ModelViewWithShader::_fragmentShaderPath = "";
ShaderProgram* ModelViewWithShader::_shaderProgram = nullptr;
GLuint ModelViewWithShader::_shaderProgramId = 0;
int ModelViewWithShader::_instanceCount = 0;


ModelViewWithShader::ModelViewWithShader()
{
	if (_shaderProgram == 0)
	{
		_shaderProgram = new ShaderProgram(_vertexShaderPath, _fragmentShaderPath);
		_shaderProgramId = _shaderProgram->getId();
	}
	_instanceCount++;
}

ModelViewWithShader::~ModelViewWithShader()
{

}

void ModelViewWithShader::setShaderSources(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	_vertexShaderPath = vertexShaderPath;
	_fragmentShaderPath = fragmentShaderPath;
}