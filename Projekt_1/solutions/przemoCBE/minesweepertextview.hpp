#ifndef __MINESWEEPER_TEXT_VIEW_HPP__
#define __MINESWEEPER_TEXT_VIEW_HPP__

#include "minesweeperboard.cpp"

class minesweeperTextView{
	public:
		minesweeperTextView(minesweeperBoard &board){
			this->board=&board;	
		};
		void display();
	private:
		minesweeperBoard *board;
		std::string makeLine(std::string every5);
		std::string makeNumbers();
		std::string makeField(unsigned int posX,unsigned int posY);
		
};

#endif
