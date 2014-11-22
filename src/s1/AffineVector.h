#pragma once

namespace s1 {

	class AffineVector
	{
	public:
		AffineVector();
		AffineVector(double dx, double dy, double dz);
		virtual ~AffineVector();

	private:
		double _dx;
		double _dy;
		double _dz;
	};

}