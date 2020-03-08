#ifndef minesweeperboard_cpp
#define minesweeperboard_cpp

#include <iostream>
#include <string>
#include <memory>
#include "minesweeperboard.hpp"

//phase 1
minesweeperBoard::minesweeperBoard(){
	this->width=10;
	this->height=20;
	board=std::make_unique<std::unique_ptr <field[]>[]>(this->width);
	for (unsigned int i=0;i<this->width;i++){
		minesweeperBoard::board[i]=std::make_unique<field[]>(this->height);
	}
	board[4][16].hasMine=true;
	board[6][3].hasMine=true;
	board[1][11].hasMine=true;
	board[4][16].hasFlag=true;
	board[7][12].isRevealed=true;
}


minesweeperBoard::minesweeperBoard(unsigned int width,unsigned int height,unsigned int mineAmount){
	this->width=width;
	this->height=height;
	if (mineAmount>(this->width*this->height/2)){
		mineAmount=(this->width*this->height/2);
	}
	board=std::make_unique<std::unique_ptr <field[]>[]>(this->width);
	for (unsigned int i=0;i<this->width;i++){
		minesweeperBoard::board[i]=std::make_unique<field[]>(this->height);
	}
	for (unsigned int i=0;i<mineAmount;i++){
		while (true){
			field &random=board[rand()%width][rand()%height];
			if (!random.hasMine){
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
