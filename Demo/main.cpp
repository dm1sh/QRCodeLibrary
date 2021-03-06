#include <iostream>
#include <locale>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#define IS_WINDOWS
#endif

#ifdef IS_WINDOWS
#include <IS_WINDOWSows.h>
#endif

#include "../QRCodeLibrary/QRCode.hpp"

using namespace std;

#ifdef IS_WINDOWS
std::string cp1251_to_utf8(const char* str)
{
	std::string res;
	WCHAR* ures = NULL;
	char* cres = NULL;

	int result_u = MultiByteToWideChar(1251, 0, str, -1, 0, 0);
	if (result_u != 0)
	{
		ures = new WCHAR[result_u];
		if (MultiByteToWideChar(1251, 0, str, -1, ures, result_u))
		{
			int result_c = WideCharToMultiByte(CP_UTF8, 0, ures, -1, 0, 0, 0, 0);
			if (result_c != 0)
			{
				cres = new char[result_c];
				if (WideCharToMultiByte(CP_UTF8, 0, ures, -1, cres, result_c, 0, 0))
				{
					res = cres;
				}
			}
		}
	}

	delete[] ures;
	delete[] cres;

	return res;
}
#else
string str_of(unsigned k, const string& input) {
	string res;
	for (;k > 0; k--)
		res += input;
	return res;
}
#endif

int main() {
#ifdef IS_WINDOWS
	SetConsoleCP(1251);
#endif

	string input;
	string buff;

	while (getline(cin, buff)) {
		input += buff + '\n';
	}
	input.pop_back();

#ifdef IS_WINDOWS
	input = cp1251_to_utf8(input.c_str());
#endif

	QRCode qr(input, CorrectionLevel::H);

	const auto& res = qr.to_vector();

#define SQUARE_WIDTH 2

#ifdef IS_WINDOWS
	const string long_sep = string((res.size() + 8) * SQUARE_WIDTH, 219),
		short_sep = string(4 * SQUARE_WIDTH, 219),
		black = string(SQUARE_WIDTH, ' '),
		white = string(SQUARE_WIDTH, 219);

	SetConsoleCP(855);
#else
	const string long_sep = str_of((res.size() + 8) * SQUARE_WIDTH, "█"),
		short_sep = str_of(4 * SQUARE_WIDTH, "█"),
		black = string(SQUARE_WIDTH, ' '),
		white = str_of(SQUARE_WIDTH, "█");
#endif

	for (int i = 0; i < 4; i++)
		cout << long_sep << endl;

	for (unsigned i = 0; i < res.size(); i++) {
		cout << short_sep;
		for (auto cell : res[i])
			switch (cell) {
			case Trit::T:
				cout << black;
				break;
			case Trit::F:
				cout << white;
				break;
			default:
				throw std::runtime_error("Empty cell is not allowed. Your QR code is corrupted.");
			}
		cout << short_sep << endl;
	}

	for (int i = 0; i < 4; i++)
		cout << long_sep << endl;

#ifdef IS_WINDOWS
	system("pause");
#endif
}
