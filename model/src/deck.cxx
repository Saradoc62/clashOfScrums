#include <iostream>
#include <random>
#include <sstream>

#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <model/cardFactory.hxx>
#include <model/deck.hxx>

Deck::Deck() : 
_xmlPath(""),
_max(0)
{

}

Deck::Deck(std::string& path, int max) :
_xmlPath(path), 
_max(max)
{
	std::cout << "Building deck from XML path : " << _xmlPath << "\n" << std::endl; 
	init();
}

Deck::~Deck()
{

}

void Deck::init()
{
	_deckCards.resize(_max);
	randomizeCards();
}

std::vector<Card*> Deck::initCardsFromXml()
{
	namespace fs = boost::filesystem;
	namespace pt = boost::property_tree;

	std::vector<Card*> cards;
	if ( !fs::exists(_xmlPath) )
	{
  		std::cout << "Can't find cards xml !" << std::endl;
	}
	else
	{
		try
		{
			//Read XML
		    pt::ptree tree;
		    pt::read_xml(_xmlPath, tree);

		    //Build Card vector
		    CardFactory factory;

		    BOOST_FOREACH( pt::ptree::value_type const& c, tree.get_child("cards") ) 
		    {
		        if( c.first == "card" ) 
		        {
		        	CardAttribute attribute;
		            CardType type = factory.getType(c.second.get<std::string>("type"));

		           	attribute.name = c.second.get<std::string>("name");
		           	attribute.cost = c.second.get<int>("cost");
		            cards.push_back(factory.makeCard(type, attribute));
		        }
		    }
		}
		catch(std::exception &ex)
		{
			std::cout << "Exception : " << ex.what() << std::endl;	
		}
	}
	return cards;
}

void Deck::randomizeCards()
{
	std::vector<Card*> cards = initCardsFromXml();

	for(unsigned int i = 0; i < _deckCards.size(); ++i)
	{
		std::random_device random_device;
		std::mt19937 engine(random_device());
		std::uniform_int_distribution<int> dist(0, cards.size() - 1);
	
		_deckCards[i] = cards[dist(engine)];
	}
}

const Card* Deck::drawNext()
{ 
	std::cout << "==> Draw Card : " << std::endl;
	Card* card = _deckCards[0];
	_deckCards.erase(_deckCards.begin());
	return card;
}

void Deck::printInfo() const
{
	std::cout << "* PRINT DECK *" << std::endl;
	std::cout << "Number of cards : " << _deckCards.size() << "/" << _max << "\n" << std::endl;
}

void Deck::print() const
{
	printInfo();

	BOOST_FOREACH( Card* const& c, _deckCards ) 
	{
		c->print();
	}
}
