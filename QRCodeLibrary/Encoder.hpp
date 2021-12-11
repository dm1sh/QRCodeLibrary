#pragma once

#include <string>
#include <array>

#include "Method.hpp"
#include "BitArray.hpp"

using namespace std;

class Encoder
{
public:
	Encoder(const string& input_, CorrectionLevel corr_lvl_, QRCodeMethod method_, unsigned char version_) : input{ input_ }, corr_lvl{ corr_lvl_ }, method{ method_ }, version{ version_ } {};

	unsigned char determite_version();

	void encode();

	static unsigned calculate_encoded_input_size(unsigned input_size, QRCodeMethod method);

	constexpr void encode_input() {
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

private:
	const string& input;
	CorrectionLevel corr_lvl;
	const QRCodeMethod method;
	unsigned char version;

	BitArray e;
	unsigned offset = 0;
};

template <typename T, unsigned N>
constexpr unsigned char upper_index(const array<T, N> arr, T val) {
	unsigned count = arr.size(), s = 0, e, step;

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