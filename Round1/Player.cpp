#include "source\Player.h"
Player::Player(KidChameleon* h) : helmet(h),kidAnim(helmet->getAnim()),
aKidLifes(helmet->getAnimLifes()),ankhs(3),
countLifes(helmet->getLifes()){}
Player::~Player(){
	delete helmet;
}
void Player::increaseEmeralds(){ emeralds++; }
void Player::increaseAnkhs(){ ankhs++; }
void Player::increaseClocks(){ addingTime += 180; }
void Player::decreaseAnkhs(){ ankhs--;; }

int Player::getCountEmeralds(){ return emeralds; }
int Player::getLifes(){ return countLifes; }
int Player::getCountAnkhs(){ return ankhs; }
int Player::getAddingTime(){ return addingTime; }
void Player::setDir(bool dir){ helmet->setDir(dir); }
void Player::setTimer(float t){ helmet->setTimer(t); }
void Player::setAddingTime(int t){ addingTime = t; }
int Player::isLife(){
	return helmet->isLife();
}
void Player::recreateCharacter(KidChameleon*k){
	delete helmet;
	helmet = k;
}
void Player::update(float time){
	if (!helmet->isLife()){
		if (helmet->getName() != "KidChameleon"){
			changeMask(new KidChameleon(helmet->getEntities(), helmet->getObjects(), kidAnim, aKidLifes));
			helmet->setHit(true);
			helmet->setTimer(1);
		}		
	}
	helmet->update(time);
}
std::string Player::getName(){ return helmet->getName(); }
void Player::setKey(std::string k){ helmet->setKey(k); }
bool Player::getKey(std::string s){ return helmet->getKey(s); }
bool Player::isHit(){ return helmet->isHit(); }
void Player::setHit(bool b){ helmet->setHit(b); }
int Player::getState(){ return helmet->getState(); }
void Player::setState(int st){ helmet->setState(st); }
FloatRect Player::getRect(){ return helmet->getRect(); }
float Player::getX(){ return helmet->getX(); }
float Player::getY(){ return helmet->getY(); }
float Player::getDx(){ return helmet->getDx(); }
float Player::getDy(){ return helmet->getDy(); }
void Player::setX(float i){ helmet->setX(i); }
void Player::setY(float i){ helmet->setY(i); }
void Player::setDx(float f){ return helmet->setDx(f); }
void Player::setDy(float f){ return helmet->setDy(f); }
void Player::changeMask(Helmets* h){
	if (helmet->getName() == h->getName()){//если та же маска то просто увеличиваем жизни до максимума
		helmet->setLifes(helmet->getMax_Lifes());
		delete h;
	}
	else{//проигрывается анимация смены маски затем helmet = h;
		h->setDir(helmet->getDir());
		h->setX(helmet->getX());
		h->setY(helmet->getY());
		h->setState(13);
		if (dynamic_cast<KidChameleon*>(h)){
			h->setState(0);
		}
		delete helmet;
		helmet = h;
	}
}
void Player::draw(RenderWindow &window)
{
	helmet->draw(window);
}
FloatRect Player::getHitbox(){ return helmet->getHitbox(); }