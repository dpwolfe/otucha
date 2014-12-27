#include "catch.hpp"
#include "Matrix3x3.h"

TEST_CASE("Matrix3x3", "[inverse]") {
	s1::Matrix3x3 m(0,0,0,0,0,0,0,0,0);

	SECTION("equals itself") {
		REQUIRE(m == m);
	}
}