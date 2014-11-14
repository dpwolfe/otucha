#pragma once

#include <iostream>

class Controller
{
public:
	Controller();
	virtual ~Controller();

	void reportVersions(std::ostream& os) const;
	void getOverallMCBoundingBox(double* xyzLimits) const;

protected:
	virtual void reportWindowInterfaceVersion(std::ostream& os) const = 0;

	double overallMCBoundingBox[6];
};