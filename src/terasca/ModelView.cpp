#include <iostream>

#include "ModelView.hpp"
#include "Matrix4x4.hpp"

double ModelView::_mcRegionOfInterest[6] = { -1.0, 1.0, -1.0, 1.0, -1.0, 1.0 };
rffalcon::AffinePoint ModelView::_eye(0, 0, 2);
rffalcon::AffinePoint ModelView::_center(0, 0, 0);
rffalcon::AffineVector ModelView::_up(0, 1, 0);
ProjectionType ModelView::_projectionType = PERSPECTIVE;
double ModelView::_zProjectionPlane = -1.0;
double ModelView::_eyeCoordinatesZMin = -2.0;
double ModelView::_eyeCoordinatesZMax = -0.01;
rffalcon::Matrix4x4 ModelView::_dynamicView;

ModelView::ModelView()
{
}

ModelView::~ModelView()
{
}

void ModelView::setMCRegionOfInterest(double xyz[6])
{
	for (int i = 0; i < 6; i++)
	{
		_mcRegionOfInterest[i] = xyz[i];
	}
}

void ModelView::setEyeCenterUp(rffalcon::AffinePoint eye, rffalcon::AffinePoint center, rffalcon::AffineVector up)
{
	_eye = eye;
	_center = center;
	_up = up;
}

void ModelView::setProjectionType(ProjectionType type)
{
	_projectionType = type;
}

void ModelView::setZProjectionPlane(double zpp)
{
	_zProjectionPlane = zpp;
}

void ModelView::setEyeCoordinatesZMinZMax(double zMin, double zMax)
{
	_eyeCoordinatesZMin = zMin;
	_eyeCoordinatesZMax = zMax;
}

void ModelView::_getMatrices(rffalcon::Matrix4x4& mc_ec, rffalcon::Matrix4x4& ec_dc)
{

	if (_projectionType == PERSPECTIVE)
	{
		mc_ec = rffalcon::Matrix4x4::lookAt(_eye, _center, _up);
		ec_dc = rffalcon::Matrix4x4::perspective(_mcRegionOfInterest[0], _mcRegionOfInterest[1], _mcRegionOfInterest[2], _mcRegionOfInterest[3],
			_eyeCoordinatesZMin, _eyeCoordinatesZMax, _zProjectionPlane);
	}
	else if (_projectionType == ORTHOGRAPHIC)
	{
		mc_ec = rffalcon::Matrix4x4::Identity;
		ec_dc = rffalcon::Matrix4x4::orthographic(_mcRegionOfInterest[0], _mcRegionOfInterest[1], _mcRegionOfInterest[2], _mcRegionOfInterest[3],
			_mcRegionOfInterest[4], _mcRegionOfInterest[5]);
	}
}

GLint ModelView::_getUniformLocation(GLuint programId, const std::string& name)
{
	GLint loc = glGetUniformLocation(programId, name.c_str());
	if (loc < 0)
	{
		std::cerr << "Unable to find per-primitive uniform: '" << name << "'" << std::endl;
	}
	return loc;
}

GLint ModelView::_getAttribLocation(GLuint programId, const std::string& name)
{
	GLint loc = glGetAttribLocation(programId, name.c_str());
	if (loc < 0)
	{
		std::cerr << "Unable to find per-vertex attribute: '" << name << "'" << std::endl;
	}
	return loc;
}
