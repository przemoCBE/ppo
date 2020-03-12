#ifndef minesweeperboard_cpp
#define minesweeperboard_cpp

#include <iostream>
#include <string>
#include <memory>
#include <random>
#include <ctime>
#include "minesweeperboard.hpp"

std::string minesweeperBoard::fieldDebug(const field &debug) const{
	std::string toReturn="...";
	if (debug.hasMine){
		toReturn[0]='M';
	}
	if (debug.isRevealed){
		toReturn[1]='O';
	}
	if (debug.hasFlag){
		toReturn[2]='F';
	}
	toReturn.append(std::to_string(static_cast<unsigned int>(debug.nearbyMines)));
	//toReturn.append(<unsigned int>(debug.nearbyMines));
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
	populateBoard(mineAmount);
}
	
//populate the board with mines       
void minesweeperBoard::populateBoard(unsigned int mineAmount){
	std::minstd_rand randomEngine(time(nullptr));	//c++11 predefined random engine
	std::uniform_int_distribution<unsigned int> randomX(0,this->width-1), randomY(0,this->height-1);
	for (unsigned int i=0;i<mineAmount;i++){
		while(!setMine(randomX(randomEngine),randomY(randomEngine),true)){};
        }
}

bool minesweeperBoard::setMine(unsigned int posX,unsigned int posY,bool val){
	field &working=getField(posX,posY);
	if (working.hasMine==val){
		return false;
	}
	working.hasMine=val;
	short a;
	if (val){
		a=1;
	}else{
		a=-1;
	}
	for (unsigned int i=posX-1;i<=posX+1;i++){
		for (unsigned int j=posY-1;j<=posY+1;j++){
			getField(i,j).nearbyMines+=a;
		}
	}
	return true;
}

#endif
