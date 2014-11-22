#pragma once

#include "AffinePoint.h"
#include "AffineVector.h"

class ModelView
{
public:
	ModelView();
	virtual ~ModelView();

	static void setMCRegionOfInterest(double xyz[6]);
	static void setEyeCenterUp(s1::AffinePoint eye, s1::AffinePoint center, s1::AffineVector up);

protected:
	static double _mcRegionOfInterest[6];
	static s1::AffinePoint _eye, _center;
	static s1::AffineVector _up;
};