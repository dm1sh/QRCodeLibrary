#pragma once

#include <vector>

#include "BitArray.hpp"
#include "Method.hpp"

using namespace std;

class DataBlocks
{
public:
	DataBlocks(const BitArray& e_data_, CorrectionLevel corr_lvl_, unsigned char version_) : e_data{ e_data_ }, corr_lvl{ corr_lvl_ }, version{ version_ } {};

	vector<unsigned char>& compose_data_and_EC_blocks();

private:
	const BitArray& e_data;
	CorrectionLevel corr_lvl;
	unsigned char version;

	vector<unsigned char> data;
};

