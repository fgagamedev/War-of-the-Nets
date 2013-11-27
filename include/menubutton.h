#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include "sdlgameobject.h"
#include "mouseclick.h"
#include "SDL2/SDL.h"

class MenuButton : public SDLGameObject, public MouseClick {

public:
	MenuButton(int, int, string, string, int = 1, bool=false);

	virtual void draw();
	virtual void update();
	virtual void clean();

    virtual bool eventInMe(SDL_Event sdlEvent);
    virtual bool verifyEvent(SDL_Event sdlEvent);

    bool setAudioOnClick(string, string);
    bool playSoundOnClick();

private:

	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2

	};

	bool released;
	bool animate;
	string soundId;
	
	SDL_Event sdlEvent;

};

#endif
