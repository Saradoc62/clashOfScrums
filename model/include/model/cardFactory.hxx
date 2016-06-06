#ifndef __CARD_FACTORY_HXX__
#define __CARD_FACTORY_HXX__

#include <configuration.h>
#include <model/feature.hxx>
#include <model/creature.hxx>
#include <model/spell.hxx>

class CardFactory
{
public:
	CardFactory() : 
	_pngPath(std::string(RESOURCES_PATH) + "PNGs/")
	{
	}
	~CardFactory() {}

	Card* makeCard(CardAttribute attribute)
	{
		switch(attribute.cardType)
		{
			case Feature:
				return new class Feature(attribute);
			case Creature:
				return new class Creature(attribute);
			case Spell:
				return new class Spell(attribute);
			default:
				return new class Card(attribute);
		}
	}

	const std::string& getPNGPath()
	{
		return _pngPath;
	}

	CardType getCardType(std::string type)
	{
		if(type == "Feature")
			return Feature;
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

	Occurence getOccurence(std::string occur)
	{
		if(occur == "Once")
			return Once;
		else if(occur == "EachTurn")
			return EachTurn;
		else
			return Unknown;
	}	

private:
	std::string _pngPath;
};

#endif
