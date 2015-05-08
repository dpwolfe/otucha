#include "gtest/gtest.h"
#include "AffinePoint.hpp"

using namespace rffalcon;

TEST(AffinePointConstructors, equality_with_default_constructor) {
	AffinePoint p;
	EXPECT_EQ(p, p);
}

TEST(AffinePointConstructors, default_constructor_is_zero) {
	AffinePoint p1;
	AffinePoint p2(0, 0, 0);
	EXPECT_EQ(p1, p2);
}

TEST(AffinePointOperators, equality_with_explicit_constructor) {
	AffinePoint p(1, 2, 3);
	EXPECT_EQ(p, p);
}

TEST(AffinePointOperators, equality_with_copy_constructor) {
	AffinePoint p1(1, 2, 3);
	AffinePoint p2(p1);
	EXPECT_EQ(p1, p2);
}

TEST(AffinePointOperators, not_equal) {
	AffinePoint p1(1, 2, 3);
	AffinePoint p2(2, 3, 4);
	EXPECT_NE(p1, p2);
}

TEST(AffinePointOperators, assignment) {
	AffinePoint p1(1, 2, 3);
	AffinePoint p2(-0.5, -1, 0.75);
	EXPECT_NE(p1, p2);
	p1 = p2;
	EXPECT_EQ(p1, p2);
}

TEST(AffinePointOperators, subtract) {
	AffinePoint p1(1, 2, 3);
	AffinePoint p2(2, 3, 4);
	AffineVector p3 = p1 - p2;
	AffineVector p4(-1, -1, -1);
	EXPECT_EQ(p3, p4);
}
