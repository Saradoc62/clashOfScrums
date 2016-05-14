#include <iostream>
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