#include "pch.h"

#define protected public
#define private public

#include "../QRCodeLibrary/Encode.hpp"

TEST(EncodeTests, CalculatesEncodedInputSize) {
	EXPECT_EQ(Encode::calculate_encoded_input_size(3, QRCodeMethod::Numeric), 10);
	EXPECT_EQ(Encode::calculate_encoded_input_size(3 + 1, QRCodeMethod::Numeric), 10 + 4);
	EXPECT_EQ(Encode::calculate_encoded_input_size(3*3 + 1, QRCodeMethod::Numeric), 10*3 + 4);
	EXPECT_EQ(Encode::calculate_encoded_input_size(3 + 2, QRCodeMethod::Numeric), 10 + 7);

	EXPECT_EQ(Encode::calculate_encoded_input_size(2, QRCodeMethod::Alphabetic), 11);
	EXPECT_EQ(Encode::calculate_encoded_input_size(2*3, QRCodeMethod::Alphabetic), 11*3);
	EXPECT_EQ(Encode::calculate_encoded_input_size(2 + 1, QRCodeMethod::Alphabetic), 11 + 6);
	EXPECT_EQ(Encode::calculate_encoded_input_size(2*3 + 1, QRCodeMethod::Alphabetic), 11*3 + 6);

	EXPECT_EQ(Encode::calculate_encoded_input_size(5, QRCodeMethod::Byte), 5 * 8);
	EXPECT_EQ(Encode::calculate_encoded_input_size(10, QRCodeMethod::Byte), 10*8);
}