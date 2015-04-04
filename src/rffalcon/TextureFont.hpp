#pragma once

#include "TextureAtlas.hpp"
#include <vector>
#include <string>
#include <memory>
#include "ft2build.h"
#include FT_FREETYPE_H
#include "vec.hpp"

namespace rffalcon
{
	struct GlyphKerning
	{
		wchar_t charCode;
		float kerning;
	};

	struct TextureGlyph
	{
        wchar_t charCode;
		int outlineType;
		float outlineThickness;
		int width;
		int height;
		int offsetX;
		int offsetY;
		float s0;
		float t0;
		float s1;
		float t1;
		float advanceX;
		float advanceY;
		std::vector<GlyphKerning> kerning;
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
		bool _shouldLoadGlyph(const wchar_t charCode);
		FT_Int32 _getFlags();
		void _setFiltering(FT_Library library);
		GlyphData _getGlyphData(FT_Library library, FT_Face face);
		void _addTextureGlyph(wchar_t charCode, GlyphData glyphData, s1::ivec4 region, FT_Face face, FT_UInt glyphIndex);
		void _renderToAtlas(GlyphData glyphData, wchar_t charCode, FT_Face face, FT_UInt glyphIndex);
		void _generateKerning();

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
		bool _filtering = true;
		unsigned char _lcdWeights[5];
	};
}