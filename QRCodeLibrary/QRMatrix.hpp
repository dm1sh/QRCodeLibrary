#pragma once

#include <vector>

#include "Method.hpp"
#include "BitArray.hpp"
#include "TritMatrix.hpp"

// Переводит версию в соответствующий ей размер QR кода
constexpr unsigned v_to_size(char version) { return version * 4 + 21; };

class QRMatrix : public TritMatrix
{
public:
	QRMatrix(char version_) : TritMatrix(v_to_size(version_)), version{ version_ } {};

	// Рисует стандартные обязательные элементы QR кода
	void draw_patterns();

	// Рисует поисковые узоры
	void draw_finder_patterns();
	/* Рисует поисковой квадрат с координатами (y, x) 
		 #######
		 #     #
		 # ### #
		 # ### #
		 # ### #
		 #     #
		 #######
	*/
	void draw_finder_square(unsigned y, unsigned x);
	// Рисует контуры вокруг поисковых квадратов
	void draw_finder_square_separators();

	// Рисует выравнивающие узоры
	void draw_alignment_patters();
	/* Рисует выравнивающий квадрат с координатами центра (y, x)
		 #####
		 #   #
		 # # #
		 #   #
		 #####
	*/
	void draw_alignment_square(unsigned y, unsigned x);

	// Рисует синхронизирующие полосы
	void draw_timing_patterns();
	// Рисует чёрный пиксель возле левого нижнего квадрата
	void draw_dark_module();

	// Размещает метаданные на QR коде (уровень коррекции, номер маски, начиная с 7-ой версии, версию)
	void place_metadata(CorrectionLevel corr_lvl, unsigned char mask_n);

	// Размещает данные с применённой маской mask_n
	void place_data(const BitArray& data, unsigned char mask_n);

	// Устанавливает версию и соответственно размер матрицы 
	void set_version(char version);

private:
	char version;
};

