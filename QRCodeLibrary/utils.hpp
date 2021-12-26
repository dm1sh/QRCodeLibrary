#pragma once

#include <stdexcept>
#include <type_traits>
#include <limits>
#include <vector>
#include <string>

constexpr static unsigned to_U(size_t val) {
	if (val > (std::numeric_limits<unsigned int>::max)())
		throw std::runtime_error("Too big number to convert it to unsigned int" + std::to_string(val));
	return static_cast<unsigned>(val);
}

using byte_list = std::vector<unsigned char>;

static byte_list str_to_bytes(const std::string& inp) {
	return byte_list(inp.begin(), inp.end());
}

static std::string bytes_to_str(const byte_list& inp) {
	return std::string(inp.begin(), inp.end());
}