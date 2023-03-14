#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "RenderWindow.hpp"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h): window(NULL) , renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* RenderWindow::loadTexture(std::string p_filePath, ColorRGB transparent_color)
{
	SDL_Surface* loadedSurface = IMG_Load(p_filePath.c_str());
	SDL_Texture* texture = NULL;

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", p_filePath.c_str(), IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, transparent_color.red, transparent_color.green, transparent_color.blue));
		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (texture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", p_filePath.c_str(), SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	return texture;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(window);
}

void RenderWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& p_entity)
{
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;

	SDL_Rect dst;
	/*dst.x = p_entity.getPos().x + (p_entity.getCurrentFrame().w - p_entity.getCurrentFrame().w * p_entity.getScale().x) / 2;
	dst.y = p_entity.getPos().y + (p_entity.getCurrentFrame().h - p_entity.getCurrentFrame().h * p_entity.getScale().y) / 2;*/
	dst.x = p_entity.getPos().x;
	dst.y = p_entity.getPos().y;
	dst.w = p_entity.getCurrentFrame().w * p_entity.getScale().x;
	dst.h = p_entity.getCurrentFrame().h * p_entity.getScale().y;

	if (p_entity.checkFlipHorizon()) 
	{
		SDL_RenderCopyEx(renderer, p_entity.getTexture(), &src, &dst, p_entity.getAngle(), 0, SDL_FLIP_HORIZONTAL);
	}
	else if (p_entity.checkFlipVertical())
	{
		SDL_RenderCopyEx(renderer, p_entity.getTexture(), &src, &dst, p_entity.getAngle(), 0, SDL_FLIP_VERTICAL);
	}
	else
	{
		SDL_RenderCopyEx(renderer, p_entity.getTexture(), &src, &dst, p_entity.getAngle(), 0, SDL_FLIP_NONE);
	}
}

void RenderWindow::render(int x, int y, SDL_Texture* p_tex)
{
	SDL_Rect src;
	src.x = 0;
	src.y = 0;
	src.w;
	src.h;

	SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h);

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, p_tex, &src, &dst);
}



void RenderWindow::display()
{
	SDL_RenderPresent(renderer);
}