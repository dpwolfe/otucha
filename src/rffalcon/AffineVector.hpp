#pragma once

namespace rffalcon {
	// forward declaration allowed for commutative operators
	class AffinePoint;

	class AffineVector
	{
	public:
		AffineVector();
		AffineVector(const AffineVector& v);
		AffineVector(double dx, double dy, double dz);
		virtual ~AffineVector();

		void normalize();
		double magnitude();
		double dot(const AffineVector& v);
		double dot(const AffinePoint& p);
		AffineVector cross(const AffineVector& v);
		AffineVector operator*(double rhs);
		AffineVector operator-(const AffineVector& rhs);
		double operator[](int index) const;

	private:
		double _dx;
		double _dy;
		double _dz;
	};

}