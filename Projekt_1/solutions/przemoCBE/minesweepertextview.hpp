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
};

#endif
