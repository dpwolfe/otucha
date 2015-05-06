#include "gtest/gtest.h"
#include "Matrix4x4.hpp"

using namespace rffalcon;

TEST(Matrix4x4Constructors, equality_with_default_constructor) {
    Matrix4x4 m;
    EXPECT_EQ(m, m);
}

TEST(Matrix4x4Constructors, default_constructor_is_identity) {
	Matrix4x4 m1;
	Matrix4x4 m2(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	EXPECT_EQ(m1, m2);
}

TEST(Matrix4x4Operators, equality_with_explicit_constructor) {
	Matrix4x4 m(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
	EXPECT_EQ(m, m);
}

TEST(Matrix4x4Operators, equality_with_copy_constructor) {
	Matrix4x4 m1(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
	Matrix4x4 m2(m1);
	EXPECT_EQ(m1, m2);
}

TEST(Matrix4x4Operators, not_equal) {
	Matrix4x4 m1(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
	Matrix4x4 m2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0);
	EXPECT_NE(m1, m2);
}

TEST(Matrix4x4Operators, inverse_multiplied_by_original_equals_identity) {
	Matrix4x4 m1(1, 1, 2, 1, 3, 1, 5, 2, 6, 2, 8, 1, 1, 2, 2, 1);
	Matrix4x4 m2(-18, 6, -1, 7, -1, 0, 0, 1, 15, -5, 1, -6, -10, 4, -1, 4);
	Matrix4x4 m3 = m1 * m2;
	EXPECT_EQ(Matrix4x4::Identity, m3);
}

TEST(Matrix4x4Operators, double_brackets) {
	Matrix4x4 m1(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
	for (int index = 0; index < 16; index++) {
		EXPECT_EQ(m1[index / 4][index % 4], index);
	}
}

TEST(Matrix4x4Operators, assignment) {
	Matrix4x4 m1(1, 1, 2, 3, 1, 5, 6, 2, 8, 1, 4, 5, 2, 3, 5, 6);
	Matrix4x4 m2(-18, 6, -1, 7, -1, 0, 0, 1, 15, -5, 1, -6, -10, 4, -1, 4);
	EXPECT_NE(m1, m2);
	m1 = m2;
	EXPECT_EQ(m1, m2);
}

TEST(Matrix4x4Methods, copy_to_column_major) {
	Matrix4x4 m1(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
	float cm[16];
	m1.copyToColumnMajor(cm);
	float expected[16] = { 0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15 };
	for (int i = 0; i < 16; i++)
	{
		EXPECT_EQ(cm[i], expected[i]);
	}
}

TEST(Matrix4x4Methods, orthographic) {
	Matrix4x4 m1 = Matrix4x4::orthographic(-1, 3, -2, 6, -3, 13);
	Matrix4x4 m2(0.5, 0, 0, -0.5, 0, 0.25, 0, -0.5, 0, 0, -0.125, -0.625, 0, 0, 0, 1);
	EXPECT_EQ(m1, m2);
}

TEST(Matrix4x4Methods, perspective) {
	Matrix4x4 m1 = Matrix4x4::perspective(-1, 3, -2, 6, -3, -1, -1);
	Matrix4x4 m2(0.5, 0, 0.5, 0, 0, 0.25, 0.5, 0, 0, 0, -2, -3, 0, 0, -1, 0);
	EXPECT_EQ(m1, m2);
}

TEST(Matrix4x4Methods, lookAt) {
	rffalcon::AffinePoint eye(1.0, 1.0, 1.0);
	rffalcon::AffinePoint center(0, 0, 0);
	rffalcon::AffineVector up(0, 1, 0);
	Matrix4x4 m1 = Matrix4x4::lookAt(eye, center, up);
	Matrix4x4 m2(0.70710678118654757, 0, -0.70710678118654757, 0,
		-0.40824829046386307, 0.81649658092772615, -0.40824829046386307, 0,
		0.57735026918962584, 0.57735026918962584, 0.57735026918962584, -1.7320508075688776,
		0, 0, 0, 1);
	EXPECT_EQ(m1, m2);
}