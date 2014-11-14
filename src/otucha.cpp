#include "GLFWController.h"
#include "ModelView.h"
#include "AffPoint.h"
#include "AffVector.h"

void set3DViewingInformation(double xyz[6])
{
	ModelView::setMCRegionOfInterest(xyz);

	s1::AffPoint eye, center;
	s1::AffVector up;
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