#ifndef __BASE_CARD_HXX__
#define __BASE_CARD_HXX__

#include <string>
#include <vector>

#include <model/cardConfig.hxx>

class Card 
{
public: 
	Card();
	Card(CardAttribute attribute);
	Card(Card const& o);
	virtual ~Card();

	const int getCost() const {return _cost;}
	const std::string getName() const {return _name;}

	virtual void applyEffectToBoard(std::vector<Card*> const& cards);
	virtual void acceptEffect(Effect effect);
	virtual void print() const;

protected:
	int _cost;
	std::string _name;
	Effect _effect;
};

#endif