#include <model/playerContext.hxx>
#include <model/card.hxx>

PlayerContext::PlayerContext(Deck* deck)
{
	_deck  = deck;
	_board = new Board();
	_hand  = new Hand();
}

PlayerContext::~PlayerContext()
{

}

void PlayerContext::drawCard()
{
	_hand->addCard(_deck->drawNext());
}

void PlayerContext::playCard(const int index)
{
	_board->addCard(_hand->getCard(index));
}

void PlayerContext::printInfo() const
{
	_hand->printInfo();
	_board->printInfo();
}

unsigned int PlayerContext::getHandCardNb() const
{
	return _hand->getCardNb();
}

unsigned int PlayerContext::getBoardCardNb() const
{
	return _board->getCardNb();
}