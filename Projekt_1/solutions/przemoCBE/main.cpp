#include "minesweeperboard.cpp"
#include <iostream>

int main(){
	minesweeperBoard board;
	//losing
	board.debugDisplay();
	board.reveal(7,7);//safe, despite landing on a mine
	board.debugDisplay();
	board.reveal(2,2);//loss
	board.debugDisplay();
	std::cout<<"------------------------\n";
	//winning by revealing
	board.createBoard(7,7,gameMode::DEBUG);
	board.debugDisplay();
	board.reveal(7,6);
	board.debugDisplay();
	board.reveal(2,6);
	board.debugDisplay();
	board.reveal(6,2);
	board.debugDisplay();
	board.toggleFlag(0,0);
	board.toggleFlag(5,4);
	board.reveal(0,1);
	board.reveal(0,3);
	board.reveal(0,5);
	board.reveal(6,5);
	board.reveal(5,6);
	board.reveal(2,1);
	board.reveal(3,1);
	board.reveal(3,2);
	board.reveal(1,2);
	board.reveal(1,3);
	board.debugDisplay();
	board.reveal(2,3);
	board.debugDisplay();
	std::cout<<"------------------------\n";
	//winning by flags
	board.createBoard(7,7,gameMode::DEBUG);
	board.reveal(2,6);
	board.debugDisplay();
	//horizontal
	for (unsigned int i=0;i<7;i++){
		board.toggleFlag(i,0);
	}
	board.debugDisplay();
	//vertical
	for (unsigned int i=2;i<7;i+=2){
		board.toggleFlag(0,i);
	}
	board.debugDisplay();
	//diagonal
	for (unsigned int i=1;i<6;i++){
		board.toggleFlag(i,i);
	}
	board.toggleFlag(7,7);	//no changes can be made outside of the board
	board.debugDisplay();
	board.toggleFlag(6,5);
	board.debugDisplay();
	board.toggleFlag(6,6);
	board.debugDisplay();
	board.toggleFlag(6,5);
	board.debugDisplay();
	board.toggleFlag(6,6);	//no changes can be made after the game ends
	board.debugDisplay();
	std::cout<<"------------------------\n";
	board.createBoard(10,10,gameMode::HARD);
	board.debugDisplay();
	return 0;
}
