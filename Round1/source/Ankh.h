#pragma once
#include "Prizes.h"
class Ankh : public Prizes {
	Vector2f center;
	Vector2f size;

	float xCopy = x;
	float yCopy = y;
public:
	Ankh(std::vector<Entity*>*e, std::vector<Object> &st, AnimationManager&a, int x, int y);
	void Animation(float time);
	void hitAction();
	void update(float time);
	void Collision(int num);
	void draw(RenderWindow &window);
};