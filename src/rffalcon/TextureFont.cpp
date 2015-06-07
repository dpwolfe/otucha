#include "TextureFont.hpp"
#include FT_LCD_FILTER_H
#include FT_STROKER_H
#include <iostream>

using namespace rffalcon;

#define POINT_RES  64
#define POINT_RESf 64.f
#define DPI        72

TextureFont::TextureFont(std::shared_ptr<TextureAtlas> atlas, const float pointSize, const std::string &filename)
	: _atlas(atlas), _pointSize(pointSize), _filename(filename)
{
	_lcdWeights[0] = 0x10;
	_lcdWeights[0] = 0x40;
	_lcdWeights[0] = 0x70;
	_lcdWeights[0] = 0x40;
	_lcdWeights[0] = 0x10;
	_initialize();
#ifdef __EMSCRIPTEN__
	_hinting = false;
#endif
}

TextureFont::~TextureFont()
{
	_atlas = nullptr;
	for (size_t index = 0; index < _glyphs.size(); ++index)
	{
		_glyphs[index]->kerning.clear();
	}
	_glyphs.clear();
}

float TextureFont::getHeight() const
{
	return _height;
}

int TextureFont::loadGlyphs(const std::wstring &text)
{
	FT_Library library;
	FT_Face face;
	FT_Error error = FT_Init_FreeType(&library);
	if (error != FT_Err_Ok) { throw new std::exception(); }

	_loadFace(&library, &face);

	FT_Int32 flags = _getFlags();
	int length = text.length();
	// Count the number of glyphs that could not be loaded into the atlas for return
	int missed = 0;
	// Load the glyph for each character in the string
	for (int i = 0; i < length; ++i)
	{
		wchar_t charCode = text[i];
		if (_shouldLoadGlyph(charCode))
		{
			_setFiltering(library);
			FT_UInt glyphIndex = FT_Get_Char_Index(face, charCode);
			error = FT_Load_Glyph(face, glyphIndex, flags);
			if (error) { throw new std::exception(); }
			GlyphData glyphData = _getGlyphData(library, face);
			ivec4 region = _renderToAtlas(glyphData, charCode, face, glyphIndex);
			if (region.x < 0) {
				missed++;
			}
		}
	}

	FT_Done_Face(face);
	FT_Done_FreeType(library);
	_atlas->upload();
	_generateKerning();

	return missed;
}

std::shared_ptr<TextureGlyph> TextureFont::getGlyph(const wchar_t charCode)
{
	std::shared_ptr<TextureGlyph> glyph = _tryGetGlyph(charCode);
	if (glyph == nullptr)
	{
		if (charCode == static_cast<wchar_t>(-1))
		{
			GlyphData glyphData;
			static unsigned char buffer[4 * 4 * 3] = {
				UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX,
				UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX,
				UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX,
				UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX
			};
			glyphData.buffer = buffer;
			glyphData.width = 4;
			glyphData.height = 4;

			ivec4 region = _renderToAtlas(glyphData, charCode, nullptr, 0);
			int width = _atlas->getWidth();
			int height = _atlas->getHeight();
			glyph = std::make_shared<TextureGlyph>();
			glyph->charCode = charCode;
			glyph->s0 = (region.x + 2) / static_cast<float>(width);
			glyph->t0 = (region.y + 2) / static_cast<float>(height);
			glyph->s1 = (region.x + 3) / static_cast<float>(width);
			glyph->t1 = (region.y + 3) / static_cast<float>(height);
			_glyphs.push_back(glyph);
		}
		else
		{
			wchar_t buf[] = { charCode };
			const std::wstring charStr(buf, 1);
			if (loadGlyphs(charStr) == 0)
			{
				glyph = _glyphs.back();
			}
		}
	}

	return glyph;
}

void TextureFont::_generateKerning()
{
	FT_Library library;
	FT_Face face;
	FT_Error error = FT_Init_FreeType(&library);
	if (error != FT_Err_Ok) { throw new std::exception(); }

	_loadFace(&library, &face);

	// indices start at 1 to skip the special -1 background glyph which is always at index 0
	for (size_t outerIndex = 1; outerIndex < _glyphs.size(); ++outerIndex)
	{
		std::shared_ptr<TextureGlyph> rightGlyph = _glyphs[outerIndex];
		FT_UInt rightGlyphIndex = FT_Get_Char_Index(face, rightGlyph->charCode);
		rightGlyph->kerning.clear();

		for (size_t innerIndex = 1; innerIndex < _glyphs.size(); ++innerIndex)
		{
			std::shared_ptr<TextureGlyph> leftGlyph = _glyphs[innerIndex];
			FT_UInt leftGlyphIndex = FT_Get_Char_Index(face, leftGlyph->charCode);
			FT_Vector kerning;
			FT_Get_Kerning(face, leftGlyphIndex, rightGlyphIndex, FT_KERNING_UNFITTED, &kerning);
			if (kerning.x)
			{
				GlyphKerning glyphKerning = { leftGlyph->charCode, kerning.x / (float)(POINT_RESf*POINT_RESf) };
				rightGlyph->kerning.push_back(glyphKerning);
			}
		}
	}

	FT_Done_Face(face);
	FT_Done_FreeType(library);
}

void TextureFont::_addTextureGlyph(wchar_t charCode, GlyphData glyphData, ivec4 region, FT_Face face, FT_UInt glyphIndex)
{
	std::shared_ptr<TextureGlyph> glyph = std::make_shared<TextureGlyph>();
	glyph->charCode = charCode;
	glyph->width = glyphData.width;
	glyph->height = glyphData.height;
	glyph->outlineType = _outlineType;
	glyph->outlineThickness = _outlineThickness;
	glyph->offsetX = glyphData.left;
	glyph->offsetY = glyphData.top;
	glyph->s0 = region.x / static_cast<float>(_atlas->getWidth());
	glyph->t0 = region.y / static_cast<float>(_atlas->getHeight());
	glyph->s1 = (region.x + glyphData.width) / static_cast<float>(_atlas->getWidth());
	glyph->t1 = (region.y + glyphData.height) / static_cast<float>(_atlas->getHeight());

	// get advance
	FT_Error error = FT_Load_Glyph(face, glyphIndex, FT_LOAD_RENDER | FT_LOAD_NO_HINTING);
	if (error != FT_Err_Ok) { throw new std::exception(); }
	FT_GlyphSlot slot = face->glyph;
	glyph->advanceX = slot->advance.x / POINT_RESf;
	glyph->advanceY = slot->advance.y / POINT_RESf;

	_glyphs.push_back(glyph);
}

GlyphData TextureFont::_getGlyphData(FT_Library library, FT_Face face)
{
	GlyphData glyphData;
	FT_Bitmap bitmap;
	int depth = _atlas->getDepth();
	if (_outlineType == 0)
	{
		FT_GlyphSlot slot = face->glyph;
		bitmap = slot->bitmap;
		glyphData.top = slot->bitmap_top;
		glyphData.left = slot->bitmap_left;
	}
	else
	{
		FT_Stroker stroker;
		FT_BitmapGlyph bitmapGlyph;
		
		FT_Error error = FT_Stroker_New(library, &stroker);
		if (error) { throw new std::exception(); }
		
		FT_Stroker_Set(stroker, static_cast<int>(_outlineThickness * POINT_RES),
			FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
		
		error = FT_Get_Glyph(face->glyph, &glyphData.glyph);
		if (error) { throw new std::exception(); }

		if (_outlineType == 1)
		{
			error = FT_Glyph_Stroke(&glyphData.glyph, stroker, 1);
		}
		else if (_outlineType == 2)
		{
			error = FT_Glyph_StrokeBorder(&glyphData.glyph, stroker, 0, 1);
		}
		else if (_outlineType == 3)
		{
			error = FT_Glyph_StrokeBorder(&glyphData.glyph, stroker, 1, 1);
		}

		if (error) { throw new std::exception(); }

		FT_Render_Mode renderMode = _atlas->getDepth() == 1 ? FT_RENDER_MODE_NORMAL : FT_RENDER_MODE_LCD;
		error = FT_Glyph_To_Bitmap(&glyphData.glyph, renderMode, 0, 1);
		if (error) { throw new std::exception(); }

		bitmapGlyph = reinterpret_cast<FT_BitmapGlyph>(glyphData.glyph);
		bitmap = bitmapGlyph->bitmap;
		glyphData.left = bitmapGlyph->left;
		glyphData.top = bitmapGlyph->top;
		FT_Stroker_Done(stroker);
	}

	glyphData.width = bitmap.width / depth;
	glyphData.height = bitmap.rows;
	glyphData.buffer = bitmap.buffer;
	glyphData.pitch = bitmap.pitch;

	return glyphData;
}

ivec4 TextureFont::_renderToAtlas(GlyphData glyphData, const wchar_t charCode, FT_Face face, FT_UInt glyphIndex)
{
	ivec4 region = _atlas->getRegion(glyphData.width + 1, glyphData.height + 1);

	if (region.x < 0)
	{
		std::cerr << "Texture Atlas is full. Glyph not added to atlas: " << charCode << std::endl;
	}
	else
	{
		_atlas->setRegion(region, glyphData);

		if (glyphData.glyph != nullptr) {
			FT_Done_Glyph(glyphData.glyph);
			glyphData.glyph = nullptr;
		}

		if (charCode != static_cast<wchar_t>(-1))
		{
			_addTextureGlyph(charCode, glyphData, region, face, glyphIndex);
		}
	}

	return region;
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

bool TextureFont::_shouldLoadGlyph(const wchar_t charCode)
{
	std::shared_ptr<TextureGlyph> glyph = _tryGetGlyph(charCode);
	return (glyph == nullptr);
}

std::shared_ptr<TextureGlyph> TextureFont::_tryGetGlyph(const wchar_t charCode)
{
	// Skip glyphs that have already been loaded
	std::shared_ptr<TextureGlyph> glyph = nullptr;
	size_t glyphCount = _glyphs.size();
	for (size_t j = 0; j < glyphCount; ++j)
	{
		std::shared_ptr<TextureGlyph> curGlyph = _glyphs[j];
		// -1 is a special background glyph where outline does not matter
		if (curGlyph->charCode == charCode &&
			((charCode == static_cast<wchar_t>(-1)) ||
			(curGlyph->outlineType == _outlineType && curGlyph->outlineThickness == _outlineThickness)))
		{
			glyph = curGlyph;
			break;
		}
	}
	
	return glyph;
}

void TextureFont::_initialize()
{
	FT_Library library;
	FT_Face face;
	FT_Size_Metrics metrics;

	FT_Error error = FT_Init_FreeType(&library);
	if (error != FT_Err_Ok) { throw new std::exception(); }

	_loadFace(&library, &face, _pointSize * 100.0f);
	metrics = face->size->metrics;
	_ascender = (metrics.ascender >> 6) / 100.0f;
	_descender = (metrics.descender >> 6) / 100.0f;
	_height = (metrics.height >> 6) / 100.0f;
	_linegap = _height - _ascender + _descender;

	FT_Done_Face(face);
	FT_Done_FreeType(library);

	// load the special -1 background glyph at index 0
	getGlyph(-1);
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