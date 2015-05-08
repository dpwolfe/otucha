#include "AffinePoint.hpp"

namespace rffalcon {

	AffinePoint::AffinePoint()
	{
		_x = 0.0;
		_y = 0.0;
		_z = 0.0;
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

	AffinePoint::~AffinePoint() { }

	bool AffinePoint::operator==(const AffinePoint& rhs) const
	{
		return _x == rhs._x && _y == rhs._y && _z == rhs._z;
	}

	bool AffinePoint::operator!=(const AffinePoint& rhs) const
	{
		return !(*this == rhs);
	}

	AffineVector AffinePoint::operator-(const AffinePoint& rhs) const
	{
		return AffineVector(_x - rhs._x, _y - rhs._y, _z - rhs._z);
	}

}
