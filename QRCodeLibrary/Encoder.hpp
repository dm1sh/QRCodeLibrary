#pragma once

#include <string>
#include <array>

#include "Method.hpp"
#include "BitArray.hpp"

using namespace std;

class Encoder
{
public:
	Encoder(const string& input_, CorrectionLevel corr_lvl_ = CorrectionLevel::M, QRCodeMethod method_ = QRCodeMethod::Dynamic, char version_ = -1) : input{ input_ }, corr_lvl{ corr_lvl_ }, method{ method_ }, version{ version_ } {};

	BitArray& encode();

	static char determite_version(unsigned size, CorrectionLevel corr_lvl);

	static unsigned calculate_encoded_input_size(unsigned input_size, QRCodeMethod method);
	static unsigned calculate_metadata_size(QRCodeMethod method, char version);

	static void write_metadata(unsigned input_size, unsigned input_bits_amount_size, QRCodeMethod method, BitArray& out);

	constexpr void encode_input(unsigned offset) {
		switch (method) {
		case QRCodeMethod::Numeric:
			encode_numeric(input, e, offset);
			break;
		case QRCodeMethod::Alphabetic:
			encode_alphabetic(input, e, offset);
			break;
		case QRCodeMethod::Byte:
			encode_byte(input, e, offset);
			break;
		}
	};

	static void encode_numeric(const string& input, BitArray& out, unsigned offset);
	static void encode_alphabetic(const string& input, BitArray& out, unsigned offset);
	static void encode_byte(const string& input, BitArray& out, unsigned offset);

	static unsigned char encode_char(char ch);

	static void pad_data(BitArray& arr, unsigned bits_written);

	char get_version() const;
	BitArray get_data() const;

private:
	const string input;
	CorrectionLevel corr_lvl;
	const QRCodeMethod method;
	char version;

	BitArray e;
};

template <typename T, size_t N>
constexpr unsigned upper_index(const array<T, N> arr, T val) {
	unsigned count = arr.size(), s = 0, e = 0, step = 0;

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