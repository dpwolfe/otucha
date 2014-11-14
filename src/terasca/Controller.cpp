#include "Controller.h"

#include <GL/glew.h>
#include <GL/gl.h>

Controller::Controller()
{
	// set default values for overallMCBoundingBox
	overallMCBoundingBox[0] = overallMCBoundingBox[2] = overallMCBoundingBox[4] = 1.0;
	overallMCBoundingBox[1] = overallMCBoundingBox[3] = overallMCBoundingBox[5] = -1.0;
}

Controller::~Controller()
{

}

void Controller::reportVersions(std::ostream& os) const
{
	os << "VERSIONS:\n";
	const char* glVer = reinterpret_cast<const char*>(glGetString(GL_VERSION));
    os << "    GL: " << ((glVer == NULL) ? "NULL(has RC been created ? )" : glVer) << std::endl;
	const char* glslVer = reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
	os << "    GLSL: " << ((glslVer == NULL) ? "NULL (has RC been created?)" : glslVer) << std::endl;
	reportWindowInterfaceVersion(os);
}

void Controller::getOverallMCBoundingBox(double xyzLimits[6]) const
{
	for (int i = 0; i < 6; i++)
	{
		xyzLimits[i] = overallMCBoundingBox[i];
	}
}