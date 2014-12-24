#include "Block.h"
#include "Matrix4x4.h"

typedef float vec3[3];

GLuint Block::_indices_xmin[4] = { 1, 0, 7, 6 };
GLuint Block::_indices_ymin[4] = { 0, 2, 6, 4 };
GLuint Block::_indices_ymax[4] = { 1, 7, 3, 5 };

Block::Block(float x, float y, float z, float lengthX, float lengthY, float lengthZ)
{
	_xmin = x;
	_xmax = x + lengthX;
	_ymin = y;
	_ymax = y + lengthY;
	_zmin = z;
	_zmax = z + lengthZ;
	_initBlock();
}

Block::~Block()
{
	glDeleteBuffers(1, _vbo);
	glDeleteVertexArrays(1, _vao);
}

void Block::render()
{
	GLint programId;
	glGetIntegerv(GL_CURRENT_PROGRAM, &programId);
	glUseProgram(_shaderProgramId);

	s1::Matrix4x4 mc_ec, ec_dc;
	_getMatrices(mc_ec, ec_dc);
	float mc_ec_cm[16];
	mc_ec.copyToColumnMajor(mc_ec_cm);
	glUniformMatrix4fv(_ppuLoc_mc_ec, 1, GL_FALSE, mc_ec_cm);
	float ec_dc_cm[16];
	ec_dc.copyToColumnMajor(ec_dc_cm);
	glUniformMatrix4fv(_ppuLoc_ec_dc, 1, GL_FALSE, ec_dc_cm);

	float color[] = { 0.0f, 0.0f, 0.8f };
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	_renderBlock(color);
}

void Block::getMCBoundingBox(double* xyzBounds) const
{
	double buffer = 0.25;
	xyzBounds[0] = _xmin - buffer;
	xyzBounds[1] = _xmax + buffer;
	xyzBounds[2] = _ymin - buffer;
	xyzBounds[3] = _ymax + buffer;
	xyzBounds[4] = _zmin - buffer;
	xyzBounds[5] = _zmax + buffer;
}

void Block::_renderBlock(float color[3])
{
	glBindVertexArray(_vao[0]);

	glUniform3fv(_ppuLoc_kd, 1, color);
	glVertexAttrib3f(_pvaLoc_mcNormal, 0.0, 0.0, 1.0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	float color2[] = { 0.8f, 0.8f, 0.0f };
	glUniform3fv(_ppuLoc_kd, 1, color2);
	glVertexAttrib3f(_pvaLoc_mcNormal, 1.0, 0.0, 0.0);
	glDrawArrays(GL_TRIANGLE_STRIP, 2, 4);

	float color3[] = { 0.0f, 0.8f, 0.0f };
	glUniform3fv(_ppuLoc_kd, 1, color3);
	glVertexAttrib3f(_pvaLoc_mcNormal, 0.0, 0.0, -1.0);
	glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);

	float color4[] = { 0.8f, 0.0f, 0.0f };
	glUniform3fv(_ppuLoc_kd, 1, color4);
	glVertexAttrib3f(_pvaLoc_mcNormal, -1.0, 0.0, 0.0);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, _indices_xmin);

	float color5[] = { 0.8f, 0.0f, 0.8f };
	glUniform3fv(_ppuLoc_kd, 1, color5);
	glVertexAttrib3f(_pvaLoc_mcNormal, 0.0, -1.0, 0.0);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, _indices_ymin);

	float color6[] = { 0.0f, 0.8f, 0.8f };
	glUniform3fv(_ppuLoc_kd, 1, color6);
	glVertexAttrib3f(_pvaLoc_mcNormal, 0.0, 1.0, 0.0);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, _indices_ymax);
}

void Block::_initBlock()
{
	vec3 vertices[] = {
		{ _xmin, _ymin, _zmax }, { _xmin, _ymax, _zmax },
		{ _xmax, _ymin, _zmax }, { _xmax, _ymax, _zmax },
		{ _xmax, _ymin, _zmin }, { _xmax, _ymax, _zmin },
		{ _xmin, _ymin, _zmin }, { _xmin, _ymax, _zmin }
	};
	glGenVertexArrays(1, _vao);
	glBindVertexArray(_vao[0]);
	glGenBuffers(1, _vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(vec3), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(_pvaLoc_mcPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(_pvaLoc_mcPosition);
	glDisableVertexAttribArray(_pvaLoc_mcNormal);
}