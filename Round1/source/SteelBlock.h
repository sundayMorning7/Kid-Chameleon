#pragma once
#include "Blocks.h"
class SteelBlock : public Blocks {
	int yCopy;
public:
	SteelBlock(AnimationManager &a, int x, int y);
	void hitAction();
	void update(float time);
};
