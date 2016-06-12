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

Deck::Deck(std::vector<Card*> cards) :
_xmlPath(""), 
_max(cards.size()),
_deckCards(cards)
{

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
		        	const pt::ptree card = c.second;
		        	CardAttribute attribute;
		        	CardType cardType = factory.getCardType(card.get<std::string>("type"));
		        	attribute.cardType = cardType;

		           	attribute.name = card.get<std::string>("name");
		           	attribute.cost = card.get<int>("cost");
		           	attribute.frame = factory.getPNGPath() + card.get<std::string>("frame");

		           	if(cardType == Creature)
		           	{
		           		attribute.dev = card.get<int>("dev");
		           		attribute.test = card.get<int>("test");
		           	}
		           	else if (cardType == Feature)
		           	{
		           		attribute.income = card.get<int>("income");
		           		attribute.benefits = card.get<int>("benefits");
		           		attribute.devRequired = card.get<int>("devRequired");
		           		attribute.testRequired = card.get<int>("testRequired");
		           		attribute.deadline = card.get<int>("deadline");
		           	}
		        
		           	const pt::ptree& effect = card.get_child("Effect");
		           	EffectType effectType = factory.getEffectType(effect.get<std::string>("<xmlattr>.type"));
		           	attribute.effect.type = effectType;

		           	if(effectType != NoEffect)
		           	{	
		           		attribute.effect.occur = factory.getOccurence(effect.get<std::string>("<xmlattr>.occur"));
		           		attribute.effect.devImpact = effect.get<int>("devImpact");
		           		attribute.effect.testImpact = effect.get<int>("testImpact");
		           		attribute.effect.costImpact = effect.get<int>("costImpact");
		           		attribute.effect.duration = effect.get<int>("duration");
		            }
		            cards.push_back(factory.makeCard(attribute));
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

		Card* card = cards[dist(engine)];

		//Duplicate cards
		if(card->getType().find("Feature") != std::string::npos)
			_deckCards[i] = new class Feature(*dynamic_cast<class Feature*>(card));
		else if(card->getType().find("Creature") != std::string::npos)
			_deckCards[i] = new class Creature(*dynamic_cast<class Creature*>(card));
		else if(card->getType().find("Spell") != std::string::npos)
			_deckCards[i] = new class Spell(*dynamic_cast<class Spell*>(card));
	}
}

Card* Deck::drawNext()
{
	Card* card = NULL;
	if(_deckCards.size() > 0)
	{
		card = _deckCards[0];
		_deckCards.erase(_deckCards.begin());
	}
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
