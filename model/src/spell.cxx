#include <iostream>
#include <model/spell.hxx>

Spell::Spell() :
Card()
{

}

Spell::Spell(CardAttribute a) :
Card(a.name, a.cost)
{

}

Spell::Spell(std::string& name, int cost) : 
Card(name, cost)
{

}

Spell::Spell(Spell const& o) : 
Card(o)
{

}

Spell::~Spell()
{
	
}

void Spell::print() const
{
	std::cout << "Type : Spell" << std::endl;
	Card::print();
	std::cout << std::endl;
}