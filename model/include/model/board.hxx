#ifndef __BOARD_HXX__
#define __BOARD_HXX__

#include <vector>

#include <model/card.hxx>

class Board 
{
public: 
	Board();
	Board(std::vector<Card*> cards);
	~Board();
	void applyEffects() const;

private:
	std::vector<Card*> _cards;
};

#endif