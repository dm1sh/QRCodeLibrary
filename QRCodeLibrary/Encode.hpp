#pragma once

#include <string>

#include "Method.hpp"

using namespace std;

class Encode
{
public:
	static unsigned calculate_encoded_input_size(unsigned input_size, QRCodeMethod method);
};

