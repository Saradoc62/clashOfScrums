#ifndef __PLAYER_CONTEXT_HXX
#define __PLAYER_CONTEXT_HXX

#include <model/deck.hxx>
#include <model/board.hxx>

class PlayerContext
{
public:
	PlayerContext();
	PlayerContext(Deck* deck);
	~PlayerContext();
	void drawCard();
	void playCard(const int index);

	unsigned int getHandCardNb() const;
	unsigned int getBoardCardNb() const;
	void printInfo() const;

private:
	Deck*  _deck;
	Board* _board;
	Hand*  _hand;
};

#endif