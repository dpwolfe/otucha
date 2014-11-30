#pragma once

#include "AffinePoint.h"
#include "AffineVector.h"
#include "ProjectionType.h"

class ModelView
{
public:
	ModelView();
	virtual ~ModelView();

	virtual void render() = 0;

	static void setMCRegionOfInterest(double xyz[6]);
	static void setEyeCenterUp(s1::AffinePoint eye, s1::AffinePoint center, s1::AffineVector up);
	static void setProjection(ProjectionType type);
	static void setZProjectionPlane(double zpp);
	static void setEyeCoordinatesZMinZMax(double zMin, double zMax);

protected:
	static double _mcRegionOfInterest[6];
	static s1::AffinePoint _eye, _center;
	static s1::AffineVector _up;
	static ProjectionType _projectionType;
	static double _zProjectionPlane;
	static double _eyeCoordinatesZMin;
	static double _eyeCoordinatesZMax;
};