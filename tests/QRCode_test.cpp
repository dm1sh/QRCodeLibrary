#include "pch.h"

#define protected public
#define private public

#include "../QRCodeLibrary/QRCode.hpp"

class QRCodeConstructorMock : public QRCode {
public:
	template <typename ...Parameters>
	QRCodeConstructorMock(Parameters ...params) {};
};
TEST(QRCodeTests, ConstructsClass) {
	QRCode qr("TEST");

	EXPECT_EQ(qr.input, "TEST");
	EXPECT_EQ(qr.corr_lvl, CorrectionLevel::Q);
	EXPECT_EQ(qr.method, QRCodeMethod::Alphabetic);
}