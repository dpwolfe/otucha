#include "GLFWController.hpp"
#include "ModelView.hpp"
#include "AffinePoint.hpp"
#include "AffineVector.hpp"
#include "ModelViewWithShader.hpp"
#include "Block.hpp"
#include "DependencyContainer.hpp"
#include "otuchaConfig.h"

#include <memory>
#include <iostream>

using namespace otucha;

void set3DViewingInformation(double xyz[6])
{
	ModelView::setMCRegionOfInterest(xyz);

	s1::AffinePoint eye(1.0, 1.0, 1.0);
	s1::AffinePoint center(0, 0, 0);
	s1::AffineVector up(0, 1, 0);

	ModelView::setEyeCenterUp(eye, center, up);

	double zpp = -1.0;
	double zmin = -99.0;
	double zmax = -0.01;

	ModelView::setProjectionType(PERSPECTIVE);
	ModelView::setZProjectionPlane(zpp);
	ModelView::setEyeCoordinatesZMinZMax(zmin, zmax);
}

int main(int argc, char* argv[])
{
	fprintf(stdout, "%s Version %d.%d\n", argv[0], otucha_VERSION_MAJOR, otucha_VERSION_MINOR);
	GLFWController c("otucha", Controller::DEPTH);
	c.reportVersions(std::cout);
	std::string appPath(argv[0]);
	unsigned found = appPath.find_last_of("/\\");
	std::string appDir = appPath.substr(0, found + 1);
	DependencyContainer::getSingleton()->setAppDir(appDir);
	ModelViewWithShader::setShaderSources(appDir + "simple.vsh", appDir + "simple.fsh");
	c.addModel(std::make_shared<Block>(-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f));

	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	double xyz[6];
	c.getOverallMCBoundingBox(xyz);
	set3DViewingInformation(xyz);

	// test console code to be removed later
	DependencyContainer::getSingleton()->getConsole()->registerCommand(L"test", [](warbler::t_consoleArgs_ptr args) {
		std::cout << "Console online" << std::endl;
	}, std::make_shared<warbler::t_consoleArgTypes>());
	DependencyContainer::getSingleton()->getConsole()->executeCommand(L"test");
	// end test console code

	auto fontFace = DependencyContainer::getSingleton()->getFontFace();

	c.run();

	return 0;
}
