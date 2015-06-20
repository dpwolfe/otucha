#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "VertexAttribute.hpp"

using namespace rffalcon;

TEST(VertexAttributeConstructors, default_with_valid_inputs)
{
	VertexAttribute a("name", 7, 4, true);
	EXPECT_EQ(a.getName(), "name");
	EXPECT_EQ(a.getSize(), 7);
	EXPECT_EQ(a.getType(), 4);
	EXPECT_EQ(a.getIsNormalized(), static_cast<GLboolean>(true));
}

TEST(VertexAttributeMethods, parse_with_valid_inputs)
{
	std::shared_ptr<VertexAttribute> a = VertexAttribute::parse("vertex:3fn");
	EXPECT_EQ(a->getName(), "vertex");
	EXPECT_EQ(a->getSize(), 3);
	EXPECT_EQ(a->getType(), GL_FLOAT);
	EXPECT_EQ(a->getIsNormalized(), static_cast<GLboolean>(true));
}

TEST(VertexAttributeMethods, parse_with_valid_inputs_2)
{
	std::shared_ptr<VertexAttribute> a = VertexAttribute::parse("color:2f");
	EXPECT_EQ(a->getName(), "color");
	EXPECT_EQ(a->getSize(), 2);
	EXPECT_EQ(a->getType(), GL_FLOAT);
	EXPECT_EQ(a->getIsNormalized(), static_cast<GLboolean>(false));
}


TEST(VertexAttributeMethods, parse_type_chars)
{
	std::shared_ptr<VertexAttribute> a = VertexAttribute::parse("color:2b");
	EXPECT_EQ(a->getType(), GL_BYTE);
	a = VertexAttribute::parse("color:2B");
	EXPECT_EQ(a->getType(), GL_UNSIGNED_BYTE);
	a = VertexAttribute::parse("color:2s");
	EXPECT_EQ(a->getType(), GL_SHORT);
	a = VertexAttribute::parse("color:2S");
	EXPECT_EQ(a->getType(), GL_UNSIGNED_SHORT);
	a = VertexAttribute::parse("color:2i");
	EXPECT_EQ(a->getType(), GL_INT);
	a = VertexAttribute::parse("color:2I");
	EXPECT_EQ(a->getType(), GL_UNSIGNED_INT);
	a = VertexAttribute::parse("color:2f");
	EXPECT_EQ(a->getType(), GL_FLOAT);
	a = VertexAttribute::parse("color:2F"); // invalid
	EXPECT_EQ(a->getType(), 0);
}

TEST(VertexAttributeMethods, getTypeSize_bool)
{
	VertexAttribute a("name", 7, GL_BOOL, true);
	EXPECT_EQ(a.getTypeSize(), sizeof(GLboolean));
}

TEST(VertexAttributeMethods, getTypeSize_byte)
{
	VertexAttribute a("name", 7, GL_BYTE, true);
	EXPECT_EQ(a.getTypeSize(), sizeof(GLbyte));
}

TEST(VertexAttributeMethods, getTypeSize_ubyte)
{
	VertexAttribute a("name", 7, GL_UNSIGNED_BYTE, true);
	EXPECT_EQ(a.getTypeSize(), sizeof(GLubyte));
}

TEST(VertexAttributeMethods, getTypeSize_short)
{
	VertexAttribute a("name", 7, GL_SHORT, true);
	EXPECT_EQ(a.getTypeSize(), sizeof(GLshort));
}

TEST(VertexAttributeMethods, getTypeSize_ushort)
{
	VertexAttribute a("name", 7, GL_UNSIGNED_SHORT, true);
	EXPECT_EQ(a.getTypeSize(), sizeof(GLushort));
}

TEST(VertexAttributeMethods, getTypeSize_int)
{
	VertexAttribute a("name", 7, GL_INT, true);
	EXPECT_EQ(a.getTypeSize(), sizeof(GLint));
}

TEST(VertexAttributeMethods, getTypeSize_uint)
{
	VertexAttribute a("name", 7, GL_UNSIGNED_INT, true);
	EXPECT_EQ(a.getTypeSize(), sizeof(GLuint));
}

TEST(VertexAttributeMethods, getTypeSize_float)
{
	VertexAttribute a("name", 7, GL_FLOAT, true);
	EXPECT_EQ(a.getTypeSize(), sizeof(GLfloat));
}

TEST(VertexAttributeMethods, getTypeSize_invalid)
{
	VertexAttribute a("name", 7, -1, true);
	EXPECT_EQ(a.getTypeSize(), 0);
}

TEST(VertexAttributeMethods, get_set_stride)
{
	VertexAttribute a("name", 7, -1, true);
	a.setStride(7);
	EXPECT_EQ(a.getStride(), 7);
}

TEST(VertexAttributeMethods, get_set_pointer)
{
	VertexAttribute a("name", 7, -1, true);
	a.setPointer(reinterpret_cast<GLchar*>(7));
	EXPECT_EQ(a.getPointer(), reinterpret_cast<GLchar*>(7));
}
