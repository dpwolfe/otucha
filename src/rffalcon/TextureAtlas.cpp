#include "TextureAtlas.hpp"
#include "vec.hpp"

using namespace rffalcon;

TextureAtlas::TextureAtlas(const int width, const int height, const int depth) : _width(width), _height(height), _depth(depth)
{
	// padding in atlas to avoid sampling artifacts
	s1::ivec3 paddingNode = { { 1, 1, width - 2 } };

	_nodes.push_back(paddingNode);

}


TextureAtlas::~TextureAtlas()
{
}

int TextureAtlas::getWidth() const
{
	return _width;
}

int TextureAtlas::getHeight() const
{
	return _height;
}

int TextureAtlas::getDepth() const
{
	return _depth;
}

s1::ivec4 TextureAtlas::getRegion(int width, int height)
{
	int bestHeight = INT_MAX;
	int bestWidth = INT_MAX;
	int bestIndex = -1;
	int nodesSize = static_cast<int>(_nodes.size());

	for (int i = 0; i < nodesSize; ++i)
	{

	}

	throw new std::exception();
}