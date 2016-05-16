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

void Board::applyEffects() const
{	
	BOOST_FOREACH( Card* const& c, _cards )
	{
		c->applyEffectToBoard(_cards);
	}
}