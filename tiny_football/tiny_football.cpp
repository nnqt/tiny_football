#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"

#define FPS		30

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
	return true;
}

bool SDLinit = init();

RenderWindow window("TINY FOOTBALL", 1280, 720); 

SDL_Texture* ballTexture = window.loadTexture()


bool gameRunning = true;
bool singlePlayer = true;
bool secondPlayer = false;

int gameState = 0;

SDL_Event event;

//fps
int desiredDelta = 1000 / FPS;
int startLoop = 0;
int endLoop = 0;

void delayTimeLoop()
{
	int delta = SDL_GetTicks() - startLoop;
	if (delta < desiredDelta)
	{
		SDL_Delay(desiredDelta - delta);
	}
}

void update()
{


	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			gameRunning = false;
			break;
		}
	}
}

void graphics()
{

}

void game()
{
	if (gameState == 0)
	{

	}
	else if (gameState == 1) {
		update();
		graphics();
	}
}

int main(int argc, char* args[])
{
	while (gameRunning)
	{	
		startLoop = SDL_GetTicks();
		game();
		delayTimeLoop();
	}
	window.cleanUp();
	return 0;
}