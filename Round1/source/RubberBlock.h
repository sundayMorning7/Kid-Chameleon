#pragma once
#include "Blocks.h"
class RubberBlock : public Blocks {
public:
	RubberBlock(AnimationManager &a, int x, int y);
	void hitAction();
	void update(float time);
	virtual void draw(RenderWindow &window);
};