#ifndef __SPELL_CARD_HXX__
#define __SPELL_CARD_HXX__

#include <model/card.hxx>

class Spell : public Card
{
public:
	Spell();
	Spell(std::string& name, int cost);
	Spell(Spell const& o);
	~Spell();

	void print() const;
};

#endif