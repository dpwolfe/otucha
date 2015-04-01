#pragma once

#include <vector>
#include "vec.hpp"

namespace rffalcon
{
	struct GlyphData
	{
		int width;
		int height;
		int top;
		int left;
		unsigned char* buffer;
		int pitch;
	};

	class TextureAtlas
	{
	public:
		TextureAtlas(const int width, const int height, const int depth);
		virtual ~TextureAtlas();

		int getWidth() const;
		int getHeight() const;
		int getDepth() const;
		s1::ivec4 getRegion(const int width, const int height);
		void setRegion(s1::ivec4 region, GlyphData glyphData);

	private:
		int _fit(const int index, const int width, const int height);
		void _addNode(s1::ivec4 region, int index);
		void _reduceNodes(int startIndex);
		void _mergeNodes();

		std::vector<s1::ivec3> _nodes;
		int _width;
		int _height;
		int _depth;
		int _glTextureId = 0;
		unsigned char *_data;
	};
}

