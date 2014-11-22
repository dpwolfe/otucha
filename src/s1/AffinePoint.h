#pragma once

namespace s1 {

	class AffinePoint
	{
	public:
		AffinePoint();
		AffinePoint(double x, double y, double z);
		virtual ~AffinePoint();

	private:
		double _x;
		double _y;
		double _z;
	};

}