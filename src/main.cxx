#include <iostream>
#include <string>

#include <boost/foreach.hpp>

#include "configuration.h"
#include <model/deck.hxx>
#include <model/creature.hxx>

int main(int argc, char* argv[])
{
	std::string xmlPath = std::string(RESOURCES_PATH) + "cards.xml";
	const int deckSize = 10;

	Deck deck(xmlPath, deckSize);
	deck.printInfo();

	while(deck.getCardNb() > 0)
	{
		const Card* A = deck.drawNext();
		A->print();
		deck.printInfo();
	}
	
	return 0;
}
