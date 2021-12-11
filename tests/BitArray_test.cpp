#include "pch.h"

#define protected public
#define private public

#include "../QRCodeLibrary/BitArray.hpp"

class BitArrayTests: public ::testing::Test {
public:
	BitArrayTests() : ::testing::Test(), a1(15) {};

	void SetUp() override {
		a1.v[0] = static_cast<unsigned char>(0b10101010);
		a1.v[1] = static_cast<unsigned char>(0b11111111);
	}

protected:
	BitArray a1;
};

TEST_F(BitArrayTests, GetsBitByIndex) {
	EXPECT_EQ(a1.get(10), 1);
	EXPECT_EQ(a1.get(0), 1);
	EXPECT_EQ(a1.get(1), 0);
}

TEST_F(BitArrayTests, SetsIndividualBit) {
	a1.set(0, 0);
	a1.set(1, 1);
	EXPECT_EQ(a1.get(0), 0);
	EXPECT_EQ(a1.get(1), 1);
}

TEST_F(BitArrayTests, SetsMultipleBits) {
	a1.set(9, 0b00110, 5);
	EXPECT_EQ(a1.v[1], 0b10011011);

	a1.set(2, 0b111, 3);
	EXPECT_EQ(a1.v[0], 0b10111010);
}
