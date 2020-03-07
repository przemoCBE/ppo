#ifndef minesweeperboard_cpp
#define minesweeperboard_cpp

#include <iostream>
#include <string>
#include "minesweeperboard.hpp"

minesweeperBoard::minesweeperBoard(){
	width=10;
	height=20;
	board[4][16].hasMine=true;
	board[6][3].hasMine=true;
	board[1][11].hasMine=true;
	board[4][16].hasFlag=true;
	board[7][12].isRevealed=true;
}

std::string minesweeperBoard::fieldDebug(const field &pole) const{
	std::string toReturn="...";
	if (pole.hasMine)
		toReturn[0]='M';
	if (pole.isRevealed)
		toReturn[1]='O';
	if (pole.hasFlag)
		toReturn[2]='F';
	return toReturn;
}

void minesweeperBoard::debugDisplay() const{
	for (unsigned int i=0;i<height;i++){
		for (unsigned int j=0;j<width;j++){
			std::cout << "[" << fieldDebug(board[j][i]) << "] ";
		}
		std::cout << std::endl;
	}
}

#endif
