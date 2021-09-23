#pragma once
#include <array>
#include "Blocks.h"
class RockBlock : public Blocks {
public:
	class Rock : public Entity{
	public:
		Rock(AnimationManager&r, int x, int y) : Entity(r, x, y){
			life = false;
			w = 8;
			h = 7;
		}
		void Animation(float time){
			if (dir) anim.flip();
			anim.tick(time);
		}
		void update(float time){
			Animation(time);
			dy += 0.0013*time;
			if (dir == 1){
				if (dx<0)dx += 0.0001*time;
				else dx = 0;
			}
			else {
				if (dx>0)dx -= 0.0001*time;
				else dx = 0;
			}
			x += dx*time;
			y += dy*time;
		}
	};
private:
	std::array<Rock, 5> rocks;
public:
	RockBlock(AnimationManager &a, int x, int y, AnimationManager&rock);

	void hitAction();
	void update(float time);
	void draw(RenderWindow &window);
};