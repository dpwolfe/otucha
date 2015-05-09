#pragma once

#include <vector>
#include "vec.hpp"
#include <GL/glew.h>
#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H

namespace rffalcon
{
	struct GlyphData
	{
		GlyphData()
		{
		}

		GlyphData(int width, int height, int top, int left, unsigned char *buffer, int pitch, FT_Glyph glyph) :
			width(width), height(height), top(top), left(left), buffer(buffer), pitch(pitch), glyph(glyph)
		{
		}

		int width = 0;
		int height = 0;
		int top = 0;
		int left = 0;
		unsigned char *buffer = nullptr;
		int pitch = 0;
		FT_Glyph glyph = nullptr;
	};

	class TextureAtlas
	{
	public:
		TextureAtlas(const int width, const int height, const int depth);
		virtual ~TextureAtlas();

		int getWidth() const;
		int getHeight() const;
		int getDepth() const;
		GLuint getGLTextureId() const;
		unsigned char* getData() const;
		ivec4 getRegion(const int width, const int height);
		void setRegion(ivec4 region, GlyphData glyphData);
		void upload();

	private:
		int _fit(const int index, const int width, const int height);
		void _addNode(ivec4 region, int index);
		void _reduceNodes(int startIndex);
		void _mergeNodes();

		std::vector<ivec3> _nodes;
		int _width;
		int _height;
		int _depth;
		GLuint _glTextureId = 0;
		unsigned char *_data;
	};
}

