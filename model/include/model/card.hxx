#ifndef __BASE_CARD_HXX__
#define __BASE_CARD_HXX__

#include <model/cardConfig.hxx>
#include <string>

class Card 
{
public: 
	Card();
	Card(CardAttribute attribute);
	Card(Card const& o);
	virtual ~Card();

	const int getCost() const {return _cost;}
	const std::string getName() const {return _name;}
	virtual void print() const;

private:
	int _cost;
	std::string _name;
	Effect _effect;

};

#endif