#include "minesweeperboard.cpp"
#include <ctime>

int main(){
	srand(time(NULL));
	minesweeperBoard board(15,15,50);
//	minesweeperBoard board;
	board.debugDisplay();
	return 0;
}
