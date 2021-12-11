#include "pch.h"

#include <sstream>

#include "BitArray.hpp"

bool BitArray::get(unsigned index) const
{
    return (v[index / 8] >> (8 - 1 - index % 8)) & 1;
}

BitArray::operator std::string() const 
{
	std::stringstream res;

	for (unsigned i = 0; i < size; i++)
		res << static_cast<int>((*this).get(i));

	return res.str();
}

void BitArray::set(unsigned index, bool val)
{
	if (val)
		v[index / 8] |= 1 << (8 - 1 - index % 8);
	else
		v[index / 8] &= ~(1 << (8 - 1 - index % 8));
}

unsigned BitArray::set(unsigned index, int32_t val, unsigned size)
{
	unsigned shift = index % 8, written = 0;
	size = std::min(size, this->size - index);
	index /= 8;

	while (written < size) {
		int input_shift = size - (8 - shift) - written;
		int right_rem = input_shift < 0 ? -input_shift : 0;

		v[index] = ((v[index] >> (8 - shift)) << (8 - shift)) |
			(unsigned char)(((1 << (8 - shift)) - 1) & ((input_shift >= 0) ? (val >> input_shift) : (val << -input_shift))) |
			(v[index] & ((1 << right_rem) - 1));

		written += 8 - shift;
		index++;
		shift = 0;
	}

	return written;
}
