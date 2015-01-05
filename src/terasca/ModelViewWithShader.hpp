#pragma once

#include <string>

#include "ModelView.hpp"
#include "ShaderProgram.hpp"

class ModelViewWithShader : public ModelView
{
public:
	ModelViewWithShader();
	virtual ~ModelViewWithShader();

	static void setShaderSources(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

protected:
	static GLuint _shaderProgramId;
	static GLint _ppuLoc_mc_ec, _ppuLoc_ec_dc, _ppuLoc_normal_mat;
	static GLint _ppuLoc_ka;
	static GLint _ppuLoc_kd;
	static GLint _ppuLoc_ks;
	static GLint _ppuLoc_m;
	static GLint _ppuLoc_a;
	static GLint _pvaLoc_mcPosition, _pvaLoc_mcNormal;

private:
	static std::string _vertexShaderPath, _fragmentShaderPath;
	static ShaderProgram* _shaderProgram;
	static int _instanceCount;

	static void _initGLSLVariableLocations();
};
