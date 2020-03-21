#include "minesweepertextview.hpp"
#include <iostream>

void minesweeperTextView::display(){
	this->displayLine();
	for(unsigned int posY=0;posY<board->getHeight();posY++){
		std::cout << '|';
		for(unsigned int posX=0;posX<board->getWidth();posX++){
			std::cout << board->getFieldInfo(posX,posY);
		}
		std::cout << '|' << std::endl;
	}
	this->displayLine();
}

void minesweeperTextView::displayLine(){
	std::cout << ' ';
	for(unsigned int posX=0;posX<board->getWidth();posX++){
		std::cout << '-';
	}
	std::cout << std::endl;
}
