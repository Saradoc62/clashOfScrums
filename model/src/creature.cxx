#include <iostream>

#include <model/cardConfig.hxx>
#include <model/creature.hxx>

Creature::Creature() :
Card()
{

}

Creature::Creature(CardAttribute a) :
Card(a),
_dev(a.dev),
_test(a.test)
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

void Creature::acceptEffect(Effect effect)
{
	switch(effect.type)
	{
		case NoEffect:
			break;
		case CostDecrease:
			_cost -= effect.costImpact;
			break;
		case Buff:
			_dev  += effect.devImpact;
			_test += effect.testImpact;
			break;
		default:
			break;
	}
}