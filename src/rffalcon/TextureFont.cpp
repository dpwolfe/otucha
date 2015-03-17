#include "TextureFont.hpp"
#include "ft2build.h"
#include FT_FREETYPE_H

using namespace rffalcon;

TextureFont::TextureFont(TextureAtlas atlas, const float pointSize, const std::string &filename)
	: _atlas(atlas), _pointSize(pointSize)
{
	if (!_initialize())
	{
		throw new std::exception();
	}
}

TextureFont::~TextureFont()
{
}

bool TextureFont::_initialize()
{
	FT_Library library;
	FT_Face face;
	FT_Size_Metrics metrics;



	return true;
}