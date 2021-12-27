#include "pch.h"

#define private public

#include "../QRCodeLibrary/Encoder.hpp"

/* upper_index function */

TEST(UpperIndexTests, FindsExactMatch) {
	array<unsigned, 5> arr1{ 1, 2, 3, 4, 5 };

	for (unsigned i = 0; i < 5; i++)
		EXPECT_EQ(upper_index(arr1, i+1), i);

	array<unsigned, 4> arr2{ 1, 2, 3, 4 };

	for (unsigned i = 0; i < 4; i++)
		EXPECT_EQ(upper_index(arr2, i + 1), i);
}

TEST(UpperIndexTests, FindsClosestUpper) {
	array<unsigned, 5> arr{ 1, 3, 5, 7, 9 };

	for (unsigned i = 0; i < 5; i++)
		EXPECT_EQ(upper_index(arr, i * 2), i);
}

TEST(UpperIndexTests, IfNothingFoundReturnsArrSize) {
	array<unsigned, 5> arr{ 0, 1, 2, 3, 4 };

	EXPECT_EQ(upper_index(arr, 5u), 5);
	EXPECT_EQ(upper_index(arr, 10u), 5);
}

/* Encoder class */

TEST(EncoderTests, CalculatesEncodedInputSize) {
	EXPECT_EQ(Encoder::calculate_encoded_input_size(3, QRCodeMethod::Numeric), 10);
	EXPECT_EQ(Encoder::calculate_encoded_input_size(3 + 1, QRCodeMethod::Numeric), 10 + 4);
	EXPECT_EQ(Encoder::calculate_encoded_input_size(3*3 + 1, QRCodeMethod::Numeric), 10*3 + 4);
	EXPECT_EQ(Encoder::calculate_encoded_input_size(3 + 2, QRCodeMethod::Numeric), 10 + 7);

	EXPECT_EQ(Encoder::calculate_encoded_input_size(2, QRCodeMethod::Alphabetic), 11);
	EXPECT_EQ(Encoder::calculate_encoded_input_size(2*3, QRCodeMethod::Alphabetic), 11*3);
	EXPECT_EQ(Encoder::calculate_encoded_input_size(2 + 1, QRCodeMethod::Alphabetic), 11 + 6);
	EXPECT_EQ(Encoder::calculate_encoded_input_size(2*3 + 1, QRCodeMethod::Alphabetic), 11*3 + 6);

	EXPECT_EQ(Encoder::calculate_encoded_input_size(5, QRCodeMethod::Byte), 5 * 8);
	EXPECT_EQ(Encoder::calculate_encoded_input_size(10, QRCodeMethod::Byte), 10*8);
}

TEST(EncoderTests, CalculatesMetadataSize) {
	EXPECT_EQ(Encoder::calculate_metadata_size(QRCodeMethod::Numeric, 0), 14);
	EXPECT_EQ(Encoder::calculate_metadata_size(QRCodeMethod::Alphabetic, 5), 13);
	EXPECT_EQ(Encoder::calculate_metadata_size(QRCodeMethod::Numeric, 10), 16);
	EXPECT_EQ(Encoder::calculate_metadata_size(QRCodeMethod::Byte, 9), 20);
	EXPECT_EQ(Encoder::calculate_metadata_size(QRCodeMethod::Byte, 8), 12);
	EXPECT_EQ(Encoder::calculate_metadata_size(QRCodeMethod::Alphabetic, 26), 17);
}

TEST(EncoderTests, DetermitesVersion) {
	EXPECT_EQ(Encoder::determite_version(1600, CorrectionLevel::M), 9);
}

TEST(EncoderTests, WritesMetadata) {
	string expected("010001100100");

	BitArray arr(to_U(expected.size()));

	Encoder::write_metadata(100, to_U(expected.size()) - 4, QRCodeMethod::Byte, arr);

	EXPECT_EQ(std::string(arr), expected);
}

TEST(EncoderTests, EncodesNumeric) {
	BitArray tmp(to_U(string("00110110001110000100101001").size()));
	Encoder::encode_numeric("8675309", tmp, 2);

	EXPECT_EQ(std::string(tmp), "00110110001110000100101001");
}

TEST(EncoderTests, EncodesAlphabetic) {
	BitArray tmp(to_U(string("0000110000101101111000110100010111001011011100010011010100001101").size()));
	Encoder::encode_alphabetic("HELLO WORLD", tmp, 3);

	EXPECT_EQ(std::string(tmp), "0000110000101101111000110100010111001011011100010011010100001101");
}

TEST(EncoderTests, EncodesBytes) {
	BitArray tmp(to_U(string("0000110100001001010011010000101111001101000010111000110100011000001011010001100000001101000010111000110100001011100100100000110100001010100011010000101110001101000110001000110100001011101011010000101111101101000010110010").size()));
	Encoder::encode_byte(str_to_bytes(u8"Дмитрий Шишков"), tmp, 4);

	EXPECT_EQ(std::string(tmp), "0000110100001001010011010000101111001101000010111000110100011000001011010001100000001101000010111000110100001011100100100000110100001010100011010000101110001101000110001000110100001011101011010000101111101101000010110010");
}

TEST(EncoderTests, PadsData) {
	BitArray arr(6*8);
	arr.v[0] = 0b11001100;
	arr.v[1] = 0b11111111;
	arr.v[2] = 0b11000000;
	
	Encoder::pad_data(arr, 18);

	EXPECT_EQ(std::string(arr), "110011001111111111000000111011000001000111101100");
}

TEST(EncoderTests, EncodesInput) {
	Encoder e1(str_to_bytes("8675309"), CorrectionLevel::Q, QRCodeMethod::Numeric);
	EXPECT_EQ(std::string(e1.get_data()), "00010000000111110110001110000100101001001110110000010001111011000001000111101100000100011110110000010001");

	Encoder e2(str_to_bytes("HELLO WORLD"), CorrectionLevel::M, QRCodeMethod::Alphabetic);
	EXPECT_EQ(std::string(e2.get_data()), "00100000010110110000101101111000110100010111001011011100010011010100001101000000111011000001000111101100000100011110110000010001");

	Encoder e3(str_to_bytes(u8"Дмитрий Шишков"), CorrectionLevel::Q, QRCodeMethod::Byte);
	EXPECT_EQ(std::string(e3.get_data()), "01000001101111010000100101001101000010111100110100001011100011010001100000101101000110000000110100001011100011010000101110010010000011010000101010001101000010111000110100011000100011010000101110101101000010111110110100001011001000001110110000010001111011000001000111101100");
}