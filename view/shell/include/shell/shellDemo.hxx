#ifndef __SHELL_DEMO_HXX__
#define __SHELL_DEMO_HXX__

#include <model/playerContext.hxx>

class ShellDemo
{
public:
	ShellDemo();
	ShellDemo(std::vector<PlayerContext*> players);
	~ShellDemo();

	void run();

private:

	void playTurn(PlayerContext* player);

	std::vector<PlayerContext*> _players;
	bool _keepPlay;
};

#endif