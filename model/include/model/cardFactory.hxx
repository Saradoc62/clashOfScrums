#ifndef __CARD_FACTORY_HXX__
#define __CARD_FACTORY_HXX__

#include <model/creature.hxx>
#include <model/spell.hxx>

enum CardType {
	None,
	Feature,
	Creature,
	Spell
};

class CardFactory
{
public:
	Card* makeCard(CardType type, std::string& name, int cost)
	{
		switch(type)
		{
			//case Feature:
				//return new Feature();
			case Creature:
				return new class Creature(name, cost);
			case Spell:
				return new class Spell(name, cost);
			default:
				return new class Card(name, cost);
		}
	}

	CardType getType(std::string type)
	{
		//if(type == "Feature")
			//return Feature;
		if (type == "Creature")
			return Creature;
		else if (type == "Spell")
			return Spell;
		else
			return None;
	}
	
};

#endif
