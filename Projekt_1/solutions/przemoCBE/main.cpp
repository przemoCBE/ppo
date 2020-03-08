#include "minesweeperboard.cpp"
#include <ctime>

int main(){
//	srand(time(NULL));
	minesweeperBoard board(10,15,10);
//	minesweeperBoard board;
	board.debugDisplay();
	return 0;
}
