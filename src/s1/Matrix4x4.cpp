#include "Matrix4x4.h"

#include <memory>

using namespace s1;

const Matrix4x4 Matrix4x4::Identity = Matrix4x4(
	1.0, 0.0, 0.0, 0.0,
	0.0, 1.0, 0.0, 0.0,
	0.0, 0.0, 1.0, 0.0,
	0.0, 0.0, 0.0, 1.0);

Matrix4x4::Matrix4x4()
{
	this->_copyFrom(Identity);
}

Matrix4x4::Matrix4x4(const Matrix4x4& m)
{
	this->_copyFrom(m);
}

Matrix4x4::~Matrix4x4()
{

}

Matrix4x4::Matrix4x4(
	double r1c1, double r1c2, double r1c3, double r1c4,
	double r2c1, double r2c2, double r2c3, double r2c4,
	double r3c1, double r3c2, double r3c3, double r3c4,
	double r4c1, double r4c2, double r4c3, double r4c4)
{
	_value[0][0] = r1c1; _value[0][1] = r1c2; _value[0][2] = r1c3; _value[0][3] = r1c4;
	_value[1][0] = r2c1; _value[1][1] = r2c2; _value[1][2] = r2c3; _value[1][3] = r2c4;
	_value[2][0] = r3c1; _value[2][1] = r3c2; _value[2][2] = r3c3; _value[2][3] = r3c4;
	_value[3][0] = r4c1; _value[3][1] = r4c2; _value[3][2] = r4c3; _value[3][3] = r4c4;
}

Matrix4x4 Matrix4x4::operator=(const Matrix4x4& rhs)
{
	this->_copyFrom(rhs);
	return *this;
}

void Matrix4x4::_copyFrom(const Matrix4x4& m)
{
	memcpy((void*)_value, (void*)m._value, 16 * sizeof(double));
}