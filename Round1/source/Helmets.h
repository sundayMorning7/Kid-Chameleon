#pragma once
#include "Prizes.h"
class Helmets : public Prizes{
protected:
	const float walkSpeed;
	const float boostWalkSpeed;
	const int Max_Lifes;
	const float Max_Velocity;
	const float Min_Velocity;
	const float jumpHeight;
	const float downHillSpeed;
	const float upHillSpeed;
	const float crawlSpeed;
	const float boostCrawlSpeed;
	const float boostUpHillSpeed;
	const float boostDownHillSpeed;
	const float noKeyPressedDownHillSpeed;
	int lifes;
	bool  hit, slowFromSlope, stopLeft, stopRight;
	float addingJump = 0.f;
	std::map<std::string, bool> key;
	enum { stay, walk, crawl, lie, jump, jumpOver, upHill, downHill, dead, fall, climb, damage, mask, transformation,slide } STATE;
	AnimationManager aLifes;
public:
	Helmets(std::vector<Entity*>*e, float maxV, float minV, float jumpH, float crawlS,
		float walkS, float downHS, float upHS, float bWS, float bCS,
		float bUHS, float bDHS, float nKPDHS, int maxLifes,
		AnimationManager&a, AnimationManager&lifes, int x, int y);
	virtual FloatRect getHitbox() = 0;
	virtual void update(float time) = 0;
	virtual void Collision(int num) = 0;
	virtual void Animation(float time) = 0;
	virtual void Keyboard() = 0;
	void hitAction(float time);
	bool isHit();
	bool isSlowFromSlope();
	int getLifes();
	float getAddingJump();
	AnimationManager& getAnimLifes();
	int getMax_Lifes();
	int getAmountOfLifes();
	float getMax_Velocity();
	float getMin_Velocity();
	float getJumpHeight();
	float getCrawlSpeed();
	float getWalkSpeed();
	float getDownHillSpeed();
	float getUpHillSpeed();
	float getBoostWalkSpeed();
	float getBoostCrawlSpeed();
	float getBoostUpHillSpeed();
	float getBoostDownHillSpeed();
	float getNoKeyPressedDownHillSpeed();
	int getState();
	void setLifes(int l);
	void setState(int i);
	void setHit(bool h);
	void setAddingJump(float f);
	void setSlowFromSlope(bool b);
	bool getKey(std::string s);
	void setKey(std::string a);
};