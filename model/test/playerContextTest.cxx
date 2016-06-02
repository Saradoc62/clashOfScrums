#define BOOST_TEST_MODULE PlayerContextTest
#include <boost/test/unit_test.hpp>

#include <configuration.h>
#include <model/playerContext.hxx>
#include <model/creature.hxx>
#include <model/spell.hxx>
#include <model/feature.hxx>

BOOST_AUTO_TEST_CASE(PlayerDrawAndPlayCardMechanism)
{
	std::vector<Card*> cards;
	const int nbOfCreatures = 10;
	const int nbOfFeatures = 3;
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
	for(unsigned int i = 0; i < nbOfFeatures; ++i)
	{
		Card* feature = new class Feature();
		cards.push_back(feature);
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

	//Check that board contains only Creature and Feature cards 
	//Spell should not be added to board
	const int expectedBoardSize = nbOfCreatures + nbOfFeatures;
	BOOST_CHECK_EQUAL(aCtxt.getBoardCardNb(), expectedBoardSize);
}


BOOST_AUTO_TEST_CASE(PlayerMoney)
{
	std::vector<Card*> cards;
	CardAttribute at, atCreat;

	//Create Feature
	at.name = "Feature1";
	at.cost = 0;
	at.income = 2000;
	at.deadline = 2; // 2 turns
	at.devRequired = 10;
	at.testRequired = 10;
	Card* feature1 = new class Feature(at);
	cards.push_back(feature1);

	//Create Creature
	atCreat.name = "Creature1";
	atCreat.cost = 1000;
	atCreat.dev = 2;
	atCreat.test = 2;
	Card* creature1 = new class Creature(atCreat);
	cards.push_back(creature1);

	//Create deck and context
	Deck deck(cards);
	PlayerContext aCtxt(&deck);

	//Simulate 4 turns

	aCtxt.prepare();

	//Check that player money is 0 to begin with
	BOOST_CHECK_EQUAL(aCtxt.getMoney(), 0);

	//Draw and play feature1 (will bring income for 2 turns and die)
	aCtxt.drawCard();
	aCtxt.playCard(0); //feature1 (top card)

	//Turn 1 : Check that player money is 2000 (income from feature1)
	BOOST_CHECK_EQUAL(aCtxt.getMoney(), 2000);
	aCtxt.update();

	//Turn 2 : Check that player money is 4000 (income from feature1)
	aCtxt.prepare();
	BOOST_CHECK_EQUAL(aCtxt.getMoney(), 4000);
	aCtxt.update();

	//Turn 3 : Check that player money is still 4000 (no income, feature 1 is dead)
	aCtxt.prepare();
	BOOST_CHECK_EQUAL(aCtxt.getMoney(), 4000);
	aCtxt.update();

	//Turn 4 : Play creature and checks that player money is 3000
	aCtxt.prepare();
	aCtxt.drawCard();
	aCtxt.playCard(0); //creature1 (top card)
	BOOST_CHECK_EQUAL(aCtxt.getMoney(), 3000);
	aCtxt.update();
}

BOOST_AUTO_TEST_CASE(PlayerFeatureCompletion)
{
	std::vector<Card*> cards;
	CardAttribute atFeat, atCreat;

	//Create Feature
	atFeat.name = "Feature1";
	atFeat.cost = 0;
	atFeat.income = 5000;
	atFeat.deadline = 4; // 4 turns
	atFeat.devRequired = 7;
	atFeat.testRequired = 5;
	Card* feature1 = new class Feature(atFeat);
	cards.push_back(feature1);

	//Create Creature
	atCreat.name = "Creature1";
	atCreat.cost = 1000;
	atCreat.dev = 2;
	atCreat.test = 2;
	Card* creature1 = new class Creature(atCreat);
	cards.push_back(creature1);

	//Create deck and context
	Deck deck(cards);
	PlayerContext aCtxt(&deck);

	aCtxt.prepare();

	//Draw and play feature1 (top card)
	aCtxt.drawCard();
	aCtxt.playCard(0);

	//Draw and play creature1 (top card)
	aCtxt.drawCard();
	aCtxt.playCard(0);

	//Initial check
	class Feature* feat = dynamic_cast<class Feature*>(feature1);

	BOOST_CHECK_EQUAL(aCtxt.getMoney(), 4000);
	BOOST_CHECK_EQUAL(feat->getRequiredDev(), 7);
	BOOST_CHECK_EQUAL(feat->getRequiredTest(), 5);
	BOOST_CHECK_EQUAL(feat->getDeadline(), 4);
	BOOST_CHECK_EQUAL(feat->isCompleted(), false);

	//Check board Card number
	BOOST_CHECK_EQUAL(aCtxt.getBoardCardNb(), 2); //one feature and one creature

	//Start making feature
	int featIdx = 1; //first feature
	int creatIdx = 1; //first creature

	aCtxt.makeFeature(featIdx, creatIdx); 
	BOOST_CHECK_EQUAL(feat->getRequiredDev(), 5);
	BOOST_CHECK_EQUAL(feat->getRequiredTest(), 3);
	BOOST_CHECK_EQUAL(feat->getDeadline(), 4);
	BOOST_CHECK_EQUAL(feat->isCompleted(), false);

	aCtxt.makeFeature(featIdx, creatIdx);
	BOOST_CHECK_EQUAL(feat->getRequiredDev(), 3);
	BOOST_CHECK_EQUAL(feat->getRequiredTest(), 1); 
	BOOST_CHECK_EQUAL(feat->getDeadline(), 4); //deadline does not change within a turn
	BOOST_CHECK_EQUAL(feat->isCompleted(), false);

	//Simulate another turn
	aCtxt.update();

	aCtxt.makeFeature(featIdx, creatIdx);
	BOOST_CHECK_EQUAL(feat->getRequiredDev(), 1);
	BOOST_CHECK_EQUAL(feat->getRequiredTest(), 0); 
	BOOST_CHECK_EQUAL(feat->getDeadline(), 3); //deadline decreases
	BOOST_CHECK_EQUAL(feat->isCompleted(), false);

	aCtxt.makeFeature(featIdx, creatIdx);
	BOOST_CHECK_EQUAL(feat->getRequiredDev(), 0);
	BOOST_CHECK_EQUAL(feat->getRequiredTest(), 0); 
	BOOST_CHECK_EQUAL(feat->getDeadline(), 3); //deadline does not change within a turn
	BOOST_CHECK_EQUAL(feat->isCompleted(), true);

	//Check board Card number
	BOOST_CHECK_EQUAL(aCtxt.getBoardCardNb(), 2); //Feature is not removed from board

	//Simulate extra turns
	aCtxt.update();
	aCtxt.update();
	aCtxt.update();
	BOOST_CHECK_EQUAL(feat->getDeadline(), 0); //deadline is 0
	//Check board Card number
	BOOST_CHECK_EQUAL(aCtxt.getBoardCardNb(), 2); //Completed feature is not removed from board
}

BOOST_AUTO_TEST_CASE(PlayerFeatureDeadlineCheck)
{
	std::vector<Card*> cards;
	CardAttribute atFeat, atCreat;

	//Create Feature
	atFeat.name = "Feature1";
	atFeat.cost = 0;
	atFeat.income = 5000;
	atFeat.deadline = 1; // 4 turns
	atFeat.devRequired = 7;
	atFeat.testRequired = 5;
	Card* feature1 = new class Feature(atFeat);
	cards.push_back(feature1);

	//Create Creature
	atCreat.name = "Creature1";
	atCreat.cost = 1000;
	atCreat.dev = 2;
	atCreat.test = 2;
	Card* creature1 = new class Creature(atCreat);
	cards.push_back(creature1);

	//Create deck and context
	Deck deck(cards);
	PlayerContext aCtxt(&deck);

	aCtxt.prepare();

	//Draw and play feature1 (top card)
	aCtxt.drawCard();
	aCtxt.playCard(0);

	//Draw and play creature1 (top card)
	aCtxt.drawCard();
	aCtxt.playCard(0);

	//Initial check
	class Feature* feat = dynamic_cast<class Feature*>(feature1);

	BOOST_CHECK_EQUAL(aCtxt.getMoney(), 4000);
	BOOST_CHECK_EQUAL(feat->getRequiredDev(), 7);
	BOOST_CHECK_EQUAL(feat->getRequiredTest(), 5);
	BOOST_CHECK_EQUAL(feat->getDeadline(), 1);
	BOOST_CHECK_EQUAL(feat->isCompleted(), false);

	//Check board Card number
	BOOST_CHECK_EQUAL(aCtxt.getBoardCardNb(), 2); //one feature and one creature

	//Start making feature
	int featIdx = 1; //first feature
	int creatIdx = 1; //first creature

	aCtxt.makeFeature(featIdx, creatIdx); 
	BOOST_CHECK_EQUAL(feat->getRequiredDev(), 5);
	BOOST_CHECK_EQUAL(feat->getRequiredTest(), 3);
	BOOST_CHECK_EQUAL(feat->getDeadline(), 1);
	BOOST_CHECK_EQUAL(feat->isCompleted(), false);

	//Simulate another turn
	aCtxt.update();

	BOOST_CHECK_EQUAL(feat->getRequiredDev(), 5);
	BOOST_CHECK_EQUAL(feat->getRequiredTest(), 3);
	BOOST_CHECK_EQUAL(feat->getDeadline(), 0); // Deadline is reached
	BOOST_CHECK_EQUAL(feat->isCompleted(), false);

	//Check board Card number
	BOOST_CHECK_EQUAL(aCtxt.getBoardCardNb(), 1); //feature has been removed from board
}