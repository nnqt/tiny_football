#pragma once
#include "Entity.hpp"
#include "Utility.hpp"

class ScrollingBG : public Entity {
public:
	ScrollingBG(Vector2f p_pos, SDL_Texture* p_tex, SDL_Rect p_frame, Vector2f p_scale) 
		:Entity(p_pos, p_tex, p_frame, p_scale, Vector2f(0, 0)) 
	{
		scrollingOffset = 0;

		mColliders.resize(4);
		//top
		mColliders[0].x = 32 * getScale().x;
		mColliders[0].y = 0 * getScale().y;
		mColliders[0].w = 632 *getScale().x;
		mColliders[0].h = 16 * getScale().y;

		//bottom
		mColliders[1].x = 32 * getScale().x;
		mColliders[1].y = 184 * getScale().y;
		mColliders[1].w = 632 * getScale().x;
		mColliders[1].h = 16 * getScale().y;

		//left
		mColliders[2].x = 24 * getScale().x;
		mColliders[2].y = 16 * getScale().y;
		mColliders[2].w = 8 * getScale().x;
		mColliders[2].h = 168 * getScale().y;

		//right
		mColliders[3].x = 664 * getScale().x;
		mColliders[3].y = 16 * getScale().y;
		mColliders[3].w = 8 * getScale().x;
		mColliders[3].h = 168 * getScale().y;

		for (int set = 0; set < mColliders.size(); ++set) {
			mColliders[set].x += getPos().x;
			mColliders[set].y += getPos().y;
		}

		goalColliders.resize(6);
		//left team: mid
		goalColliders[0].x = 64 * getScale().x;
		goalColliders[0].y = 80 * getScale().y;
		goalColliders[0].w = 8 * getScale().x;
		goalColliders[0].h = 40 * getScale().y;

		//left team: top
		goalColliders[1].x = 64 * getScale().x;
		goalColliders[1].y = 72 * getScale().y;
		goalColliders[1].w = 16 * getScale().x;
		goalColliders[1].h = 8 * getScale().y;

		//left team: bot
		goalColliders[2].x = 64 * getScale().x;
		goalColliders[2].y = 120 * getScale().y;
		goalColliders[2].w = 16 * getScale().x;
		goalColliders[2].h = 8 * getScale().y;

		//right team: mid
		goalColliders[3].x = 624 * getScale().x;
		goalColliders[3].y = 80 * getScale().y;
		goalColliders[3].w = 8 * getScale().x;
		goalColliders[3].h = 40 * getScale().y;

		//right team: top
		goalColliders[4].x = 616 * getScale().x;
		goalColliders[4].y = 72 * getScale().y;
		goalColliders[4].w = 16 * getScale().x;
		goalColliders[4].h = 8 * getScale().y;

		//right team: bot
		goalColliders[5].x = 616 * getScale().x;
		goalColliders[5].y = 120 * getScale().y;
		goalColliders[5].w = 16 * getScale().x;
		goalColliders[5].h = 8 * getScale().y;

		for (int set = 0; set < goalColliders.size(); ++set) {
			goalColliders[set].x += getPos().x;
			goalColliders[set].y += getPos().y;
		}
	};
	~ScrollingBG() {};
	std::vector <SDL_Rect> getMClolliders() {
		return mColliders;
	}
	std::vector <SDL_Rect> mColliders;
	std::vector <SDL_Rect> goalColliders;
private:
	int scrollingOffset;
};