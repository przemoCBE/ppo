#include "minesweepertextview.hpp"
#include <iostream>

void minesweeperTextView::display(){
	this->displayLine();
	for(unsigned int posY=0;posY<board->getHeight();posY++){
		//add a marker every 5 rows
		if (posY%5==0){
			std::cout << '+';
		}else{
			std::cout << '|';
		}
		for(unsigned int posX=0;posX<board->getWidth();posX++){
			std::cout << board->getFieldInfo(posX,posY);
		}
		if (posY%5==0){
			std::cout << '+' << posY;
		}else{
			std::cout << '|';
		}
		std::cout << std::endl;
	}
	this->displayLine();
	this->displayNumbers();
}

void minesweeperTextView::displayLine(){
	std::cout << ' ';
	for(unsigned int posX=0;posX<board->getWidth();posX++){
		//add a marker every 5 columns
		if (posX%5==0){
			std::cout << '+';
		}else{
			std::cout << '-';
		}
	}
	std::cout << std::endl;
}

void minesweeperTextView::displayNumbers(){
	std::cout << ' ';
	for(unsigned int posX=0;posX<board->getWidth();posX++){
		if (posX%5==0){
			std::cout << posX;
			posX+=std::to_string(posX).length()-1;
		}else{
			std::cout << ' ';
		}
	}
	std::cout << std::endl;
}
