#ifndef minesweeperboard_hpp
#define minesweeperboard_hpp

#include "field.hpp"
#include <memory>

class minesweeperBoard{
	public:
		minesweeperBoard(unsigned int width,unsigned int height,unsigned int mineAmount);
		minesweeperBoard();
		void debugDisplay() const;
		void createBoard(const unsigned int &width,const unsigned int &height){
			this->width=width;
			this->height=height;
			board.reset();
			board=std::make_unique<std::unique_ptr <field[]>[]>(this->width);
			for (unsigned int i=0;i<this->width;i++){
				minesweeperBoard::board[i]=std::make_unique<field[]>(this->height);
			}
		};
		//TODO: safety against polulating non-empty boards
		void populateBoard(unsigned int mineAmount){
			if (mineAmount>(this->width*this->height/2)){
				mineAmount=(this->width*this->height/2);
			}
			field *random;
			for (unsigned int i=0;i<mineAmount;i++){
				do{
					random=&board[rand()%width][rand()%height];
				}while(random->hasMine);
				random->hasMine=true;
			}
		};	
	private:
		std::unique_ptr<std::unique_ptr <field[]>[]> board;
		unsigned int width;
		unsigned int height;
		
		std::string fieldDebug(const field &pole) const;	//for debugDisplay()
		

};

#endif
