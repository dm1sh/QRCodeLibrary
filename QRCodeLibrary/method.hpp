#pragma once

#include <string>

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
	static QRCodeMethod determite_method(string input);

	static constexpr bool is_num(char ch);
	static bool is_alphabetic(char ch);
};