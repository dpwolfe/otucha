#pragma once

namespace rffalcon
{
	class TextureGlyph
	{
	public:
		TextureGlyph(char charCode);
		virtual ~TextureGlyph();

		char getCharCode();

	private:
		char _charCode;
	};
}
