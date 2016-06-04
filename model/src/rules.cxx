#include <iostream>

#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <model/rules.hxx>

Rules::Rules() :
_xmlPath(""),
_numberOfDecks(0),
_deckSize(0),
_maxNbOfCardsToDrawPerTurn(0)
{

}

Rules::Rules(std::string const& xmlPath) :
_xmlPath(xmlPath)
{
	std::cout << "Loading rules from XML path : " << _xmlPath << "\n" << std::endl;
	init();
}

Rules::Rules(Rules const& o) :
_xmlPath(o._xmlPath),
_numberOfDecks(o._numberOfDecks),
_deckSize(o._deckSize),
_maxNbOfCardsToDrawPerTurn(o._maxNbOfCardsToDrawPerTurn)
{

}

Rules::~Rules()
{
	
}

void Rules::init()
{
	namespace fs = boost::filesystem;
	namespace pt = boost::property_tree;

	if ( !fs::exists(_xmlPath) )
	{
  		std::cout << "Can't find rules xml !" << std::endl;
	}
	else
	{
		try
		{
			//Read XML
		    pt::ptree tree;
		    pt::read_xml(_xmlPath, tree);

		    _numberOfDecks 				= tree.get<int>("rules.numberOfDecks");
		    _deckSize					= tree.get<int>("rules.deckSize");
		    _maxNbOfCardsToDrawPerTurn 	= tree.get<int>("rules.maxNbOfCardsToDrawPerTurn");
		}
		catch(std::exception &ex)
		{
			std::cout << "Exception : " << ex.what() << std::endl;	
		}
	}
}