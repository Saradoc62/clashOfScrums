#ifndef __BOARD_HXX__
#define __BOARD_HXX__

#include <vector>

#include <model/card.hxx>

class Board 
{
public: 
	Board();
	Board(std::vector<Card*> cards);
	virtual ~Board();

	virtual void addCard(Card* card);
	virtual Card* getCard(const int index);
	virtual Card* getCardType(CardType type, const int index);
	virtual std::vector<Card*> getCards();
	virtual void applyEffects() const;
	void update();

	virtual unsigned int getCardNb() const;
	virtual int getCardTypeNb(CardType type) const;

	virtual void printInfo() const;
	virtual void print() const;
    virtual void printCardType(CardType type) const;

protected:
	std::vector<Card*> _cards;

};

class Hand : public Board
{
public:
	Hand();
	Hand(std::vector<Card*> cards);
	virtual ~Hand();

	virtual void addCard(Card* card);
	virtual Card* getCard(const int index);

	virtual void printInfo() const;
	void printWithCost() const;

};

#endif