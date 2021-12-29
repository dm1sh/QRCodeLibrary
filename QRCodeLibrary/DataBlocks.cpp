#include "pch.h"

#include "DataBlocks.hpp"
#include "Tables.hpp"
#include "utils.hpp"

DataBlocks::DataBlocks(const byte_list& e_data_, CorrectionLevel corr_lvl_, char version_) : e_data{ e_data_ }, corr_lvl{ corr_lvl_ }, version{ version_ } 
{
	vector<pair<unsigned, unsigned>>data_block_sizes;

	divide_to_blocks(data_block_sizes, to_U(e_data.size()), Tables::data_blocks_number.at(corr_lvl).at(version));

	unsigned EC_bytes_number = Tables::correction_bytes_num.at(corr_lvl).at(version);
	vector<byte_list> EC_blocks(data_block_sizes.size(), byte_list());

	for (unsigned i = 0; i < data_block_sizes.size(); i++)
		compose_EC_bytes(EC_blocks[i], e_data.cbegin() + data_block_sizes[i].second, EC_bytes_number, data_block_sizes[i].first);

	join_data_and_EC_blocks(data, e_data, data_block_sizes, EC_blocks, EC_bytes_number);
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

void DataBlocks::compose_EC_bytes(byte_list& res, const byte_list::const_iterator& src, unsigned corr_bytes_num, unsigned db_size)
{
	res.reserve(max(db_size, corr_bytes_num));
	res.insert(res.end(), src, src + db_size);
	res.resize(res.capacity(), 0);

	auto gen_poly = Tables::reed_solomon_generative_polynomial.at(corr_bytes_num);

	for (unsigned j = 0; j < db_size; j++) {
		unsigned char A = res[0]; 
		res.erase(res.begin());
		res.push_back(0);

		if (A == 0)
			continue;

		unsigned char B = Tables::reverse_galois_field.at(A);

		for (unsigned k = 0; k < corr_bytes_num; k++) {
			unsigned char C = (gen_poly.at(k) + B) % 255;
			res[k] ^= Tables::galois_field[C];
		}
	}
}

unsigned get_db_byte_index(unsigned block_index, unsigned byte_index, const vector<pair<unsigned, unsigned>>& db_sizes) {
	return db_sizes[block_index].second + byte_index;
}

void DataBlocks::join_data_and_EC_blocks(byte_list& res, const byte_list& e_data, const vector<pair<unsigned, unsigned>>& db_sizes, const vector<byte_list>& ec_codes, unsigned ec_bytes_number)
{
	res.reserve(e_data.size() + ec_codes.at(0).size() * ec_codes.size());

	for (unsigned i = 0; i < db_sizes[db_sizes.size() - 1].first; i++)
		for (unsigned j = 0; j < db_sizes.size(); j++)
			if (i < db_sizes[j].first)
				res.push_back(e_data[get_db_byte_index(j, i, db_sizes)]);

	for (unsigned i = 0; i < ec_bytes_number; i++)
		for (unsigned j = 0; j < ec_codes.size(); j++)
			res.push_back(ec_codes[j][i]);
}
