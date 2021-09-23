#pragma once
#include "IronKnight.h"
#include "KidChameleon.h"
class Player
{
private:
	Helmets* helmet;
	AnimationManager kidAnim;
	AnimationManager aKidLifes;
	int emeralds;
	int ankhs;
	int countLifes;
	int addingTime;
public:
	Player(KidChameleon* h);
	~Player();
	void recreateCharacter(KidChameleon*k);
	std::string getName();
	void increaseEmeralds();
	void increaseAnkhs();
	void increaseClocks();
	void decreaseAnkhs();
	
	void setKey(std::string k);
	void setState(int st);
	void setHit(bool b);
	void setX(float i);
	void setY(float i);
	void setDx(float f);
	void setDy(float f);
	void setDir(bool dir);
	void setTimer(float t);
	void setAddingTime(int t);

	AnimationManager& getAnimLifes(){ return helmet->getAnimLifes(); }
	int getCountEmeralds();
	int getCountAnkhs();
	int getLifes();
	int getAddingTime();
	int getState();
	float getX();
	float getY();
	float getDx();
	float getDy();
	bool getKey(std::string s);
	FloatRect getRect();

	int isLife();
	bool isHit();

	void update(float time);

	void changeMask(Helmets* h);
	void draw(RenderWindow &window);
	FloatRect getHitbox();
	void setLife(bool life){
		helmet->setLife(life);
	}
	void setLifes(){
		helmet->setLifes(helmet->getMax_Lifes());
	}
};