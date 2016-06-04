#include <boost/foreach.hpp>

#include <model/playerContext.hxx>
#include <model/card.hxx>
#include <model/feature.hxx>
#include <model/creature.hxx>

PlayerContext::PlayerContext()
{
	_money = 0;
	_board = new Board();
	_hand  = new Hand();
}

PlayerContext::~PlayerContext()
{

}

void PlayerContext::prepare()
{
	BOOST_FOREACH(Card* const& card, _board->getCards())
	{
		updateMoney(card);
	}
}

void PlayerContext::update()
{
	_board->update();
}

void PlayerContext::updateMoney(Card* card)
{
	if(card->getType().find("Feature") != std::string::npos)
	{
		class Feature* feat = dynamic_cast<class Feature*>(card);
		if(feat->getDeadline() > 0)
			_money += feat->getIncome();
	}
	else
	{
		_money -= card->getCost();
	}
}

void PlayerContext::drawCard(Deck* deck)
{
	Card* card = deck->drawNext();
	std::cout << "==> Draw Card : " << card->getName() << "\n" << std::endl;
	_hand->addCard(card);
}

bool PlayerContext::playCard(const int index)
{
	bool status = true;
	Card* card = _hand->getCard(index);
	if(_money >= card->getCost())
	{
		std::cout << "==> Play Card : " << card->getName() << "\n" << std::endl;
		_board->addCard(card);
		updateMoney(card);
	}
	else
	{
		std::cout << "Not enough money to play : " << card->getName() << "\n" << std::endl;
		_hand->addCard(card);
		status = false;
	}
	return status;
}

void PlayerContext::makeFeature(int featureIdx, int creatureIdx)
{
	Card* feat = _board->getCardType(Feature, featureIdx);
	Card* creat = _board->getCardType(Creature, creatureIdx);

	if(feat && creat)
	{
		class Feature* feature = dynamic_cast<class Feature*>(feat);
		class Creature* creature = dynamic_cast<class Creature*>(creat);

		feature->acceptCreature(creature);
	}
}

void PlayerContext::printActions() const
{
	std::cout << "* ACTIONS *"   	<< std::endl;
	std::cout << "1 : Draw Card" 	<< std::endl;
	std::cout << "2 : Play Card" 	<< std::endl;
	std::cout << "3 : Make Feature" << std::endl;
	std::cout << "4 : End Turn"  	<< std::endl;
	std::cout << "5 : End Game \n" 	<< std::endl;
}

unsigned int PlayerContext::getHandCardNb() const
{
	return _hand->getCardNb();
}

unsigned int PlayerContext::getBoardCardNb() const
{
	return _board->getCardNb();
}

int PlayerContext::getBoardCardTypeNb(CardType type) const
{
	return _board->getCardTypeNb(type);
}

void PlayerContext::printInfo() const
{
	std::cout << "* PRINT PLAYER CONTEXT *" << std::endl;
	std::cout << "Money = " << _money << "\n" << std::endl;
	//_hand->printInfo();
	//_board->printInfo();
}

void PlayerContext::printHand() const
{
	_hand->print();
}

void PlayerContext::printHandWithCost() const
{
	_hand->printWithCost();
}

void PlayerContext::printBoard() const
{
	_board->print();
}

void PlayerContext::printBoardFeatures() const
{
	std::cout << "* PRINT BOARD FEATURES *" << std::endl;
	_board->printCardType(Feature);
}

void PlayerContext::printBoardCreatures() const
{
	std::cout << "* PRINT BOARD CREATURES *" << std::endl;
	_board->printCardType(Creature);
}
