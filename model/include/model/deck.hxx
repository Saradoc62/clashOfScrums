#ifndef __DECK_HXX__
#define __DECK_HXX__

#include <vector>
#include <string>

#include <model/card.hxx>

class Deck 
{
public: 
	Deck();
	Deck(std::string& path, int max);
	Deck(std::vector<Card*> cards);
	~Deck();

	Card* drawNext();
	const int getCardNb() const {return _deckCards.size();}

	void setVerbose(const bool mode) {_verbose = mode;}

	void printInfo() const;
	void print() const;

private:
	void init();
	std::vector<Card*> initCardsFromXml();
	void randomizeCards();

	std::string _xmlPath;
	int _max;
	bool _verbose;
	std::vector<Card*> _deckCards;
};

#endif