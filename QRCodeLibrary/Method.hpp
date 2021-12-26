#pragma once

#include "utils.hpp"

using namespace std;

enum class QRCodeMethod {
	Dynamic,
	Numeric,
	Alphabetic,
	Byte
};

enum class CorrectionLevel {
	L,
	M,
	Q,
	H
};

class Method {
public:
	static QRCodeMethod determite_method(byte_list& input);

	static constexpr bool is_num(char ch) { return ch >= '0' && ch <= '9'; };
};
