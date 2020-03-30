#ifndef __MINESWEEPER_TEXT_CONTROLLER_HPP__
#define __MINESWEEPER_TEXT_CONTROLLER_HPP__


#include "minesweeperboard.hpp"
#include "minesweepertextview.hpp"

class minesweeperTextController{
	public:
		minesweeperTextController(minesweeperBoard &board,minesweeperTextView &display){
			this->board=&board;
			this->display=&display;
		}
		void play();
	private:
		minesweeperBoard *board;
		minesweeperTextView *display;
		bool exit=false;
		
		std::string parse(std::string input);
		void posCommands(char command,unsigned int posX,unsigned int posY);
		void quit();
};

#endif
