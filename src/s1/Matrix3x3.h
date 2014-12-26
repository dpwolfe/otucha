#pragma once

namespace s1 {
	class Matrix3x3 {
	public:
		Matrix3x3();
		Matrix3x3(const Matrix3x3& m);
		Matrix3x3(
			double r1c1, double r1c2, double r1c3,
			double r2c1, double r2c2, double r2c3,
			double r3c1, double r3c2, double r3c3);

		virtual ~Matrix3x3();

		double determinant() const;

		static const Matrix3x3 Identity;

	private:
		double _value[3][3];

		void _copyFrom(const Matrix3x3& m);
	};
}