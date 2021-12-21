#pragma once

#include <type_traits>
#include <limits>

constexpr unsigned to_U(size_t val) {
	if (val > (std::numeric_limits<unsigned int>::max)())
		throw std::runtime_error("Too big number to convert it to unsigned int" + std::to_string(val));
	return static_cast<unsigned>(val);
}
