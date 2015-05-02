#include "gtest/gtest.h"
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