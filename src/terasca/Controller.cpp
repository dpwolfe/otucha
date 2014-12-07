#include "Controller.h"

#include <GL/glew.h>
#include <GL/gl.h>

Controller* Controller::_instance = nullptr;
int Controller::initialWindowWidth = 512;
int Controller::initialWindowHeight = 512;

Controller::Controller() : glClearFlags(GL_COLOR_BUFFER_BIT)
{
	_instance = this;

	// set default values for overallMCBoundingBox
	overallMCBoundingBox[0] = overallMCBoundingBox[2] = overallMCBoundingBox[4] = 1.0;
	overallMCBoundingBox[1] = overallMCBoundingBox[3] = overallMCBoundingBox[5] = -1.0;
}

Controller::~Controller()
{
	if (this == _instance)
	{
		_instance = nullptr;
	}
}

void Controller::reportVersions(std::ostream& os) const
{
	os << "VERSIONS:\n";
	const char* glVer = reinterpret_cast<const char*>(glGetString(GL_VERSION));
	os << "    GL: " << ((glVer == nullptr) ? "NULL (has RC been created ? )" : glVer) << std::endl;
	const char* glslVer = reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
	os << "    GLSL: " << ((glslVer == nullptr) ? "NULL (has RC been created?)" : glslVer) << std::endl;
	reportWindowInterfaceVersion(os);
}

void Controller::getOverallMCBoundingBox(double xyzLimits[6]) const
{
	for (int i = 0; i < 6; i++)
	{
		xyzLimits[i] = overallMCBoundingBox[i];
	}
}

void Controller::handleReshape(int width, int height)
{
	glViewport(0, 0, width, height);
	redraw();
}

void Controller::handleAsciiChar(unsigned char theChar, int x, int y)
{
	const unsigned char ESC = 27;
	if (theChar == ESC)
	{
		endProgram();
	}

	double dsX, dsY;
	screenSpaceToDeviceSpace(x, y, dsX, dsY);

	for (std::vector<ModelView*>::iterator it = models.begin(); it < models.end(); it++)
	{
		(*it)->handleCommand(theChar, dsX, dsY);
	}

	redraw();
}

void Controller::endProgram()
{
	exit(0);
}

bool Controller::checkForErrors(std::ostream& os, const std::string& context)
{
	bool result = false;
	GLenum e = glGetError();
	if (e != GL_NO_ERROR)
	{
		result = true;
		os << "Controller::checkForErrors [" << context << "]:";
		while (e != GL_NO_ERROR)
		{
			os << " " << std::hex << e;
			e = glGetError();
		}
		os << std::endl;
	}
	
	return result;
}

void Controller::screenSpaceToDeviceSpace(int x, int y, double& dsX, double& dxY)
{
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	double xv = x - viewport[0];
	dsX = 2.0 * xv / static_cast<double>(viewport[2]) - 1.0;
	double yv = (viewport[3] - y) - viewport[1];
	dxY = 2.0 * yv / static_cast<double>(viewport[3]) - 1.0;
}

void Controller::setClearFlags(int rcFlags)
{
	glClearFlags = GL_COLOR_BUFFER_BIT;
	if ((rcFlags & RenderingContextBit::DEPTH) != 0)
	{
		glClearFlags |= GL_DEPTH_BUFFER_BIT;
	}
	if ((rcFlags & RenderingContextBit::STENCIL) != 0)
	{
		glClearFlags |= GL_STENCIL_BUFFER_BIT;
	}
}