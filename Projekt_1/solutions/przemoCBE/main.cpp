#include "minesweeperboard.cpp"
#include <ctime>
#include <iostream>

int main(){
	srand(time(NULL));
	minesweeperBoard board;
//	minesweeperBoard board;
	board.debugDisplay();
	std::cout<<"------\n";
	board.createBoard(15,20,1);
	board.debugDisplay();
	return 0;
}
