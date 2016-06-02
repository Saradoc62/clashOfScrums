#include <shell/shellDemo.hxx>

ShellDemo::ShellDemo()
{

}

ShellDemo::ShellDemo(std::vector<PlayerContext*> players) :
_players(players),
_keepPlay(true)
{

}

ShellDemo::~ShellDemo()
{

}

void ShellDemo::playTurn(PlayerContext* player)
{
	int action, index;
	bool endOfTurn = false;

	player->prepare();

	do 
	{
		player->printInfo();
		player->printActions();
		std::cin >> action;

		switch(action)
		{
			case drawCard:
			{
				if(player->getDeckCardNb() > 0)
				{
					player->drawCard();
				}
				player->printHand();
				break;
			}
			case playCard:
			{
				player->printHandWithCost();
				if(player->getHandCardNb() > 0)
				{
					std::cout << "Select card to play " << std::endl;
					std::cin >> index;
					if(index <= player->getHandCardNb())
					{
						if(player->playCard(index-1))
						{
							player->printBoard();
							player->printHand();
						}
					}
				}
				break;
			}
			case makeFeature:
			{
				int featureIdx, creatureIdx;
				player->printBoardFeatures();
				std::cout << "Select a feature " << std::endl;
				std::cin >> featureIdx;
				player->printBoardCreatures();
				std::cout << "Select a creature " << std::endl;
				std::cin >> creatureIdx;

				if(featureIdx <= player->getBoardCardTypeNb(Feature) && creatureIdx <= player->getBoardCardTypeNb(Creature))
				{
					player->makeFeature(featureIdx, creatureIdx);
				}
				player->printBoardFeatures();
				break;
			}
			case endTurn:
			{
				player->update();
				endOfTurn = true;
				break;
			}
			case stopGame:
			{
				endOfTurn = true;
				_keepPlay = false;
				break;
			}
		}
	} while(!endOfTurn);
}

void ShellDemo::run()
{
	int next = 0, i = 0;
	const unsigned int nbOfPlayers = _players.size();

	std::cout << "Start Game \n" << std::endl;

	do
	{
		std::cout << "-- Player " << next + 1 << " turn ! \n" << std::endl;
	  	playTurn(_players[next]);
	  	next = ++i % nbOfPlayers;

	} while(_keepPlay);
}