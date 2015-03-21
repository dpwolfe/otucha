#pragma once

#include "TextureAtlas.hpp"
#include <vector>
#include <string>
#include <memory>
#include "ft2build.h"
#include FT_FREETYPE_H

namespace rffalcon
{
	struct TextureGlyph
	{
        char charCode;
		float outlineType;
		float outlineThickness;
	};

	class TextureFont
	{
	public:
		TextureFont(std::shared_ptr<TextureAtlas> atlas, const float pointSize, const std::string &filename);
		~TextureFont();

		float getHeight() const;
		void loadGlyphs(const std::string &text);

	private:
		void _initialize();
		void _loadFace(FT_Library *library, FT_Face *face);
		void _loadFace(FT_Library *library, FT_Face *face, float pointSize);
		void _getFace(FT_Library *library, FT_Face *face);
		bool _shouldLoadGlyph(const char charCode);
		FT_Int32 _getFlags();

		std::shared_ptr<TextureAtlas> _atlas;
		float _pointSize;
		std::vector<std::shared_ptr<TextureGlyph>> _glyphs;
		float _height = 0;
		float _ascender = 0;
		float _descender = 0;
		float _linegap = 0;
		int _outlineType = 0;
		float _outlineThickness = 0.0;
		std::string _filename;
		bool _hinting = true;
	};
}