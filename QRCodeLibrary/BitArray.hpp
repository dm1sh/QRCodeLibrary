#pragma once

#include <vector>
#include <string>
#include <stdexcept>

#include "utils.hpp"

using namespace std;

// Деление a на b с округлением в большую сторону
constexpr static unsigned ceil_div(unsigned a, unsigned b) {
	if (b == 0) throw runtime_error("Dividion by zero not possible");
	return a / b + (a % b > 0);
}

class BitArray
{
public:
	// Создаёт массив заполненный нулями размера size
	BitArray(unsigned size_ = 0) : size{ size_ }, v(ceil_div(size_, 8), 0) {};
	// Создаёт массив из байт input
	BitArray(const byte_list& input) : size(to_U(input.size()) * 8), v{ input } {};

	operator std::string() const;
	
	unsigned size; // размер массива в битах 
	byte_list v;

	// Принимает index - индекс в массиве, возвращает соответствующий index-ый бит
	bool get(unsigned index) const;
	// Принимает индекс и булевую переменную (0 или 1). Устанавливает соответствующий бит массива
	void set(unsigned index, bool val);
	// Принимает индекс, 32-х битное число и количество бит из числа. Устанавливает начиная с индекса size бит соответствующими младшими двоичными разрядами числа val
	unsigned set(unsigned index, int32_t val, unsigned size);

	// Принимает новый размер для массива в битах
	void resize(unsigned new_size);
};

