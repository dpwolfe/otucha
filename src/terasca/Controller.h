#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "ModelView.h"

class Controller
{
public:
	Controller();
	virtual ~Controller();

	void reportVersions(std::ostream& os) const;
	void getOverallMCBoundingBox(double* xyzLimits) const;
	virtual void redraw() const {}

protected:
	virtual void reportWindowInterfaceVersion(std::ostream& os) const = 0;
	virtual void handleReshape(int width, int height);

	double overallMCBoundingBox[6];
	int glClearFlags;
	std::vector<ModelView*> models;

	static Controller* _instance;
	static bool checkForErrors(std::ostream& os, const std::string& context);
};