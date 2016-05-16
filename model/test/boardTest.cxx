#define BOOST_TEST_MODULE BoardTest
#include <boost/test/unit_test.hpp>

#include <model/creature.hxx>
#include <model/spell.hxx>
#include <model/board.hxx>


BOOST_AUTO_TEST_CASE(checkBoardEffects)
{
	CardAttribute atCreature1, atCreature2, atSpell;

	//Create creature 1
	atCreature1.name = "creature1";
	atCreature1.cost = 100;
	Card* creature1 = new class Creature(atCreature1);

	//Create creature 2
	Effect effect1;
	effect1.type = Buff;
	effect1.devImpact = 2;
	atCreature2.name = "creature2";
	atCreature2.effect = effect1;
	Card* creature2 = new class Creature(atCreature2);	

	//Create Spell
	Effect effect2;
	effect2.type = CostDecrease;
	effect2.costImpact = 50;
	atSpell.name = "spell";
	atSpell.effect = effect2;
	Card* spell = new class Spell(atSpell);

	//Create Board
	std::vector<Card*> cards;
	cards.push_back(creature1);
	cards.push_back(creature2);
	cards.push_back(spell);
	Board board(cards);

	//Check state
	BOOST_CHECK_EQUAL(creature1->getCost(), 100);
	BOOST_CHECK_EQUAL(dynamic_cast<class Creature*>(creature1)->getDev(), 0);
	BOOST_CHECK_EQUAL(dynamic_cast<class Creature*>(creature2)->getDev(), 0);

	//Apply effects
	board.applyEffects();

	//Check state
	BOOST_CHECK_EQUAL(creature1->getCost(), 50);
	BOOST_CHECK_EQUAL(dynamic_cast<class Creature*>(creature1)->getDev(), 2);
	BOOST_CHECK_EQUAL(dynamic_cast<class Creature*>(creature2)->getDev(), 2);
}
