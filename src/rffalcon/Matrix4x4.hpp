#pragma once

#include "AffinePoint.hpp"
#include "AffineVector.hpp"

namespace rffalcon
{
	class Matrix4x4
	{
	public:
		class Matrix4x4Row
		{
		public:
			Matrix4x4Row(const Matrix4x4& parent, int row);
			double operator[](int column) const;
		private:
			const Matrix4x4& _parent;
			int _row;
		};

		Matrix4x4();
		Matrix4x4(const Matrix4x4& m);
		Matrix4x4(
			double r1c1, double r1c2, double r1c3, double r1c4,
			double r2c1, double r2c2, double r2c3, double r2c4,
			double r3c1, double r3c2, double r3c3, double r3c4,
			double r4c1, double r4c2, double r4c3, double r4c4);
		virtual ~Matrix4x4();

		Matrix4x4 operator=(const Matrix4x4& rhs);
		Matrix4x4Row operator[](int row) const;
		Matrix4x4 operator*(const Matrix4x4& rhs) const;
		void copyToColumnMajor(float matrix[16]) const;

		static Matrix4x4 orthographic(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax);
		static Matrix4x4 perspective(double xmin, double xmax, double ymin, double ymax, double zmin, double zmax, double zpp);
		static Matrix4x4 lookAt(AffinePoint& eye, AffinePoint& center, AffineVector& up);

		static const Matrix4x4 Identity;

	private:
		friend class Matrix4x4Row;

		double _value[4][4];

		void _copyFrom(const Matrix4x4& m);
		double _get(int row, int column) const;
	};
}
