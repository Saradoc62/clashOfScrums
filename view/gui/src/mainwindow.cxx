#include <iostream>

#include <QtGui/QPixmap>

#include <configuration.h>
#include "gui/mainwindow.hxx"
#include "ui_mainwindow.h"

static int drawnCardsNb = 0;

MainWindow::MainWindow(std::vector<PlayerContext*> players, 
    				   Deck* deck, 
    				   Rules rules,
    				   QWidget *parent) :
	_players(players),
	_rules(rules),
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	_deck = deck;

    ui->setupUi(this);

    //signal and slots
    connect(ui->drawCardButton, SIGNAL (released()), this, SLOT (drawCard()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cleanLabels()
{
	for(unsigned int i = 0; i < _cardLabels.size(); ++i)
	{
		delete _cardLabels[i];
	}
	_cardLabels.clear();
}

void MainWindow::printPlayerHand(PlayerContext* player)
{
	cleanLabels();

	const Hand* hand = player->getHand();
	const int startX = 20; 
	const int startY = 290; 
	const int width = 200;
	const int height = 300;
	const int offSet = 10;

	for(unsigned int i = 0; i < player->getHandCardNb(); ++i)
	{
		const Card* card = hand->getCard(i);

		QLabel* cardLabel = new QLabel(ui->centralwidget);
	    cardLabel->setObjectName(QString::fromUtf8("cardLabel"));
	    cardLabel->setGeometry(QRect(startX + i * (width+offSet), startY, width, height));
	    cardLabel->setText(QString(card->getName().c_str()));

	    QPixmap pix(card->getFrame().c_str());
	    cardLabel->setPixmap(pix.scaled(width, height, Qt::KeepAspectRatio));
	    cardLabel->show();

	    _cardLabels.push_back(cardLabel);
	}	
}

void MainWindow::drawCard()
{
	PlayerContext* player = _players[0]; //TODO fix
	if(drawnCardsNb < _rules.getMaxNbOfCardsToDrawPerTurn() && _deck->getCardNb() > 0)
	{
		player->drawCard(_deck);
		++drawnCardsNb;
	}
	player->printHand();
	printPlayerHand(player);
}
