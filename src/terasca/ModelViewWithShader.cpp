#include "ModelViewWithShader.hpp"
#include "Matrix3x3.hpp"

using namespace terasca;

ModelViewWithShader::ModelViewWithShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	_shaderProgram = std::make_shared<ShaderProgram>(vertexShaderPath, fragmentShaderPath);
	_shaderProgramId = _shaderProgram->getId();
	_initGLSLVariableLocations();
}

ModelViewWithShader::~ModelViewWithShader()
{
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
	_ppuLoc_texture = _getUniformLocation(_shaderProgramId, "texture");
	_pvaLoc_mcNormal = _getAttribLocation(_shaderProgramId, "mcNormal");
	
	glVertexAttribPointer(_pvaLoc_mcPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(_pvaLoc_mcPosition);
	glDisableVertexAttribArray(_pvaLoc_mcNormal);
}

void ModelViewWithShader::renderModels()
{
	glUseProgram(_shaderProgramId);

	rffalcon::Matrix4x4 mc_ec, ec_dc;
	_getMatrices(mc_ec, ec_dc);
	float mc_ec_cm[16];
	mc_ec.copyToColumnMajor(mc_ec_cm);
	glUniformMatrix4fv(_ppuLoc_mc_ec, 1, GL_FALSE, mc_ec_cm);
	float ec_dc_cm[16];
	ec_dc.copyToColumnMajor(ec_dc_cm);
	glUniformMatrix4fv(_ppuLoc_ec_dc, 1, GL_FALSE, ec_dc_cm);

	rffalcon::Matrix3x3 normal_mat = rffalcon::Matrix3x3(mc_ec).inverse().transpose();
	float normal_mat_cm[9];
	normal_mat.copyToColumnMajor(normal_mat_cm);
	glUniformMatrix3fv(_ppuLoc_normal_mat, 1, GL_FALSE, normal_mat_cm);

#ifndef __EMSCRIPTEN__
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif

	for (size_t index = 0; index < _models.size(); ++index)
	{
		std::shared_ptr<rffalcon::PhongMaterial> material = _models[index]->getPhongMaterial();
		if (material != nullptr)
		{
			_setPhongMaterial(material);
		}
		_models[index]->render();
	}
}

void ModelViewWithShader::_setPhongMaterial(std::shared_ptr<rffalcon::PhongMaterial> material)
{
	glUniform3fv(_ppuLoc_ka, 1, material->ka);
	glUniform3fv(_ppuLoc_kd, 1, material->kd);
	glUniform3fv(_ppuLoc_ks, 1, material->ks);
	glUniform1f(_ppuLoc_m, material->m);
	glUniform1f(_ppuLoc_a, material->a);
}