#include "pch.h"

#define protected public
#define private public

#include "../QRCodeLibrary/DataBlocks.hpp"

using std::vector;
using std::pair;

TEST(DataBlocksTests, ComposesSizesOfDatablocks) {
	vector<pair<unsigned, unsigned>> db_s;

	DataBlocks::divide_to_blocks(db_s, 182, 5);

	const vector<pair<unsigned, unsigned>> res{ {36, 0}, {36, 36}, {36, 72}, {37, 108}, {37, 145} };
	EXPECT_EQ(db_s, res);
}

TEST(DataBlocksTests, GeneratesECBytes) {
	const byte_list input{ 64, 196, 132, 84, 196, 196, 242, 194, 4, 132, 20, 37, 34, 16, 236, 17 };
	byte_list tmp;

	DataBlocks::compose_EC_bytes(tmp, input.cbegin(), 28, 16);

	const byte_list res{ 16, 85, 12, 231, 54, 54, 140, 70, 118, 84, 10, 174, 235, 197, 99, 218, 12, 254, 246, 4, 190, 56, 39, 217, 115, 189, 193, 24 };
	EXPECT_EQ(tmp, res);
}

TEST(DataBlocksTests, JoinsDataAndECBlocks) {
	byte_list joined;
	const byte_list e_data{
		67, 85, 70, 134, 87, 38, 85, 194, 119, 50, 6, 18, 6, 103, 38,
		246, 246, 66, 7, 118, 134, 242, 7, 38, 86, 22, 198, 199, 146, 6,
		182, 230, 247, 119, 50, 7, 118, 134, 87, 38, 82, 6, 134, 151, 50, 7,
		70, 247, 118, 86, 194, 6, 151, 50, 16, 236, 17, 236, 17, 236, 17, 236
	};
	const vector<pair<unsigned, unsigned>> d_b_sizes{ {15, 0}, {15, 15}, {16, 30}, {16, 46} };
	const vector<byte_list> EC_blocks{
		{ 213, 199, 11, 45, 115, 247, 241, 223, 229, 248, 154, 117, 154, 111, 86, 161, 111, 39 },
		{ 87, 204, 96, 60, 202, 182, 124, 157, 200, 134, 27, 129, 209, 17, 163, 163, 120, 133 },
		{ 148, 116, 177, 212, 76, 133, 75, 242, 238, 76, 195, 230, 189, 10, 108, 240, 192, 141 },
		{ 235, 159, 5, 173, 24, 147, 59, 33, 106, 40, 255, 172, 82, 2, 131, 32, 178, 236 }
	};

	DataBlocks::join_data_and_EC_blocks(joined, e_data, d_b_sizes, EC_blocks, 18);

	const byte_list res{
		67, 246, 182, 70, 85, 246, 230, 247, 70, 66, 247, 118, 134, 7, 119,
		86, 87, 118, 50, 194, 38, 134, 7, 6, 85, 242, 118, 151, 194, 7,
		134, 50, 119, 38, 87, 16, 50, 86, 38, 236, 6, 22, 82, 17, 18,
		198, 6, 236, 6, 199, 134, 17, 103, 146, 151, 236, 38, 6, 50, 17,
		7, 236, 213, 87, 148, 235, 199, 204, 116, 159, 11, 96, 177, 5, 45,
		60, 212, 173, 115, 202, 76, 24, 247, 182, 133, 147, 241, 124, 75, 59,
		223, 157, 242, 33, 229, 200, 238, 106, 248, 134, 76, 40, 154, 27, 195,
		255, 117, 129, 230, 172, 154, 209, 189, 82, 111, 17, 10, 2, 86, 163,
		108, 131, 161, 163, 240, 32, 111, 120, 192, 178, 39, 133, 141, 236
	};
	EXPECT_EQ(joined, res);
}

TEST(DataBlocksTests, ComposesJoinedDataAndECBlocks) {
	const byte_list e_data{
		67, 85, 70, 134, 87, 38, 85, 194, 119, 50, 6, 18, 6, 103, 38,
		246, 246, 66, 7, 118, 134, 242, 7, 38, 86, 22, 198, 199, 146, 6,
		182, 230, 247, 119, 50, 7, 118, 134, 87, 38, 82, 6, 134, 151, 50, 7,
		70, 247, 118, 86, 194, 6, 151, 50, 16, 236, 17, 236, 17, 236, 17, 236
	};

	DataBlocks db(e_data, CorrectionLevel::Q, 4);

	const byte_list joined{
		67, 246, 182, 70, 85, 246, 230, 247, 70, 66, 247, 118, 134, 7, 119,
		86, 87, 118, 50, 194, 38, 134, 7, 6, 85, 242, 118, 151, 194, 7,
		134, 50, 119, 38, 87, 16, 50, 86, 38, 236, 6, 22, 82, 17, 18,
		198, 6, 236, 6, 199, 134, 17, 103, 146, 151, 236, 38, 6, 50, 17,
		7, 236, 213, 87, 148, 235, 199, 204, 116, 159, 11, 96, 177, 5, 45,
		60, 212, 173, 115, 202, 76, 24, 247, 182, 133, 147, 241, 124, 75, 59,
		223, 157, 242, 33, 229, 200, 238, 106, 248, 134, 76, 40, 154, 27, 195,
		255, 117, 129, 230, 172, 154, 209, 189, 82, 111, 17, 10, 2, 86, 163,
		108, 131, 161, 163, 240, 32, 111, 120, 192, 178, 39, 133, 141, 236
	};

	EXPECT_EQ(db.get_joined_data_and_EC_blocks(), joined);
}