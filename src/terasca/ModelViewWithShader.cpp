#include "ModelViewWithShader.h"

std::string ModelViewWithShader::_vertexShaderPath = "";
std::string ModelViewWithShader::_fragmentShaderPath = "";
ShaderProgram* ModelViewWithShader::_shaderProgram = nullptr;
GLuint ModelViewWithShader::_shaderProgramId = 0;
int ModelViewWithShader::_instanceCount = 0;
GLint ModelViewWithShader::_ppuLoc_mc_ec = -2;
GLint ModelViewWithShader::_ppuLoc_ec_dc = -2;
GLint ModelViewWithShader::_ppuLoc_kd = -2;
GLint ModelViewWithShader::_pvaLoc_mcPosition = -2;
GLint ModelViewWithShader::_pvaLoc_mcNormal = -2;


ModelViewWithShader::ModelViewWithShader()
{
	if (_shaderProgram == 0)
	{
		_shaderProgram = new ShaderProgram(_vertexShaderPath, _fragmentShaderPath);
		_shaderProgramId = _shaderProgram->getId();
		_initGLSLVariableLocations();
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

void ModelViewWithShader::_initGLSLVariableLocations()
{
	_ppuLoc_mc_ec = _getUniformLocation(_shaderProgramId, "mc_ec");
	_ppuLoc_ec_dc = _getUniformLocation(_shaderProgramId, "ec_dc");
	_ppuLoc_kd = _getUniformLocation(_shaderProgramId, "kd");
	_pvaLoc_mcPosition = _getAttribLocation(_shaderProgramId, "mcPosition");
	_pvaLoc_mcNormal = _getAttribLocation(_shaderProgramId, "mcNormal");
}