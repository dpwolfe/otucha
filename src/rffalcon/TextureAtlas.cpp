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
