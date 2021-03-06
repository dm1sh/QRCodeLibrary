#include "pch.h"

#define protected public
#define private public

#include "../QRCodeLibrary/Method.hpp"

TEST(MethodTests, DetermitesStringMethod) {
	EXPECT_EQ(Method::determite_method(str_to_bytes("123")), QRCodeMethod::Numeric);
	EXPECT_EQ(Method::determite_method(str_to_bytes("ABC")), QRCodeMethod::Alphabetic);
	EXPECT_EQ(Method::determite_method(str_to_bytes("ghfjghfj gfjhgd")), QRCodeMethod::Byte);
}

TEST(MethodTests, ChecksNumber) {
	EXPECT_TRUE(Method::is_num('1'));
	EXPECT_TRUE(Method::is_num('5'));
	EXPECT_TRUE(Method::is_num('0'));

	EXPECT_FALSE(Method::is_num('a'));
	EXPECT_FALSE(Method::is_num('j'));
	EXPECT_FALSE(Method::is_num('\n'));
	EXPECT_FALSE(Method::is_num('_'));
}