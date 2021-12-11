#include "pch.h"

#include "Method.hpp"
#include "Tables.hpp"

QRCodeMethod Method::determite_method(string& input)
{
	QRCodeMethod type = QRCodeMethod::Numeric;

	for (auto ch : input) {
		if (type == QRCodeMethod::Numeric)
			if (!is_num(ch))
				type = QRCodeMethod::Alphabetic;
		if (type == QRCodeMethod::Alphabetic)
			if (!is_alphabetic(ch))
				type = QRCodeMethod::Byte;
		if (type == QRCodeMethod::Byte)
			break;
	}

	return type;
}

bool Method::is_alphabetic(char ch)
{
	return find(Tables::alphabetic.cbegin(), Tables::alphabetic.cend(), ch) != Tables::alphabetic.cend();
}
