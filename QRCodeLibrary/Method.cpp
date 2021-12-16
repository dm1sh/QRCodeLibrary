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
			if (!Tables::is_alphabetic(ch))
				type = QRCodeMethod::Byte;
		if (type == QRCodeMethod::Byte)
			break;
	}

	return type;
}
