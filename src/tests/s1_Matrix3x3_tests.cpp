#include "gtest/gtest.h"
#include "Matrix3x3.hpp"

using namespace s1;

TEST(Matrix3x3Constructors, equality_with_default_constructor) {
    Matrix3x3 m;
    EXPECT_EQ(m, m);
}

TEST(Matrix3x3Constructors, default_constructor_is_identity) {
	Matrix3x3 m1;
	Matrix3x3 m2(1, 0, 0, 0, 1, 0, 0, 0, 1);
	EXPECT_EQ(m1, m2);
}

TEST(Matrix3x3Constructors, constructor_with_Matrix4x4_properly_takes_3x3_elements) {
	Matrix4x4 m4x4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
	Matrix3x3 m3x3(m4x4);
	Matrix3x3 m3x3expected(0, 1, 2, 4, 5, 6, 8, 9, 10);
	EXPECT_EQ(m3x3, m3x3expected);
}

TEST(Matrix3x3Operators, equality_with_explicit_constructor) {
	Matrix3x3 m(0, 1, 2, 3, 4, 5, 6, 7, 8);
	EXPECT_EQ(m, m);
}

TEST(Matrix3x3Operators, equality_with_copy_constructor) {
	Matrix3x3 m1(0, 1, 2, 3, 4, 5, 6, 7, 8);
	Matrix3x3 m2(m1);
	EXPECT_EQ(m1, m2);
}

TEST(Matrix3x3Operators, not_equal) {
	Matrix3x3 m1(0, 1, 2, 3, 4, 5, 6, 7, 8);
	Matrix3x3 m2(1, 2, 3, 4, 5, 6, 7, 8, 0);
	EXPECT_NE(m1, m2);
}

TEST(Matrix3x3Operators, inverse_multiplied_by_original_equals_identity) {
	Matrix3x3 m1(1, 1, 2, 3, 1, 5, 6, 2, 8);
	Matrix3x3 m2(-0.5, -1, 0.75, 1.5, -1, 0.25, 0, 1, -0.5);
	Matrix3x3 m3 = m1 * m2;
	EXPECT_EQ(Matrix3x3::Identity, m3);
}

TEST(Matrix3x3Methods, transpose) {
	Matrix3x3 m1(0, 1, 2, 3, 4, 5, 6, 7, 8);
	Matrix3x3 m2 = m1.transpose();
	Matrix3x3 m3(0, 3, 6, 1, 4, 7, 2, 5, 8);
	EXPECT_EQ(m2, m3);
}

TEST(Matrix3x3Methods, transpose_twice) {
	Matrix3x3 m1(0, 1, 2, 3, 4, 5, 6, 7, 8);
	Matrix3x3 m2 = m1.transpose().transpose();
	EXPECT_EQ(m1, m2);
}

TEST(Matrix3x3Methods, inverse_identity_equals_identity) {
	Matrix3x3 m1;
	Matrix3x3 m2 = m1.inverse();
	EXPECT_EQ(m1, m2);
}

TEST(Matrix3x3Methods, inverse) {
	Matrix3x3 m1(1, 1, 2, 3, 1, 5, 6, 2, 8);
	Matrix3x3 m2 = m1.inverse();
	Matrix3x3 m3(-0.5, -1, 0.75, 1.5, -1, 0.25, 0, 1, -0.5);
	EXPECT_EQ(m2, m3);
}

TEST(Matrix3x3Methods, inverse_twice) {
	Matrix3x3 m1(1, 1, 2, 3, 1, 5, 6, 2, 8);
	Matrix3x3 m2 = m1.inverse().inverse();
	EXPECT_EQ(m1, m2);
}

TEST(Matrix3x3Methods, copy_to_column_major) {
	Matrix3x3 m1(0, 1, 2, 3, 4, 5, 6, 7, 8);
	float cm[9];
	m1.copyToColumnMajor(cm);
	float expected[9] = { 0, 3, 6, 1, 4, 7, 2, 5, 8 };
	for (int i = 0; i < 9; i++)
	{
		EXPECT_EQ(cm[i], expected[i]);
	}
}
