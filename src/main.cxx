#include <vector>

#include <configuration.h>
#include <shell/shellDemo.hxx>

int main(int argc, char* argv[])
{
	//Load Deck
	std::string xmlPath = std::string(RESOURCES_PATH) + "cards.xml";
	const int deckSize = 10;
	Deck deck(xmlPath, deckSize);

	//Create players
	const int nbOfPlayers = 4;
	std::vector<PlayerContext*> players;
	for(int i = 0; i < nbOfPlayers; ++i)
	{
		PlayerContext* player = new PlayerContext(&deck);
		players.push_back(player);
	}

	//Run demo
	ShellDemo demo(players);
	demo.run();

	return 0;
}
