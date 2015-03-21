#include "TextureFont.hpp"

using namespace rffalcon;

#define POINT_RES 64
#define DPI 72

TextureFont::TextureFont(std::shared_ptr<TextureAtlas> atlas, const float pointSize, const std::string &filename)
	: _atlas(atlas), _pointSize(pointSize), _filename(filename)
{
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
	_loadFace(&library, &face);
	int length = text.length();
	int sizeGlyphs = static_cast<int>(_glyphs.size());
	// Load the glyph for each character in the string
	for (int i = 0; i < length; ++i)
	{
		// Skip glyphs that have already been loaded
		for (int j = 0; j < sizeGlyphs; ++j)
		{
			TextureGlyph glyph = _glyphs[j];
			if (glyph.charCode == text[i])
			{

			}
		}
	}
}

void TextureFont::_initialize()
{
	FT_Library library;
	FT_Face face;
	FT_Size_Metrics metrics;

	FT_Error error = FT_Init_FreeType(&library);
	if (error != FT_Err_Ok)
	{
		throw new std::exception();
	}

	_loadFace(&library, &face, _pointSize * 100.0f);
	metrics = face->size->metrics;
	_ascender = (metrics.ascender >> 6) / 100.0f;
	_descender = (metrics.descender >> 6) / 100.0f;
	_height = (metrics.height >> 6) / 100.0f;
	_linegap = _height - _ascender + _descender;

	FT_Done_Face(face);
	FT_Done_FreeType(library);
}

void TextureFont::_loadFace(FT_Library *library, FT_Face *face, float pointSize)
{
	FT_Error error = FT_New_Face(*library, _filename.c_str(), 0, face);
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

void TextureFont::_loadFace(FT_Library *library, FT_Face *face)
{
	_loadFace(library, face, _pointSize);
}