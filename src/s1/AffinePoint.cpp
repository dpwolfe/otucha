#include "AffinePoint.hpp"

namespace s1 {

	AffinePoint::AffinePoint()
	{

	}

	AffinePoint::AffinePoint(double x, double y, double z)
	{
		_x = x;
		_y = y;
		_z = z;
	}

	AffinePoint::AffinePoint(const AffinePoint& p)
	{
		_x = p._x;
		_y = p._y;
		_z = p._z;
	}

	AffinePoint::~AffinePoint()
	{

	}

	AffineVector AffinePoint::operator-(AffinePoint& rhs)
	{
		return AffineVector(_x - rhs._x, _y - rhs._y, _z - rhs._z);
	}

}
