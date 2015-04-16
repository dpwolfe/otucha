#pragma once

#include <string>

#include "ModelView.hpp"
#include "ShaderProgram.hpp"
#include "PhongMaterial.hpp"

namespace terasca
{
	class ModelViewWithShader : public ModelView
	{
	public:
		ModelViewWithShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
		virtual ~ModelViewWithShader();

		virtual void renderModels();

	private:
		void _initGLSLVariableLocations();
		void _setPhongMaterial(std::shared_ptr<rffalcon::PhongMaterial> material);

		std::shared_ptr<ShaderProgram> _shaderProgram = nullptr;
		GLuint _shaderProgramId = 0;
		GLint _ppuLoc_mc_ec = -2;
		GLint _ppuLoc_ec_dc = -2;
		GLint _ppuLoc_normal_mat = -2;
		GLint _ppuLoc_ka = -2;
		GLint _ppuLoc_kd = -2;
		GLint _ppuLoc_ks = -2;
		GLint _ppuLoc_m = -2;
		GLint _ppuLoc_a = -2;
		GLint _ppuLoc_texture = -2;
		GLint _pvaLoc_mcPosition = -2;
		GLint _pvaLoc_mcNormal = -2;
	};
}
