#pragma once

#include <string>
#include <array>
#include <stdexcept>

#include "Method.hpp"
#include "BitArray.hpp"
#include "utils.hpp"

class Encoder
{
public:
	Encoder(const byte_list& input_, CorrectionLevel corr_lvl_ = CorrectionLevel::M, QRCodeMethod method_ = QRCodeMethod::Dynamic, char version_ = -1);

	static char determite_version(unsigned size, CorrectionLevel corr_lvl);

	static constexpr unsigned calculate_encoded_input_size(unsigned input_size, QRCodeMethod method);
	static unsigned calculate_metadata_size(QRCodeMethod method, char version);

	static void write_metadata(unsigned input_size, unsigned input_bits_amount_size, QRCodeMethod method, BitArray& out);

	constexpr void encode_input(unsigned offset) {
		switch (method) {
		case QRCodeMethod::Numeric:
			encode_numeric(bytes_to_str(input), e, offset);
			break;
		case QRCodeMethod::Alphabetic:
			encode_alphabetic(bytes_to_str(input), e, offset);
			break;
		case QRCodeMethod::Byte:
			encode_byte(input, e, offset);
			break;
		}
	};

	static void encode_numeric(const std::string& input, BitArray& out, unsigned offset);
	static void encode_alphabetic(const std::string& input, BitArray& out, unsigned offset);
	static void encode_byte(const byte_list& input, BitArray& out, unsigned offset);

	static void pad_data(BitArray& arr, unsigned bits_written);

	constexpr char get_version() const { return version; };
	BitArray& get_data();

private:
	static constexpr unsigned char encode_char(char ch);

	const byte_list input;
	CorrectionLevel corr_lvl;
	const QRCodeMethod method;
	char version;

	BitArray e;
};

constexpr unsigned Encoder::calculate_encoded_input_size(unsigned input_size, QRCodeMethod method)
{
	if (method == QRCodeMethod::Dynamic) throw std::runtime_error("Specify correct method");

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

template <typename T, size_t N>
constexpr unsigned upper_index(const std::array<T, N>& arr, T val) {
	unsigned count = N, s = 0, e = 0, step = 0;

	while (count > 0) {
		step = count / 2;
		e = s + step;

		if (arr[e] < val) {
			s = e + 1;
			count -= step + 1;
		}
		else 
			count = step;
	}

	return s;
}
