#ifndef __BASE_CARD_HXX__
#define __BASE_CARD_HXX__

#include <string>

class Card 
{
public: 
	Card();
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