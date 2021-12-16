#pragma once

#include <string>

#include "Method.hpp"
#include "QRMatrix.hpp"

using namespace std;

class QRCode
{
public:
	QRCode(string& input_, CorrectionLevel corr_lvl_ = CorrectionLevel::M, QRCodeMethod method_ = QRCodeMethod::Dynamic, char version_ = -1, unsigned char mask_n = 0);

	string to_string() const { return matrix.to_string(); };
	string to_ascii(char black = '#', char white = ' ', char empty = 'E') const { return matrix.to_ascii(black, white, empty); }
	vector<vector<Trit>> to_vector() const { return matrix.to_vector(); };

protected:
	string input;
	CorrectionLevel corr_lvl;
	QRCodeMethod method;
	char version;

	QRMatrix matrix;
};

