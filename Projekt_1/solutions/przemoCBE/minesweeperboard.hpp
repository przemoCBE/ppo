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
			this->setMine(4,16,true);
			this->getField(4,16).hasFlag=true;
			this->setMine(6,3,true)=true;
			this->setMine(1,1,true)=true;
			this->getField(7,12).isRevealed=true;
		};
		void debugDisplay() const;
		void createBoard(unsigned int width,unsigned int height,unsigned int mineAmount=0);
		
		unsigned int getWidth() const {return width;}
		unsigned int getHeight() const {return height;}
	private:
		bool setMine(unsigned int posX,unsigned int posY,bool val);
		//remember to add & to the variable name if you want to modify the values of the field
		field &getField(unsigned int posX,unsigned int posY){
			if (posX<this->width&&posY<this->height){
				return board[posX][posY];
			}
			return *std::make_unique<field>();
		}
		//game board
		std::unique_ptr<std::unique_ptr <field[]>[]> board;
		//dimensions of the game board
		unsigned int width;
		unsigned int height;
		//used by debugDisplay()
		std::string fieldDebug(const field &debug) const;
		
		void populateBoard(unsigned int mineAmount);
};

#endif
