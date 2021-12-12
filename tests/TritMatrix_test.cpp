#include "pch.h"

#define protected public
#define private public

#include "../QRCodeLibrary/TritMatrix.hpp"

TEST(TritMatrixTests, CreatesVectorOfVectors) {
	TritMatrix m(5, 4);

	ASSERT_EQ(m.c.size(), 4);

	for (int i = 0; i < 4; i++)
		EXPECT_EQ(m.c[i].size(), 5);
}

TEST(TritMatrixTests, GetsByCoordinates) {
	TritMatrix m(5, 4);

	m.c[1][4] = Trit::F;

	EXPECT_EQ(m.get(1, 4), Trit::F);
	EXPECT_EQ(m.get(1, 3), Trit::EMPTY);
}

TEST(TritMatrixTests, SetsIndividualCell) {
	TritMatrix m(5, 4);

	m.set(1, 3, Trit::T);

	EXPECT_EQ(m.get(1, 3), Trit::T);
	EXPECT_EQ(m.get(1, 4), Trit::EMPTY);

	m.set(1, 4, Trit::F);

	EXPECT_EQ(m.get(1, 3), Trit::T);
	EXPECT_EQ(m.get(1, 4), Trit::F);
}

TEST(TritMatrixTests, SetsIndividualCellWithBool) {
	TritMatrix m(5, 4);

	m.set(1, 3, 1);

	EXPECT_EQ(m.get(1, 3), Trit::T);
	EXPECT_EQ(m.get(1, 4), Trit::EMPTY);

	m.set(1, 4, 0);

	EXPECT_EQ(m.get(1, 3), Trit::T);
	EXPECT_EQ(m.get(1, 4), Trit::F);
}

TEST(TritMatrixTests, ConvertsToString) {
	TritMatrix m(2, 2);

	m.set(0, 0, 1);
	m.set(1, 0, 0);
	m.set(1, 1, 1);

	EXPECT_EQ(m.to_string(), "1E\n01");
}

TEST(TritMatrixTests, SetsMultipleCells) {
	TritMatrix m(5, 4);

	m.set(1, 1, 0b101, 3);

	ASSERT_EQ(m.to_string(), "EEEEE\nE101E\nEEEEE\nEEEEE");

	m.set(2, 0, 0b11111, 5);

	ASSERT_EQ(m.to_string(), "EEEEE\nE101E\n11111\nEEEEE");

	m.set(2, 1, 0b010, 3);

	EXPECT_EQ(m.to_string(), "EEEEE\nE101E\n10101\nEEEEE");
}

TEST(TritMatrixTests, ConvertsToASCII) {
	TritMatrix m(2, 2);

	m.set(0, 0, 0b10, 2);
	m.set(1, 0, 0b01, 2);

	EXPECT_EQ(m.to_ascii(), "# \n #");
}
