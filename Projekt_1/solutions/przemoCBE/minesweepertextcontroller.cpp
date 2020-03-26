#ifndef __MINESWEEPER_TEXT_CONTROLLER_CPP__
#define __MINESWEEPER_TEXT_CONTROLLER_CPP__

#include "minesweepertextcontroller.hpp"
#include <sstream>
#include <iostream>

void minesweeperTextController::play(){
	std::string input,output="";
	while(!this->exit){
		this->display->display();
		std::cout << output << std::endl << "command:";
		std::getline(std::cin,input);
		output = this->parse(input);
		std::cout << "\033[2J\033[1;1H";
	}
}

void minesweeperTextController::posCommands(char command,unsigned int posX,unsigned int posY){
	switch(command){
		case 'r':
			board->reveal(posX,posY);
			break;
		case 'f':
			board->toggleFlag(posX,posY);
			
	}
}

void minesweeperTextController::quit(){
	std::string choice;
	std::cout << "really quit?(y/N):";
	std::getline(std::cin,choice);
	if(choice=="Y"||choice=="y"){
		this->exit=true;
	}
}

std::string minesweeperTextController::parse(std::string inputStr){
	std::istringstream input(inputStr);
	//uses single character commands
	char command;
	unsigned int i=0;
	input >> command;
	unsigned int pos[2];
	switch (command){
		//no arguments
		case 'h':	//help
			return "---help---\n"
			       "r posX posY - reveal specified field\n"
			       "f posX posY - toggle flag on a specified field\n"
			       "q - quit\n"
			       "h - display this\n"
			       "----------";
		case 'q':	//quit
			this->quit();
			return"";
		//posX and posY as arguments
		case 'r':	//reveal
		case 'f':	//flag
			while(!input.eof()){
				if (i>=2){
					return "too many arguments";
				}
				std::string argument;
				input >> argument;
				try{
					pos[i]=std::stoul(argument);
					//will throw std::invalid_argument if string is not an integer
				}
				catch(std::invalid_argument &arg){
					return "invalid argument(s)!";
				}
				i++;
			}
			if (i<1){
				return "too few arguments";
			}
			std::cout << command << pos[1];
			this->posCommands(command,pos[0],pos[1]);
			return "";
		default:
			return "invalid command\n"
			       "type h for help";
		}
	return "TODO";
}

#endif
