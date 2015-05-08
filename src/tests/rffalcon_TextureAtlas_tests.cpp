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