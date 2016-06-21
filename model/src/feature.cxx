#include <iostream>

#include <model/cardConfig.hxx>
#include <model/feature.hxx>

Feature::Feature() :
Card(),
_income(0),
_benefits(0),
_devRequired(0),
_testRequired(0),
_deadline(0)
{

}

Feature::Feature(CardAttribute a) :
Card(a),
_income(a.income),
_benefits(a.benefits),
_devRequired(a.devRequired),
_testRequired(a.testRequired),
_deadline(a.deadline)
{

}

Feature::Feature(Feature const& o) :
Card(o),
_income(o._income),
_benefits(o._benefits),
_devRequired(o._devRequired),
_testRequired(o._testRequired),
_deadline(o._deadline)
{

}

Feature::~Feature()
{

}

void Feature::update()
{
	_deadline -= 1;
}

void Feature::acceptCreature(Creature* creature)
{
	if(_deadline > 0)
	{
		_devRequired -= creature->getDev();
		_testRequired -= creature->getTest();

		if(_devRequired <= 0)
			_devRequired = 0;
		if(_testRequired <= 0)
			_testRequired = 0;
	}
}

void Feature::print() const
{
	std::cout << "Type : Feature" << std::endl;
	Card::print();
	std::cout << "Income  : " 		<< _income 		 << std::endl;
	std::cout << "Benefits : " 		<< _benefits 	 << std::endl;
	std::cout << "DevRequired : " 	<< _devRequired  << std::endl;
	std::cout << "TestRequired : " 	<< _testRequired << std::endl;
	std::cout << "Deadline : " 		<< _deadline 	 << std::endl;	
}
