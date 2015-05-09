#include "gtest/gtest.h"
#include "TextureAtlas.hpp"

using namespace rffalcon;

TEST(TextureAtlasConstructors, default_with_valid_inputs)
{
	TextureAtlas a(500, 500, 1);
}

TEST(TextureAtlasMethods, getWidth)
{
	TextureAtlas a(512, 256, 1);
	EXPECT_EQ(a.getWidth(), 512);
}

TEST(TextureAtlasMethods, getHeight)
{
	TextureAtlas a(512, 256, 1);
	EXPECT_EQ(a.getHeight(), 256);
}

TEST(TextureAtlasMethods, getDepth)
{
	TextureAtlas a(512, 256, 1);
	EXPECT_EQ(a.getDepth(), 1);
}

TEST(TextureAtlasMethods, getRegion)
{
	TextureAtlas a(512, 256, 1);
	ivec4 expectedRegion = { { 1, 1, 77, 44 } };
	ivec4 region = a.getRegion(77, 44);
	EXPECT_EQ(region, expectedRegion);
}

TEST(TextureAtlasMethods, getRegion_is_unique)
{
	TextureAtlas a(512, 256, 1);
	ivec4 expectedRegion = { { 1, 1, 77, 44 } };
	ivec4 region1 = a.getRegion(77, 44);
	ivec4 region2 = a.getRegion(77, 44);
	EXPECT_NE(region1.x, region2.x);
}

TEST(TextureAtlasMethods, setRegion)
{
	TextureAtlas a(512, 256, 1);
	ivec4 region = a.getRegion(5, 5);
	unsigned char buffer[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	GlyphData glyphData(4, 4, 0, 0, buffer, 4, nullptr);
	a.setRegion(region, glyphData);
	unsigned char *data = a.getData();
	for (int index = 0; index < 16; index++)
	{
		int actual = (data + (region.y + index / 4) * a.getWidth() + region.x + (index % 4))[0];
		EXPECT_EQ(actual, buffer[index]);
	}
}