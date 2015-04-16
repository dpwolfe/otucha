#pragma once

#include <string>
#include <GL/glew.h>

#include "AffinePoint.hpp"
#include "AffineVector.hpp"
#include "ProjectionType.hpp"
#include "Matrix4x4.hpp"

class ModelView
{
public:
	ModelView();
	virtual ~ModelView();

	virtual void renderModels() = 0;
	virtual void handleCommand(unsigned char key, double ldsX, double ldsY) { }
	virtual void getMCBoundingBox(double* xyzBounds) const = 0;

	static void setMCRegionOfInterest(double xyz[6]);
	static void setEyeCenterUp(rffalcon::AffinePoint eye, rffalcon::AffinePoint center, rffalcon::AffineVector up);
	static void setProjectionType(ProjectionType type);
	static void setZProjectionPlane(double zpp);
	static void setEyeCoordinatesZMinZMax(double zMin, double zMax);

protected:
	static void _getMatrices(rffalcon::Matrix4x4& mc_ec, rffalcon::Matrix4x4& ec_dc);
	static GLint _getUniformLocation(GLuint programId, const std::string& name);
	static GLint _getAttribLocation(GLuint progrmId, const std::string& name);

	static double _mcRegionOfInterest[6];
	static rffalcon::AffinePoint _eye, _center;
	static rffalcon::AffineVector _up;
	static ProjectionType _projectionType;
	static double _zProjectionPlane;
	static double _eyeCoordinatesZMin;
	static double _eyeCoordinatesZMax;
	static rffalcon::Matrix4x4 _dynamicView;
};
