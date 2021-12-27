#include "pch.h"

#include <sstream>

#include "BitArray.hpp"

bool BitArray::get(unsigned index) const
{
	if (index >= size) throw std::out_of_range("No such element in array");

    return (v[index / 8] >> (8 - index % 8 - 1)) & 1; // получаем байт, в котором хранится искомый бит, смещаем его вправо на то, сколько бит стоят справа от индекса и применяем маску 00000001 
}

BitArray::operator std::string() const 
{
	std::stringstream res;

	for (unsigned i = 0; i < size; i++) // для каждого бита в массиве
		res << static_cast<int>(get(i)); // выводим его как число в строковый поток

	return res.str(); // возвращаем строку, полученную из строкового потока
}

void BitArray::set(unsigned index, bool val)
{
	if (index >= size) throw std::out_of_range("No such element in array");

	if (val == 1)
		v[index / 8] |= 1 << (8 - index % 8 - 1); // к байту, где нужно установить бит прибавляем при помощи битового или единицу, сменённую на то, сколько бит стоят справа от индекса
	else
		v[index / 8] &= ~(1 << (8 - index % 8 - 1)); // к байту, где нужно установить бит применяем битовую маску, где включены все биты кроме того, который соответсвует данному индексу 
}

unsigned BitArray::set(unsigned index, int32_t val, unsigned size)
{
	if (index >= this->size) throw std::out_of_range("No such element in array");

	unsigned shift = index % 8; // смещение слева внутри байта
	unsigned written = 0; // количество записанных байт

	if (size > this->size - index) throw std::out_of_range("Number of bits to write from this index is more than BitArray capability");

	// Цикл для каждого изменяемого в процессе записи байта массива пока не записали все входные данные
	for (int i = index / 8; written < size; i++) {
		int input_shift = size - (8 - shift) - written; // смещение справа для входных данных данных
		int right_rem = input_shift < 0 ? -input_shift : 0; // то, сколько бит нужно взять из исходного массива справа от записываемых данных

		v[i] = (v[i] & (-1 << (8 - shift))) | // данные исходного байта слева от записываемых. Битовая маска зануляет те биты, которые будут браться из записываемых данных
			(((1 << (8 - shift)) - 1) & // битовая маска, оставляющая 8-shift бит слева
			  ((input_shift >= 0) ? (val >> input_shift) : (val << -input_shift))) | // если положительное, тогда смещаемся вправо, иначе - влево
			(v[i] & ((1 << right_rem) - 1)); // берём последние right_rem бит исходного байта

		written += 8 - shift; // наращиваем количество записанных бит на то, сколько бит было записано на этой итерации
		shift = 0; // сбрасываем левое смещение после первой итерации
	}

	return written;
}

void BitArray::resize(unsigned new_size)
{
	v.resize(ceil_div(new_size, 8));

	size = new_size;
}
