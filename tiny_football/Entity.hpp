#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include "Math.hpp"

class Entity
{
public:
	Entity(Vector2f p_pos, SDL_Texture* p_tex);

	Vector2f& getPos()
	{
		return pos;
	}

	float getAngle()
	{
		return angle;
	}

	void setAngle(float p_angle);
	SDL_Texture* getTexture();
	SDL_Rect getCurrentFrame();
private:
	Vector2f pos;
	float angle;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};
