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
// Переводит строку из кодировки CP 1251 в UTF-8 
std::string cp1251_to_utf8(const char* str)
{
	std::string res;
	WCHAR* ures = NULL;
	char* cres = NULL;

	int result_u = MultiByteToWideChar(1251, 0, str, -1, 0, 0); // определяем сколько символов будет иметь широкосимвольная строка (UTF-16)
	if (result_u != 0)
	{
		ures = new WCHAR[result_u]; // инициализируем временную строку для символов в UTF-16 
		if (MultiByteToWideChar(1251, 0, str, -1, ures, result_u))
		{
			int result_c = WideCharToMultiByte(CP_UTF8, 0, ures, -1, 0, 0, 0, 0); // определяем сколько символов будет иметь строка в кодировке UTF-8
			if (result_c != 0)
			{
				cres = new char[result_c]; // инициализируем временную строку для символов в UTF-8
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
// создаёт строку, состоящую из k раз повторённых строк input
string str_of(unsigned k, const string& input) {
	string res;
	for (;k > 0; k--)
		res += input;
	return res;
}
#endif

int main() {
#ifdef IS_WINDOWS
	SetConsoleCP(1251); // устанавливаем кодировку в консоли CP 1251
#endif

	string input; // строка, содержащая пользовательский ввод
	string buff; // буфер для ввода строк

	while (getline(cin, buff)) { // пока пользователь не ввёл символ EOF
		input += buff + '\n'; // сохраняем ввод с символом переноса строки в конце
	}
	input.pop_back(); // удаляем последний добавленный символ переноса строки

#ifdef IS_WINDOWS
	input = cp1251_to_utf8(input.c_str()); // переводим ввод в UTF-8
#endif

	QRCode qr(input, CorrectionLevel::H);

	const auto& res = qr.to_vector();

#define SQUARE_WIDTH 2

#ifdef IS_WINDOWS
	const string long_sep = string((res.size() + 8) * SQUARE_WIDTH, 219), // строка из блоков на всю ширину QR кода для рамок над и под ним
		short_sep = string(4 * SQUARE_WIDTH, 219), // строка из 4 блоков для боковых рамок справа и слева вокруг QR кода
		black = string(SQUARE_WIDTH, ' '), // строка для чёрного квадрата в QR коде
		white = string(SQUARE_WIDTH, 219); // строка для белого квадрата в QR коде 

	SetConsoleCP(855);
#else
	const string long_sep = str_of((res.size() + 8) * SQUARE_WIDTH, "█"), // строка из блоков на всю ширину QR кода для рамок над и под ним
		short_sep = str_of(4 * SQUARE_WIDTH, "█"), // строка из 4 блоков для боковых рамок справа и слева вокруг QR кода
		black = string(SQUARE_WIDTH, ' '), // строка для чёрного квадрата в QR коде
		white = str_of(SQUARE_WIDTH, "█"); // строка для белого квадрата в QR коде 
#endif

	// Вывод четырёх строк белых квадратов в качестве фона
	for (int i = 0; i < 4; i++)
		cout << long_sep << endl;

	for (unsigned i = 0; i < res.size(); i++) { // для каждой строки QR кода
		cout << short_sep; // вывод белого фона справа от строки
		for (auto cell : res[i]) // для каждой клетки QR кода
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
		cout << short_sep << endl; // вывод белого фона слева от строки
	}

	// Вывод четырёх строк белых квадратов в качестве фона
	for (int i = 0; i < 4; i++)
		cout << long_sep << endl;

#ifdef IS_WINDOWS
	system("pause");
#endif
}
