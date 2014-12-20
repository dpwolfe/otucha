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
	float _xmin, _xmax, _ymin, _ymax, _zmin, _zmax;
	GLuint _vao[1];
	GLuint _vbo[1];

	void _renderBlock(float* color);
	void _initBlock();

	static GLuint _indices_xmin[4], _indices_ymin[4], _indices_ymax[4];
};

