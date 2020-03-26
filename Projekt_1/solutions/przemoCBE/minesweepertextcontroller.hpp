#ifndef __MINESWEEPER_TEXT_CONTROLLER_HPP__
#define __MINESWEEPER_TEXT_CONTROLLER_HPP__

class minesweeperTextController{
	public:
		minesweeperTextController(minesweeperBoard &board,minesweeperTextView view){
			this->board=&board;
			this->view=&view;
		}
		void play();
	private:
		minesweeperBoard *board;
		minesweeperTextView *view;
}

#endif
