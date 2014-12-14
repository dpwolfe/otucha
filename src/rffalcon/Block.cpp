#include "Block.h"
#include "Matrix4x4.h"

Block::Block(float x, float y, float z, float lengthX, float lengthY, float lengthZ)
{
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
}
