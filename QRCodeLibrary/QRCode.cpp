#include "pch.h"
#include "QRCode.hpp"

QRCode::QRCode(string input_, CorrectionLevel corr_lvl_, QRCodeMethod method_, unsigned char version_) :
	input{ input_ }, corr_lvl{ corr_lvl_ }, method{ method_ }, version{ version_ } 
{
	if (method == QRCodeMethod::Dynamic)
		method = Method::determite_method(input);
}
