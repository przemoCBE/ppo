#ifndef field_hpp
#define field_hpp

//a single field on a minesweeper board

struct field{
	bool hasMine:1,
	     hasFlag:1,
	     isRevealed:1;
};

#endif
