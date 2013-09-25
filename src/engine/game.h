#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"

class Game{

public:
	Game();
	~Game();

	void init();
	void run();

private:
	bool isFinished;

};

#endif
