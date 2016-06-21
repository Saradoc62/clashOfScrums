#include <iostream>

#include <QtGui/QPixmap>

#include <configuration.h>
#include "gui/mainwindow.hxx"
#include "ui_mainwindow.h"
#include <gui/cardWidget.hxx>


MainWindow::MainWindow(std::vector<PlayerContext*> players, 
    				   Deck* deck, 
    				   Rules rules,
    				   QWidget *parent) :
	_internalTurnCount(0),
	_imgPath(std::string(RESOURCES_PATH) + "Icons/"),
	_players(players),
	_deck(deck),
	_rules(rules),
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setBackGround();

    _currentPlayer = _players.front();
    printPlayerMoney(_currentPlayer);

    //signal and slots
    connect(ui->drawCardButton, SIGNAL (released()), this, SLOT (drawCard()));
    connect(ui->endTurnButton, SIGNAL (released()), this, SLOT (endTurnAndSetNextPlayer()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setBackGround()
{
	const std::string bgPath = _imgPath + "Board.jpeg";
    QPixmap background(bgPath.c_str());
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);
}

void MainWindow::cleanHandWidgets()
{
	for(unsigned int i = 0; i < _handCardWidgets.size(); ++i)
	{
		_handCardWidgets[i]->close();
	}
	_handCardWidgets.clear();
	_handCardWidgets.resize(0);
}

void MainWindow::cleanBoardWidgets()
{
	for(unsigned int i = 0; i < _boardCardWidgets.size(); ++i)
	{
		_boardCardWidgets[i]->close();
	}
	_boardCardWidgets.clear();
	_boardCardWidgets.resize(0);
}

CardWidget* MainWindow::createWidget(const Card* card, const int xIndex, const LabelLocation location)
{
	CardWidget* cardWidget = new CardWidget(card, ui->centralwidget);
	cardWidget->setPosition(xIndex, location);
	cardWidget->show();
	return cardWidget;
}

void MainWindow::printPlayerHand(PlayerContext* player)
{
	cleanHandWidgets();

	const Hand* hand = player->getHand();

	for(unsigned int i = 0; i < player->getHandCardNb(); ++i)
	{
		const int xIndex = i;
		CardWidget* cardWidget = createWidget(hand->getCard(i), xIndex, inHand);
		connect(cardWidget, SIGNAL (cardWidgetClickedSignal()), this, SLOT (playCard()));
		connect(cardWidget, SIGNAL (hoverLeaveSignal()), this, SLOT (drawHand()));
		_handCardWidgets.push_back(cardWidget);
	}	
}

void MainWindow::printPlayerBoard(PlayerContext* player)
{
	cleanBoardWidgets();

	const Board* board = player->getBoard();

	for(unsigned int i = 0; i < player->getBoardCardNb(); ++i)
	{
		const int xIndex = i;
		CardWidget* cardWidget = createWidget(board->getCard(i), xIndex, inBoard);
		_boardCardWidgets.push_back(cardWidget);
	}	
}

void MainWindow::printPlayerMoney(PlayerContext* player)
{
	std::string moneyText = "Money : " + std::to_string(player->getMoney());
    ui->moneyLabel->setText(QString(moneyText.c_str()));
}

void MainWindow::updatePlayerLabel(std::string const& name)
{
	const std::string playerName = "Player " + name;
    ui->playerLabel->setText(QString(playerName.c_str()));
}

void MainWindow::printPlayerContext(PlayerContext* player)
{
	printPlayerHand(player);
	printPlayerBoard(player); 
	printPlayerMoney(player);
}

void MainWindow::endTurnAndSetNextPlayer()
{
	_currentPlayer->update();

	const int next = ++_internalTurnCount % _players.size();
	_currentPlayer = _players[next];
	updatePlayerLabel(std::to_string(next+1));

	_currentPlayer->prepare();
	printPlayerContext(_currentPlayer);
}

void MainWindow::drawCard()
{
	PlayerContext* player = getCurrentPlayer();
	if( _deck->getCardNb() > 0
		&& player->getDrawnCardNb() < _rules.getMaxNbOfCardsToDrawPerTurn()
		&& player->getHandCardNb() < _rules.getMaxNbOfCardInHand() )
	{
		player->drawCard(_deck);
	}
	printPlayerContext(player);
}

void MainWindow::playCard()
{
	PlayerContext* player = getCurrentPlayer();

	for(unsigned int i = 0; i < _handCardWidgets.size(); ++i)
	{
		if(_handCardWidgets[i]->isSelected())
		{
			if(player->playCard(i))
			{
				printPlayerContext(player);
			}
			_handCardWidgets[i]->setSelected(false);
			break;
		}
	}
}

void MainWindow::drawHand()
{
	PlayerContext* player = getCurrentPlayer();

	for(unsigned int i = 0; i < _handCardWidgets.size(); ++i)
	{
		const int xIndex = i;
		_handCardWidgets[i]->setPosition(xIndex, inHand);
		_handCardWidgets[i]->raise();
	}
}

