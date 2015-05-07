#include "gtest/gtest.h"
#include "AffineVector.hpp"
#include "AffinePoint.hpp"

using namespace rffalcon;

TEST(AffineVectorConstructors, equality_with_default_constructor) {
    AffineVector v;
    EXPECT_EQ(v, v);
}

TEST(AffineVectorConstructors, default_constructor_is_zero) {
	AffineVector v1;
	AffineVector v2(0, 0, 0);
	EXPECT_EQ(v1, v2);
}

TEST(AffineVectorOperators, equality_with_explicit_constructor) {
	AffineVector v(1, 2, 3);
	EXPECT_EQ(v, v);
}

TEST(AffineVectorOperators, equality_with_copy_constructor) {
	AffineVector v1(1, 2, 3);
	AffineVector v2(v1);
	EXPECT_EQ(v1, v2);
}

TEST(AffineVectorOperators, not_equal) {
	AffineVector v1(1, 2, 3);
	AffineVector v2(2, 3, 4);
	EXPECT_NE(v1, v2);
}

TEST(AffineVectorOperators, normalize) {
	AffineVector v1(1, 2, 3);
	v1.normalize();
	AffineVector v2(0.26726124191242440, 0.53452248382484879, 0.80178372573727319);
	EXPECT_EQ(v1, v2);
}

TEST(AffineVectorOperators, assignment) {
	AffineVector v1(1, 2, 3);
	AffineVector v2(-0.5, -1, 0.75);
	EXPECT_NE(v1, v2);
	v1 = v2;
	EXPECT_EQ(v1, v2);
}

TEST(AffineVectorOperators, multiply) {
	AffineVector v1(1, 2, 3);
	AffineVector v2(2, 4, 6);
	AffineVector v3 = v1*2;
	EXPECT_EQ(v3, v2);
}

TEST(AffineVectorOperators, subtract) {
	AffineVector v1(1, 2, 3);
	AffineVector v2(2, 3, 4);
	AffineVector v3 = v1 - v2;
	AffineVector v4(-1, -1, -1);
	EXPECT_EQ(v3, v4);
}

TEST(AffineVectorOperators, bracket) {
	AffineVector v1(1, 2, 3);
	EXPECT_EQ(v1[-1], 0);
	EXPECT_EQ(v1[0], 1);
	EXPECT_EQ(v1[1], 2);
	EXPECT_EQ(v1[2], 3);
	EXPECT_EQ(v1[3], 0);
}

TEST(AffineVectorMethods, dot_with_point) {
	AffineVector v(1, 2, 3);
	AffinePoint p(2, 3, 7);
	double result = v.dot(p);
	EXPECT_EQ(result, 29);
}

TEST(AffineVectorMethods, dot_with_vector) {
	AffineVector v1(1, 2, 3);
	AffineVector v2(2, 3, 7);
	double result = v1.dot(v2);
	EXPECT_EQ(result, 29);
}

TEST(AffineVectorMethods, cross) {
	AffineVector v1(1, 2, 3);
	AffineVector v2(2, 3, 7);
	AffineVector v3 = v1.cross(v2);
	AffineVector v4(5, -1, -1);
	EXPECT_EQ(v3, v4);
}
