#include "AffineVector.hpp"

#include <math.h>

#include "AffinePoint.hpp"

namespace s1 {

	AffineVector::AffineVector()
	{

	}

	AffineVector::AffineVector(const AffineVector& v)
	{
		_dx = v._dx;
		_dy = v._dy;
		_dz = v._dz;
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

	void AffineVector::normalize()
	{
		double m = magnitude();
		if (m > 0.0) {
			_dx /= m;
			_dy /= m;
			_dz /= m;
		}
	}

	double AffineVector::magnitude()
	{
		return sqrt((_dx * _dx) + (_dy * _dy) + (_dz * _dz));
	}

	double AffineVector::dot(const AffineVector& v)
	{
		return (_dx * v._dx) + (_dy * v._dy) + (_dz * v._dz);
	}

	double AffineVector::dot(const AffinePoint& v)
	{
		return (_dx * v._x) + (_dy * v._y) + (_dz * v._z);
	}

	AffineVector AffineVector::cross(const AffineVector& rhs)
	{
		return AffineVector(
			_dy*rhs._dz - _dz*rhs._dy,
			_dz*rhs._dx - _dx*rhs._dz,
			_dx*rhs._dy - _dy*rhs._dx);
	}

	AffineVector AffineVector::operator*(double rhs)
	{
		return AffineVector(_dx * rhs, _dy * rhs, _dz * rhs);
	}

	AffineVector AffineVector::operator-(const AffineVector& rhs)
	{
		return AffineVector(_dx - rhs._dx, _dy - rhs._dy, _dz - rhs._dz);
	}

	double AffineVector::operator[](int index) const
	{
		switch (index) {
		case 0:
			return _dx;
		case 1:
			return _dy;
		case 2:
			return _dz;
		default:
			return 0;
		}
	}

}
