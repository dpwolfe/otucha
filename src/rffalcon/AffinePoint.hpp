#pragma once

#include "AffineVector.hpp"

namespace rffalcon {

	class AffinePoint
	{
		friend class AffineVector;
	public:
		AffinePoint();
		AffinePoint(const AffinePoint &p);
		AffinePoint(double x, double y, double z);
		virtual ~AffinePoint();

		bool operator==(const AffinePoint &rhs) const;
		bool operator!=(const AffinePoint &rhs) const;
		AffineVector operator-(const AffinePoint &rhs) const;

	private:
		double _x;
		double _y;
		double _z;
	};

}
