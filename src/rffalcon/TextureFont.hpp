#pragma once

#include "TextureAtlas.hpp"
#include <vector>
#include <string>
#include "ft2build.h"
#include FT_FREETYPE_H

namespace rffalcon
{
	struct TextureGlyph
	{

	};

	class TextureFont
	{
	public:
		TextureFont(TextureAtlas atlas, const float pointSize, const std::string &filename);
		~TextureFont();

		float getHeight() const;

	private:
		void _initialize(const std::string &filename);
		void _loadFace(FT_Library *library, FT_Face *face, const std::string &filename);

		TextureAtlas _atlas;
		float _pointSize;
		std::vector<TextureGlyph> _glyphs;
		float _height = 0;
		float _ascender = 0;
		float _descender = 0;
		float _linegap = 0;
	};
}