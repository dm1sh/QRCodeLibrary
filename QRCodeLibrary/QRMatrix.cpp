#include "pch.h"

#include "QRMatrix.hpp"
#include "Tables.hpp"

void QRMatrix::draw_patterns()
{
	draw_finder_patterns();
	draw_alignment_patters();
	draw_timing_patterns();
	draw_dark_module();
}

void QRMatrix::draw_finder_patterns()
{
	draw_finder_square(0, 0);
	draw_finder_square(c.size() - 7, 0);
	draw_finder_square(0, c.size() - 7);
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
	set(7, 0, 0b0000000, 7);
	set(7, c.size() - 7, 0b0000000, 7);
	set(c.size() - 8, 0, 0b0000000, 7);

	for (unsigned i = 0; i < 8; i++) {
		set(i, 7, 0);
		set(i, c.size() - 8, 0);
		set(c.size() - 8 + i, 7, 0);
	}
}

void QRMatrix::draw_alignment_patters()
{
	auto& coordinates = Tables::alignment_patterns_coordinates.at(version);
	for (unsigned i = 0; i < coordinates.size(); i++) {
		unsigned s = i, e = coordinates.size();
		if (coordinates[i] == 6)
			s++, e--;

		for (unsigned j = s; j < e; j++) {
			draw_alignment_square(coordinates[i], coordinates[j]);
			if (i != j)
				draw_alignment_square(coordinates[j], coordinates[i]);
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
		set(6, i, 1);
		set(6, i + 1, 0);
		set(i, 6, 1);
		set(i + 1, 6, 0);
	}
}

void QRMatrix::draw_dark_module()
{
	set(c.size() - 8, 8, 1);
}

void QRMatrix::place_metadata(CorrectionLevel corr_lvl, unsigned char mask_n)
{
	if (version >= 6) {
		const auto& v_codes = Tables::version_codes.at(version-6);
		for (unsigned i = 0; i < 3; i++)
			for (unsigned j = 0; j < 6; j++) {
				set(c.size() - 11 + i, j, (v_codes.at(i) >> (6 - 1 - j)) & 1);
				set(j, c.size() - 11 + i, (v_codes.at(i) >> (6 - 1 - j)) & 1);
			}
	}

	unsigned code = Tables::corr_lvl_and_mask_codes.at(corr_lvl)[mask_n];

	unsigned y1 = 8, y2 = c.size() - 1, x1 = 0, x2 = 8;
	for (unsigned i = 0; i < 15; i++) {
		set(y1, x1, (code >> (15 - 1 - i)) & 1);
		set(y2, x2, (code >> (15 - 1 - i)) & 1);

		if (x1 < 8) {
			x1++;
			if (x1 == 6) x1++;
		}
		else {
			if (x1 == 8) y1--;
			if (y1 == 6) y1--;
		}

		if (y2 > c.size() - 8) y2--;
		if (y2 == c.size() - 8) { y2 = 8; x2 = c.size() - 8; }
		else if (y2 == 8) 
			x2++;

	}

	return;
}

void QRMatrix::place_data(const BitArray& data, unsigned char mask_n)
{
	unsigned y = c.size() - 1;
	unsigned x = y;
	unsigned step = 0;
	bool horiz_dir = true;
	bool up = true;

	const auto& mask = Tables::mask_functions.at(mask_n);

	while (true) {
		if (x == 6)
			x--;

		if (get(y, x) == Trit::EMPTY) {
			if (step < data.size) {
				set(y, x, mask(y, x) ? data.get(step) : !data.get(step));
				step++;
			}
			else set(y, x, !mask(y, x));
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
					if (x == 1) // т.к. сделали шаг "вправо" на строчке 130
						break;

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
