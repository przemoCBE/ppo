#include "minesweeperboard.cpp"
#include <iostream>

int main(){
	minesweeperBoard board;
	board.debugDisplay();
	std::cout<<"------\n";
	board.createBoard(10,20,100);
	board.debugDisplay();
	return 0;
}
