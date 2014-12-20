#pragma once

#include "AffinePoint.h"
#include "AffineVector.h"

namespace s1
{
	class Matrix4x4
	{
	public:
		Matrix4x4();
		Matrix4x4(const Matrix4x4& m);
		Matrix4x4(
			double r1c1, double r1c2, double r1c3, double r1c4,
			double r2c1, double r2c2, double r2c3, double r2c4,
			double r3c1, double r3c2, double r3c3, double r3c4,
			double r4c1, double r4c2, double r4c3, double r4c4);
		virtual ~Matrix4x4();

		Matrix4x4 operator=(const Matrix4x4& rhs);
		void copyToColumnMajor(float matrix[16]);

		static Matrix4x4 orthogonal(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax);
		static Matrix4x4 perspective(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax, double zpp);
		static Matrix4x4 lookAt(AffinePoint& eye, AffinePoint& center, AffineVector& up);

		static const Matrix4x4 Identity;

	private:
		double _value[4][4];

		void _copyFrom(const Matrix4x4& m);
	};
}