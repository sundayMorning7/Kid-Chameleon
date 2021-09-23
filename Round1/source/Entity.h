#pragma once
#include "AnimationManager.h"
#include "Level.h"
using namespace sf;
class Entity
{
protected:
	float x, y, dx, dy, w, h;
	std::vector<Object> obj;
	bool life, dir;
	float timer, timer_end;
	std::string Name;
	int Health;
	AnimationManager anim;
public:
	Entity(){}
	Entity(AnimationManager &A, int X, int Y);

	void option(std::string NAME, float SPEED , int HEALTH, std::string FIRST_ANIM);
	virtual void update(float time) = 0;
	virtual void draw(RenderWindow &window);
	
	bool isLife();
	std::string getName();
	float getX();
	float getY();
	float getDx();
	float getDy();
	bool getDir();
	FloatRect getRect();
	AnimationManager& getAnim();
	std::vector<Object>& getObjects();
	
	void setX(float i);
	void setY(float i);
	void setDx(float i);
	void setDy(float i);
	void setDir(bool d);
	void setLife(bool l);
	void setTimer(float t);
};