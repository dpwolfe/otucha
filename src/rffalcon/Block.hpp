#pragma once

#include "ModelViewWithShader.hpp"

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
	GLuint _vbo[2];

	void _renderBlock();
	void _initBlock();

	static GLuint _element_indices[12];
};

