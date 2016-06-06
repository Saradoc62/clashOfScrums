#ifndef __PLAYER_CONTEXT_HXX__
#define __PLAYER_CONTEXT_HXX__

#include <model/deck.hxx>
#include <model/board.hxx>

enum Actions 
{
	drawCard = 1,
	playCard = 2,
	makeFeature = 3,
	endTurn  = 4,
	stopGame = 5
};

class PlayerContext
{
public:
	PlayerContext();
	~PlayerContext();

	//players methods
	void prepare();
	void update();
	void drawCard(Deck* deck);
	bool playCard(const int index);
	void makeFeature(int featureIdx, int creatureIdx);

	//getters
	int getMoney() const {return _money;}
	unsigned int getHandCardNb() const;
	unsigned int getBoardCardNb() const;
	int getBoardCardTypeNb(CardType type) const;
	const Hand* getHand() const {return _hand;}

	//print
	void printActions() const;
	void printInfo() const;
	void printHand() const;
	void printHandWithCost() const;
	void printBoard() const;
	void printBoardFeatures() const;
    void printBoardCreatures() const;

private:
	void updateMoney(Card* card);

	int    _money;

	Board* _board;
	Hand*  _hand;
};

#endif
