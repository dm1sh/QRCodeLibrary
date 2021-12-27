#include "pch.h"

#include "QRCode.hpp"
#include "Encoder.hpp"
#include "DataBlocks.hpp"
#include "Tables.hpp"

QRCode::QRCode(const byte_list& input_, CorrectionLevel corr_lvl_, QRCodeMethod method_, char version_, unsigned char mask_n) :
	input{ input_ }, corr_lvl{ corr_lvl_ }, method{ method_ }, version{ version_ }, matrix(0)
{
	if (method == QRCodeMethod::Dynamic) {
		if (input.size() > Tables::max_capability.at(corr_lvl).at(0) / 8) // Если данных мало, можно не пытаться кодировать данные, а просто использовать байты
			method = Method::determite_method(input);
		else
			method = QRCodeMethod::Byte;
	}
	
  /* Кодирование данных */
	Encoder encoder(input, corr_lvl, method, version);
	const BitArray& encoded_data = encoder.get_data();
	version = encoder.get_version();

	/* Создание байтов коррекции и объединение данных */
	DataBlocks data_blocks(encoded_data.v, corr_lvl, version);
	const BitArray final_message(data_blocks.get_joined_data_and_EC_blocks());

	/* Компоновка рисунка QR кода */
	matrix.set_version(version);
	matrix.draw_patterns();
	matrix.place_metadata(corr_lvl, mask_n);
	matrix.place_data(final_message, mask_n);
}
