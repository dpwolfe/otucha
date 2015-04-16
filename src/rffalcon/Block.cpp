#include <iostream>

#include "Block.hpp"
#include "Matrix3x3.hpp"
#include "vec.hpp"
#include "PhongMaterial.hpp"

using namespace rffalcon;

// _element_indices are in the order of 3 sides: xmin, ymin, ymax
GLuint Block::_element_indices[12] = { 1, 0, 7, 6, 0, 2, 6, 4, 1, 7, 3, 5 };

Block::Block(float x, float y, float z, float lengthX, float lengthY, float lengthZ)
{
	_xmin = x;
	_xmax = x + lengthX;
	_ymin = y;
	_ymax = y + lengthY;
	_zmin = z;
	_zmax = z + lengthZ;
	_phongMaterial = std::make_shared<PhongMaterial>(PhongMaterial::PolishedCopper);
}

Block::~Block()
{
	glDeleteBuffers(2, _vbo);
	glDeleteVertexArrays(1, _vao);
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

void Block::render()
{
	if (!_initialized)
	{
		_initBlock();
		_initialized = true;
	}

	glBindVertexArray(_vao[0]);
	
	GLint programId;
	glGetIntegerv(GL_CURRENT_PROGRAM, &programId);
	GLint pvaLoc_mcNormal = glGetAttribLocation(programId, "mcNormal");
	if (pvaLoc_mcNormal  < 0)
	{
		std::cerr << "Unable to find per-vertex attribute: 'mcNormal'" << std::endl;
	}
	else
	{
		glVertexAttrib3f(pvaLoc_mcNormal, 0.0, 0.0, 1.0);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		//float color2[] = { 0.8f, 0.8f, 0.0f };
		//glUniform3fv(_ppuLoc_kd, 1, color2);
		glVertexAttrib3f(pvaLoc_mcNormal, 1.0, 0.0, 0.0);
		glDrawArrays(GL_TRIANGLE_STRIP, 2, 4);

		//float color3[] = { 0.0f, 0.8f, 0.0f };
		//glUniform3fv(_ppuLoc_kd, 1, color3);
		glVertexAttrib3f(pvaLoc_mcNormal, 0.0, 0.0, -1.0);
		glDrawArrays(GL_TRIANGLE_STRIP, 4, 4);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[1]);

		//float color4[] = { 0.8f, 0.0f, 0.0f };
		//glUniform3fv(_ppuLoc_kd, 1, color4);
		glVertexAttrib3f(pvaLoc_mcNormal, -1.0, 0.0, 0.0);
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)0);

		//float color5[] = { 0.8f, 0.0f, 0.8f };
		//glUniform3fv(_ppuLoc_kd, 1, color5);
		glVertexAttrib3f(pvaLoc_mcNormal, 0.0, -1.0, 0.0);
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)(4 * sizeof(int)));

		//float color6[] = { 0.0f, 0.8f, 0.8f };
		//glUniform3fv(_ppuLoc_kd, 1, color6);
		glVertexAttrib3f(pvaLoc_mcNormal, 0.0, 1.0, 0.0);
		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, (void*)(8 * sizeof(int)));
	}
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
	glGenBuffers(2, _vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(vec3), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 12 * sizeof(int), _element_indices, GL_STATIC_DRAW);
	
	GLint programId;
	glGetIntegerv(GL_CURRENT_PROGRAM, &programId);
	GLint pvaLoc_mcNormal = glGetAttribLocation(programId, "mcNormal");
	GLint pvaLoc_mcPosition = glGetAttribLocation(programId, "mcPosition");

	if (pvaLoc_mcPosition < 0)
	{
		std::cerr << "Unable to find per-vertex attribute: 'mcPosition'" << std::endl;
	}
	else
	{
		glVertexAttribPointer(pvaLoc_mcPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(pvaLoc_mcPosition);
	}

	if (pvaLoc_mcNormal  < 0)
	{
		std::cerr << "Unable to find per-vertex attribute: 'mcNormal'" << std::endl;
	}
	else
	{
		glDisableVertexAttribArray(pvaLoc_mcNormal);
	}
}
