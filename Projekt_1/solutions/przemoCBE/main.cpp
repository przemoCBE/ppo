#include "minesweeperboard.cpp"
#include <ctime>
#include <iostream>

int main(){
	srand(time(NULL));
	minesweeperBoard board(15,15,50);
//	minesweeperBoard board;
	board.debugDisplay();
	std::cout<<"------\n";
	board.createBoard(20,20);
	board.debugDisplay();
	return 0;
}
