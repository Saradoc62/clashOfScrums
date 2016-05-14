#include <iostream>
#include <string>

#include <boost/foreach.hpp>

#include <model/deck.hxx>
#include <model/creature.hxx>

int main(int argc, char* argv[])
{
	std::string xmlPath = "/Users/Cyril/dev/clashOfScrums/config/cards.xml";
	const int deckSize = 10;
	
	Deck deck(xmlPath, deckSize);
	deck.printInfo();

	while(deck.getCardNb() > 0)
	{
		const Card* A = deck.drawNext();
		A->print();
		deck.printInfo();
	}

	// std::string toto("toto");
	// Creature A(toto, 100);
	// A.print();

	// Creature B(A);
	// B.print();

	// Creature C = B;
	// C.print();

	return 0;
}
