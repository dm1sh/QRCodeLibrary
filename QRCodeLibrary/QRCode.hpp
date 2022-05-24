#pragma once

#include <string>

#include "Method.hpp"
#include "QRMatrix.hpp"
#include "utils.hpp"

class QRCode
{
public:
	QRCode(const byte_list& input_, CorrectionLevel corr_lvl_ = CorrectionLevel::M, QRCodeMethod method_ = QRCodeMethod::Dynamic, char version_ = -1, unsigned char mask_n = 0);
	QRCode(const std::string& input_, CorrectionLevel corr_lvl_ = CorrectionLevel::M, QRCodeMethod method_ = QRCodeMethod::Dynamic, char version_ = -1, unsigned char mask_n = 0) : QRCode(str_to_bytes(input_), corr_lvl_, method_, version_, mask_n) {};

	std::string to_string() const { return matrix.to_string(); };
	std::string to_ascii(char black = '#', char white = ' ', char empty = 'E') const { return matrix.to_ascii(black, white, empty); }
	std::vector<std::vector<Trit>> to_vector() const { return matrix.to_vector(); };

protected:
	byte_list input;
	CorrectionLevel corr_lvl;
	QRCodeMethod method;
	char version;

	QRMatrix matrix;
};

