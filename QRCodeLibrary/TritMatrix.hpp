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
	TritMatrix(unsigned width, unsigned height) : c{ height, vector<Trit>(width, Trit::EMPTY) } {};
	TritMatrix(unsigned size) : c{ size, vector<Trit>(size, Trit::EMPTY) } {};

	Trit get(unsigned y, unsigned x) const;

	void set(unsigned y, unsigned x, Trit val);
	void set(unsigned y, unsigned x, bool val);
	void set(unsigned y, unsigned x, int32_t val, unsigned char size);

	void resize(unsigned width, unsigned height);

	string to_ascii(char black = '#', char white = ' ', char empty = 'E') const;
	string to_string() const { return to_ascii('1', '0', 'E'); };
	vector<vector<Trit>> to_vector() const { return c; };

protected:
	vector<vector<Trit>> c;
};

