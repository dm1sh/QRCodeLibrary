#pragma once

#include <array>
#include <map>

#include "Method.hpp"

namespace Tables {
	static const std::array<char, 45> alphabetic{
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
		'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
		'U', 'V', 'W', 'X', 'Y', 'Z', ' ', '$', '%', '*',
		'+', '-', '.', '/', ':'
	};

	static const std::map<CorrectionLevel, const std::array<unsigned, 20>> max_capability{
		{ CorrectionLevel::L, {{152, 272, 440, 640, 864, 1088, 1248, 1552, 1856, 2192, 2592, 2960, 3424, 3688, 4184, 4712, 5176, 5768, 6360, 6888}} },
		{ CorrectionLevel::M, {{128, 224, 352, 512, 688, 864, 992, 1232, 1456, 1728, 2032, 2320, 2672, 2920, 3320, 3624, 4056, 4504, 5016, 5352}} },
		{ CorrectionLevel::Q, {{104, 176, 272, 384, 496, 608, 704, 880, 1056, 1232, 1440, 1648, 1952, 2088, 2360, 2600, 2936, 3176, 3560, 3880}} },
		{ CorrectionLevel::H, {{72, 128, 208, 288, 368, 480, 528, 688, 800, 976, 1120, 1264, 1440, 1576, 1784, 2024, 2264, 2504, 2728, 3080}} }
	};

	static const std::map<QRCodeMethod, unsigned char> mode_indicator{
		{ QRCodeMethod::Numeric, 0b0001 },
		{ QRCodeMethod::Alphabetic, 0b0010 },
		{ QRCodeMethod::Byte, 0b0100 }
	};
	static const std::map<QRCodeMethod, const std::array<const std::pair<unsigned char, unsigned char>, 3>> data_amount_lengths{
		{ QRCodeMethod::Numeric, {{ {0, 10}, {8, 12}, {25, 14} }} },
		{ QRCodeMethod::Alphabetic, {{ {0, 9}, {8, 11}, {25, 13} }} } ,
		{ QRCodeMethod::Byte, {{ {0, 8}, {8, 16}, {25, 16} }} }
	};
}
