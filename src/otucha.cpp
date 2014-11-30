#include "GLFWController.h"
#include "ModelView.h"
#include "AffinePoint.h"
#include "AffineVector.h"

void set3DViewingInformation(double xyz[6])
{
	ModelView::setMCRegionOfInterest(xyz);

	s1::AffinePoint eye(0, 0, 2.0);
	s1::AffinePoint center(0, 0, 0);
	s1::AffineVector up(0, 1, 0);

	ModelView::setEyeCenterUp(eye, center, up);

	double zpp = -1.0;
	double zmin = -2.0;
	double zmax = -0.01;

	ModelView::setProjection(PERSPECTIVE);
	ModelView::setZProjectionPlane(zpp);
	ModelView::setEyeCoordinatesZMinZMax(zmin, zmax);
}

int main(int argc, char* argv[])
{
	GLFWController c("otucha");
	c.reportVersions(std::cout);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	double xyz[6];
	c.getOverallMCBoundingBox(xyz);
	set3DViewingInformation(xyz);

	c.run();

	return 0;
}