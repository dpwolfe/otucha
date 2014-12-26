#include "Matrix3x3.h"

#include <memory>

using namespace s1;

const Matrix3x3 Matrix3x3::Identity = Matrix3x3(
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0);

Matrix3x3::Matrix3x3()
{
	this->_copyFrom(Identity);
}

Matrix3x3::Matrix3x3(const Matrix3x3& m)
{
	this->_copyFrom(m);
}

Matrix3x3::Matrix3x3(
	double r1c1, double r1c2, double r1c3, 
	double r2c1, double r2c2, double r2c3,
	double r3c1, double r3c2, double r3c3)
{
	_value[0][0] = r1c1; _value[0][1] = r1c2; _value[0][2] = r1c3;
	_value[1][0] = r2c1; _value[1][1] = r2c2; _value[1][2] = r2c3;
	_value[2][0] = r3c1; _value[2][1] = r3c2; _value[2][2] = r3c3;
}

Matrix3x3::~Matrix3x3()
{

}

double Matrix3x3::determinant() const
{
	double det = _value[0][0] * (_value[1][1] * _value[2][2] - _value[2][1] * _value[1][2]);
	det -= _value[0][1] * (_value[1][0] * _value[2][2] - _value[2][0] * _value[1][2]);
	det += _value[0][2] * (_value[1][0] * _value[2][1] - _value[2][0] * _value[1][1]);
	return det;
}

void Matrix3x3::_copyFrom(const Matrix3x3& m)
{
	memcpy((void*)_value, (void*)m._value, 9 * sizeof(double));
}