#include "AffineVector.h"

namespace s1 {

	AffineVector::AffineVector()
	{

	}

	AffineVector::AffineVector(double dx, double dy, double dz)
	{
		_dx = dx;
		_dy = dy;
		_dz = dz;
	}

	AffineVector::~AffineVector()
	{

	}

}