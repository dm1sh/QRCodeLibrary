#include "pch.h"

#include "Encode.hpp"

unsigned Encode::calculate_encoded_input_size(unsigned input_size, QRCodeMethod method)
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

