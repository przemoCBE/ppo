#ifndef minesweeperboard_hpp
#define minesweeperboard_hpp

#include "field.hpp"
#include <memory>

class minesweeperBoard{
	public:
		minesweeperBoard(unsigned int width,unsigned int height,unsigned int mineAmount=0){
			this->createBoard(width,height,mineAmount);
		};
		//phase 1 test constructor
		minesweeperBoard():minesweeperBoard(10,20){
			this->board[4][16].hasMine=true;
			this->board[6][3].hasMine=true;
			this->board[1][11].hasMine=true;
			this->board[4][16].hasFlag=true;
			this->board[7][12].isRevealed=true;
		};
		void debugDisplay() const;
		void createBoard(unsigned int width,unsigned int height,unsigned int mineAmount=0);
	private:
		std::unique_ptr<std::unique_ptr <field[]>[]> board;
		unsigned int width;
		unsigned int height;
		
		std::string fieldDebug(const field &pole) const;	//for debugDisplay()
};

#endif
