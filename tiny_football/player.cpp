#include "Player.hpp"

Player::Player(Vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_frame, Vector2f p_scale, SDL_Rect* p_spriteClip) 
	: Entity(p_pos, p_tex, p_frame, p_scale, Vector2f(0, 0))
{
	spriteClip = p_spriteClip;
	mColliders = SDL_Rect{ getPos().x , getPos().y, 16 * getScale().x,16 *getScale().y};
	updateClip();
}

Player::~Player(){}

void Player::nextAnimation() 
{
	if (currentFrameClip < (clip.size()-1)) 
	{
		currentFrameClip++;
	}
	else
	{
		currentFrameClip = 0;
	}
	setCurrentFrame(clip[currentFrameClip]);
}

int Player::getDirection()
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
	else if ((getVelocity().x == 0) && (getVelocity().y == 0))
	{
		return currentDirection;
	}
	else
		return -1;
}

void Player::updateClip() {
	if (nextDirection == DIRECTION_UP)
	{
		mClip = 2;
		currentFrameClip = 0;
		clip.clear();
		clip.push_back(spriteClip[6]);
		clip.push_back(spriteClip[7]);
		setFlipHorizon(false);
		setFlipVertical(false);
	}
	else if (nextDirection == DIRECTION_DOWN)
	{
		mClip = 2;
		currentFrameClip = 0;
		clip.clear();
		clip.push_back(spriteClip[8]);
		clip.push_back(spriteClip[9]);
		setFlipHorizon(false);
		setFlipVertical(false);
	}
	else if (nextDirection == DIRECTION_RIGHT)
	{
		mClip = 4;
		currentFrameClip = 0;
		clip.clear();
		clip.push_back(spriteClip[0]);
		clip.push_back(spriteClip[1]);
		clip.push_back(spriteClip[2]);
		clip.push_back(spriteClip[3]);
		setFlipHorizon(false);
		setFlipVertical(false);
	}
	else if (nextDirection == DIRECTION_LEFT)
	{
		mClip = 4;
		currentFrameClip = 0;
		clip.clear();
		clip.push_back(spriteClip[0]);
		clip.push_back(spriteClip[1]);
		clip.push_back(spriteClip[2]);
		clip.push_back(spriteClip[3]);
		setFlipHorizon(true);
		setFlipVertical(false);
	}
	else if (nextDirection == DIRECTION_UP_LEFT)
	{
		mClip = 2;
		currentFrameClip = 0;
		clip.clear();
		clip.push_back(spriteClip[4]);
		clip.push_back(spriteClip[5]);
		setFlipHorizon(true);
		setFlipVertical(false);
	}
	else if (nextDirection == DIRECTION_UP_RIGHT)
	{
		mClip = 2;
		currentFrameClip = 0;
		clip.clear();
		clip.push_back(spriteClip[4]);
		clip.push_back(spriteClip[5]);
		setFlipHorizon(false);
		setFlipVertical(false);
	}
	else if (nextDirection == DIRECTION_DOWN_LEFT)
	{
		mClip = 4;
		currentFrameClip = 0;
		clip.clear();
		clip.push_back(spriteClip[0]);
		clip.push_back(spriteClip[1]);
		clip.push_back(spriteClip[2]);
		clip.push_back(spriteClip[3]);
		setFlipHorizon(true);
		setFlipVertical(false);
	}
	else if (nextDirection == DIRECTION_DOWN_RIGHT)
	{
		mClip = 4;
		currentFrameClip = 0;
		clip.clear();
		clip.push_back(spriteClip[0]);
		clip.push_back(spriteClip[1]);
		clip.push_back(spriteClip[2]);
		clip.push_back(spriteClip[3]);
		setFlipHorizon(false);
		setFlipVertical(false);
	}
}

void Player::updatePosition()
{
	int x = getPos().x + getSpeed() * getVelocity().x;
	int y = getPos().y + getSpeed() * getVelocity().y;
	setPos(Vector2f(x,y));
}

void Player::moveBack()
{
	int x = getPos().x - getSpeed() * getVelocity().x;
	int y = getPos().y - getSpeed() * getVelocity().y;
	setPos(Vector2f(x, y));
}

void Player::update() {
	nextDirection = getDirection();
	if (nextDirection != currentDirection)
	{
		updateClip();
		currentDirection = nextDirection;
	}
	countFrame++;
	if (countFrame > 6) {
		countFrame = 0;
		nextAnimation();
	}
}

bool Player::checkCollison(std::vector <SDL_Rect>& p_wall)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = mColliders.x;
	rightA =  mColliders.x + mColliders.w;
	topA = mColliders.y;
	bottomA = mColliders.y + mColliders.h;

	std::vector <SDL_Rect> wallColliders = p_wall;

	for (int Bbox = 0; Bbox < wallColliders.size(); Bbox++)
	{
		leftB = wallColliders[Bbox].x;
		rightB = + wallColliders[Bbox].x + wallColliders[Bbox].w;
		topB = + wallColliders[Bbox].y;
		bottomB = + wallColliders[Bbox].y + wallColliders[Bbox].h;

		if (((bottomA <= topB) || (topA >= bottomB) || (rightA <= leftB) || (leftA >= rightB)) == false)
		{
			return true;
		}
	}
	return false;
}

void Player::shiftColliders()
{
	mColliders.x = getPos().x;
	mColliders.y = getPos().y;
}