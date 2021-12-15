#pragma once

#include <vector>
#include <string>

using namespace std;

constexpr unsigned ceil_div(unsigned a, unsigned b) {
	return a / b + (a % b > 0);
}

class BitArray
{
public:
	BitArray(unsigned size_ = 0) : size{ size_ }, v(ceil_div(size_, 8), 0) {};
	BitArray(const vector<unsigned char>& input) : size(input.size() * 8), v{ input } {};

	operator std::string() const;
	
	unsigned size;
	vector<unsigned char> v;

	bool get(unsigned index) const;
	void set(unsigned index, bool val);
	unsigned set(unsigned index, int32_t val, unsigned size);

	void resize(unsigned new_size);
};

