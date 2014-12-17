#pragma once

#include "AffineVector.h"

namespace s1 {

	class AffinePoint
	{
		friend class AffineVector;
	public:
		AffinePoint();
		AffinePoint(const AffinePoint& p);
		AffinePoint(double x, double y, double z);
		virtual ~AffinePoint();

		AffineVector operator-(AffinePoint& rhs);

	private:
		double _x;
		double _y;
		double _z;
	};

}