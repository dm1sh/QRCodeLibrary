#include "pch.h"

#include "QRCode.hpp"
#include "Encoder.hpp"
#include "DataBlocks.hpp"

QRCode::QRCode(string& input_, CorrectionLevel corr_lvl_, QRCodeMethod method_, unsigned char version_) :
	input{ input_ }, corr_lvl{ corr_lvl_ }, method{ method_ }, version{ version_ }
{
	if (method == QRCodeMethod::Dynamic)
		method = Method::determite_method(input);

	Encoder encoder(input, corr_lvl, method, version);
	version = encoder.get_version();
	const BitArray& encoded_data = encoder.encode();

	DataBlocks data_blocks(encoded_data.v, corr_lvl, version);
	vector<unsigned char>& blocked_data = data_blocks.compose_data_and_EC_blocks();
}
