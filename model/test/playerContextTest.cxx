#define BOOST_TEST_MODULE PlayerContextTest
#include <boost/test/unit_test.hpp>

#include <configuration.h>
#include <model/playerContext.hxx>

BOOST_AUTO_TEST_CASE(PlayerDrawAndPlayCardMechanism)
{
	//Create Deck
	std::string xmlPath = std::string(RESOURCES_PATH) + "cards.xml";
	const int deckSize = 10;
	Deck deck(xmlPath, deckSize);

	//Create context
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
	//whereas player's board increases correctly until hand is empty
	int j = 0;
	while(aCtxt.getHandCardNb() > 0)
	{
		aCtxt.playCard(0); //Play top card
		BOOST_CHECK_EQUAL(aCtxt.getHandCardNb(), --i);
		BOOST_CHECK_EQUAL(aCtxt.getBoardCardNb(), ++j);
	}
}
