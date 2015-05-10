#pragma once

#include <string>
#include <GL/glew.h>
#include <vector>

#include "AffinePoint.hpp"
#include "AffineVector.hpp"
#include "ProjectionType.hpp"
#include "Matrix4x4.hpp"
#include "ModelBase.hpp"

namespace terasca
{
	class ModelView
	{
	public:
		ModelView();
		virtual ~ModelView();

		virtual void renderModels() = 0;
		virtual void handleCommand(unsigned char key, double ldsX, double ldsY) { }
		virtual void getMCBoundingBox(double* xyzBounds) const;
		void addModel(std::shared_ptr<rffalcon::ModelBase> model);
		void setProjectionType(ProjectionType type);
		const double* getMCRegionOfInterest() const;
		void setMCRegionOfInterest(double xyz[6]);
		void setEyeCenterUp(rffalcon::AffinePoint eye, rffalcon::AffinePoint center, rffalcon::AffineVector up);
		void setZProjectionPlane(double zpp);
		void setEyeCoordinatesZMinZMax(double zMin, double zMax);

	protected:
		ProjectionType _projectionType = PERSPECTIVE;

		void _getMatrices(rffalcon::Matrix4x4& mc_ec, rffalcon::Matrix4x4& ec_dc);

		double _mcRegionOfInterest[6];
		rffalcon::AffinePoint _eye = rffalcon::AffinePoint(0, 0, 2);
		rffalcon::AffinePoint _center = rffalcon::AffinePoint(0, 0, 0);
		rffalcon::AffineVector _up = rffalcon::AffineVector(0, 1, 0);
		double _zProjectionPlane = -1.0;
		double _eyeCoordinatesZMin = -2.0;
		double _eyeCoordinatesZMax = -0.01;
		rffalcon::Matrix4x4 _dynamicView;
		std::vector<std::shared_ptr<rffalcon::ModelBase>> _models;
		
		static GLint _getUniformLocation(GLuint programId, const std::string& name);
		static GLint _getAttribLocation(GLuint progrmId, const std::string& name);
	};
}

