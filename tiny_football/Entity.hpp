#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "Utility.hpp"

class Entity
{
public:
	Entity(Vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_frame_rect, Vector2f p_scale, Vector2f p_velocity);

	Vector2f getPos()
	{
		return pos;
	}
	float getAngle()
	{
		return angle;
	}
	Vector2f getScale()
	{
		return scale;
	}
	void setPos(Vector2f p_pos);
	void setAngle(float p_angle);
	void setScale(Vector2f p_scale);
	void setCurrentFrame(SDL_Rect p_rect);
	SDL_Texture* getTexture();
	SDL_Rect getCurrentFrame();
	void setVelocity(Vector2f p_v);
	Vector2f getVelocity();
	bool checkFlipHorizon() 
	{
		return flipHorizon;
	}
	bool checkFlipVertical()
	{
		return flipVertical;
	}
	void setFlipHorizon(bool p_exp);
	void setFlipVertical(bool p_exp);
	void setSpeed(int p_speed);
	int getSpeed()
	{
		return speed;
	}
	Vector2f velocity;
private:
	int speed = 10;
	Vector2f pos;
	float angle ;
	Vector2f scale ;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
	bool flipHorizon = false;
	bool flipVertical = false;
};
