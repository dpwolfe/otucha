#pragma once

#include "TextureAtlas.hpp"
#include <vector>

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

	private:
		bool _initialize();

		TextureAtlas _atlas;
		float _pointSize;
		std::vector<TextureGlyph> _glyphs;
		float _height = 0;
		float _ascender = 0;
		float _descender = 0;
	};
}