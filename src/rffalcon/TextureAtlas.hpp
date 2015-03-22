#pragma once

#include <vector>
#include "vec.hpp"

namespace rffalcon {
	class TextureAtlas
	{
	public:
		TextureAtlas(const int width, const int height, const int depth);
		virtual ~TextureAtlas();

		int getWidth() const;
		int getHeight() const;
		int getDepth() const;
		s1::ivec4 getRegion(int width, int height);

	private:
		std::vector<s1::ivec3> _nodes;
		int _width;
		int _height;
		int _depth;
		int _glTextureId = 0;
	};
}

