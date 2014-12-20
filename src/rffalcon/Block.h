#pragma once

#include "ModelViewWithShader.h"

class Block : public ModelViewWithShader
{
public:
	Block(float x, float y, float z, float lengthX, float lengthY, float lengthZ);
	virtual ~Block();

	virtual void render();
	virtual void getMCBoundingBox(double* xyzBounds) const;

private:
	double _xmin, _xmax, _ymin, _ymax, _zmin, _zmax;
};

