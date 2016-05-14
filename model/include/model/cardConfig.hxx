#include <string>

enum CardType {
	None,
	Feature,
	Creature,
	Spell
};

enum Effect {
	NoEffect
};

struct CardAttribute {
	std::string name;
	int cost;
	int dev;
	int test;
	Effect effect;
};