#include <iostream>

#include <QtGui/QPixmap>

#include <configuration.h>
#include "gui/mainwindow.hxx"
#include "ui_mainwindow.h"
#include <gui/cardLabel.hxx>

enum LabelPosition
{
	top = 0, 
	bottom = 1
};

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

void MainWindow::cleanHandLabels()
{
	for(unsigned int i = 0; i < _handCardLabels.size(); ++i)
	{
		_handCardLabels[i]->close();
	}
	_handCardLabels.clear();
	_handCardLabels.resize(0);
}

void MainWindow::cleanBoardLabels()
{
	for(unsigned int i = 0; i < _boardCardLabels.size(); ++i)
	{
		_boardCardLabels[i]->close();
	}
	_boardCardLabels.clear();
	_boardCardLabels.resize(0);
}

CardLabel* MainWindow::createLabel(const Card* card, const int xIndex, const int yIndex)
{
	CardLabel* cardLabel = new CardLabel(card, ui->centralwidget);
	cardLabel->setPosition(xIndex, yIndex);
	cardLabel->show();
	return cardLabel;
}

void MainWindow::printPlayerHand(PlayerContext* player)
{
	cleanHandLabels();

	const int yIndex = bottom;
	const Hand* hand = player->getHand();

	for(unsigned int i = 0; i < player->getHandCardNb(); ++i)
	{
		const int xIndex = i;
		CardLabel* cardLabel = createLabel(hand->getCard(i), xIndex, yIndex);
		connect(cardLabel, SIGNAL (cardLabelClickedSignal()), this, SLOT (playCard()));
		_handCardLabels.push_back(cardLabel);
	}	
}

void MainWindow::printPlayerBoard(PlayerContext* player)
{
	cleanBoardLabels();

	const int yIndex = top;
	const Board* board = player->getBoard();

	for(unsigned int i = 0; i < player->getBoardCardNb(); ++i)
	{
		const int xIndex = i;
		CardLabel* cardLabel = createLabel(board->getCard(i), xIndex, yIndex);
		_boardCardLabels.push_back(cardLabel);
	}	
}

void MainWindow::endTurnAndSetNextPlayer()
{
	_currentPlayer->update();

	const int next = ++_internalTurnCount % _players.size();
	_currentPlayer = _players[next];

	_currentPlayer->prepare();
	printPlayerHand(_currentPlayer);
	printPlayerBoard(_currentPlayer);
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

	for(unsigned int i = 0; i < _handCardLabels.size(); ++i)
	{
		if(_handCardLabels[i]->isSelected())
		{
			player->playCard(i);
			break;
		}
	}
	printPlayerHand(player);
	printPlayerBoard(player); 
}
