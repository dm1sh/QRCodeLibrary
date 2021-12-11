#pragma once

#include <array>
#include <map>

#include "Method.hpp"

class Tables {
public:
	static const std::array<char, 45>alphabetic;

	static const std::map<CorrectionLevel, const std::array<unsigned, 20>> max_capability;
};