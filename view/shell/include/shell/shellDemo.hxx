#ifndef __SHELL_DEMO_HXX__
#define __SHELL_DEMO_HXX__

#include <model/playerContext.hxx>
#include <model/deck.hxx>

class ShellDemo
{
public:
	ShellDemo();
	ShellDemo(std::vector<PlayerContext*> players, Deck* deck);
	~ShellDemo();

	void run();

private:

	void playTurn(PlayerContext* player);

	std::vector<PlayerContext*> _players;
	Deck* _deck;
	bool _keepPlay;
};

#endif