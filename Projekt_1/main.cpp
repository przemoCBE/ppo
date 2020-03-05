#include <iostream>
#include <time.h>
#include "minesweeperboard.hpp"

using namespace std;

int main(){
	srand(time(NULL));
//	minesweeperBoard tablica(10,100,50); //rzeczywista generacja planszy
	minesweeperBoard tablica;
	tablica.debugDisplay();
	return 0;
}
