#pragma once
#include "Dragon.h"
class EnemyFactory{
private:
	std::vector<Entity*>*entities;
	std::vector<Object> obj;

	Texture tDragon;
	AnimationManager dragon;
public:
	EnemyFactory(std::vector<Entity*>*e, std::vector<Object> &st);
	Enemy* makeEnemy(std::string name, int x, int y);
};

