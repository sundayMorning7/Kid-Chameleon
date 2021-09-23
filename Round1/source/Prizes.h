#pragma once
#include "Blocks.h"
class Prizes : public Entity {
protected:
	bool landed;
	bool hit;
	std::vector<Entity*>*entities;//динамические обьекты
	std::vector<Entity*>::iterator it;
public:
	Prizes(std::vector<Entity*>*e,AnimationManager &a, int x, int y) : Entity(a, x, y),entities(e){}
	std::vector<Entity*>* getEntities(){ return entities; }
	void setHit(bool b){ hit = b; }
	bool getHit(){ return hit; }
	void setLanded(bool b){ landed = b; }
};