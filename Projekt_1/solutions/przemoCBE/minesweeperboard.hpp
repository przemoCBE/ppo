#ifndef minesweeperboard_hpp
#define minesweeperboard_hpp

#include "field.hpp"
#include <memory>

class minesweeperBoard{
	public:
		minesweeperBoard(unsigned int width,unsigned int height,unsigned int mineAmount);
		minesweeperBoard();
		void debugDisplay() const;
	private:
		std::unique_ptr<std::unique_ptr <field[]>[]> board;
		unsigned int width;
		unsigned int height;
		std::string fieldDebug(const field &pole) const;	//for debugDisplay()
};

#endif
