#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "gameestate.h"

class PlayState : public GameState{

public:

	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateId() const;

private:

	static const std::string playId;
};

#endif