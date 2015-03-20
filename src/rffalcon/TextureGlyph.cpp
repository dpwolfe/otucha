#include "TextureGlyph.hpp"

using namespace rffalcon;

TextureGlyph::TextureGlyph(char charCode) : _charCode(charCode)
{

}

TextureGlyph::~TextureGlyph()
{

}

char TextureGlyph::getCharCode()
{
	return _charCode;
}