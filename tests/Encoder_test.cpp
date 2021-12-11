#include "pch.h"

#define private public

#include "../QRCodeLibrary/Encoder.hpp"

/* upper_index function */

TEST(UpperIndexTests, FindsExactMatch) {
	array<int, 5> arr1{ 1, 2, 3, 4, 5 };

	for (int i = 0; i < 5; i++)
		EXPECT_EQ(upper_index(arr1, i+1), i);

	array<int, 4> arr2{ 1, 2, 3, 4 };

	for (int i = 0; i < 4; i++)
		EXPECT_EQ(upper_index(arr2, i + 1), i);
}

TEST(UpperIndexTests, FindsClosestUpper) {
	array<int, 5> arr{ 1, 3, 5, 7, 9 };

	for (int i = 0; i < 5; i++)
		EXPECT_EQ(upper_index(arr, i * 2), i);
}

TEST(UpperIndexTests, IfNothingFoundReturnsArrSize) {
	array<int, 5> arr{ 0, 1, 2, 3, 4 };

	EXPECT_EQ(upper_index(arr, 5), 5);
	EXPECT_EQ(upper_index(arr, 10), 5);
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
}

TEST(EncoderTests, DetermitesVersion) {
	EXPECT_EQ(Encoder::determite_version(1600, CorrectionLevel::M), 9);
}

TEST(EncoderTests, WritesMetadata) {
	string expected("010001100100");

	BitArray arr(expected.size());

	Encoder::write_metadata(100, expected.size() - 4, QRCodeMethod::Byte, arr);

	EXPECT_EQ(std::string(arr), expected);
}

TEST(EncoderTests, EncodesNumeric) {
	BitArray tmp(string("00110110001110000100101001").size());
	Encoder::encode_numeric("8675309", tmp, 2);

	EXPECT_EQ(std::string(tmp), "00110110001110000100101001");
}

TEST(EncoderTests, EncodesAlphabetic) {
	BitArray tmp(string("0000110000101101111000110100010111001011011100010011010100001101").size());
	Encoder::encode_alphabetic("HELLO WORLD", tmp, 3);

	EXPECT_EQ(std::string(tmp), "0000110000101101111000110100010111001011011100010011010100001101");
}

TEST(EncoderTests, EncodesBytes) {
	BitArray tmp(string("0000110100001001010011010000101111001101000010111000110100011000001011010001100000001101000010111000110100001011100100100000110100001010100011010000101110001101000110001000110100001011101011010000101111101101000010110010").size());
	Encoder::encode_byte(u8"Дмитрий Шишков", tmp, 4);

	EXPECT_EQ(std::string(tmp), "0000110100001001010011010000101111001101000010111000110100011000001011010001100000001101000010111000110100001011100100100000110100001010100011010000101110001101000110001000110100001011101011010000101111101101000010110010");
}

TEST(EncoderTests, EncodesInput) {
	Encoder e1("8675309", CorrectionLevel::M, QRCodeMethod::Numeric);
	e1.encode();
	EXPECT_EQ(std::string(e1.get_data()), "00010000000111110110001110000100101001");

	Encoder e2("HELLO WORLD", CorrectionLevel::M, QRCodeMethod::Alphabetic);
	e2.encode();
	EXPECT_EQ(std::string(e2.get_data()), "00100000010110110000101101111000110100010111001011011100010011010100001101");

	Encoder e3(u8"Дмитрий Шишков", CorrectionLevel::M, QRCodeMethod::Byte);
	e3.encode();
	EXPECT_EQ(std::string(e3.get_data()), "010000011011110100001001010011010000101111001101000010111000110100011000001011010001100000001101000010111000110100001011100100100000110100001010100011010000101110001101000110001000110100001011101011010000101111101101000010110010");
}