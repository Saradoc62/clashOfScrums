#include <shell/shellDemo.hxx>
#include <shell/actions.hxx>

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

	printActions();
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
		case stopGame:
		{
			_keepPlay = false;
			break;
		}
	}
}

void ShellDemo::run()
{
	int next = 0, i = 0;
	const unsigned int nbOfPlayers = _players.size();

	std::cout << "Start Game \n" << std::endl;

	do
	{
		std::cout << "Player " << next + 1 << " turn ! " << std::endl;
	  	playTurn(_players[next]);
	  	next = ++i % nbOfPlayers;

	} while(_keepPlay);
}