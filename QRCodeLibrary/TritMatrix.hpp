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

	Trit get(unsigned y, unsigned x) const;

	void set(unsigned y, unsigned x, Trit val);
	void set(unsigned y, unsigned x, bool val);
	void set(unsigned y, unsigned x, int32_t val, unsigned char size);

	string to_ascii() const;
	string to_string() const;

private:
	vector<vector<Trit>> c;
};

