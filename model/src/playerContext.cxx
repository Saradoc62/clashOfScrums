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
	Card* card = _deck->drawNext();
	std::cout << "==> Draw Card : " << card->getName() << "\n" << std::endl;
	_hand->addCard(card);
}

void PlayerContext::playCard(const int index)
{
	Card* card = _hand->getCard(index);
	std::cout << "==> Play Card : " << card->getName() << "\n" << std::endl;
	_board->addCard(card);
}

void PlayerContext::printActions() const
{
	std::cout << "* ACTIONS *"   << std::endl;
	std::cout << "1 : Draw Card" << std::endl;
	std::cout << "2 : Play Card" << std::endl;
	std::cout << "3 : End Turn"  << std::endl;
	std::cout << "4 : End Game \n" << std::endl;
}

unsigned int PlayerContext::getHandCardNb() const
{
	return _hand->getCardNb();
}

unsigned int PlayerContext::getBoardCardNb() const
{
	return _board->getCardNb();
}

unsigned int PlayerContext::getDeckCardNb() const
{
	return _deck->getCardNb();
}

void PlayerContext::printInfo() const
{
	std::cout << "* PRINT PLAYER CONTEXT *" << std::endl;
	_hand->printInfo();
	_board->printInfo();
}

void PlayerContext::printHand() const
{
	_hand->print();
}

void PlayerContext::printBoard() const
{
	_board->print();
}
