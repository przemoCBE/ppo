#ifndef minesweeperboard_hpp
#define minesweeperboard_hpp

#include "field.hpp"

class minesweeperBoard{
	field board[100][100];
	unsigned int width;
	unsigned int height;
	std::string fieldDebug(const field &pole) const;	//for debugDisplay()
 public:
	minesweeperBoard(unsigned int w,unsigned int h,unsigned int ileMin);
	minesweeperBoard();
	void debugDisplay() const;
};

#endif
