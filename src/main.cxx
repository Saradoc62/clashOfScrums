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
	std::vector<PlayerContext*> players;

	PlayerContext* player1 = new PlayerContext(&deck);
	players.push_back(player1);

	//Run demo
	ShellDemo demo(players);
	demo.run();
}
