#include <iostream>
#include <boost/foreach.hpp>

#include <model/board.hxx>
#include <model/feature.hxx>

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

const Card* Board::getCard(const int index) const
{
	Card* card = _cards[index];
	return card;
}

const std::string Board::getCardName(const int index) const
{
	return _cards[index]->getName();
}

//Get occurence <index> of CardType <type> in Board
Card* Board::getCardType(CardType type, const int index)
{
	Card* res = NULL;
	int found = 0;
	BOOST_FOREACH(Card* const& c, _cards)
	{
		if(c->getType().find(toString(type)) != std::string::npos)
		{
			++found;
			if(found == index)
			{
				res = c;
				break;
			}
		}
	}
	return res;
}

std::vector<Card*> Board::getCards()
{
	return _cards;
}

void Board::applyEffects() const
{	
	BOOST_FOREACH( Card* const& c, _cards )
	{
		c->applyEffectToBoard(_cards);
	}
}

void Board::update()
{
	for(unsigned int i = 0; i < _cards.size(); ++i)
	{
		if(_cards[i]->getType().find("Feature") != std::string::npos)
		{
			class Feature* feat = dynamic_cast<class Feature*>(_cards[i]);

			//Update feature
			feat->update();
			if(feat->getDeadline() == 0 && !feat->isCompleted())
			{
				//remove uncompleted features from board if deadline is reached
				_cards.erase(_cards.begin() + i);
			}
		}
	}
}

unsigned int Board::getCardNb() const
{
	return _cards.size();
}

int Board::getCardTypeNb(CardType type) const
{
	int nb = 0;
	BOOST_FOREACH(Card* const& c, _cards)
	{
		if(c->getType().find(toString(type)) != std::string::npos)
		{
			++nb;
		}
	}
	return nb;
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

void Board::printCardType(CardType type) const
{
	int i = 0;
	BOOST_FOREACH(Card* const& c, _cards)
	{
		if(c->getType().find(toString(type)) != std::string::npos)
		{
			std::cout << toString(type) << " " << ++i << " : " << std::endl;
			c->print();
		}
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

Card* Hand::playCard(const int index)
{
	Card* card = _cards[index];
	_cards.erase(_cards.begin() + index);
	return card;
}

void Hand::printInfo() const
{
	std::cout << "* PRINT HAND *" << std::endl;
	std::cout << "Number of cards : " << _cards.size() << "\n" << std::endl;
}

void Hand::printWithCost() const
{
	printInfo();

	int i = 0;
	BOOST_FOREACH(Card* const& c, _cards)
	{
		std::cout << ++i << " : " << c->getName() << ", " << c->getCost() << std::endl;
	}
	std::cout << std::endl;
}