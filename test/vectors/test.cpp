/*
   This test checks the vector functionality.
   */

#include "tmath.hpp"
#include "tmath_test.hpp"

int main(int argc, char const *argv[]) {
	using TMathTest::assertTrue;
	using TMathTest::assertError;
	using TMath::DOUBLE;
	using TMath::Vector;

	Vector nullVector1 {0, 0, 0};
	Vector nullVector2(3);
	Vector smallVector(0);

	// check equality operator
	assertTrue(nullVector1 == nullVector2, "{0, 0, 0} == Vector(3)");
	assertError([&](){ nullVector1 == smallVector; }, "{0, 0, 0} == Vector(0)");

	Vector identityVector1 = {1, 0, 0};
	Vector identityVector2 = {0, 1, 0};
	Vector identityVector3 = {0, 0, 1};

	// check unequality operator
	assertTrue(identityVector1 != identityVector2, "{1, 0, 0} != {0, 1, 0}");
	assertError([&](){ identityVector1 != smallVector; }, "{1, 0, 0} != Vector(0)");

	Vector vectorSum1 = identityVector1 + identityVector2;
	Vector vectorSum2 = vectorSum1 + identityVector3;
	Vector vectorSum3 = {1, 1, 1};

	// check add operator
	assertTrue(vectorSum2 == vectorSum3, "{1, 0, 0} + {0, 1, 0} + {0, 0, 1} == {1, 1, 1}");
	assertError([&]() { vectorSum1 + smallVector; }, "{1, 0, 0} + Vector(0)");

	Vector vectorSub1 = vectorSum1 - identityVector1;
	Vector vectorSub2 = vectorSub1 - identityVector2;

	// check subtraction operator
	assertTrue(vectorSub1 == identityVector2, "{1, 1, 0} - {1, 0, 0} == {0, 1, 0}");
	assertError([&](){ vectorSub1 - smallVector; }, "{0, 1, 0} - Vector(0)");

	Vector vectorScalar1 { 2, 2, 2 };
	Vector vectorScalar2 { 0.5, 0.5, 0.5 };
	Vector vectorScalar3 { -1, -1, -1 };
	DOUBLE scalar1 = 2.0;
	DOUBLE scalar2 = 0.0;
	DOUBLE scalar3 = -1.0;

	// check scalar multiplication
	assertTrue(vectorSum3 * scalar1 == vectorScalar1, "{1, 1, 1} * 2.0 == {2.0, 2.0, 2.0}");
	assertTrue(vectorSum3 / scalar1 == vectorScalar2, "{1, 1, 1} / 2.0 == {0.5, 0.5, 0.5}");
	assertTrue(vectorSum3 * scalar2 == nullVector1, "{1, 1, 1} * 0 == {0, 0, 0}");
	assertTrue(vectorSum3 * scalar3 == vectorScalar3, "{1, 1, 1} * -1 == {-1, -1, -1}");

	// check vector inversion
	assertTrue(-vectorSum3 == vectorScalar3, "-{1, 1, 1} == {-1, -1, -1}");

	// check dot product operator
	DOUBLE dotProduct1 = 1;
	DOUBLE dotProduct2 = 0;
	DOUBLE dotProduct3 = 3;

	assertTrue(vectorSum3.dot(identityVector1) == dotProduct1, "{1, 1, 1} (dot) {1, 0, 0} == 1");
	assertTrue(identityVector1.dot(identityVector2) == dotProduct2, "{1, 0, 0} (dot) {0, 1, 0} == 0");
	assertTrue(vectorSum3.dot(vectorSum3) == dotProduct3, "{1, 1, 1} (dot) {1, 1, 1} == 3");
	assertError([&](){ vectorSum3.dot(smallVector); }, "{1, 1, 1} (dot) Vector(0)");

	// check cross product operator
	Vector crossProduct1 {0, 0, 0};
	Vector crossProduct2 {0, 1, -1};
	Vector crossProduct3 {-1, 0, 1};

	assertTrue(vectorSum3.cross(vectorSum3) == crossProduct1, "{1, 1, 1} x {1, 1, 1} == {0, 0, 0}");
	assertTrue(vectorSum3.cross(identityVector1) == crossProduct2, "{1, 1, 1} x {1, 0, 0} == {0, 1, -1}");
	assertTrue(vectorSum3.cross(identityVector2) == crossProduct3, "{1, 1, 1} x {0, 1, 0} == {-1, 0, 1}");
	assertError([&](){ vectorSum3.cross(smallVector);}, "{1, 1, 1} x Vector(0)");

	// check sum operation
	DOUBLE sum1 = 1;
	DOUBLE sum2 = 3;
	DOUBLE sum3 = 0;

	assertTrue(identityVector1.sum() == sum1, "sum({1, 0, 0}) == 1");
	assertTrue(vectorSum3.sum() == sum2, "sum({1, 1, 1}) == 3");
	assertTrue(nullVector1.sum() == sum3, "sum({0, 0, 0}) == 0");

	// check norm operation
	Vector normVector1 {2, 2, 1};
	Vector normedVector1 {2.0/3.0, 2.0/3.0, 1.0/3.0};
	assertTrue(identityVector1.norm() == identityVector1, "norm({1, 0, 0}) == {1, 0, 0}");
	assertTrue(identityVector2.norm() == identityVector2, "norm({0, 1, 0}) == {0, 1, 0}");
	assertTrue(identityVector3.norm() == identityVector3, "norm({0, 0, 1}) == {0, 0, 1}");
	assertTrue(normVector1.norm() == normedVector1, "norm({2, 2, 1}) == {2/3, 2/3, 1/3}");
	assertError([&](){ smallVector.norm(); }, "norm(Vector(0))");

	return 0;
}
