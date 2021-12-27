#pragma once

#include <vector>

#include "BitArray.hpp"
#include "Method.hpp"

using namespace std;

// Разделяет данные на блоки, генерирует для них коды коррекции и объединяет их
class DataBlocks
{
public:
	DataBlocks(const byte_list& e_data_, CorrectionLevel corr_lvl_, char version_);

	// Возвращает массив из соединённых блоков
	byte_list& get_joined_data_and_EC_blocks() { return data; };

	// Считает размеры блоков данных
	static void divide_to_blocks(vector<pair<unsigned, unsigned>>& db_sizes, unsigned data_size, unsigned db_number);
	// Генерирует коды коррекции для данного блока данных
	static void compose_EC_bytes(byte_list& res, const byte_list::const_iterator& src, unsigned corr_bytes_num, unsigned db_size);
	// Объединяет данные и коды коррекции
	static void join_data_and_EC_blocks(byte_list&res, const byte_list& e_data, const vector<pair<unsigned, unsigned>>& db_sizes, const vector<byte_list>& ec_codes, unsigned ec_bytes_number);

private:
	const byte_list& e_data;
	CorrectionLevel corr_lvl;
	char version;

	byte_list data;
};

