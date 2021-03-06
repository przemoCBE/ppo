#ifndef __MINESWEEPER_BOARD_HPP__
#define __MINESWEEPER_BOARD_HPP__

#include "field.hpp"
#include <memory>
#include <string>


enum gameMode                     { DEBUG, EASY=10, NORMAL=20, HARD=30 };
enum gameState                    { NEW , RUNNING , FINISHED_WIN , FINISHED_LOSS };
const std::string gameStateName[] {"NEW","RUNNING","FINISHED_WIN","FINISHED_LOSS"};//debugDisplay()

class minesweeperBoard{
	public:
		minesweeperBoard(unsigned int width,unsigned int height,unsigned int mineAmount=0){this->createBoard(width,height,mineAmount);};
		minesweeperBoard(unsigned int width,unsigned int height,gameMode mode){this->createBoard(width,height,mode);};
		
		void debugDisplay() const;
		void createBoard(unsigned int width,unsigned int height,unsigned int mineAmount=0);
		void createBoard(unsigned int width,unsigned int height,gameMode mode){
			if (mode==gameMode::DEBUG){
				this->createBoard(width,height);
				this->populateDebug();
			}else{
				this->createBoard(width,height,(width*height)*(mode*0.01));
			}
		}
		unsigned int getBoardWidth() const {return width;}
		unsigned int getBoardHeight() const {return height;}
		unsigned int getFlagAmount() const {return flagAmount;}
		unsigned int getMineAmount() const {return mineAmount;}
		gameState getGameState() const {return state;}
		
		bool getFlag(unsigned int posX,unsigned int posY) const {
			if (this->isOnBoard(posX,posY)){
				return this->board[posX][posY].hasFlag;
			}
			return false;
		}
		int countMines(unsigned int posX,unsigned int posY) const {
			//actually just return a precounted amount
			if (this->isRevealed(posX,posY)){
				return this->board[posX][posY].nearbyMines;
			}
			return -1;
		}
		bool isRevealed(unsigned int posX,unsigned int posY) const{
			if (this->isOnBoard(posX,posY)){
				return this->board[posX][posY].isRevealed;
			}
			return false;
		}
		bool reveal(unsigned int posX,unsigned int posY);
		bool toggleFlag(unsigned int posX,unsigned int posY);
		char getFieldInfo(unsigned int posX,unsigned int posY) const;
		
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
		gameState state=gameState::NEW;
		//used by debugDisplay()
		std::string fieldDebug(unsigned int posX,unsigned int posY) const;
		void populateBoard(unsigned int mineAmount);
		void populateDebug();
		void revealFlood(unsigned int posX,unsigned int posY); //used by reveal()
		void safeSpot(unsigned int posX,unsigned int posY);
		bool setMine(unsigned int posX,unsigned int posY,const bool val);
		
		//private getters
		bool hasMine(unsigned int posX,unsigned int posY) const {
			if (this->isOnBoard(posX,posY)){
				return this->board[posX][posY].hasMine;
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
