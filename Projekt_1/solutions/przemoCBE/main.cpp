#include "minesweeperboard.cpp"
#include <iostream>

int main(){
	minesweeperBoard board;
	board.debugDisplay();
	std::cout<<"------\n";
	board.createBoard(10,20,50);
	board.debugDisplay();
	return 0;
}
