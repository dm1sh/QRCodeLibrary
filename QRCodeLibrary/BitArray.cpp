#include "pch.h"

#include <sstream>

#include "BitArray.hpp"

bool BitArray::get(unsigned index) const
{
	if (index >= size) throw std::out_of_range("No such element in array");

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
	if (index >= size) throw std::out_of_range("No such element in array");

	if (val)
		v[index / 8] |= 1 << (8 - 1 - index % 8);
	else
		v[index / 8] &= ~(1 << (8 - 1 - index % 8));
}

unsigned BitArray::set(unsigned index, int32_t val, unsigned size)
{
	if (index >= this->size) throw std::out_of_range("No such element in array");

	unsigned shift = index % 8, written = 0;

	if (size > this->size - index) throw std::out_of_range("Number of bits to write from this index is more than BitArray capability");

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

void BitArray::resize(unsigned new_size)
{
	v.resize(ceil_div(new_size, 8));

	size = new_size;
}
