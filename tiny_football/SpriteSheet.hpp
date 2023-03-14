#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Utility.hpp"

class SpriteSheet 
{
public:
	SpriteSheet(std::string p_filePath, ColorRGB transparent_color, SDL_Renderer* renderer);
	~SpriteSheet();

	void render(SDL_Texture* p_texture, Vector2f p_pos, SDL_Renderer* renderer);
private:
	SDL_Texture* mTexture;
};