#ifndef __DECK_HXX__
#define __DECK_HXX__

#include <vector>
#include <string>

class Card;

class Deck 
{
public: 
	Deck();
	Deck(std::string& path, int max);
	~Deck();

	const Card* drawNext();
	const int getCardNb() const {return _deckCards.size();}

	void printInfo() const;
	void print() const;

private:
	void init();
	std::vector<Card*> initCardsFromXml();
	void randomizeCards();

	std::string _xmlPath;
	int _max;
	std::vector<Card*> _deckCards;
};

#endif