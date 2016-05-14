#ifndef __CREATURE_CARD_HXX__
#define __CREATURE_CARD_HXX__

#include <model/card.hxx>

class Creature : public Card
{
public:
	Creature();
	Creature(std::string& name, int cost);
	Creature(Creature const& o);
	~Creature();

	void print() const;

private:
	int _dev;
	int _test;
};

#endif