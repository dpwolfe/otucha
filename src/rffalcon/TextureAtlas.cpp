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

s1::ivec4 TextureAtlas::getRegion(const int width, const int height)
{
	int bestHeight = INT_MAX;
	int bestWidth = INT_MAX;
	int bestIndex = -1;
	int nodesSize = static_cast<int>(_nodes.size());

	for (int index = 0; index < nodesSize; ++index)
	{
		int y = _fit(index, width, height);
	}

	throw new std::exception();
}

int TextureAtlas::_fit(const int index, const int width, const int height)
{
	s1::ivec3 node = _nodes[index];
	int x = node.x;
	int y = node.y;
	int widthLeft = width;
	int curIndex = index;
	if ((x + width) > (_width - 1)) { return -1; }
	y = node.y;
	while (widthLeft > 0)
	{
		node = _nodes[curIndex];
		if (node.y > y)
		{
			y = node.y;
		}
		
		if ((y + height) > (_height - 1)) { return -1; }
		widthLeft -= node.z;
		++curIndex;
	}
	return y;
}