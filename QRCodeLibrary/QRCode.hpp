#pragma once

#include <string>

#include "method.hpp"

using namespace std;

class QRCode
{
public:
	QRCode(string input_, CorrectionLevel corr_lvl_ = CorrectionLevel::Q, QRCodeMethod method_ = QRCodeMethod::Dynamic, unsigned char version_ = 0);

protected:
	string input;
	CorrectionLevel corr_lvl;
	QRCodeMethod method;
	unsigned char version;
};

