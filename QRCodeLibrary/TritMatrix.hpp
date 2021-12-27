#pragma once

#include <vector>
#include <string>

using namespace std;

enum Trit {
	EMPTY = -1,
	F,
	T,
};

class TritMatrix
{
public:
	// Создаёт матрицу heigt x width
	TritMatrix(unsigned width, unsigned height) : c{ height, vector<Trit>(width, Trit::EMPTY) } {};
	// Создаёт матрицу size x size
	TritMatrix(unsigned size) : c{ size, vector<Trit>(size, Trit::EMPTY) } {};

	Trit get(unsigned y, unsigned x) const;

	void set(unsigned y, unsigned x, Trit val);
	void set(unsigned y, unsigned x, bool val);
	// записывает size последних бит val в строку y матрицы. 1 передодится в Trit.T, 0 в Trit.F
	void set(unsigned y, unsigned x, int32_t val, unsigned char size);

	void resize(unsigned width, unsigned height);

	string to_ascii(char black = '#', char white = ' ', char empty = 'E') const;
	string to_string() const { return to_ascii('1', '0', 'E'); };
	vector<vector<Trit>> to_vector() const { return c; };

protected:
	vector<vector<Trit>> c;
};

