#ifndef minesweeperboard_cpp
#define minesweeperboard_cpp

#include <iostream>
#include "minesweeperboard.hpp"

using std::cout;

//phase 1
minesweeperBoard::minesweeperBoard(){
	width=10;
	height=20;
	board[4][16].hasMine=true;
	board[6][3].hasMine=true;
	board[1][11].hasMine=true;
	board[4][16].hasFlag=true;
	board[7][12].isRevealed=true;
}

minesweeperBoard::minesweeperBoard(unsigned int w,unsigned int h,unsigned int mineAmount){
	if (w>100)
		w=100;
	if (h>100)
		h=100;
	if (mineAmount>(w*h/2))
		mineAmount=(w*h/2);
	width=w;
	height=h;
	for (unsigned int i=0;i<mineAmount;i++){
		//generuj liczby losowe aż trafisz na pole, które nie ma miny
		while (true){
			field &random=board[rand()%w][rand()%h];
			if (random.hasMine==false){
				random.hasMine=true;
				break;
			}
		}
	}
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
