#include <iostream>
#include <model/card.hxx>

Card::Card() : 
_cost(0),
_name("")
{

}

Card::Card(CardAttribute a) : 
_cost(a.cost),
_name(a.name)
{

}

Card::Card(std::string& name, int cost) : 
_cost(cost),
_name(name)
{

}

Card::Card(Card const& o) :
_cost(o._cost),
_name(o._name)
{

}

Card::~Card()
{
	
}

void Card::print() const
{
	std::cout << "Name : " << _name << std::endl;
	std::cout << "Cost : " << _cost << std::endl;
}