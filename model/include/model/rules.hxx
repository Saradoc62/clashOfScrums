#ifndef __RULES_HXX__
#define __RULES_HXX__

#include <string>

class Rules
{
public:
	Rules();
	Rules(std::string const& xmlPath);
	Rules(Rules const& o);
	~Rules();

	const int getDeckSize() const {return _deckSize;}
	const int getMaxNbOfCardsToDrawPerTurn() const {return _maxNbOfCardsToDrawPerTurn;}

private:
	void init();

	std::string _xmlPath;
	int _numberOfDecks;
	int _deckSize;
	int _maxNbOfCardsToDrawPerTurn;

};

#endif