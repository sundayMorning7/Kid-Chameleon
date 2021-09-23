#pragma once
#include "Blocks.h"
#include <time.h>
class Enemy : public Entity
{
protected:
	bool hit;
	std::vector<Entity*>*entities;//динамические обьекты
	std::vector<Entity*>::iterator it;
	enum{walk,attack,dead}STATE;
public:
	Enemy(std::vector<Entity*>*e,AnimationManager &a, int x, int y) : Entity(a, x, y),entities(e){}
	void setHit(bool b){ hit = b; }
	bool getHit(){ return hit; }
};