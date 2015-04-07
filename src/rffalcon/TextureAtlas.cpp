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
	_data = new unsigned char[width * height * depth];
}


TextureAtlas::~TextureAtlas()
{
	delete [] _data;
	_data = nullptr;
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

GLuint TextureAtlas::getGLTextureId() const
{
	return _glTextureId;
}

s1::ivec4 TextureAtlas::getRegion(const int width, const int height)
{
	int bestY = INT_MAX;
	int bestWidth = INT_MAX;
	int bestIndex = -1;
	int nodeCount = static_cast<int>(_nodes.size());
	s1::ivec4 region = { { -1, -1, width, height } };

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

	if (bestIndex != -1)
	{
		_addNode(region, bestIndex);
		_reduceNodes(bestIndex);
		_mergeNodes();
	}

	return region;
}

// Add node to envelope
void TextureAtlas::_addNode(s1::ivec4 region, int index)
{
	s1::ivec3 node;
	node.x = region.x;
	node.yNext = region.y + region.height;
	node.width = region.width;
	_nodes.insert(_nodes.begin() + index, node);
}

// Remove nodes that are no longer part of the envelope
void TextureAtlas::_reduceNodes(int startIndex)
{
	for (int index = startIndex + 1; index < static_cast<int>(_nodes.size()); ++index)
	{
		s1::ivec3 curNode = _nodes[index];
		s1::ivec3 prevNode = _nodes[index - 1];
		if (curNode.x < (prevNode.x + prevNode.width))
		{
			_nodes.erase(_nodes.begin() + index);
			int widthReduction = prevNode.x + prevNode.width - curNode.x;
			curNode.width -= widthReduction;
			if (curNode.width <= 0)
			{
				--index;
			}
			else
			{
				curNode.x += widthReduction;
				_nodes.insert(_nodes.begin() + index, curNode);
				// reduced width of the curNode, rest of envelope will be unaffected
				break;
			}
		}
		else
		{
			// rest of envelope unaffected
			break;
		}
	}
}

// Merge adjacent nodes on the envelope that have the same yNext value
void TextureAtlas::_mergeNodes()
{
	for (int index = 0; index < static_cast<int>(_nodes.size()) - 1; ++index)
	{
		s1::ivec3 curNode = _nodes[index];
		s1::ivec3 nextNode = _nodes[index + 1];
		if (curNode.yNext == nextNode.yNext)
		{
			curNode.width += nextNode.width;
			_nodes.erase(_nodes.begin() + index + 1);
			--index;
		}
	}
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

void TextureAtlas::setRegion(s1::ivec4 region, GlyphData glyphData)
{
	int depth = getDepth();
	int width = getWidth();
	int charSize = sizeof(char);
	for (int i = 0; i < glyphData.height; ++i)
	{
		memcpy(_data + ((region.y + i) * width + region.x) * charSize * depth,
			   _data + (i * glyphData.pitch * charSize), width * charSize * depth);
	}
	
}

void TextureAtlas::upload()
{
	if (_glTextureId == 0)
	{
		glGenTextures(1, &_glTextureId);
	}

	glBindTexture(GL_TEXTURE_2D, _glTextureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	GLenum pixelDataType;
	int internalFormat;
	if (_depth == 4)
	{
#ifdef GL_UNSIGNED_INT_8_8_8_8_REV
		pixelDataType = GL_UNSIGNED_INT_8_8_8_8_REV;
#else
		pixelDataType = GL_UNSIGNED_BYTE;
#endif
		internalFormat = GL_RGBA;
	}
	else {
		pixelDataType = GL_UNSIGNED_BYTE;
		internalFormat = (_depth == 3) ? GL_RGB : GL_RED;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, internalFormat, pixelDataType, _data);
}