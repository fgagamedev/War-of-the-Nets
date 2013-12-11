#include "menustate.h"
#include "playstate.h"
#include "creditstate.h"
#include "configurationstate.h"
#include "tutorialstate.h"
#include "attractstate.h"
#include "inputhandler.h"
#include "networkstate.h"
#include "render.h"
#include "texturemanager.h"
#include "game.h"
#include "text.h"
#include "SDL2/SDL.h"
#include "soundmanager.h"
#include "gameoverstate.h"
#include <iostream>

const std::string MenuState::menuId = "MENU";

void
MenuState::update()
{
	for(int i =0; i<(int)menuObjects.size(); i++)
		menuObjects[i]->update();
		
		
	if((int)SDL_GetTicks() - atualTime > atractTime)
	{
	    //InputHandler::getInstance()->removeEvent(this);
	    Game::Instance()->getStateMachine()->pushState(new AttractState());
    }
}

void
MenuState::render()
{

	TextureManager::Instance()->drawFrame("fundo", 0, 0, 1280,
	 700, 0, 0, Render::getInstance()->getRenderer(), 0);

	TextureManager::Instance()->draw("title", Game::Instance()->getWindow()->getWidth()/2 - 1132/2, 10, 
		Render::getInstance()->getRenderer());

	for(int i =0; i<(int)menuObjects.size(); i++)
		menuObjects[i]->draw();
}

bool
MenuState::onEnter()
{
    atractTime = 10000;
	atualTime = SDL_GetTicks();
	
	if(!TextureManager::Instance()->loadImage("resources/img/fundo.png",
		"fundo", Render::getInstance()->getRenderer()))
	{
		return false;
	}

	
	if(!TextureManager::Instance()->loadImage("resources/img/title.png",
	 "title", Render::getInstance()->getRenderer()))
	{
		return false;
	}
	
	createMenu();

	SoundManager::Instance()->loadSound("resources/audio/Five_Armies.ogg", "theme", MUSIC);
	SoundManager::Instance()->playMusic("theme", 1);
	
	InputHandler::getInstance()->addEvent(this);
	

	return true;
}

void 
MenuState::enable()
{
    atualTime = SDL_GetTicks();
    playButton->setActive(true);
	aboutButton->setActive(true);
	exitButton->setActive(true);
	configurationButton->setActive(true);
	tutorialButton->setActive(true);
}

void 
MenuState::disable()
{
    playButton->setActive(false);
	aboutButton->setActive(false);
	exitButton->setActive(false);
	configurationButton->setActive(false);
	tutorialButton->setActive(false);
}

void 
MenuState::createMenu()
{

	int espacamento = 20;

	playButton = new MenuButton(0, 0, "resources/img/play.png", "playbutton", 3, true);
	int playx = (Game::Instance()->getWindow()->getWidth() / 2) - (playButton->getWidth() / 2);
	int playy= (Game::Instance()->getWindow()->getHeight() / 2) - ((playButton->getHeight()) / 2);
	playButton->setPosition(playx, playy);
	playButton->setEventListener(this);
	playButton->setAudioOnClick("resources/audio/fx_stab-001.wav", "playClick");
	InputHandler::getInstance()->addMouseClick(playButton);

	
	aboutButton = new MenuButton(0, 0, "resources/img/about.png", "aboutbutton",3, true);
	int aboutx = playx;
	int abouty= (Game::Instance()->getWindow()->getHeight() / 2) + (aboutButton->getHeight() / 2) + espacamento;
	aboutButton->setPosition(aboutx, abouty);
	aboutButton->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(aboutButton);

	tutorialButton = new MenuButton(0, 0, "resources/img/tutorial_button.png", "tutorial",3, true);
	int tutorialy= abouty + aboutButton->getHeight() + espacamento;
	tutorialButton->setPosition(playx, tutorialy);
	tutorialButton->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(tutorialButton);
	
	exitButton = new MenuButton(0, 0, "resources/img/exit.png", "exitbutton", 3, true);
	int exitx = aboutx;
	int exity = tutorialy + espacamento + tutorialButton->getHeight();
	exitButton->setPosition(exitx, exity);
	exitButton->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(exitButton);
	
	configurationButton = new MenuButton(0, 0, "resources/img/configbutton.png", "config", 3, true);
	int configurationx = (Game::Instance()->getWindow()->getWidth()) - configurationButton->getWidth();
	int configurationy = (Game::Instance()->getWindow()->getHeight()) - configurationButton->getHeight();
	configurationButton->setPosition(configurationx, configurationy);
	configurationButton->setEventListener(this);
	InputHandler::getInstance()->addMouseClick(configurationButton);
	
	menuObjects.push_back(configurationButton);
	menuObjects.push_back(playButton);
	menuObjects.push_back(aboutButton);
	menuObjects.push_back(exitButton);
	menuObjects.push_back(tutorialButton);

}

bool 
MenuState::onExit()
{
	for(int i =0; i<(int)menuObjects.size(); i++)
		menuObjects[i]->clean();

	menuObjects.clear();

	
	TextureManager::Instance()->clearFromTextureMap("playbutton");
	TextureManager::Instance()->clearFromTextureMap("exitbutton");
	TextureManager::Instance()->clearFromTextureMap("fundo");
	TextureManager::Instance()->clearFromTextureMap("title");
	TextureManager::Instance()->clearFromTextureMap("config");
	TextureManager::Instance()->clearFromTextureMap("tutorial");

	SoundManager::Instance()->stopSound();
	SoundManager::Instance()->clearFromSoundManager("theme", MUSIC);
	SoundManager::Instance()->clearFromSoundManager("playClick", SFX);
	
	InputHandler::getInstance()->removeMouseClick(playButton);
	InputHandler::getInstance()->removeMouseClick(aboutButton);
	InputHandler::getInstance()->removeMouseClick(exitButton);
	InputHandler::getInstance()->removeMouseClick(configurationButton);
	InputHandler::getInstance()->removeMouseClick(tutorialButton);

    InputHandler::getInstance()->removeEvent(this);
    
    
	return true;
}

std::string 
MenuState::getStateId() const
{
	return menuId;
}

void
MenuState::menuToPlay()
{
	//Game::Instance()->getStateMachine()->pushState(new GameOverState());
	//Game::Instance()->getStateMachine()->pushState(new PlayState());
	Game::Instance()->getStateMachine()->changeState(new NetworkState());
}

void
MenuState::menuToCredit()
{
	Game::Instance()->getStateMachine()->pushState(new CreditState());
}

void
MenuState::exitFromMenu()
{
    //Game::Instance()->getStateMachine()->popState();
	Game::Instance()->finishGame();
}

void
MenuState::menuToOption()
{
	Game::Instance()->getStateMachine()->pushState(new ConfigurationState());
}

void
MenuState::menuToTutorial()
{
	Game::Instance()->getStateMachine()->pushState(new TutorialState());
}

void
MenuState::onMouseClick(MouseClick *mouseClick)
{
    if(mouseClick == playButton)
        menuToPlay();
    if(mouseClick == aboutButton)
        menuToCredit();
    if(mouseClick == exitButton)
        exitFromMenu();
    if(mouseClick == configurationButton)
        menuToOption();
    if(mouseClick == tutorialButton)
        menuToTutorial();
}



bool
MenuState::eventInMe(SDL_Event)
{
    return false;
}


bool 
MenuState::verifyEvent(SDL_Event sdlEvent)
{
    if(sdlEvent.type == SDL_MOUSEMOTION)
    {
        
        if( this->sdlEvent.motion.x == 0 &&
            this->sdlEvent.motion.y == 0)
        {
            SDL_Event temp = sdlEvent;
            this->sdlEvent = temp;
            return false;
        }
        
        if( abs(this->sdlEvent.motion.x - sdlEvent.motion.x) > 2 ||
            abs(this->sdlEvent.motion.y - sdlEvent.motion.y) > 2 )
        {
            atualTime = SDL_GetTicks();
            return true;
        }
        else
        {
            return false;
        }
    }

    if( (sdlEvent.type == SDL_MOUSEBUTTONDOWN) ||
        (sdlEvent.type == SDL_MOUSEBUTTONUP) ||
        (sdlEvent.type == SDL_KEYDOWN) ||
        (sdlEvent.type == SDL_KEYUP))
    {
        atualTime = SDL_GetTicks();
        return true;
    }
    else
    {
        return false;
    }
}


