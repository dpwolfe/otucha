#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "ModelView.h"

class Controller
{
public:
	enum MouseButton
	{
		LEFT_BUTTON, MIDDLE_BUTTON, RIGHT_BUTTON
	};

	enum ModifierBit
	{
		ALT = 1, CONTROL = 2, SHIFT = 4
	};

	Controller();
	virtual ~Controller();

	void reportVersions(std::ostream& os) const;
	void getOverallMCBoundingBox(double* xyzLimits) const;
	virtual void redraw() const {}

protected:
	virtual void reportWindowInterfaceVersion(std::ostream& os) const = 0;
	virtual void handleReshape(int width, int height);
	virtual void handleAsciiChar(unsigned char theChar, int x, int y);
	virtual void handleMouseButton(MouseButton button, bool isPressed, int x, int y, int mods) {}
	virtual void handleMouseScroll(double xOffset, double yOffset) {}
	virtual void handleMousePosition(int x, int y) {}
	virtual void endProgram();
	void screenSpaceToDeviceSpace(int x, int y, double& dsX, double& dsY);

	double overallMCBoundingBox[6];
	int glClearFlags;
	std::vector<ModelView*> models;

	static Controller* _instance;
	static bool checkForErrors(std::ostream& os, const std::string& context);
};