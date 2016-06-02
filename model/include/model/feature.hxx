#ifndef __FEATURE_CARD_HXX__
#define __FEATURE_CARD_HXX__

#include <model/card.hxx>
#include <model/creature.hxx>

class Feature : public Card
{
public:
	Feature();
	Feature(CardAttribute attribute);
	Feature(Feature const& o);
	~Feature();

	const int getIncome() const {return _income;}
	const int getDeadline() const {return _deadline;}
	const int getRequiredDev() const {return _devRequired;}
	const int getRequiredTest() const {return _testRequired;}

	void update();
	void acceptCreature(class Creature* creature);
	bool isCompleted() {return _devRequired == 0 && _testRequired == 0;}

	void print() const;

private:
	int _income;
	int _benefits;
	int _devRequired;
	int _testRequired;
	int _deadline;
};

#endif