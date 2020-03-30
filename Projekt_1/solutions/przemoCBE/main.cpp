#include "minesweeperboard.hpp"
#include "minesweepertextview.hpp"
#include "minesweepertextcontroller.hpp"

int main(){
	minesweeperBoard board(50,10,gameMode::EASY);
	minesweeperTextView display(board);
	minesweeperTextController control(board,display);
	
	control.play();
	return 0;
}
