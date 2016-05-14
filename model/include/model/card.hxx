#ifndef __BASE_CARD_HXX__
#define __BASE_CARD_HXX__

#include <model/cardConfig.hxx>
#include <string>

class Card 
{
public: 
	Card();
	Card(CardAttribute attribute);
	Card(std::string& name, int cost);
	Card(Card const& o);
	virtual ~Card();

	const int getCost() const {return _cost;}
	virtual void print() const;

private:
	int _cost;
	std::string _name;

};

#endif