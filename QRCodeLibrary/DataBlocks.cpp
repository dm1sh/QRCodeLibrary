#include "pch.h"

#include "DataBlocks.hpp"
#include "Tables.hpp"

vector<unsigned char>& DataBlocks::compose_data_and_EC_blocks()
{
	vector<pair<unsigned, unsigned>>data_block_sizes;

	divide_to_blocks(data_block_sizes, e_data.size(), Tables::data_blocks_number.at(corr_lvl).at(version));

	unsigned EC_bytes_number = Tables::correction_bytes_num.at(corr_lvl).at(version);
	vector<vector<unsigned char>> EC_blocks(data_block_sizes.size(), vector<unsigned char>());
	for (unsigned i = 0; i < data_block_sizes.size(); i++)
		compose_EC_bytes(EC_blocks[i], e_data.cbegin() + data_block_sizes[i].second, EC_bytes_number, data_block_sizes[i].first);

	return data;
}

void DataBlocks::divide_to_blocks(vector<pair<unsigned, unsigned>>& db_sizes, unsigned data_size, unsigned db_number)
{
	db_sizes.reserve(db_number);

	for (unsigned i = 0; i < db_number; i++)
		db_sizes.push_back(std::make_pair(data_size / db_number, data_size / db_number * i));

	for (unsigned i = 0; i < data_size % db_number; i++) {
		db_sizes[db_number - 1 - i].first++;
		db_sizes[db_number - 1 - i].second += (data_size % db_number - 1 - i);
	}
}

void DataBlocks::compose_EC_bytes(vector<unsigned char>& res, const vector<unsigned char>::const_iterator& src, unsigned corr_bytes_num, unsigned db_size)
{
	res.reserve(max(db_size, corr_bytes_num));
	res.insert(res.end(), src, src + db_size);
	res.resize(res.capacity(), 0);

	for (unsigned j = 0; j < db_size; j++) {
		unsigned char A = res[0];
		res.erase(res.begin());
		res.push_back(0);

		if (A == 0)
			continue;

		unsigned char B = Tables::reverse_galois_field.at(A);

		for (unsigned k = 0; k < corr_bytes_num; k++) {
			unsigned char C = (Tables::reed_solomon_generative_polynomial.at(corr_bytes_num).at(k) + B) % 255;
			res[k] ^= Tables::galois_field[C];
		}
	}
}
