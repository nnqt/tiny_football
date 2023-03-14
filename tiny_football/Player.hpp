#pragma once
#include <iostream>
#include "Entity.hpp"
#include "Utility.hpp"
#include <vector>
#include "ScrollingBG.hpp"

#define DIRECTION_UP 0
#define DIRECTION_DOWN 1
#define DIRECTION_LEFT 2
#define DIRECTION_RIGHT 3
#define DIRECTION_UP_LEFT 4
#define DIRECTION_UP_RIGHT 5
#define DIRECTION_DOWN_LEFT 6
#define DIRECTION_DOWN_RIGHT 7

class Player:public Entity {
public:
	Player(Vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_frame, Vector2f p_scale, SDL_Rect* p_spriteClip);
	~Player();

	void update();
	void nextAnimation();
	int getDirection();
	void updateClip();
	void updatePosition();
	bool checkCollison(std::vector <SDL_Rect>& p_wall);
	void moveBack();
	void shiftColliders();
	SDL_Rect mColliders;
	int currentDirection = DIRECTION_RIGHT;
	int nextDirection = DIRECTION_RIGHT;
	bool isActive = false;
	bool isGoalKeeper = false;
private:
	std::vector <SDL_Rect> clip;
	int countFrame = 0;
	int currentFrameClip = 0;
	int mClip = 0;
	SDL_Rect* spriteClip;

};