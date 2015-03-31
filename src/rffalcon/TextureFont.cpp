#include "TextureFont.hpp"
#include FT_LCD_FILTER_H
#include FT_STROKER_H
#include <iostream>

using namespace rffalcon;

#define POINT_RES 64
#define DPI 72

TextureFont::TextureFont(std::shared_ptr<TextureAtlas> atlas, const float pointSize, const std::string &filename)
	: _atlas(atlas), _pointSize(pointSize), _filename(filename)
{
	_lcdWeights[0] = 0x10;
	_lcdWeights[0] = 0x40;
	_lcdWeights[0] = 0x70;
	_lcdWeights[0] = 0x40;
	_lcdWeights[0] = 0x10;
	_initialize();
}

TextureFont::~TextureFont()
{
}

float TextureFont::getHeight() const
{
	return _height;
}

void TextureFont::loadGlyphs(const std::string &text)
{
	int width = _atlas->getWidth();
	int height = _atlas->getHeight();
	int depth = _atlas->getDepth();

	FT_Library library;
	FT_Face face;
	FT_Error error = FT_Init_FreeType(&library);
	if (error != FT_Err_Ok) { throw new std::exception(); }

	_loadFace(library, &face);

	FT_Int32 flags = _getFlags();
	int length = text.length();
	// Load the glyph for each character in the string
	for (int i = 0; i < length; ++i)
	{
		char charCode = text[i];
		if (_shouldLoadGlyph(charCode))
		{
			_setFiltering(library);
			FT_UInt glyphIndex = FT_Get_Char_Index(face, charCode);
			error = FT_Load_Glyph(face, glyphIndex, flags);
			if (error) { throw new std::exception(); }
			GlyphLocation glyphLocation = _getGlyphLocation(library, face);
			s1::ivec4 region = _atlas->getRegion(glyphLocation.width + 1, glyphLocation.height + 1);
			if (region.x < 0)
			{
				std::cerr << "Texture Atlas is full." << std::endl;
			}
			else
			{

			}
		}
	}

	FT_Done_Face(face);
	FT_Done_FreeType(library);
}

GlyphLocation TextureFont::_getGlyphLocation(FT_Library library, FT_Face face)
{
	GlyphLocation glyphLocation;
	FT_Bitmap bitmap;
	int depth = _atlas->getDepth();
	if (_outlineType == 0)
	{
		FT_GlyphSlot slot = face->glyph;
		bitmap = slot->bitmap;
		glyphLocation.top = slot->bitmap_top;
		glyphLocation.left = slot->bitmap_left;
	}
	else
	{
		FT_Stroker stroker;
		FT_BitmapGlyph bitmapGlyph;
		
		FT_Error error = FT_Stroker_New(library, &stroker);
		if (error) { throw new std::exception(); }
		
		FT_Stroker_Set(stroker, static_cast<int>(_outlineThickness * POINT_RES),
			FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
		
		FT_Glyph glyph;
		error = FT_Get_Glyph(face->glyph, &glyph);
		if (error) { throw new std::exception(); }

		if (_outlineType == 1)
		{
			error = FT_Glyph_Stroke(&glyph, stroker, 1);
		}
		else if (_outlineType == 2)
		{
			error = FT_Glyph_StrokeBorder(&glyph, stroker, 0, 1);
		}
		else if (_outlineType == 3)
		{
			error = FT_Glyph_StrokeBorder(&glyph, stroker, 1, 1);
		}

		if (error) { throw new std::exception(); }

		FT_Render_Mode renderMode = _atlas->getDepth() == 1 ? FT_RENDER_MODE_NORMAL : FT_RENDER_MODE_LCD;
		error = FT_Glyph_To_Bitmap(&glyph, renderMode, 0, 1);
		if (error) { throw new std::exception(); }

		bitmapGlyph = reinterpret_cast<FT_BitmapGlyph>(glyph);
		bitmap = bitmapGlyph->bitmap;
		glyphLocation.left = bitmapGlyph->left;
		glyphLocation.top = bitmapGlyph->top;
		FT_Stroker_Done(stroker);
	}

	glyphLocation.width = bitmap.width / depth;
	glyphLocation.height = bitmap.rows;

	return glyphLocation;
}

void TextureFont::_setFiltering(FT_Library library)
{
	if (_atlas->getDepth() == 3)
	{
		FT_Library_SetLcdFilter(library, FT_LCD_FILTER_LIGHT);
		if (_filtering)
		{
			FT_Library_SetLcdFilterWeights(library, _lcdWeights);
		}
	}
}

FT_Int32 TextureFont::_getFlags()
{
	FT_Int32 flags = 0;
	if (_outlineType > 0)
	{
		flags |= FT_LOAD_NO_BITMAP;
	}
	else
	{
		flags |= FT_LOAD_RENDER;
	}

	if (!_hinting)
	{
		flags |= FT_LOAD_NO_HINTING | FT_LOAD_NO_AUTOHINT;
	}
	else
	{
		flags |= FT_LOAD_FORCE_AUTOHINT;
	}

	if (_atlas->getDepth() == 3)
	{
		flags |= FT_LOAD_TARGET_LCD;
	}

	return flags;
}

bool TextureFont::_shouldLoadGlyph(const char charCode)
{
	// Skip glyphs that have already been loaded
	bool skip = false;
	int sizeGlyphs = static_cast<int>(_glyphs.size());
	for (int j = 0; j < sizeGlyphs; ++j)
	{
		auto glyph = _glyphs[j];
		if (glyph->charCode == charCode &&
			(glyph->outlineType == _outlineType && glyph->outlineThickness == _outlineThickness))
		{
			skip = true;
			break;
		}
	}
	
	return skip;
}

void TextureFont::_initialize()
{
	FT_Library library;
	FT_Face face;
	FT_Size_Metrics metrics;

	FT_Error error = FT_Init_FreeType(&library);
	if (error != FT_Err_Ok) { throw new std::exception(); }

	_loadFace(library, &face, _pointSize * 100.0f);
	metrics = face->size->metrics;
	_ascender = (metrics.ascender >> 6) / 100.0f;
	_descender = (metrics.descender >> 6) / 100.0f;
	_height = (metrics.height >> 6) / 100.0f;
	_linegap = _height - _ascender + _descender;

	FT_Done_Face(face);
	FT_Done_FreeType(library);
}

void TextureFont::_loadFace(FT_Library library, FT_Face *face, float pointSize)
{
	FT_Error error = FT_New_Face(library, _filename.c_str(), 0, face);
	if (error != FT_Err_Ok)
	{
		throw new std::exception();
	}

	error = FT_Select_Charmap(*face, FT_ENCODING_UNICODE);
	if (error)
	{
		throw new std::exception();
	}

	error = FT_Set_Char_Size(*face, (int)(pointSize * POINT_RES), 0, DPI * POINT_RES, DPI);
	if (error)
	{
		throw new std::exception();
	}
	
	FT_Matrix matrix = {
		(int)((1.0 / POINT_RES) * 0x10000L),
		0,
		0,
		0x10000L
	};

	FT_Set_Transform(*face, &matrix, nullptr);
}

void TextureFont::_loadFace(FT_Library library, FT_Face *face)
{
	_loadFace(library, face, _pointSize);
}