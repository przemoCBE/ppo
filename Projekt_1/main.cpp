#include <iostream>
#include <time.h>
#include "minesweeperboard.hpp"

using namespace std;

int main(){
	srand(time(NULL));	//kryptograficznie niebezpieczny
//	minesweeperBoard tablica(10,40,200); //rzeczywista generacja planszy
	minesweeperBoard tablica;
	tablica.debugDisplay();
	return 0;
}
