#pragma once

#include <vector>

#include "BitArray.hpp"
#include "Method.hpp"

using namespace std;

class DataBlocks
{
public:
	DataBlocks(const vector<unsigned char>& e_data_, CorrectionLevel corr_lvl_, unsigned char version_) : e_data{ e_data_ }, corr_lvl{ corr_lvl_ }, version{ version_ } {};

	vector<unsigned char>& compose_joined_data_and_EC_blocks();

	static void divide_to_blocks(vector<pair<unsigned, unsigned>>& db_sizes, unsigned data_size, unsigned db_number);
	static void compose_EC_bytes(vector<unsigned char>& res, const vector<unsigned char>::const_iterator& src, unsigned corr_bytes_num, unsigned db_size);
	static void join_data_and_EC_blocks(vector<unsigned char>&res, const vector<unsigned char>& e_data, const vector<pair<unsigned, unsigned>>& db_sizes, const vector<vector<unsigned char>>& ec_codes);

private:
	const vector<unsigned char>& e_data;
	CorrectionLevel corr_lvl;
	unsigned char version;

	vector<unsigned char> data;
};

