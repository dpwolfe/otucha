#pragma once

#include "vec.hpp"
#ifdef TEST
    #define GLAPI
#endif
#include <GL/glew.h>

namespace rffalcon
{
	struct PhongMaterial
	{
	public:
		GLfloat ka[3];
		GLfloat kd[3];
		GLfloat ks[3];
		GLfloat m;
		GLfloat a;
		
		const static PhongMaterial Gold;
		const static PhongMaterial Copper;
		const static PhongMaterial PolishedCopper;
	};	
}