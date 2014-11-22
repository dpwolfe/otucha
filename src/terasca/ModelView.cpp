#include "ModelView.h"

double ModelView::_mcRegionOfInterest[6] = { -1.0, 1.0, -1.0, 1.0, -1.0, 1.0 };
s1::AffinePoint ModelView::_eye(0, 0, 2);
s1::AffinePoint ModelView::_center(0, 0, 0);
s1::AffineVector ModelView::_up(0, 1, 0);

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