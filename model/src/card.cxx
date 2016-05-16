#include <iostream>
#include <boost/foreach.hpp>

#include <model/card.hxx>

Card::Card() : 
_cost(0),
_name(""),
_effect(Effect())
{

}

Card::Card(CardAttribute a) : 
_cost(a.cost),
_name(a.name),
_effect(a.effect)
{

}

Card::Card(Card const& o) :
_cost(o._cost),
_name(o._name),
_effect(o._effect)
{

}

Card::~Card()
{
	
}

void Card::print() const
{
	std::cout << "Name : " << _name << std::endl;
	std::cout << "Cost : " << _cost << std::endl;
	_effect.print();
}

void Card::applyEffectToBoard(std::vector<Card*> const& cards)
{	
	BOOST_FOREACH(Card* const& c, cards)
	{
		c->acceptEffect(_effect);
	}
}

void Card::acceptEffect(Effect effect)
{
	switch(effect.type)
	{
		case NoEffect:
			break;
		case CostDecrease:
			_cost -= effect.costImpact;
			break;
		default:
			break;
	}
}