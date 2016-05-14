#ifndef __BOARD_HXX__
#define __BOARD_HXX__

#include <vector>

class Card;

class Board 
{
public: 
	Board();
	~Board();

private:
	std::vector<Card*> _cards;
};

#endif