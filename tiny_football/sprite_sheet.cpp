#include "SpriteSheet.hpp"
#include <iostream>

SpriteSheet::SpriteSheet(std::string p_filePath, ColorRGB transparent_color, SDL_Renderer* renderer)
{	
	SDL_Surface* loadedSurface = IMG_Load(p_filePath.c_str());
	mTexture = NULL;

	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", p_filePath.c_str(), IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, transparent_color.red, transparent_color.green, transparent_color.blue));

		mTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", p_filePath.c_str(), SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}

}

SpriteSheet::~SpriteSheet() {
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}
}