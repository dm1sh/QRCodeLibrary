#pragma once

#include <vector>

#include "Method.hpp"
#include "BitArray.hpp"
#include "TritMatrix.hpp"

constexpr unsigned v_to_size(char version) { return version * 4 + 21; };

class QRMatrix : public TritMatrix
{
public:
	QRMatrix(char version_) : TritMatrix(v_to_size(version_)), version{ version_ } {};

	void draw_patterns();

	void draw_finder_patterns();
	void draw_finder_square(unsigned y, unsigned x);
	void draw_finder_square_separators();

	void draw_alignment_patters();
	void draw_alignment_square(unsigned y, unsigned x);

	void draw_timing_patterns();
	void draw_dark_module();

	void place_metadata(CorrectionLevel corr_lvl, unsigned char mask_n);

	void place_data(const BitArray& data, unsigned char mask_n);

	void set_version(char version);

private:
	char version;
};

