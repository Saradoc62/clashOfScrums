#define BOOST_TEST_MODULE BoardTest
#include <boost/test/unit_test.hpp>

#include <model/creature.hxx>
#include <model/spell.hxx>
#include <model/board.hxx>


BOOST_AUTO_TEST_CASE(checkBoardEffects)
{
	CardAttribute atCreature, atSpell;
	atCreature.name = "creature";
	atCreature.cost = 100;

	Effect effect;
	effect.type = CostDecrease;
	effect.costImpact = 50;

	atSpell.name = "spell";
	atSpell.effect = effect;

	Card* creature = new class Creature(atCreature);	
	Card* spell = new class Spell(atSpell);

	std::vector<Card*> cards;
	cards.push_back(creature);
	cards.push_back(spell);

	Board board(cards);

	BOOST_CHECK_EQUAL(creature->getCost(), 100);

	board.applyEffects();

	BOOST_CHECK_EQUAL(creature->getCost(), 50);

}
