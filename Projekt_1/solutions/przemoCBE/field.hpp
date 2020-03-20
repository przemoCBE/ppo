#ifndef __FIELD_HPP__
#define __FIELD_HPP__

//a single field on a minesweeper board

struct field{
	unsigned char nearbyMines:4;
	bool hasMine:1,
	     hasFlag:1,
	     isRevealed:1;
};

#endif
