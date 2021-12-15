#include "pch.h"

#define protected public
#define private public

#include "../QRCodeLibrary/Method.hpp"

TEST(MethodTests, DetermitesStringMethod) {
	string a1("123");
	string a2("ABC");
	string a3("ghfjghfj gfjhgd");

	EXPECT_EQ(Method::determite_method(a1), QRCodeMethod::Numeric);
	EXPECT_EQ(Method::determite_method(a2), QRCodeMethod::Alphabetic);
	EXPECT_EQ(Method::determite_method(a3), QRCodeMethod::Byte);
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