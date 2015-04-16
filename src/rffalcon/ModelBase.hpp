#pragma once

#include <memory>
#include <GL/glew.h>
#include "PhongMaterial.hpp"

namespace rffalcon
{
	class ModelBase
	{
	public:
		ModelBase();
		virtual ~ModelBase();

		virtual void getMCBoundingBox(double* xyzBounds) const = 0;
		virtual void render() = 0;
		std::shared_ptr<PhongMaterial> getPhongMaterial();

	protected:
		std::shared_ptr<PhongMaterial> _phongMaterial = nullptr;
	};
}