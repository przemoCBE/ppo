#include "minesweepertextcontroller.hpp"
#include <sstream>
#include <iostream>

void minesweeperTextController::play(){
	std::string input,output="";
	while(!this->exit){
		std::cout << "\033[2J\033[1;1H";
		this->display->display();
		std::cout << output << std::endl << "command:";
		if (this->board->getGameState()==gameState::FINISHED_LOSS){
			std::cout << "\nyou lose!";
			return;
		}
		if (this->board->getGameState()==gameState::FINISHED_WIN){
			std::cout << "\nyou win!";
			return;
		}
		std::getline(std::cin,input);
		output = this->parse(input);
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
	input >> command;
	unsigned int pos[2];
	std::string argument;
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
			for (unsigned int i=0;i<2;i++){
				input >> argument;
				if (argument.length()==0){
					return "command requires more (2) arguments!";
				}
				try{
					pos[i]=std::stoul(argument);
				}
				catch(std::invalid_argument &arg){
					return "invalid argument(s), number expected!";
				}
			}
			//discard any whitespaces
			input >> std::ws;
			//check if stream is empty
			if(!input.eof()){
				return "command requires less (2) arguments!";
			}
			this->posCommands(command,pos[0],pos[1]);
			return "";
		default:
			return "invalid command\n"
			       "type h for help";
		}
}
