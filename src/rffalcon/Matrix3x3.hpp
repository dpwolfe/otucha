#pragma once

#include "Matrix4x4.hpp"

namespace rffalcon {
	class Matrix3x3 {
	public:
		class Matrix3x3Row
		{
		public:
			Matrix3x3Row(const Matrix3x3& parent, int row);
			double operator[](int column) const;
		private:
			const Matrix3x3& _parent;
			int _row;
		};

		Matrix3x3();
		Matrix3x3(const Matrix3x3& m);
		Matrix3x3(
			double r1c1, double r1c2, double r1c3,
			double r2c1, double r2c2, double r2c3,
			double r3c1, double r3c2, double r3c3);
		Matrix3x3(const Matrix4x4& m);

		virtual ~Matrix3x3();

		Matrix3x3 operator=(const Matrix3x3& rhs);
		Matrix3x3Row operator[](int row) const;
		bool operator==(const Matrix3x3& rhs) const;
		bool operator!=(const Matrix3x3& rhs) const;
		Matrix3x3 operator*(const Matrix3x3& rhs) const;
		double determinant() const;
		Matrix3x3 transpose() const;
		Matrix3x3 inverse() const;
		void copyToColumnMajor(float matrix[9]) const;

		static const Matrix3x3 Identity;

	private:
		double _value[3][3];

		void _copyFrom(const Matrix3x3& m);
		double _get(int row, int column) const;
	};
}
