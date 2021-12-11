#include "pch.h"

#include "Encoder.hpp"
#include "Tables.hpp"

unsigned char Encoder::determite_version()
{
	const auto& sizes = Tables::max_capability.at(corr_lvl);

	return upper_index(sizes, input.size());
}

void Encoder::encode()
{
	unsigned bit_num = calculate_encoded_input_size(input.size(), method);
}

unsigned Encoder::calculate_encoded_input_size(unsigned input_size, QRCodeMethod method)
{
	unsigned bit_num = 0;

	switch (method) {
	case QRCodeMethod::Numeric:
		bit_num = 10 * (input_size / 3);
		if (input_size % 3 == 2)
			bit_num += 7;
		else if (input_size % 3 == 1)
			bit_num += 4;
		break;
	case QRCodeMethod::Alphabetic:
		bit_num = 11 * (input_size / 2);
		if (input_size % 2 == 1)
			bit_num += 6;
		break;
	case QRCodeMethod::Byte:
		bit_num = input_size * 8;
		break;
	}

	return bit_num;
}

void Encoder::encode_numeric(const string& input, BitArray& out, unsigned offset)
{
	for (unsigned i = 0; i < input.size() / 3; i++) {
		int bin = stoi(input.substr(i * 3, 3));
		out.set(offset + i * 10, bin, 10);
	}

	if (input.size() % 3 == 2) {
		int bin = stoi(input.substr(input.size() - 2, 2));
		out.set(offset + input.size() / 3 * 10, bin, 7);
	}
	else if (input.size() % 3 == 1)
		out.set(offset + input.size() / 3 * 10, input[input.size() - 1] - '0', 4);
}

void Encoder::encode_alphabetic(const string& input, BitArray& out, unsigned offset)
{
	for (unsigned i = 0; i < input.size() / 2; i++) {
		int bin = encode_char(input[i * 2]) * 45 + encode_char(input[i * 2 + 1]);
		out.set(offset + i * 11, bin, 11);
	}

	if (input.size() % 2 == 1) {
		int bin = encode_char(input[input.size() - 1]);
		out.set(offset + input.size() / 2 * 11, bin, 6);
	}
}

void Encoder::encode_byte(const string& input, BitArray& out, unsigned offset)
{
	for (unsigned i = 0; i < input.size(); i++)
		out.set(offset + i * 8, input[i], 8);
}

unsigned char Encoder::encode_char(char ch)
{
	for (unsigned i = 0; i < Tables::alphabetic.size(); i++)
		if (ch == Tables::alphabetic.at(i))
			return i;

	throw std::runtime_error("No such character in alphabet. Use bytes QR code method.");
}
