#include "minesweeperboard.cpp"
#include "minesweepertextview.cpp"
#include "minesweepertextcontroller.cpp"

int main(){
	minesweeperBoard board(20,20,gameMode::EASY);
	minesweeperTextView display(board);
	minesweeperTextController control(board,display);
	
	control.play();
	return 0;
}
