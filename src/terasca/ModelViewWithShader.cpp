#include "ModelViewWithShader.hpp"

std::string ModelViewWithShader::_vertexShaderPath = "";
std::string ModelViewWithShader::_fragmentShaderPath = "";
std::shared_ptr<ShaderProgram> ModelViewWithShader::_shaderProgram = nullptr;
GLuint ModelViewWithShader::_shaderProgramId = 0;
int ModelViewWithShader::_instanceCount = 0;
GLint ModelViewWithShader::_ppuLoc_mc_ec = -2;
GLint ModelViewWithShader::_ppuLoc_ec_dc = -2;
GLint ModelViewWithShader::_ppuLoc_normal_mat = -2;
GLint ModelViewWithShader::_ppuLoc_ka = -2;
GLint ModelViewWithShader::_ppuLoc_kd = -2;
GLint ModelViewWithShader::_ppuLoc_ks = -2;
GLint ModelViewWithShader::_ppuLoc_m = -2;
GLint ModelViewWithShader::_ppuLoc_a = -2;
GLint ModelViewWithShader::_pvaLoc_mcPosition = -2;
GLint ModelViewWithShader::_pvaLoc_mcNormal = -2;


ModelViewWithShader::ModelViewWithShader()
{
	if (_shaderProgram == 0)
	{
		_shaderProgram = std::make_shared<ShaderProgram>(_vertexShaderPath, _fragmentShaderPath);
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
	glBindAttribLocation(_shaderProgramId, 0, "mcPosition");
	_pvaLoc_mcPosition = 0;
	_shaderProgram->link();
	_ppuLoc_mc_ec = _getUniformLocation(_shaderProgramId, "mc_ec");
	_ppuLoc_ec_dc = _getUniformLocation(_shaderProgramId, "ec_dc");
	_ppuLoc_normal_mat = _getUniformLocation(_shaderProgramId, "normal_mat");
	_ppuLoc_ka = _getUniformLocation(_shaderProgramId, "ka");
	_ppuLoc_kd = _getUniformLocation(_shaderProgramId, "kd");
	_ppuLoc_ks = _getUniformLocation(_shaderProgramId, "ks");
	_ppuLoc_m = _getUniformLocation(_shaderProgramId, "m");
	_ppuLoc_a = _getUniformLocation(_shaderProgramId, "a");
	_pvaLoc_mcNormal = _getAttribLocation(_shaderProgramId, "mcNormal");
}
