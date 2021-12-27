#include "pch.h"

#include "QRMatrix.hpp"
#include "Tables.hpp"
#include "utils.hpp"

void QRMatrix::draw_patterns()
{
	draw_finder_patterns();
	draw_alignment_patters();
	draw_timing_patterns();
	draw_dark_module();
}

void QRMatrix::draw_finder_patterns()
{
	draw_finder_square(0, 0); // левый верхний
	draw_finder_square(to_U(c.size()) - 7, 0); // левый нижний
	draw_finder_square(0, to_U(c.size()) - 7); // правый верхний
	draw_finder_square_separators();
}

void QRMatrix::draw_finder_square(unsigned y, unsigned x)
{
	set(y, x, 0b1111111, 7);
	set(y + 1, x, 0b1000001, 7);

	for (int i = 2; i < 5; i++)
		set(y + i, x, 0b1011101, 7);

	set(y + 5, x, 0b1000001, 7);
	set(y + 6, x, 0b1111111, 7);
}

void QRMatrix::draw_finder_square_separators()
{
	set(7, 0, 0b0000000, 7); // низ левого верхнего
	set(7, to_U(c.size()) - 7, 0b0000000, 7); // низ правого верхнего
	set(to_U(c.size()) - 8, 0, 0b0000000, 7); // верх левого нижнего

	for (unsigned i = 0; i < 8; i++) {
		set(i, 7, 0); // право левого верхнего
		set(i, to_U(c.size()) - 8, 0); // лево верхнего правого
		set(to_U(c.size()) - 8 + i, 7, 0); // право нижнего левого
	}
}

void QRMatrix::draw_alignment_patters()
{
	auto& coordinates = Tables::alignment_patterns_coordinates.at(version);

	// Нужно поставить выравнивающий узор в каждой парной	комбинации координат за исключением тех, где происходит пересечение с поисковыми узорами
	for (unsigned i = 0; i < coordinates.size(); i++) {
		unsigned s = i, e = to_U(coordinates.size()); // начинаем выбирать вторую координату с i-того индекса, така как комбинации до него уже поставлены отражением относительно главной диагонали
		if (coordinates[i] == 6) // если одна из координат равна 6, значит крайние координаты (6 и ближняя к другому краю) будут давать пересечение с поисковыми паттернами
			s++, e--; // а значит их неужно исключить

		for (unsigned j = s; j < e; j++) {
			draw_alignment_square(coordinates[i], coordinates[j]);
			if (i != j) // если координаты различны
				draw_alignment_square(coordinates[j], coordinates[i]); // рисуем симметрично относительно главной диагонали
		}
	}
}

void QRMatrix::draw_alignment_square(unsigned y, unsigned x)
{
	set(y - 2, x - 2, 0b11111, 5);
	set(y - 1, x - 2, 0b10001, 5);
	set(y, x - 2, 0b10101, 5);
	set(y + 1, x - 2, 0b10001, 5);
	set(y + 2, x - 2, 0b11111, 5);
}

void QRMatrix::draw_timing_patterns()
{
	for (unsigned i = 8; i < c.size() - 8; i += 2) {
		// вертикальная полоса синхронизации
		set(6, i, 1);
		set(6, i + 1, 0);
		// горизонтальная
		set(i, 6, 1);
		set(i + 1, 6, 0);
	}
}

void QRMatrix::draw_dark_module()
{
	set(to_U(c.size()) - 8, 8, 1);
}

void QRMatrix::place_metadata(CorrectionLevel corr_lvl, unsigned char mask_n)
{
	if (version >= 6) { // для версий начиная с седьмой
		const auto& v_codes = Tables::version_codes.at(version-6);

		for (unsigned i = 0; i < 3; i++)
			for (unsigned j = 0; j < 6; j++) {
				// побитово наносим информацию 
				set(to_U(c.size()) - 11 + i, j, (v_codes.at(i) >> (6 - 1 - j)) & 1); // горизонтально и
				set(j, to_U(c.size()) - 11 + i, (v_codes.at(i) >> (6 - 1 - j)) & 1); // вертикально
				// соответствующие биты информации получаются путём смещения и применения единичной битовой маски
			}
	}

	unsigned code = Tables::corr_lvl_and_mask_codes.at(corr_lvl)[mask_n];
	// Используются два "курсора" с координатами (y1, x2), (y2, x2). Первый огибает против часововй стрелки левый верхний поисковой квадрат, второй поднимается по правой стороне левого нижнего квадрата и слева направо под правым верхним квадратом
	unsigned y1 = 8, y2 = to_U(c.size()) - 1, x1 = 0, x2 = 8;
	for (unsigned i = 0; i < 15; i++) {
		set(y1, x1, (code >> (15 - 1 - i)) & 1);
		set(y2, x2, (code >> (15 - 1 - i)) & 1);

		// Первый курсор
		if (x1 < 8) { // пока не достигли правого нижнего угла квадрата
			x1++; // наращиваем горизонтальную координату
			if (x1 == 6) x1++; // пропускаем столбец с синхронизирующей линией
		}
		else { // если достигли правой стороны
			y1--; // уменьшаем вертикальную координату
			if (y1 == 6) y1--; // пропускаем строку с синхронизирующей линией
		}

		// Второй курсор
		if (y2 > c.size() - 8) // пока не достигли верха левого нижнего квадрата
			y2--; // уменьшаем вертикальую координату
		if (y2 == to_U(c.size()) - 8) { // когда достигли, "перепрыгиваем" к правому верхнему квадрату
			y2 = 8;
			x2 = to_U(c.size()) - 8;
	  } else if (y2 == 8) // если находимся под правым верхним квадратом
			x2++; // наращиваем горизонтальную координату

	}

	return;
}

void QRMatrix::place_data(const BitArray& data, unsigned char mask_n)
{
	unsigned y = to_U(c.size()) - 1;
	unsigned x = y;
	unsigned step = 0; // то, сколько бит данных было записано и индекс по совместительству	
	bool horiz_dir = true; // флаг обозначающий то, что на этом шаге нужно двигаться горизонтально
	bool up = true; // флаг, обозначающий направление вертикального движения (true => вверх)

	const auto& mask = Tables::mask_functions.at(mask_n);

	while (true) {
		if (x == 6) // если попадаем на вертикальную линию синхронизации
			x--; // сразу пропускаем её и перемещаемся на столбец влево

		if (get(y, x) == Trit::EMPTY) { // если клетка не заполнена
			if (step < data.size) { // если ещё не закончились данные
				set(y, x, mask(y, x) ? data.get(step) : !data.get(step)); // устанавливаем клетке значение и инвертируем его если маска равно нулю
				step++;
			}
			else set(y, x, !mask(y, x)); // иначе считаем, что значение равно 0 и применяем маску
		}

		if (horiz_dir) 
			x--;
		else {
			x++;
			if (up) {
				if (y == 0) {
					x -= 2;
					up = !up;
				}
				else
					y--;
			}
			else {
				if (y == c.size() - 1) {
					if (x == 1) // если достигли точки (c.size() - 1, 0) но x проверяется 1, так как уже на этой итерации сделали шаг "вправо" на строчке 162 (x++)
						break; // можно прерывать цикл записи. запись всегда будет заканчиваться в левом нижнем углу, так как это так для первой версси, а потом размеры QR кода увеличиваются на 4 с каждой версией, а значит будет успевать пройти весь "цикл смены наравления" (визуализация представлена на изображениях в п. "Расположение данных") 

					x -= 2;
					up = !up;
				}
				else
					y++;
			}
		}

		horiz_dir = !horiz_dir;
	}

}

void QRMatrix::set_version(char version_) {
	TritMatrix::resize(v_to_size(version_), v_to_size(version_));
	version = version_;
}
