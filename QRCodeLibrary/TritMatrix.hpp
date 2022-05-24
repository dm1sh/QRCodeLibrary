#pragma once

#include <vector>
#include <string>

enum Trit {
	EMPTY = -1,
	F,
	T,
};

class TritMatrix
{
public:
	TritMatrix(unsigned width, unsigned height) : c{ height, std::vector<Trit>(width, Trit::EMPTY) } {};
	TritMatrix(unsigned size) : c{ size, std::vector<Trit>(size, Trit::EMPTY) } {};

	Trit get(unsigned y, unsigned x) const;

	void set(unsigned y, unsigned x, Trit val);
	void set(unsigned y, unsigned x, bool val);
	void set(unsigned y, unsigned x, int32_t val, unsigned char size);

	void resize(unsigned width, unsigned height);

	std::string to_ascii(char black = '#', char white = ' ', char empty = 'E') const;
	std::string to_string() const { return to_ascii('1', '0', 'E'); };
	std::vector<std::vector<Trit>> to_vector() const { return c; };

protected:
	std::vector<std::vector<Trit>> c;
};

