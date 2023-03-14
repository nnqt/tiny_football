#include "Entity.hpp"
#include <SDL.h>
#include <SDL_image.h>

Entity::Entity(Vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_frame_rect, Vector2f p_scale, Vector2f p_velocity)
	:pos(p_pos), tex(p_tex), angle(0), scale(p_scale), velocity(p_velocity)
{
	currentFrame.x = p_frame_rect.x;
	currentFrame.y = p_frame_rect.y;
	currentFrame.w = p_frame_rect.w;
	currentFrame.h = p_frame_rect.h;
}

void Entity::setAngle(float p_angle)
{
	angle = p_angle;
}

void Entity::setPos(Vector2f p_pos)
{
	pos.x = p_pos.x;
	pos.y = p_pos.y;
}

void Entity::setScale(Vector2f p_scale)
{
	scale.x = p_scale.x;
	scale.y = p_scale.y;
}

void Entity::setCurrentFrame(SDL_Rect p_rect)
{
	currentFrame.x = p_rect.x;
	currentFrame.y = p_rect.y;
	currentFrame.w = p_rect.w;
	currentFrame.h = p_rect.h;
}

SDL_Texture* Entity::getTexture()
{
	return tex;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}

void Entity::setVelocity(Vector2f p_v)
{
	velocity.x = p_v.x;
	velocity.y = p_v.y;
}

Vector2f Entity::getVelocity()
{
	return velocity;
}

void Entity::setFlipHorizon(bool p_exp) 
{
	flipHorizon = p_exp;
}

void Entity::setFlipVertical(bool p_exp)
{
	flipVertical = p_exp;
}

void Entity::setSpeed(int p_speed)
{
	speed = p_speed;
}
