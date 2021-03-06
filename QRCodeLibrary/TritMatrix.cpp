#include "pch.h"
#include "TritMatrix.hpp"

#include <stdexcept>

Trit TritMatrix::get(unsigned y, unsigned x) const
{
    return c[y][x];
}

void TritMatrix::set(unsigned y, unsigned x, Trit val)
{
    c[y][x] = val;
}

void TritMatrix::set(unsigned y, unsigned x, int32_t val, unsigned char size)
{
    if (x + size > c.at(0).size()) throw std::out_of_range("Value to write is out of matrix range");
    for (unsigned char i = 0; i < size; i++)
        set(y, x + i, (val >> (size - 1 - i)) & 1);
}

void TritMatrix::set(unsigned y, unsigned x, bool val)
{
    set(y, x, val ? Trit::T : Trit::F);
}

std::string TritMatrix::to_ascii(char black, char white, char empty) const
{
    std::string res;

    for (unsigned i = 0; i < c.size(); i++) {
        for (unsigned j = 0; j < c.at(0).size(); j++)
            switch (c[i][j])
            {
            case Trit::T:
                res.push_back(black);
                break;
            case Trit::F:
                res.push_back(white);
                break;
            case Trit::EMPTY:
                res.push_back(empty);
                break;
            }
        if (i != c.size() - 1)
            res.push_back('\n');
    }

    return res;
}

void TritMatrix::resize(unsigned width, unsigned height)
{
    c.resize(height);
    for (unsigned i = 0; i < height; i++)
        c[i].resize(width, Trit::EMPTY);
}
