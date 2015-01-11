#include "GLFWController.hpp"
#include "ModelView.hpp"
#include "AffinePoint.hpp"
#include "AffineVector.hpp"
#include "ModelViewWithShader.hpp"
#include "Block.hpp"
#include "otuchaConfig.h"

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
	ModelViewWithShader::setShaderSources("simple.vsh", "simple.fsh");
	c.addModel(new Block(-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f));

	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	double xyz[6];
	c.getOverallMCBoundingBox(xyz);
	set3DViewingInformation(xyz);

	c.run();

	return 0;
}
