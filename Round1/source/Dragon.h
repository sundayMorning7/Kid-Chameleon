#pragma once
#include <ctime>
#include "Enemy.h"
class Dragon : public Enemy{
	float timer2 = 0;
	float timer3 = 0;
	void staticCollision(int num, Object&obj);
	void dynamicCollision(int num, Entity* e);
	void deadAction(float time);
public:
	Dragon(std::vector<Entity*>*e, std::vector<Object> &st, AnimationManager &a, int x, int y);
	void Animation(float time);
	void Collision(int num);
	void setAction(float time);
	void update(float time);
	virtual void draw(RenderWindow &window);
};