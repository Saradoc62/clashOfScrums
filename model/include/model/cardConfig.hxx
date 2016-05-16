#ifndef __CARD_CONFIG_HXX__
#define __CARD_CONFIG_HXX__

#include <string>
#include <iostream>

enum CardType {
	None,
	Feature,
	Creature,
	Spell
};

enum EffectType {
	NoEffect,
	CostDecrease,
	Buff
};

namespace {
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
				return "None";		}
	}
}

struct Effect {
	EffectType type;
	int costImpact;
	int devImpact;
	int testImpact;
	int duration;

	Effect()
	{
		type = NoEffect;
		devImpact = 0;
		testImpact = 0;
		duration = 0;
	}

	void print() const
	{
		std::cout << "EffectType    : " << toString(type) << std::endl;
		if(type != NoEffect)
		{
			std::cout << "costImpact    : " << costImpact << std::endl;
			std::cout << "DevImpact     : " << devImpact << std::endl;
			std::cout << "TestImpact    : " << testImpact << std::endl;
			std::cout << "Duration      : " << duration << std::endl;
		}
	}
};

struct CardAttribute {
	CardType cardType;
	std::string name;
	int cost;
	int dev;
	int test;
	Effect effect;

	CardAttribute()
	{
		name = "";
		cost = 0;
		dev = 0;
		test = 0;
		effect = Effect();
	}
};

#endif
