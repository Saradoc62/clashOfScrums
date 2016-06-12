#include <iostream>
#include <vector>
#include <QtGui>

#include <configuration.h>
#include <shell/shellDemo.hxx>
#include <gui/mainwindow.hxx>

void usage();
int runShellDemo(std::vector<PlayerContext*> players, Deck* deck, Rules rules);
int runQtGuiDemo(std::vector<PlayerContext*> players, Deck* deck, Rules rules, int argc, char* argv[]);

int main(int argc, char* argv[])
{
	std::string option;

	if(argc < 2)
		usage();
	else
		option = std::string(argv[1]);

	//Load rules
	std::string rulesXmlPath = std::string(RESOURCES_PATH) + "rules.xml";
	Rules rules(rulesXmlPath);

	//Load Deck
	std::string cardsXmlPath = std::string(RESOURCES_PATH) + "cards.xml";
	const int deckSize = rules.getDeckSize();
	Deck deck(cardsXmlPath, deckSize);

	//Create players
	const int nbOfPlayers = 2;
	std::vector<PlayerContext*> players;
	for(int i = 0; i < nbOfPlayers; ++i)
	{
		PlayerContext* player = new PlayerContext();
		players.push_back(player);
	}

	//Run main program
	if (option == "-s" || option == "--shell")
		runShellDemo(players, &deck, rules);
	else if (option == "-g" || option == "--gui")
		runQtGuiDemo(players, &deck, rules, argc, argv);
	else
		usage();

	return 0;
}

int runShellDemo(std::vector<PlayerContext*> players, Deck* deck, Rules rules)
{
	ShellDemo demo(players, deck, rules);
	demo.run();

	return 0;
}

int runQtGuiDemo(std::vector<PlayerContext*> players, Deck* deck, Rules rules, int argc, char* argv[])
{
	QApplication a(argc, argv);
	MainWindow ui(players, deck, rules);
	ui.show();
	return a.exec();
}

void usage()
{
	std::cout << "Use -s (or --shell) for shell mode." 	<< std::endl;
	std::cout << "Use -g (or --gui) for GUI mode." 		<< std::endl;
}