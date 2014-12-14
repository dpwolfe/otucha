#pragma once

#include "ModelViewWithShader.h"

class Block : public ModelViewWithShader
{
public:
	Block(float x, float y, float z, float lengthX, float lengthY, float lengthZ);
	virtual ~Block();

	virtual void render();
};

