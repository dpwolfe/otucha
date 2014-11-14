#pragma once

class ModelView
{
public:
	ModelView();
	virtual ~ModelView();

	static void setMCRegionOfInterest(double xyz[6]);

protected:
	static double mcRegionOfInterest[6];
};