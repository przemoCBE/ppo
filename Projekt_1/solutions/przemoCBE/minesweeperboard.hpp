#ifndef minesweeperboard_hpp
#define minesweeperboard_hpp

#include "field.hpp"
#include <memory>


enum gameMode                     { DEBUG, EASY=10, NORMAL=20, HARD=30 };
enum gameState                    { NEW , RUNNING , FINISHED_WIN , FINISHED_LOSS };
const std::string gameStateName[] {"NEW","RUNNING","FINISHED_WIN","FINISHED_LOSS"};//debugDisplay()

class minesweeperBoard{
	public:
		minesweeperBoard(unsigned int width,unsigned int height,unsigned int mineAmount=0){this->createBoard(width,height,mineAmount);};
		minesweeperBoard(unsigned int width,unsigned int height,gameMode mode){this->createBoard(width,height,mode);};
		//test constructor
		minesweeperBoard():minesweeperBoard(10,20,DEBUG){};
		void debugDisplay() const;
		void createBoard(unsigned int width,unsigned int height,unsigned int mineAmount=0);
		void createBoard(unsigned int width,unsigned int height,gameMode mode){
			if (mode){
				createBoard(width,height,(width*height)*(mode*0.01));	
			}else{
				createBoard(width,height);
				populateDebug();
			}
		};
		
		unsigned int getWidth() const {return width;}
		unsigned int getHeight() const {return height;}
		unsigned int getFlagAmount() const {return flagAmount;};
		
		gameState getGameState() const {return state;};
		
		bool getFlag(unsigned int posX,unsigned int posY) const {
			if (isOnBoard(posX,posY)){
				return board[posX][posY].hasFlag;
			}
			return false;
		}/*
		bool getMine(unsigned int posX,unsigned int posY) const {
			if (isRevealed(posX,posY))){
				return hasMine(posX,posY)
			}
			return false;
		}*/
		bool getRevealed(unsigned int posX,unsigned int posY) const{
			if (isOnBoard(posX,posY)){
				return board[posX][posY].isRevealed;
			}
			return false;
		}
		
		int getNearbyMines(unsigned int posX,unsigned int posY) const {
			if (getRevealed(posX,posY)){
				return board[posX][posY].nearbyMines;
			}
			return -1;
		}
		bool reveal(unsigned int posX,unsigned int posY);
		bool toggleFlag(unsigned int posX,unsigned int posY);
		
		char getFieldInfo() const;
		
	private:
		//game board
		std::unique_ptr<std::unique_ptr <field[]>[]> board;
		//dimensions of the game board
		unsigned int width;
		unsigned int height;
		
		//for tracking win conditions and user interface
		//win if all three are equal
		unsigned int mineAmount=0;
		unsigned int flagAmount=0;
		unsigned int flaggedMineAmount=0;
		//win if it reaches mineAmount
		unsigned int coveredFields;	
		
		gameState state=NEW;
		//used by debugDisplay()
		std::string fieldDebug(unsigned int posX,unsigned int posY) const;
		
		void populateBoard(unsigned int mineAmount);
		void populateDebug();
		//used by reveal()
		void revealFlood(unsigned int posX,unsigned int posY);
		void safeSpot(unsigned int posX,unsigned int posY);
		
		bool setMine(unsigned int posX,unsigned int posY,const bool val);
		//similar to getMine
		bool hasMine(unsigned int posX,unsigned int posY) const {
			if (isOnBoard(posX,posY)){
				return board[posX][posY].hasMine;
			}
			return false;
		}
		
		bool isOnBoard(unsigned int posX,unsigned int posY) const{
			if (posX<this->width&&posY<this->height){
				return true;
			}
			return false;
		};
};


#endif
