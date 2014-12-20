#include <iostream>


#include "ModelView.h"
#include "Matrix4x4.h"

double ModelView::_mcRegionOfInterest[6] = { -1.0, 1.0, -1.0, 1.0, -1.0, 1.0 };
s1::AffinePoint ModelView::_eye(0, 0, 2);
s1::AffinePoint ModelView::_center(0, 0, 0);
s1::AffineVector ModelView::_up(0, 1, 0);
ProjectionType ModelView::_projectionType = PERSPECTIVE;
double ModelView::_zProjectionPlane = -1.0;
double ModelView::_eyeCoordinatesZMin = -2.0;
double ModelView::_eyeCoordinatesZMax = -0.01;

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

void ModelView::setEyeCenterUp(s1::AffinePoint eye, s1::AffinePoint center, s1::AffineVector up)
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

void ModelView::_getMatrices(s1::Matrix4x4& mc_ec, s1::Matrix4x4& ec_dc)
{
	mc_ec = s1::Matrix4x4::lookAt(_eye, _center, _up);

	if (_projectionType == PERSPECTIVE)
	{
		ec_dc = s1::Matrix4x4::perspective(_mcRegionOfInterest[0], _mcRegionOfInterest[1], _mcRegionOfInterest[2], _mcRegionOfInterest[3],
			_eyeCoordinatesZMin, _eyeCoordinatesZMax, _zProjectionPlane);
	}
	else if (_projectionType == ORTHOGONAL)
	{
		ec_dc = s1::Matrix4x4::orthogonal(_mcRegionOfInterest[0], _mcRegionOfInterest[1], _mcRegionOfInterest[2], _mcRegionOfInterest[3],
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