#include <iostream>
#include <boost/foreach.hpp>

#include <model/card.hxx>

Card::Card() : 
_cost(0),
_name(""),
_frame(""),
_effect(Effect())
{

}

Card::Card(CardAttribute a) : 
_cost(a.cost),
_name(a.name),
_frame(a.frame),
_effect(a.effect)
{

}

Card::Card(Card const& o) :
_cost(o._cost),
_name(o._name),
_frame(o._frame),
_effect(o._effect)
{

}

Card::~Card()
{
	
}

void Card::print() const
{
	std::cout << "Name    : " << _name 		<< std::endl;
	std::cout << "Cost    : " << _cost 		<< std::endl;
	std::cout << "Frame   : " << _frame 	<< std::endl;
	_effect.print();
}

void Card::applyEffectToBoard(std::vector<Card*> const& cards)
{	
	const bool hasEffect = _effect.type != NoEffect;
	const bool onceEffectNotAlreadyApplied = !(_effect.occur == Once && _effect.alreadyApplied);

	if(hasEffect && onceEffectNotAlreadyApplied)
	{
		BOOST_FOREACH(Card* const& c, cards) 
		{
			c->acceptEffect(_effect);
		}
		_effect.alreadyApplied = true;
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