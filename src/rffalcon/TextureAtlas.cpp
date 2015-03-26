#include "TextureAtlas.hpp"
#include "vec.hpp"

using namespace rffalcon;

TextureAtlas::TextureAtlas(const int width, const int height, const int depth) 
	: _width(width), _height(height), _depth(depth)
{
	// starter node for fitting algorithm
	// contains padding in atlas to avoid sampling artifacts
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
	int bestY = INT_MAX;
	int bestWidth = INT_MAX;
	int bestIndex = -1;
	int nodeCount = static_cast<int>(_nodes.size());
	s1::ivec4 region = { { 0, 0, width, height } };

	for (int index = 0; index < nodeCount; ++index)
	{
		int y = _fit(index, width, height);
		if (y >= 0) {
			s1::ivec3 node = _nodes[index];
			if (y < bestY || (y == bestY && node.width < bestWidth))
			{
				bestY = y;
				bestIndex = index;
				bestWidth = node.width;
				region.x = node.x;
				region.y = node.yNext;
			}
		}
	}

	if (bestIndex == -1)
	{
		throw new std::exception();
	}

	return region;
}

int TextureAtlas::_fit(const int index, const int width, const int height)
{
	s1::ivec3 node = _nodes[index];
	int x = node.x;
	int y = node.y;
	int widthLeft = width;
	int curIndex = index;
	int result = -1;
	
	// if adding this node left-aligned to the node at the index
	// would not go outside right edge of the texture
	if ((x + width) <= (_width - 1))
	{
		// move the new node's y position to the envelope
		y = node.yNext;
		// while this node might collide with the envelope in the x direction
		while (widthLeft > 0)
		{
			node = _nodes[curIndex];
			// if the new node collides with the envelope in the x direction
			if (node.yNext > y)
			{
				// push the new node down to the envelope
				y = node.yNext;
			}

			// if adding this node would not go outside the bottom edge of the texture
			if ((y + height) <= (_height - 1))
			{
				widthLeft -= node.width;
				++curIndex;
			}
			else
			{
				// No room to add the new node below the index node
				y = -1;
				break;
			}
		}
		result = y;
	}

	return result;
}