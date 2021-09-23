#pragma once
#include "Entity.h"
class Blocks : public Entity{
protected:
	bool hit;
public:
	Blocks(AnimationManager &A, int X, int Y) :Entity(A, X, Y){}
	virtual void hitAction() = 0;

	bool getHit(){ return hit; }
	void setHit(bool b){ hit = b; }
};