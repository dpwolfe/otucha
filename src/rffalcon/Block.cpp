#include "Block.h"
#include "Matrix4x4.h"

Block::Block(float x, float y, float z, float lengthX, float lengthY, float lengthZ)
{
	_xmin = x;
	_xmax = x + lengthX;
	_ymin = y;
	_ymax = y + lengthY;
	_zmin = z;
	_zmax = z + lengthZ;
}

Block::~Block()
{
}

void Block::render()
{
	GLint programId;
	glGetIntegerv(GL_CURRENT_PROGRAM, &programId);
	glUseProgram(_shaderProgramId);

	s1::Matrix4x4 mc_ec, ec_ds;
	getMatrices(mc_ec, ec_ds);
}

void Block::getMCBoundingBox(double* xyzBounds) const
{
	xyzBounds[0] = _xmin;
	xyzBounds[1] = _xmax;
	xyzBounds[2] = _ymin;
	xyzBounds[3] = _ymax;
	xyzBounds[4] = _zmin;
	xyzBounds[5] = _zmax;
}