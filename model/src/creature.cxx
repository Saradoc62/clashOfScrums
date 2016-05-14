#include <iostream>
#include <model/creature.hxx>

Creature::Creature() :
Card()
{

}

Creature::Creature(CardAttribute a) :
Card(a.name, a.cost),
_dev(a.dev),
_test(a.test)
{

}

Creature::Creature(std::string& name, int cost) : 
Card(name, cost), 
_dev(0), 
_test(0)
{

}

Creature::Creature(Creature const& o) :
Card(o),
_dev(o._dev),
_test(o._test)
{

}

Creature::~Creature()
{
	
}

void Creature::print() const
{
	std::cout << "Type : Creature" << std::endl;
	Card::print();
	std::cout << "Dev  : " << _dev << std::endl;
	std::cout << "Test : " << _test << "\n" << std::endl;
}