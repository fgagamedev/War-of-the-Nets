#include "game.h"
#include "image.h"
#include "render.h"
#include "text.h"
#include "sdlsettings.h"
#include "rectangle.h"
#include "pixel.h"
#include "line.h"
#include "circle.h"
#include "hexagon.h"
#include <cmath>

#include <iostream>
using namespace std;

#define PLAY_GAME 1

Game::Game()
{
	cout << "Creating War of the Nets" << endl;
}

Game::~Game()
{
	cout << "Finishing War of the Nets" << endl;
	if(window != NULL)
		delete window;
}

void
Game::init()
{
	cout << "Intialize" << endl;

	if(SDLSettings::setUpEnviroment())
		cout << "Enviroment Set" << endl;
	else
		cout << "Could not Set Enviroment" << endl;

	const char * title = "War of The Nets";
	this->window = new Window(800, 600, 0, 0, title);
	(this->window)->createWindow();
}


void
Game::run()
{
	cout << "Run" << endl;

	bool quit = false;
	
	presentation();
	
	SDL_Event event;	
	while(!quit)
	{
		SDL_PollEvent(&event);
		if(event.type == SDL_QUIT)
			quit = true;
	}
}

void
Game::presentation()
{
	Render * rend = this->window->getRender();
	
	rend->clear();

	Image logo;
	
	logo.loadImage("resources/img/logo.png", rend->getRenderer());
	int logoX = (this->window->getWidth() / 2) - (logo.getWidth() / 2);
	int logoY = (this->window->getHeight() / 2) - (logo.getHeight() / 2);
	rend->renderTexture(logo.getTexture(), logoX, logoY);
	

	Text * phrase = new Text("Apresenta: ", 32);
	phrase->setFont("resources/font/Army.ttf");
	SDL_Color whiteColor = {255, 255, 255, 0};
	phrase->generateTexture(rend->getRenderer(), whiteColor, whiteColor);
	int phraseX = logoX + (phrase->getWidth() / 2);
	int phraseY = (logoY + logo.getHeight() + 15);
	rend->renderTexture(phrase->getTexture(), phraseX, phraseY);
    
	rend->present();
	
	//SDL_Delay(5000);
	
	
	rend->clear();
	
	Text * gameName = new Text("WAR OF THE NETS", 92);
	gameName->setFont("resources/font/Army.ttf");
	gameName->generateTexture(rend->getRenderer(), whiteColor, whiteColor);
	int gameNameX = (this->window->getWidth() / 2) - (gameName->getWidth() / 2);
	int gameNameY = (this->window->getHeight() / 2) - (gameName->getHeight() / 2);
	rend->renderTexture(gameName->getTexture(), gameNameX, gameNameY);
	
	rend->present();
	
	
	//SDL_Delay(5000);
	
	rend->clear();
	
	int espacamento = 15;
	
	gameNameX = (this->window->getWidth() / 2) - (gameName->getWidth() / 2);
	gameNameY = espacamento * 5;
	rend->renderTexture(gameName->getTexture(), gameNameX, gameNameY);
	
	Image aboutButton;
	aboutButton.loadImage("resources/img/aboutbutton.png", rend->getRenderer());
	int aboutButtonX = espacamento;
	int aboutButtonY = this->window->getHeight() - aboutButton.getHeight() - espacamento;
	rend->renderTexture(aboutButton.getTexture(), aboutButtonX, aboutButtonY);
	
	Image playButton;
	playButton.loadImage("resources/img/playbutton.png", rend->getRenderer());
	int playButtonX = espacamento;
	int playButtonY = aboutButtonY - playButton.getHeight() - espacamento;
	rend->renderTexture(playButton.getTexture(), playButtonX, playButtonY);
	
	Image exitButton;
	exitButton.loadImage("resources/img/exitbutton.png", rend->getRenderer());
	int exitButtonX = this->window->getWidth() - exitButton.getWidth() - espacamento;
	int exitButtonY = this->window->getHeight() - exitButton.getHeight() - espacamento;
	rend->renderTexture(exitButton.getTexture(), exitButtonX, exitButtonY);
	
	rend->present();
	
	
	//SDL_Delay(5000);
	
	
	
	rend->clear();
	
	Hexagon * hex = new Hexagon(80);
	int hexX = 10;
	int hexY = 10;
	hex->init();
	hex->setDrawColor(150, 255, 255, 255);
	hex->draw();
	rend->renderTexture(hex->generateTexture(rend->getRenderer()), hexX, hexY);
	
	Image torre;
	torre.loadImage("resources/img/torre.png", rend->getRenderer());
	int torreX = hexX + (hex->getWidth() / 2) - (torre.getWidth() / 2);
	int torreY = hexY + (hex->getHeight() / 2) - (torre.getHeight() / 1) + (torre.getHeight() / 4);
	rend->renderTexture(torre.getTexture(), torreX, torreY);
	
	
	hexX = hexX + hex->getWidth() * 2;
	hexY = hexY + hex->getHeight();
	rend->renderTexture(hex->generateTexture(rend->getRenderer()), hexX, hexY);
	
	torreX = hexX + (hex->getWidth() / 2) - (torre.getWidth() / 2);
	torreY = hexY + (hex->getHeight() / 2) - (torre.getHeight() / 1) + (torre.getHeight() / 4);
	rend->renderTexture(torre.getTexture(), torreX, torreY);
	
	hexX = hexX - hex->getWidth() * 2;
	//hexY = hexY + hex->getHeight();
	rend->renderTexture(hex->generateTexture(rend->getRenderer()), hexX, hexY);
	
	Image base;
	base.loadImage("resources/img/base.png", rend->getRenderer());
	int baseX = hexX + (hex->getWidth() / 2) - (torre.getWidth() / 2);
	int baseY = hexY + (hex->getHeight() / 2) - (torre.getHeight() / 1) + (torre.getHeight() / 4);
	rend->renderTexture(base.getTexture(), baseX, baseY);
		
	
	Image settingsButton;
	settingsButton.loadImage("resources/img/settingsbutton.png", rend->getRenderer());
	int settingsButtonX = this->window->getWidth() - settingsButton.getWidth();
	int settingsButtonY = this->window->getHeight() - settingsButton.getHeight();
	rend->renderTexture(settingsButton.getTexture(), settingsButtonX, settingsButtonY);
		
	Image bomb;
	bomb.loadImage("resources/img/bomb.png", rend->getRenderer());
	int bombX = this->window->getWidth() - bomb.getWidth();
	int bombY = settingsButtonY - bomb.getHeight() - espacamento;
	rend->renderTexture(bomb.getTexture(), bombX, bombY);
	
	Image spySymbol;
	spySymbol.loadImage("resources/img/spysymbol.png", rend->getRenderer());
	int spySymbolX = this->window->getWidth() - spySymbol.getWidth();
	int spySymbolY = bombY - spySymbol.getHeight() - espacamento;
	rend->renderTexture(spySymbol.getTexture(), spySymbolX, spySymbolY);
	
	Image tecnologiSymbol;
	tecnologiSymbol.loadImage("resources/img/tecnologisymbol.png", rend->getRenderer());
	int tecnologiSymbolX = this->window->getWidth() - tecnologiSymbol.getWidth();
	int tecnologiSymbolY = spySymbolY - tecnologiSymbol.getHeight() - espacamento;
	rend->renderTexture(tecnologiSymbol.getTexture(), tecnologiSymbolX, tecnologiSymbolY);
	
	
	//hexX = hexX - hex->getWidth() * 2;
	hexY = hexY + hex->getHeight();
	rend->renderTexture(hex->generateTexture(rend->getRenderer()), hexX, hexY);
	
	Image spyUnit;
	spyUnit.loadImage("resources/img/spyunit.png", rend->getRenderer());
	int spyUnitX = hexX + (hex->getWidth() / 2) - (spyUnit.getWidth() / 2);
	int spyUnitY = hexY + (hex->getHeight() / 2) - (spyUnit.getHeight() / 1) + (spyUnit.getHeight() / 4);
	rend->renderTexture(spyUnit.getTexture(), spyUnitX, spyUnitY);
	
	/*
	
	Hexagon * hex2 = new Hexagon(140);
	hex2->init();
	hex2->setDrawColor(150, 255, 255, 255);
	hex2->draw();
	rend->renderTexture(hex2->generateTexture(rend->getRenderer()), hex->getWidth(), 0);
	
	Image base;
	base.loadImage("resources/img/base.png", rend->getRenderer());
	int baseX = hex->getWidth() + (hex2->getWidth() / 2) - (base.getWidth() / 2);
	int baseY = 0 + (hex2->getHeight() / 2) - (base.getHeight() / 2);
	rend->renderTexture(base.getTexture(), baseX, baseY);
	
	Hexagon * hex3 = new Hexagon(140);
	hex2->init();
	hex2->setDrawColor(150, 255, 255, 255);
	hex2->draw();
	int h = ((hex->getHeight() / (sqrt(3)*2))/2) - 2;
	rend->renderTexture(hex2->generateTexture(rend->getRenderer()), hex->getWidth(), hex->getHeight() - h);
	
	torreX = hex->getWidth() + (hex3->getWidth() / 2) - (torre.getWidth() / 2);
	torreY = (hex->getHeight() - h) + (hex3->getHeight() / 2) - (torre.getHeight() / 2);
	rend->renderTexture(torre.getTexture(), torreX, torreY);
	*/
	
	rend->present();
	
	
	cout << "Renderer" << endl;
}

void
Game::menu()
{
	int choice = 0;
	
	if(choice == PLAY_GAME)
		mainLoop();
}

void updateTime();
void getInput();	
void getNetworkMessage();
void simulateWorld();
void updateObjects();
void renderWorld();

void
Game::mainLoop()
{
	bool levelComplete = false;

	while(!levelComplete)
	{
		updateTime();
		getInput();	
		getNetworkMessage();
		simulateWorld();
		updateObjects();
		renderWorld();
		levelComplete = true;
	}
}

void updateTime()
{
	cout<<"Update time"<<endl;
}

void getInput()
{
	cout<<"Inputs received"<<endl;
}

void getNetworkMessage()
{
	cout<<"Getting Network Message"<<endl;
}

void simulateWorld()
{
	cout<<"Simulating world units"<<endl;
}

void updateObjects()
{
	cout<<"Onjects atualized"<<endl;
}

void renderWorld()
{
	cout<<"World Screen Atualized"<<endl;
}
