#ifndef minesweeperboard_cpp
#define minesweeperboard_cpp

#include <iostream>
#include <string>
#include <memory>
#include <random>
#include <ctime>
#include "minesweeperboard.hpp"

void minesweeperBoard::debugDisplay() const{
	for (unsigned int i=0;i<height;i++){
		for (unsigned int j=0;j<width;j++){
			std::cout << "[" << fieldDebug(j,i) << "] ";
		}
		std::cout << std::endl;
	}
	
	std::cout << "---------------\n"
	          << "there are:\n"
	          << this->mineAmount         << " mines\n"
	          << this->flagAmount         << " flags\n"
	          << this->flaggedMineAmount   << " flagged mines\n"
	          << this->coveredFields        << " covered fields\n"
	          << "---------------\n"
	          << "game is in " << gameStateName[this->state] <<" state\n"
	          << "---------------\n";
}

std::string minesweeperBoard::fieldDebug(unsigned int posX,unsigned int posY) const{
	if (!isOnBoard(posX,posY)){
		return "err ";	
	};
	field debug=board[posX][posY];
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
	return toReturn;
}

void minesweeperBoard::createBoard(unsigned int width,unsigned int height,unsigned int mineAmount){
	if (width<4){
		width=4;
	}
	if (height<4){
		height=4;
	}
	if (mineAmount>(width*height-9)){
		mineAmount=(width*height-9);
	}
	//set width/height
	this->width=width;
	this->height=height;
	//set win condition trackers
	this->mineAmount=0;	//operated by setMine()
	this->coveredFields=(width*height);
	this->flagAmount=0;
	this->flaggedMineAmount=0;
	
	this->state=NEW;
	//create the board
	board=std::make_unique<std::unique_ptr <field[]>[]>(this->width);
	for (unsigned int i=0;i<this->width;i++){
		minesweeperBoard::board[i]=std::make_unique<field[]>(this->height);
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

void minesweeperBoard::populateDebug(){
	//horizontal
	for (unsigned int i=0;i<this->width;i++){
		setMine(i,0,true);
	}
	//vertical
	for (unsigned int i=2;i<this->height;i+=2){
		setMine(0,i,true);
	}
	//diagonal
	for (unsigned int i=1;i<this->width&&i<this->height;i++){
		setMine(i,i,true);
	}
}

bool minesweeperBoard::setMine(unsigned int posX,unsigned int posY,const bool hasMine){
	if (isOnBoard(posX,posY)&&board[posX][posY].hasMine!=hasMine){
		board[posX][posY].hasMine=hasMine;
		short a;
		if (hasMine){
			a=1;
		}else{
			a=-1;
		}
		for (unsigned int i=posX;i<=posX+2;i++){
			for (unsigned int j=posY;j<=posY+2;j++){
				if (isOnBoard(i-1,j-1)){
					board[i-1][j-1].nearbyMines+=a;
				}
			}
		}
		this->mineAmount+=a;
		return true;
	}
	return false;
}
//return true if the game ends
bool minesweeperBoard::reveal(unsigned int posX,unsigned int posY){
	if (!isOnBoard(posX,posY)){
		return false;
	}
	switch (this->state){
		case NEW:
			safeSpot(posX,posY);
			this->state=RUNNING;
		case RUNNING:
		break;
		default:
			return false;
	}
	if (hasMine(posX,posY)){
		this->board[posX][posY].isRevealed=true;
		this->state=FINISHED_LOSS;
		return true;
	}
	revealFlood(posX,posY);
	if (this->coveredFields==this->mineAmount){
		this->state=FINISHED_WIN;
		return true;
	}
	return false;
}

void minesweeperBoard::revealFlood(unsigned int posX,unsigned int posY){
	if (!isOnBoard(posX,posY)||getRevealed(posX,posY)){
		return;
	}
	this->board[posX][posY].isRevealed=true;
	this->coveredFields--;
	if (getNearbyMines(posX,posY)>0){
		return;
	}
	for (unsigned int i=posX;i<=posX+2;i++){
		for (unsigned int j=posY;j<=posY+2;j++){
			revealFlood(i-1,j-1);
		}
	}
}

//create a safe spot to prevent landing on a mine in the first move
void minesweeperBoard::safeSpot(unsigned int posX,unsigned int posY){
	unsigned int movedMines=0;
	for (unsigned int i=posX;i<=posX+2;i++){
		for (unsigned int j=posY;j<=posY+2;j++){
			if (hasMine(i-1,j-1)){
				movedMines++;
			}
			setMine(i-1,j-1,true);
		}
	}
	populateBoard(movedMines);
	for (unsigned int i=posX;i<=posX+2;i++){
		for (unsigned int j=posY;j<=posY+2;j++){
			setMine(i-1,j-1,false);
		}
	}
}
//return true if the game ends
bool minesweeperBoard::toggleFlag(unsigned int posX,unsigned int posY){
	if (!isOnBoard(posX,posY)||board[posX][posY].isRevealed||this->state!=RUNNING){
		return false;
	}
	int a;
	if (this->board[posX][posY].hasFlag){
		a=-1;
	}else{
		a=1;
	}
	this->flagAmount+=a;
	if (this->board[posX][posY].hasMine){
		this->flaggedMineAmount+=a;
	}
	board[posX][posY].hasFlag=!board[posX][posY].hasFlag;
	if(mineAmount==flagAmount&&mineAmount==flaggedMineAmount){
		this->state=FINISHED_WIN;
		return true;
	}
	return false;
}

char minesweeperBoard::getFieldInfo(unsigned int posX,unsigned int posY) const{
	if (!isOnBoard(posX,posY)){
		return '#';
	}
	if (!getRevealed(posX,posY)){
		if (getFlag(posX,posY)){
			return 'F';
		}
		return '_';
	}
	if (hasMine(posX,posY)){
		return 'X';
	}
	char toReturn = std::to_string(getNearbyMines(posX,posY))[0];
	if (toReturn=='0'){
		toReturn=' ';
	}
	return toReturn;
}

#endif
