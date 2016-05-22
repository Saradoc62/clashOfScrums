#include <shell/shellDemo.hxx>
#include <shell/actions.hxx>

ShellDemo::ShellDemo()
{

}

ShellDemo::ShellDemo(std::vector<PlayerContext*> players) :
_players(players)
{

}

ShellDemo::~ShellDemo()
{

}

void ShellDemo::run()
{
	bool keepPlay = true;

	PlayerContext* player = _players[0];

	int action, index;
	std::cout << "Start Game \n" << std::endl;

	do
	{
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
				keepPlay = false;
				break;
			}
		}

	} while(keepPlay);
}