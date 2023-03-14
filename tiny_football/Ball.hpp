#pragma once
#include "Entity.hpp"
#include "Player.hpp"
#include "ScrollingBG.hpp"
#include "Utility.hpp"

#define DIRECTION_UP 0
#define DIRECTION_DOWN 1
#define DIRECTION_LEFT 2
#define DIRECTION_RIGHT 3
#define DIRECTION_UP_LEFT 4
#define DIRECTION_UP_RIGHT 5
#define DIRECTION_DOWN_LEFT 6
#define DIRECTION_DOWN_RIGHT 7

class Ball : public Entity {
public:
	Ball(Vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_frame, Vector2f p_scale)
		:Entity(p_pos, p_tex, p_frame, p_scale, Vector2f(0, 0)) 
	{
		mCollider.r = 3 * getScale().x;
		mCollider.x = getPos().x + mCollider.r;
		mCollider.y = getPos().y + mCollider.r;

	}
	~Ball() {};
	bool checkCollison(SDL_Rect& p_player);
	int checkCollison(std::vector <SDL_Rect>& p_Rect);
	void shot();
	void updatePos(int x, int y);
	int getDirection();
	void update();
	void moveForward();
	void moveBack();

	float speed = 0;
	float timer = 0;
	Circle mCollider;
	int currentDirection = -1;
	int nextDirection = -1;
	bool shotFlag = false;
private:
};