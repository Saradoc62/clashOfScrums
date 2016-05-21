#include <boost/foreach.hpp>
#include <model/board.hxx>

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

void Board::addCard(const Card* card)
{
	_cards.push_back(const_cast<Card*>(card));
}

const Card* Board::getCard(const int index)
{
	const Card* card = _cards[index];
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

void Board::printInfo() const
{
	std::cout << "* PRINT BOARD *" << std::endl;
	std::cout << "Number of cards : " << _cards.size() << std::endl;
}

unsigned int Board::getCardNb() const
{
	return _cards.size();
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

void Hand::printInfo() const
{
	std::cout << "* PRINT HAND *" << std::endl;
	std::cout << "Number of cards : " << _cards.size() << std::endl;
}