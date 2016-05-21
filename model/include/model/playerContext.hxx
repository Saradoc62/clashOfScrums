#ifndef __PLAYER_CONTEXT_HXX__
#define __PLAYER_CONTEXT_HXX__

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
	unsigned int getDeckCardNb() const;

	void printInfo() const;
	void printHand() const;
	void printBoard() const;

private:
	Deck*  _deck;
	Board* _board;
	Hand*  _hand;
};

#endif