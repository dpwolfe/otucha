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

Matrix3x3::Matrix3x3(const Matrix4x4& m)
{
	_value[0][0] = m[0][0]; _value[0][1] = m[0][1]; _value[0][2] = m[0][2];
	_value[1][0] = m[1][0]; _value[1][1] = m[1][1]; _value[1][2] = m[1][2];
	_value[2][0] = m[2][0]; _value[2][1] = m[2][1]; _value[2][2] = m[2][2];
}

Matrix3x3::~Matrix3x3()
{

}

Matrix3x3 Matrix3x3::operator=(const Matrix3x3& rhs)
{
	this->_copyFrom(rhs);
	return *this;
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

Matrix3x3 Matrix3x3::transpose() const
{
	return Matrix3x3(
		this->_value[0][0], this->_value[1][0], this->_value[2][0],
		this->_value[0][1], this->_value[1][1], this->_value[2][1],
		this->_value[0][2], this->_value[1][2], this->_value[2][2]);
}

Matrix3x3 Matrix3x3::inverse() const
{
	double recDet = 1.0/determinant();
	return Matrix3x3(
		(_value[1][1] * _value[2][2] - _value[2][1] * _value[1][2]) * recDet,
		(_value[0][2] * _value[2][1] - _value[2][2] * _value[0][1]) * recDet,
		(_value[0][1] * _value[1][2] - _value[1][1] * _value[0][2]) * recDet,
		(_value[1][2] * _value[2][0] - _value[2][2] * _value[1][0]) * recDet,
		(_value[0][0] * _value[2][2] - _value[2][0] * _value[0][2]) * recDet,
		(_value[0][2] * _value[1][0] - _value[1][2] * _value[0][0]) * recDet,
		(_value[1][0] * _value[2][1] - _value[2][0] * _value[1][1]) * recDet,
		(_value[0][1] * _value[2][0] - _value[2][1] * _value[0][0]) * recDet,
		(_value[0][0] * _value[1][1] - _value[1][0] * _value[0][1]) * recDet
		);
}

void Matrix3x3::copyToColumnMajor(float matrix[9]) const
{
	int i = 0;
	for (int col = 0; col < 3; col++)
	{
		for (int row = 0; row < 3; row++)
		{
			matrix[i++] = static_cast<float>(this->_value[row][col]);
		}
	}
}