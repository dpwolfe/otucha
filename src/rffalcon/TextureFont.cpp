#include "TextureFont.hpp"

using namespace rffalcon;

#define POINT_RES 64
#define DPI 72

TextureFont::TextureFont(TextureAtlas atlas, const float pointSize, const std::string &filename)
	: _atlas(atlas), _pointSize(pointSize)
{
	_initialize(filename);
}

TextureFont::~TextureFont()
{
}

void TextureFont::_initialize(const std::string &filename)
{
	FT_Library library;
	FT_Face face;
	FT_Size_Metrics metrics;

	FT_Error error = FT_Init_FreeType(&library);
	if (error != FT_Err_Ok)
	{
		throw new std::exception();
	}

	_loadFace(&library, &face, filename);
	metrics = face->size->metrics;
	_ascender = (metrics.ascender >> 6) / 100.0;
	_descender = (metrics.descender >> 6) / 100.0;
	_height = (metrics.height >> 6) / 100.0;
	_linegap = _height - _ascender + _descender;

	FT_Done_Face(face);
	FT_Done_FreeType(library);
}

void TextureFont::_loadFace(FT_Library *library, FT_Face *face, const std::string &filename)
{
	FT_Error error = FT_New_Face(*library, filename.c_str(), 0, face);
	if (error != FT_Err_Ok)
	{
		throw new std::exception();
	}

	error = FT_Select_Charmap(*face, FT_ENCODING_UNICODE);
	if (error)
	{
		throw new std::exception();
	}

	error = FT_Set_Char_Size(*face, (int)(_pointSize * 100.0 * POINT_RES), 0, DPI * POINT_RES, DPI);
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