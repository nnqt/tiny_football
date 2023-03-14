#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Entity.hpp"
#include "Utility.hpp"

class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(std::string p_filePath, ColorRGB transparent);
	void cleanUp();
	void clear();
	void render(Entity& p_entity);
	void render(int x, int y, SDL_Texture* p_tex);

	void display();
	SDL_Renderer* renderer;
private:
	SDL_Window* window;
};