#pragma once
#include "Entity.h"
class Flag : public Entity {
public:
	Flag(AnimationManager &a, int x, int y);
	void update(float time);
};