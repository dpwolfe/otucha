#include "gtest/gtest.h"
#include "TextureAtlas.hpp"

using namespace rffalcon;

TEST(TextureAtlasConstructors, default_with_valid_inputs)
{
	TextureAtlas a(500, 500, 1);
}