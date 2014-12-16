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

void ModelView::setProjection(ProjectionType type)
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

void ModelView::getMatrices(s1::Matrix4x4& wc_ec, s1::Matrix4x4& ec_dc)
{
	wc_ec = s1::Matrix4x4::Identity;
	ec_dc = s1::Matrix4x4::Identity;
}