#include <vector>

#include <configuration.h>
#include <shell/shellDemo.hxx>

int main(int argc, char* argv[])
{
	//Load rules
	std::string rulesXmlPath = std::string(RESOURCES_PATH) + "rules.xml";
	Rules rules(rulesXmlPath);

	//Load Deck
	std::string cardsXmlPath = std::string(RESOURCES_PATH) + "cards.xml";
	const int deckSize = 10;
	Deck deck(cardsXmlPath, deckSize);

	//Create players
	const int nbOfPlayers = 4;
	std::vector<PlayerContext*> players;
	for(int i = 0; i < nbOfPlayers; ++i)
	{
		PlayerContext* player = new PlayerContext();
		players.push_back(player);
	}

	//Run demo
	ShellDemo demo(players, &deck, rules);
	demo.run();

	return 0;
}
