#define BOOST_TEST_MODULE DeckTest
#include <boost/test/unit_test.hpp>

#include <model/deck.hxx>

BOOST_AUTO_TEST_CASE(CheckDeckSize)
{
	std::string xmlPath = "/Users/Cyril/dev/clashOfScrums/config/cards.xml";
	const int deckSize = 10;
	
	Deck deck(xmlPath, deckSize);

	int i = 0;
	while(deck.getCardNb() > 0)
	{
		BOOST_CHECK_EQUAL(deck.getCardNb(), deckSize - i);
    	deck.drawNext();
    	++i;
	}
}
