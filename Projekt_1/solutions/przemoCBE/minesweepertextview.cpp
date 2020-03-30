#include "minesweepertextview.hpp"
#include <iostream>

void minesweeperTextView::display(){
	std::cout<<"┏"<<this->makeLine("┯")<<"┓"<<std::endl;
	for(unsigned int posY=0;posY<board->getBoardHeight();posY++){
		//add a marker every 5 rows
		if (posY%5==0){
			std::cout << "┠";
		}else{
			std::cout << "┃";
		}
		for(unsigned int posX=0;posX<board->getBoardWidth();posX++){
			std::cout << this->makeField(posX,posY);
		}
		if (posY%5==0){
			std::cout << "┨" << posY;
		}else{
			std::cout << "┃";
		}
		std::cout << std::endl;
	}
	std::cout<<"┗"<<this->makeLine("┷")<<"┛"<<std::endl
	         <<' '<<this->makeNumbers()<<std::endl;
}

std::string minesweeperTextView::makeLine(std::string every5){
	std::string toReturn;
	for(unsigned int posX=0;posX<board->getBoardWidth();posX++){
		//add a marker every 5 columns
		if (posX%5==0){
			toReturn+=every5;
		}else{
			toReturn+="━";
		}
	}
	return toReturn;
}

std::string minesweeperTextView::makeNumbers(){
	std::string toReturn;
	for(unsigned int posX=0;posX<board->getBoardWidth();posX++){
		if (posX%5==0){
			toReturn+=std::to_string(posX);
			posX+=std::to_string(posX).length()-1;
		}else{
			toReturn+=' ';
		}
	}
	return toReturn;
}

std::string minesweeperTextView::makeField(unsigned int posX,unsigned int posY){
	std::string toReturn;
	toReturn+=this->board->getFieldInfo(posX,posY);
	switch(toReturn[0]){
		case '_':
			return "▒";
		case ' ':
			if (posX%5==0){
				if (posY%5==0){
					return "┼";
				}
				return "│";
			}
			if (posY%5==0){
				return "─";
			}
			return " ";
		case 'F':
			return "⚑";
	}
	return toReturn;
}
