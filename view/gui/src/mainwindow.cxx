#include <iostream>

#include <QtGui/QPixmap>

#include <configuration.h>
#include "gui/mainwindow.hxx"
#include "ui_mainwindow.h"
#include <gui/cardLabel.hxx>

MainWindow::MainWindow(std::vector<PlayerContext*> players, 
    				   Deck* deck, 
    				   Rules rules,
    				   QWidget *parent) :
	_internalTurnCount(0),
	_players(players),
	_deck(deck),
	_rules(rules),
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    _currentPlayer = _players.front();

    //signal and slots
    connect(ui->drawCardButton, SIGNAL (released()), this, SLOT (drawCard()));
    connect(ui->endTurnButton, SIGNAL (released()), this, SLOT (endTurnAndSetNextPlayer()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cleanLabels()
{
	for(unsigned int i = 0; i < _cardLabels.size(); ++i)
	{
		_cardLabels[i]->close();
	}
	_cardLabels.clear();
	_cardLabels.resize(0);
}

void MainWindow::createLabel(const Card* card)
{
	const int pos = _cardLabels.size();
	CardLabel* cardLabel = new CardLabel(card, ui->centralwidget);
	cardLabel->setPosition(pos);
	cardLabel->show();
	connect(cardLabel, SIGNAL (cardLabelClickedSignal()), this, SLOT (playCard()));
	_cardLabels.push_back(cardLabel);
}

void MainWindow::printPlayerHand(PlayerContext* player)
{
	cleanLabels();

	const Hand* hand = player->getHand();

	for(unsigned int i = 0; i < player->getHandCardNb(); ++i)
	{
		createLabel(hand->getCard(i));
	}	
}

void MainWindow::endTurnAndSetNextPlayer()
{
	_currentPlayer->update();

	const int next = ++_internalTurnCount % _players.size();
	_currentPlayer = _players[next];

	_currentPlayer->prepare();
	printPlayerHand(_currentPlayer);
}

void MainWindow::drawCard()
{
	PlayerContext* player = getCurrentPlayer();
	if(player->getDrawnCardNb() < _rules.getMaxNbOfCardsToDrawPerTurn() && _deck->getCardNb() > 0)
	{
		player->drawCard(_deck);
	}
	printPlayerHand(player);
}

void MainWindow::playCard()
{
	PlayerContext* player = getCurrentPlayer();

	for(unsigned int i = 0; i < _cardLabels.size(); ++i)
	{
		if(_cardLabels[i]->isSelected())
		{
			player->playCard(i);
			break;
		}
	}
	printPlayerHand(player);
	//printPlayerBoard(player); 
}
