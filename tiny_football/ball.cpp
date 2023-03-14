#include "Ball.hpp"
#include <math.h>

double distanceSquared(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
}

int Ball::checkCollison(std::vector <SDL_Rect>& p_Rect)
{
	for (int set = 0; set < p_Rect.size(); ++set)
	{
		int cX, cY;
		if (mCollider.x < p_Rect[set].x)
		{
			cX = p_Rect[set].x;
		}
		else if (mCollider.x > p_Rect[set].x + p_Rect[set].w)
		{
			cX = p_Rect[set].x + p_Rect[set].w;
		}
		else
		{
			cX = mCollider.x;
		}
		if (mCollider.y < p_Rect[set].y)
		{
			cY = p_Rect[set].y;
		}
		else if (mCollider.y > p_Rect[set].y + p_Rect[set].h)
		{
			cY = p_Rect[set].y + p_Rect[set].h;
		}
		else
		{
			cY = mCollider.y;
		}
		if (distanceSquared(mCollider.x, mCollider.y, cX, cY) < mCollider.r * mCollider.r)
		{
			return set;
		}
	}

	return -1;
}

bool Ball::checkCollison(SDL_Rect& p_Rect) 
{
	int cX, cY;

	if (mCollider.x < p_Rect.x)
	{
		cX = p_Rect.x;
	}
	else if (mCollider.x > p_Rect.x + p_Rect.w)
	{
		cX = p_Rect.x + p_Rect.w;
	}
	else
	{
		cX = mCollider.x;
	}
	if (mCollider.y < p_Rect.y)
	{
		cY = p_Rect.y;
	}
	else if (mCollider.y > p_Rect.y + p_Rect.h)
	{
		cY = p_Rect.y + p_Rect.h;
	}
	else
	{
		cY = mCollider.y;
	}
	if (distanceSquared(mCollider.x, mCollider.y, cX, cY) < mCollider.r * mCollider.r)
	{
		return true;
	}

	return false;
}

void Ball::shot()
{
	shotFlag = true;
}

int Ball::getDirection()
{
	if ((getVelocity().x == 0) && (getVelocity().y > 0))
	{
		return DIRECTION_DOWN;
	}
	else if ((getVelocity().x == 0) && (getVelocity().y < 0))
	{
		return DIRECTION_UP;
	}
	else if ((getVelocity().x > 0) && (getVelocity().y == 0))
	{
		return DIRECTION_RIGHT;
	}
	else if ((getVelocity().x < 0) && (getVelocity().y == 0))
	{
		return DIRECTION_LEFT;
	}
	else if ((getVelocity().x > 0) && (getVelocity().y > 0))
	{
		return DIRECTION_DOWN_RIGHT;
	}
	else if ((getVelocity().x > 0) && (getVelocity().y < 0))
	{
		return DIRECTION_UP_RIGHT;
	}
	else if ((getVelocity().x < 0) && (getVelocity().y > 0))
	{
		return DIRECTION_DOWN_LEFT;
	}
	else if ((getVelocity().x < 0) && (getVelocity().y < 0))
	{
		return DIRECTION_UP_LEFT;
	}
	else
		return -1;
}

void Ball::updatePos(int p_x, int p_y)
{
	setPos(Vector2f(p_x,p_y));
	mCollider.x = p_x + mCollider.r;
	mCollider.y = p_y + mCollider.r;
}

float fakeMove(float p_speed, float timer) 
{
	p_speed = 16 - timer * timer ;
	if (p_speed < 0)
		return 0;
	return p_speed;
}

void Ball::update() {
	if ((getDirection() != -1) && (shotFlag == true)) {
		if(speed != 0)
		{
			speed = fakeMove(speed, timer);
			timer += 0.1;
			moveForward();
		}
		else {
			shotFlag = false;
			velocity = Vector2f(0, 0);
		}
		return;
	}
	if (shotFlag == true) {
		shotFlag = false;
	}
}

void Ball::moveForward()
{
	int x = getPos().x + speed * getVelocity().x;
	int y = getPos().y + speed * getVelocity().y;
	setPos(Vector2f(x, y));
	mCollider.x = x + mCollider.r;
	mCollider.y = y + mCollider.r;
}

void Ball::moveBack()
{
	int x = getPos().x - speed * getVelocity().x;
	int y = getPos().y - speed * getVelocity().y;
	setPos(Vector2f(x, y));
	mCollider.x = x + mCollider.r;
	mCollider.y = y + mCollider.r;
}