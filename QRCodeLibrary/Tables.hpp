#pragma once

#include <array>
#include <map>

#include "Method.hpp"

class Tables {
public:
	static const std::array<char, 45>alphabetic;

	static const std::map<CorrectionLevel, const std::array<unsigned, 20>>max_capability;

	static const std::map<QRCodeMethod, unsigned char>mode_indicator;
	static const std::map<QRCodeMethod, const std::array<const std::pair<unsigned char, unsigned char>, 3>>data_amount_lengths;
};