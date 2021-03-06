#ifndef __CARD_CONFIG_HXX__
#define __CARD_CONFIG_HXX__

#include <string>
#include <iostream>

enum CardType {
	NoneType,
	FeatureType,
	CreatureType,
	SpellType
};

enum EffectType {
	NoEffect,
	CostDecrease,
	Buff
};

enum Occurence {
	Once,
	EachTurn,
	Unknown
};

namespace {
	std::string toString(CardType type)
	{
		switch(type)
		{
			case FeatureType:
				return "Feature";
			case CreatureType:
				return "Creature";
			case SpellType:
				return "Spell";
			default:
				return "None";		
		}
	}

	std::string toString(EffectType type)
	{
		switch(type)
		{
			case NoEffect:
				return "NoEffect";
			case CostDecrease:
				return "CostDecrease";
			case Buff:
				return "Buff";
			default:
				return "None";		
		}
	}

	std::string toString(Occurence occur)
	{
		switch(occur)
		{
			case Once:
				return "Once";
			case EachTurn:
				return "EachTurn";	
			case Unknown:
				return "Unknown";
		}
	}
}

struct Effect {
	EffectType type;
	Occurence occur;
	bool alreadyApplied;
	int costImpact;
	int devImpact;
	int testImpact;
	int duration;

	Effect()
	{
		type = NoEffect;
		occur = Unknown;
		alreadyApplied = false;
		costImpact = 0;
		devImpact = 0;
		testImpact = 0;
		duration = 0;
	}

	void print() const
	{
		std::cout << "EffectType    : " << toString(type) << std::endl;
		if(type != NoEffect)
		{
			std::cout << "Occurence     : " << toString(occur)  << std::endl;
			std::cout << "costImpact    : " << costImpact 		<< std::endl;
			std::cout << "DevImpact     : " << devImpact 		<< std::endl;
			std::cout << "TestImpact    : " << testImpact 		<< std::endl;
			std::cout << "Duration      : " << duration 		<< std::endl;
		}
	}
};

struct CardAttribute {
	CardType cardType;
	std::string name;
	std::string frame;
	int cost;
	int dev;
	int test;
	int income;
    int benefits;
    int devRequired;
	int testRequired;
	int deadline;
	Effect effect;

	CardAttribute()
	{
		cardType = NoneType;
		name = "";
		frame = "";
		cost = 0;
		dev = 0;
		test = 0;
		income = 0;
		benefits = 0;
		devRequired = 0;
		testRequired = 0;
		deadline = 0;
		effect = Effect();
	}
};

#endif
