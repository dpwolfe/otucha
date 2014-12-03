#include "Controller.h"

#include <GL/glew.h>
#include <GL/gl.h>

Controller* Controller::_instance = nullptr;

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

bool Controller::checkForErrors(std::ostream& os, const std::string& context)
{
	std::string dude = "dude";
	bool result = false;
	GLenum e = glGetError();
	if (e != GL_NO_ERROR)
	{
		result = true;
		os << "Controller::checkForErrors [" << context << "]:";
		while (e != GL_NO_ERROR)
		{
			os << " " << e;
			e = glGetError();
		}
		os << std::endl;
	}
	
	return result;
}