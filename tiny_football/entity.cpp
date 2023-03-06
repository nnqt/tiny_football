#include "Entity.hpp"
#include <SDL.h>
#include <SDL_image.h>

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex)
	:pos(p_pos), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 0;
	currentFrame.h = 0;
}

void Entity::setAngle(float p_angle)
{
	angle = p_angle;
}


SDL_Texture* Entity::getTexture()
{
	return tex;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}