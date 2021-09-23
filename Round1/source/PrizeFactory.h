#pragma once
#include "Ankh.h"
#include "Emerald.h"
#include "IronKnight.h"
#include "KidChameleon.h"
#include "Clock.h"
class PrizeFactory{
private:
	std::vector<Entity*>*entities;
	std::vector<Object> obj;

	Texture tCharacterSprites;
	Texture tAnkh;
	Texture tEmerald;
	Texture tClock;

	AnimationManager ironKnight;
	AnimationManager kidChameleon;
	AnimationManager ankh;
	AnimationManager emerald;
	AnimationManager clock;

	Texture tKidLifes;
	AnimationManager aKidLifes;
	Texture tIronLifes;
	AnimationManager aIronLifes;
public:
	PrizeFactory(std::vector<Entity*>*e, std::vector<Object> &st);
	Prizes* makePrize(std::string name, int x, int y);
};

