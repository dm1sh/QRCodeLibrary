#include "pch.h"

#include "Encoder.hpp"
#include "Tables.hpp"
#include "utils.hpp"

#include <stdexcept>

BitArray& Encoder::encode()
{
	unsigned encoded_bit_num = calculate_encoded_input_size(to_U(input.size()), method);
	unsigned metadata_bit_num = calculate_metadata_size(method, ((version < 0) ? 0 : version));

	if (version < 0) {
		version = 0;
		while (metadata_bit_num + encoded_bit_num >= Tables::max_capability.at(corr_lvl).at(version)) {
			version = determite_version(metadata_bit_num + encoded_bit_num, corr_lvl);
			metadata_bit_num = calculate_metadata_size(method, version);
		}
	}
	else if (metadata_bit_num + encoded_bit_num >= Tables::max_capability.at(corr_lvl).at(version))
		throw std::invalid_argument("This version is too low for input of this size. Set negative version to calculate it dynamicly");

	e.resize(Tables::max_capability.at(corr_lvl).at(version));

	write_metadata(to_U(input.size()), metadata_bit_num - 4, method, e);
	encode_input(metadata_bit_num);

	pad_data(e, metadata_bit_num + encoded_bit_num);

	return e;
}

char Encoder::determite_version(unsigned size, CorrectionLevel corr_lvl)
{
	const auto& sizes = Tables::max_capability.at(corr_lvl);

	char version = upper_index(sizes, size);
	if (version > 39) throw std::runtime_error("Too much data. There is no such QR code version that can store so mush characters");

	return version;
}

unsigned Encoder::calculate_metadata_size(QRCodeMethod method, char version)
{
	if (method == QRCodeMethod::Dynamic) throw std::runtime_error("Specify correct method");

	unsigned char size = 0;

	auto lengths = Tables::data_amount_lengths.at(method);

	for (int i = 0; i < 3 && lengths[i].first <= version; i++)
		size = lengths[i].second;

	return size + 4;
}

void Encoder::write_metadata(unsigned input_size, unsigned input_bits_amount_size, QRCodeMethod method, BitArray& out)
{
	if (method == QRCodeMethod::Dynamic) throw std::runtime_error("Specify correct method");

	out.set(0, Tables::mode_indicator.at(method), 4);
	out.set(4, input_size, input_bits_amount_size);
}

void Encoder::encode_numeric(const string& input, BitArray& out, unsigned offset)
{
	for (unsigned i = 0; i < input.size() / 3; i++) {
		int bin = stoi(input.substr(i * 3, 3));
		out.set(offset + i * 10, bin, 10);
	}

	if (input.size() % 3 == 2) {
		int bin = stoi(input.substr(input.size() - 2, 2));
		out.set(offset + to_U(input.size()) / 3 * 10, bin, 7);
	}
	else if (input.size() % 3 == 1)
		out.set(offset + to_U(input.size()) / 3 * 10, input[input.size() - 1] - '0', 4);
}

void Encoder::encode_alphabetic(const string& input, BitArray& out, unsigned offset)
{
	for (unsigned i = 0; i < input.size() / 2; i++) {
		int bin = encode_char(input[i * 2]) * 45 + encode_char(input[i * 2 + 1]);
		out.set(offset + i * 11, bin, 11);
	}

	if (input.size() % 2 == 1) {
		int bin = encode_char(input[input.size() - 1]);
		out.set(offset + to_U(input.size()) / 2 * 11, bin, 6);
	}
}

void Encoder::encode_byte(const string& input, BitArray& out, unsigned offset)
{
	for (unsigned i = 0; i < input.size(); i++)
		out.set(offset + i * 8, input[i], 8);
}

constexpr unsigned char Encoder::encode_char(char ch)
{
	for (unsigned char i = 0; i < Tables::alphabetic.size(); i++)
		if (ch == Tables::alphabetic.at(i))
			return i;

	if (!Tables::is_alphabetic(ch))
		throw std::runtime_error("No such character in alphabet. Use bytes QR code method.");

	return 0;
}

void Encoder::pad_data(BitArray& arr, unsigned bits_written)
{
	unsigned encoded_bytes = ceil_div(bits_written, 8);
	unsigned max_capability_bytes = arr.size / 8;

	for (unsigned i = encoded_bytes; i < max_capability_bytes; i++)
		arr.v[i] = ((i - encoded_bytes) % 2 == 0) ? 0b11101100 : 0b00010001;
}

BitArray Encoder::get_data() const
{
	if (e.size == 0) throw std::runtime_error("Data is not calculated yet");

	return e;
}
