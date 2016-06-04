#ifndef __SHELL_DEMO_HXX__
#define __SHELL_DEMO_HXX__

#include <model/rules.hxx>
#include <model/playerContext.hxx>
#include <model/deck.hxx>

class ShellDemo
{
public:
	ShellDemo();
	ShellDemo(std::vector<PlayerContext*> players, Deck* deck, Rules rules);
	~ShellDemo();

	void run();

private:

	void playTurn(PlayerContext* player);

	std::vector<PlayerContext*> _players;
	Deck* _deck;
	Rules _rules;
	bool _keepPlay;
};

#endif