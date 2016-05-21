#ifndef __ACTIONS_HXX__
#define __ACTIONS_HXX__

#include <iostream>

enum Actions 
{
	drawCard = 1,
	playCard = 2,
	stopGame = 3
};

void printActions()
{
	std::cout << "* ACTIONS *" << std::endl;
	std::cout << "1 : Draw Card" << std::endl;
	std::cout << "2 : Play Card" << std::endl;
	std::cout << "3 : End Game \n" << std::endl;
}

#endif
