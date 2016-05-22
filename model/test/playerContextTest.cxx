#define BOOST_TEST_MODULE PlayerContextTest
#include <boost/test/unit_test.hpp>

#include <configuration.h>
#include <model/playerContext.hxx>
#include <model/creature.hxx>
#include <model/spell.hxx>

BOOST_AUTO_TEST_CASE(PlayerDrawAndPlayCardMechanismConsistency)
{
	std::vector<Card*> cards;
	const int nbOfCreatures = 10;
	const int nbOfSpells = 5;

	//Create fake cards
	for(unsigned int i = 0; i < nbOfCreatures; ++i)
	{
		Card* creature = new class Creature();
		cards.push_back(creature);
	}
	for(unsigned int i = 0; i < nbOfSpells; ++i)
	{
		Card* spell = new class Spell();
		cards.push_back(spell);
	}

	//Create deck and context
	Deck deck(cards);
	PlayerContext aCtxt(&deck);

	//Successively draw card and check that player's hand increases correctly 
	//until deck is empty
	int i = 0;
	while(deck.getCardNb() > 0)
	{
		aCtxt.drawCard();
		BOOST_CHECK_EQUAL(aCtxt.getHandCardNb(), ++i);
	}

	//Successively play card and check that player's hand decreases correctly 
	//until hand is empty
	while(aCtxt.getHandCardNb() > 0)
	{
		aCtxt.playCard(0); //Play top card
		BOOST_CHECK_EQUAL(aCtxt.getHandCardNb(), --i);
	}

	//Check that board contains only creature cards 
	//Spell should not be added to board
	const int expectedBoardSize = nbOfCreatures;
	BOOST_CHECK_EQUAL(aCtxt.getBoardCardNb(), expectedBoardSize);
}
