#include "minesweepertextview.hpp"
#include <iostream>

void minesweeperTextView::display(){
	for(unsigned int posX=0;posX<board->getWidth();posX++){
		for(unsigned int posY=0;posY<board->getHeight();posY++){
			std::cout << board->getFieldInfo(posX,posY);
		}
		std::cout << std::endl;
	}
}
