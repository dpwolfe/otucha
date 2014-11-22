#include "GLFWController.h"
#include "ModelView.h"
#include "AffinePoint.h"
#include "AffineVector.h"

void set3DViewingInformation(double xyz[6])
{
	ModelView::setMCRegionOfInterest(xyz);

	s1::AffinePoint eye, center;
	s1::AffineVector up;

	// todo: set eye, center, up
	ModelView::setEyeCenterUp(eye, center, up);
}

int main(int argc, char* argv[])
{
	GLFWController c("otucha");
	c.reportVersions(std::cout);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	double xyz[6];
	c.getOverallMCBoundingBox(xyz);
	set3DViewingInformation(xyz);
}