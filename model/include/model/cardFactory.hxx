#ifndef __CARD_FACTORY_HXX__
#define __CARD_FACTORY_HXX__

#include <model/creature.hxx>
#include <model/spell.hxx>

class CardFactory
{
public:
	Card* makeCard(CardAttribute attribute)
	{
		switch(attribute.cardType)
		{
			//case Feature:
				//return new Feature();
			case Creature:
				return new class Creature(attribute);
			case Spell:
				return new class Spell(attribute);
			default:
				return new class Card(attribute);
		}
	}

	CardType getCardType(std::string type)
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

	EffectType getEffectType(std::string type)
	{
		if(type == "Buff")
			return Buff;
		else if(type == "CostDecrease")
			return CostDecrease;
		else
			return NoEffect;
	}	
};

#endif
