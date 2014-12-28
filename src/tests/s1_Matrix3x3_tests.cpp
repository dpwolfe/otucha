#include "catch.hpp"
#include "Matrix3x3.h"

TEST_CASE("Matrix3x3 equality with default constructor", "[operators]") {
	s1::Matrix3x3 m;
	REQUIRE(m == m);
}

TEST_CASE("Matrix3x3 default constructor is identity", "[constructors]") {
	s1::Matrix3x3 m1;
	s1::Matrix3x3 m2(1, 0, 0, 0, 1, 0, 0, 0, 1);
	REQUIRE(m1 == m2);
}

TEST_CASE("Matrix3x3 equality with explicit constructor", "[operators]") {
	s1::Matrix3x3 m(0, 1, 2, 3, 4, 5, 6, 7, 8);
	REQUIRE(m == m);
}

TEST_CASE("Matrix3x3 equality with copy constructor", "[operators]") {
	s1::Matrix3x3 m1(0, 1, 2, 3, 4, 5, 6, 7, 8);
	s1::Matrix3x3 m2(m1);
	REQUIRE(m1 == m2);
}

TEST_CASE("Matrix3x3 not equal", "[operators]") {
	s1::Matrix3x3 m1(0, 1, 2, 3, 4, 5, 6, 7, 8);
	s1::Matrix3x3 m2(1, 2, 3, 4, 5, 6, 7, 8, 0);
	REQUIRE(m1 != m2);
}

TEST_CASE("Matrix3x3 transpose", "[methods]") {
	s1::Matrix3x3 m1(0, 1, 2, 3, 4, 5, 6, 7, 8);
	s1::Matrix3x3 m2 = m1.transpose();
	s1::Matrix3x3 m3(0, 3, 6, 1, 4, 7, 2, 5, 8);
	REQUIRE(m2 == m3);
}

TEST_CASE("Matrix3x3 transpose twice", "[methods]") {
	s1::Matrix3x3 m1(0, 1, 2, 3, 4, 5, 6, 7, 8);
	s1::Matrix3x3 m2 = m1.transpose().transpose();
	REQUIRE(m1 == m2);
}

TEST_CASE("Matrix3x3 inverse identity equals identity", "[methods]") {
	s1::Matrix3x3 m1;
	s1::Matrix3x3 m2 = m1.inverse();
	REQUIRE(m1 == m2);
}

TEST_CASE("Matrix3x3 inverse", "[methods]") {
	s1::Matrix3x3 m1(1, 1, 2, 3, 1, 5, 6, 2, 8);
	s1::Matrix3x3 m2 = m1.inverse();
	s1::Matrix3x3 m3(-0.5, -1, 0.75, 1.5, -1, 0.25, 0, 1, -0.5);
	REQUIRE(m2 == m3);
}

TEST_CASE("Matrix3x3 inverse twice", "[methods]") {
	s1::Matrix3x3 m1(1, 1, 2, 3, 1, 5, 6, 2, 8);
	s1::Matrix3x3 m2 = m1.inverse().inverse();
	REQUIRE(m1 == m2);
}