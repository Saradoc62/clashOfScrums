#include <boost/foreach.hpp>
#include <model/board.hxx>

#include <iostream>

Board::Board()
{

}

Board::Board(std::vector<Card*> cards) :
_cards(cards)
{

}

Board::~Board()
{

}

void Board::addCard(Card* card)
{
	//Spell cards are not added to board
	if(card->getType().find("Spell") == std::string::npos) 
	{
		_cards.push_back(card);
		applyEffects();
	}
	else
	{
		//But its effect are still applied
		card->applyEffectToBoard(_cards);
	}
}

Card* Board::getCard(const int index)
{
	Card* card = _cards[index];
	_cards.erase(_cards.begin() + index);
	return card;
}

void Board::applyEffects() const
{	
	BOOST_FOREACH( Card* const& c, _cards )
	{
		c->applyEffectToBoard(_cards);
	}
}

unsigned int Board::getCardNb() const
{
	return _cards.size();
}

void Board::printInfo() const
{
	std::cout << "* PRINT BOARD *" << std::endl;
	std::cout << "Number of cards : " << _cards.size() << "\n" << std::endl;
}

void Board::print() const
{
	printInfo();

	int i = 0;
	BOOST_FOREACH(Card* const& c, _cards)
	{
		std::cout << ++i << " : " << c->getName() << std::endl;
	}
	std::cout << std::endl;
}

// ---------------------------------------------------------------- //

Hand::Hand() :
Board()
{

}

Hand::Hand(std::vector<Card*> cards) :
Board(cards)
{

}

Hand::~Hand()
{

}

void Hand::addCard(Card* card)
{
	_cards.push_back(card);
}

void Hand::printInfo() const
{
	std::cout << "* PRINT HAND *" << std::endl;
	std::cout << "Number of cards : " << _cards.size() << "\n" << std::endl;
}