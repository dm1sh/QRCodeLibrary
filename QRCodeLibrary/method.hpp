#pragma once

#include <string>

using namespace std;

enum class QRCodeMethod {
	Dynamic,
	Numeric,
	Alphabetic,
	Byte
};

enum class CorrectionLevel {
	L,
	M,
	Q,
	H
};