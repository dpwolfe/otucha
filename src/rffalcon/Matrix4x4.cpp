#include "Matrix4x4.hpp"

#include <memory>
#include <assert.h>

using namespace rffalcon;

Matrix4x4::Matrix4x4Row::Matrix4x4Row(const Matrix4x4& parent, int row)
	: _parent(parent), _row(row) {}

double Matrix4x4::Matrix4x4Row::operator[](int column) const {
	return _parent._get(_row, column);
}

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

Matrix4x4::Matrix4x4Row Matrix4x4::operator[](int row) const
{
	return Matrix4x4Row(*this, row);
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& rhs) const
{
	Matrix4x4 result;
	for (int row = 0; row < 4; row++)
	{
		for (int column = 0; column < 4; column++)
		{
			double sum = 0.0;
			for (int i = 0; i < 4; i++)
			{
				sum += _value[row][i] * rhs._value[i][column];
			}
			result._value[row][column] = sum;
		}
	}
	return result;
}

void Matrix4x4::copyToColumnMajor(float matrix[16]) const
{
	int i = 0;
	for (int col = 0; col < 4; col++)
	{
		for (int row = 0; row < 4; row++)
		{
			matrix[i++] = static_cast<float>(this->_value[row][col]);
		}
	}
}

Matrix4x4 Matrix4x4::orthographic(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax)
{
	assert(xmin < xmax && ymin < ymax && zmin < zmax);

	return Matrix4x4(
		2.0/(xmax-xmin), 0.0,              0.0,             -(xmax+xmin)/(xmax-xmin),
		0.0,             2.0/(ymax-ymin),  0.0,             -(ymax+ymin)/(ymax-ymin),
		0.0,             0.0,             -2.0/(zmax-zmin),  (zmax+zmin)/(zmax-zmin),
		0.0,             0.0,              0.0,              1.0);
}

Matrix4x4 Matrix4x4::perspective(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax, double zpp)
{
	assert(xmin < xmax && ymin < ymax && zmin < zmax && zmax < 0 && zpp < 0);

	return Matrix4x4(
		-2.0*zpp/(xmax-xmin), 0.0,                 (xmax+xmin)/(xmax-xmin),  0.0,
		0.0,                 -2.0*zpp/(ymax-ymin), (ymax+ymin)/(ymax-ymin),  0.0,
		0.0,                  0.0,                 (zmax+zmin)/(zmax-zmin), -2.0*zmin*zmax/(zmax-zmin),
		0.0,                  0.0,                 -1.0,                     0.0);
}

Matrix4x4 Matrix4x4::lookAt(AffinePoint& eye, AffinePoint& center, AffineVector& up)
{
	rffalcon::AffineVector u, v, w;
	w = center - eye;
	w.normalize();
	u = w.cross(up);
	u.normalize();
	v = u.cross(w);
	double tx = u.dot(eye);
	double ty = v.dot(eye);
	double tz = w.dot(eye);
	return Matrix4x4(
		 u[0],  u[1],  u[2], tx,
		 v[0],  v[1],  v[2], ty,
		-w[0], -w[1], -w[2], tz,
   		  0.0,   0.0,   0.0, 1.0);
}

void Matrix4x4::_copyFrom(const Matrix4x4& m)
{
	memcpy((void*)_value, (void*)m._value, 16 * sizeof(double));
}

double Matrix4x4::_get(int row, int column) const
{
	return _value[row][column];
}
