#ifndef minesweeperboard_cpp
#define minesweeperboard_cpp

#include <iostream>
#include <string>
#include <memory>
#include "minesweeperboard.hpp"

std::string minesweeperBoard::fieldDebug(const field &debug) const{
	std::string toReturn="...";
	if (debug.hasMine)
		toReturn[0]='M';
	if (debug.isRevealed)
		toReturn[1]='O';
	if (debug.hasFlag)
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

void minesweeperBoard::createBoard(unsigned int width,unsigned int height,unsigned int mineAmount){
	//set width/height
	this->width=width;
	this->height=height;
	//create the board
	board=std::make_unique<std::unique_ptr <field[]>[]>(this->width);
	for (unsigned int i=0;i<this->width;i++){
		minesweeperBoard::board[i]=std::make_unique<field[]>(this->height);
	}
	if (mineAmount>(this->width*this->height/2)){
		mineAmount=(this->width*this->height/2);
	}
	//populate the board with mines
	field *random;
	for (unsigned int i=0;i<mineAmount;i++){
		do{
			random=&board[rand()%width][rand()%height];
		}while(random->hasMine);
		random->hasMine=true;
	}
}

#endif
