#include "pch.h"

#define protected public
#define private public

#include "../QRCodeLibrary/DataBlocks.hpp"

TEST(DataBlocksTests, ComposesSizesOfDatablocks) {
	vector<pair<unsigned, unsigned>> db_s;
	vector<pair<unsigned, unsigned>> res{ {36, 0}, {36, 36}, {36, 72}, {37, 108}, {37, 145} };

	DataBlocks::divide_to_blocks(db_s, 182, 5);

	EXPECT_EQ(db_s, res);
}

TEST(DataBlocksTests, GeneratesECBytes) {
	vector<unsigned char> input{ 64, 196, 132, 84, 196, 196, 242, 194, 4, 132, 20, 37, 34, 16, 236, 17 };
	vector<unsigned char> tmp;
	vector<unsigned char> res{ 16, 85, 12, 231, 54, 54, 140, 70, 118, 84, 10, 174, 235, 197, 99, 218, 12, 254, 246, 4, 190, 56, 39, 217, 115, 189, 193, 24 };

	DataBlocks::compose_EC_bytes(tmp, input.cbegin(), 28, 16);

	EXPECT_EQ(tmp, res);
}

TEST(DataBlocksTests, ComposesDataAndECBlocks) {
	DataBlocks db(vector<unsigned char>(182), CorrectionLevel::M, 8);
}