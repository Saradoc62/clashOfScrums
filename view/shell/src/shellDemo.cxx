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

	do 
	{
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
				if(player->getHandCardNb() > 0)
				{
					std::cout << "Select card to play " << std::endl;
					std::cin >> index;
					if(index-1 < player->getHandCardNb())
					{
						player->playCard(index-1);
						player->printBoard();
						player->printHand();
					}
				}
				break;
			}
			case endTurn:
			{
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