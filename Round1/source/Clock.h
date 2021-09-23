#pragma once
#include "Prizes.h"
namespace MyClock{
	class Clock : public Prizes {
		Vector2f center;
		Vector2f size;

		float xCopy = x;
		float yCopy = y;
	public:
		Clock(std::vector<Entity*>*e, std::vector<Object> &st, AnimationManager&a, int x , int y);
		void Animation(float time);
		void hitAction();
		void update(float time);
		void Collision(int num);
		void draw(RenderWindow &window);
	};
}