#pragma once
#include "Helmets.h"
class KidChameleon : public Helmets{
	void solidCollision(int num,Object&obj);
	void downHillCollision(int num, Object& obj);
	void upHillCollision(int num, Object& obj);
	void zebraCollision(int num);
	void prizeBlockCollision(int num);
	void steelBlockCollision(int num);
	void rubberBlockCollision(int num);
	void jumpOverCase(Blocks* bl,bool dir);
	
	int died;
public:
	KidChameleon(std::vector<Entity*>*e, std::vector<Object> &st, AnimationManager&a, AnimationManager&lifes, int x = 0, int y = 0);
	FloatRect getHitbox();
	void Keyboard();
	void Animation(float time);
	void deadAction(float time);
	void Collision(int num);
	void update(float time);
	virtual void draw(RenderWindow &window);
};