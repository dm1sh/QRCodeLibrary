#include <iostream>
#include <locale>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <Windows.h>
#endif

#include "../QRCodeLibrary/QRCode.hpp"

using namespace std;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
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
string str_of(unsigned k, const string input) {
	string res;
	for (;k > 0; k--)
		res += input;
	return res;
}
#endif

int main() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	SetConsoleCP(1251);
#endif

	string input, buff;

	while(getline(cin, buff)) {
		input += buff + '\n';
	}
	input.pop_back();

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	input = cp1251_to_utf8(input.c_str());
#endif

	QRCode qr(input);

	const auto& res = qr.to_vector();


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	const string long_sep = string((res.size() + 8) * 2, 219),
		short_sep = string(4 * 2, 219),
		black = string(2, 219),
		white = "  ";

	SetConsoleCP(855);
#else
	const string long_sep = str_of((res.size() + 8) * 2, "█"),
		short_sep = str_of(4 * 2, "█"),
		black = str_of(2, "█"),
		white = "  ";
#endif

	for (int i = 0; i < 4; i++)
		cout << long_sep << endl;

	for (unsigned i = 0; i < res.size(); i++) {
		cout << short_sep;
		for (auto cell : res[i])
			switch (cell) {
			case Trit::T:
				cout << white;
				break;
			case Trit::F:
				cout << black;
				break;
			default:
				throw std::runtime_error("Empty cell is not allowed. Your QR code is corrupted.");
			}
		cout << short_sep << endl;
	}

	for (int i = 0; i < 4; i++)
		cout << long_sep << endl;
}