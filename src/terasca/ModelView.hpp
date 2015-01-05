#pragma once

#include <string>
#include <GL/glew.h>
#ifdef _WIN32
    #include <GL/gl.h>
#elif __APPLE__
    #include <OpenGL/gl.h>
#endif

#include "AffinePoint.hpp"
#include "AffineVector.hpp"
#include "ProjectionType.hpp"
#include "Matrix4x4.hpp"

class ModelView
{
public:
	ModelView();
	virtual ~ModelView();

	virtual void render() = 0;
	virtual void handleCommand(unsigned char key, double ldsX, double ldsY) { }
	virtual void getMCBoundingBox(double* xyzBounds) const = 0;

	static void setMCRegionOfInterest(double xyz[6]);
	static void setEyeCenterUp(s1::AffinePoint eye, s1::AffinePoint center, s1::AffineVector up);
	static void setProjectionType(ProjectionType type);
	static void setZProjectionPlane(double zpp);
	static void setEyeCoordinatesZMinZMax(double zMin, double zMax);

protected:
	static void _getMatrices(s1::Matrix4x4& mc_ec, s1::Matrix4x4& ec_dc);
	static GLint _getUniformLocation(GLuint programId, const std::string& name);
	static GLint _getAttribLocation(GLuint progrmId, const std::string& name);

	static double _mcRegionOfInterest[6];
	static s1::AffinePoint _eye, _center;
	static s1::AffineVector _up;
	static ProjectionType _projectionType;
	static double _zProjectionPlane;
	static double _eyeCoordinatesZMin;
	static double _eyeCoordinatesZMax;
	static s1::Matrix4x4 _dynamicView;
};
