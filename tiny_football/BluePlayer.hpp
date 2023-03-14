#pragma once
#include "Player.hpp"

class BluePlayer : public Player {
public:
	BluePlayer(Vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_frame, Vector2f p_scale, SDL_Rect* p_spriteClip)
		:Player(p_pos, p_tex, p_frame, p_scale, p_spriteClip)
	{
		currentDirection = DIRECTION_LEFT;
		nextDirection = DIRECTION_LEFT;
		updateClip();
	}
	~BluePlayer() {};
private:
};
