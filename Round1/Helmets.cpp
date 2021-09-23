#include "source\Helmets.h"
Helmets::Helmets(std::vector<Entity*>*e, float maxV, float minV, 
	float jumpH, float crawlS,float walkS, float downHS, float upHS,
	float bWS, float bCS,float bUHS, float bDHS, float nKPDHS, int maxLifes,
	AnimationManager&a, AnimationManager&lifes, int x, int y) : Prizes(e, a, x, y),
		Max_Velocity(maxV), Min_Velocity(minV),
		jumpHeight(jumpH), crawlSpeed(crawlS), walkSpeed(walkS),
		downHillSpeed(downHS), upHillSpeed(upHS), boostWalkSpeed(bWS),
		boostCrawlSpeed(bCS), boostUpHillSpeed(bUHS), boostDownHillSpeed(bDHS),
		noKeyPressedDownHillSpeed(nKPDHS), Max_Lifes(maxLifes), lifes(Max_Lifes),aLifes(lifes){

}
void Helmets::hitAction(float time){
	std::string hitString = anim.currentAnim + "Hit";
	float prevCurrentFrame = anim.animList[anim.currentAnim].currentFrame;
	if (timer == 0){
		lifes--;
	}
	if (lifes <= 0){ STATE = dead; }

	timer += time;
	if (timer > 1000) {
		hit = false;
		timer = 0;
	}
	else if (timer < 1000){
		if (timer>80 && timer<160 || timer>200 && timer<260 ||
			timer>300 && timer<360 || timer>400 && timer<460 ||
			timer>500 && timer<560 || timer>600 && timer<660 ||
			timer>700 && timer<760 || timer>800 && timer<860 ||
			timer>900 && timer<960) {
			std::string noHitString = hitString.substr(0, hitString.size() - 3);
			anim.set(noHitString);
		}
		else anim.set(hitString);
		anim.animList[anim.currentAnim].currentFrame = prevCurrentFrame;
	}
}
bool Helmets::isHit(){ return hit; }
bool Helmets::isSlowFromSlope(){ return slowFromSlope; }
int Helmets::getLifes(){ return lifes; }
float Helmets::getAddingJump(){ return addingJump; }
AnimationManager& Helmets::getAnimLifes(){ return aLifes; }
int Helmets::getMax_Lifes(){ return Max_Lifes; }
int Helmets::getAmountOfLifes(){ return lifes; }
float Helmets::getMax_Velocity(){ return Max_Velocity; }
float Helmets::getMin_Velocity(){ return Min_Velocity; }
float Helmets::getJumpHeight(){ return jumpHeight; }
float Helmets::getCrawlSpeed(){ return crawlSpeed; }
float Helmets::getWalkSpeed(){ return walkSpeed; }
float Helmets::getDownHillSpeed(){ return downHillSpeed; }
float Helmets::getUpHillSpeed(){ return upHillSpeed; }
float Helmets::getBoostWalkSpeed(){ return boostWalkSpeed; }
float Helmets::getBoostCrawlSpeed(){ return boostCrawlSpeed; }
float Helmets::getBoostUpHillSpeed(){ return boostUpHillSpeed; }
float Helmets::getBoostDownHillSpeed(){ return boostDownHillSpeed; }
float Helmets::getNoKeyPressedDownHillSpeed(){ return noKeyPressedDownHillSpeed; }
int Helmets::getState(){ return STATE; }
void Helmets::setLifes(int l){ lifes = l; }
void Helmets::setState(int i){
	switch (i){
	case 0:STATE = stay; break;
	case 1:STATE = walk; break;
	case 2:STATE = crawl; break;
	case 3:STATE = lie; break;
	case 4:STATE = jump; break;
	case 5:STATE = jumpOver; break;
	case 6:STATE = upHill; break;
	case 7:STATE = downHill; break;
	case 8:STATE = dead; break;
	case 9:STATE = fall; break;
	case 10:STATE = climb; break;
	case 11:STATE = damage; break;
	case 12:STATE = mask; break;
	case 13:STATE = transformation; break;
	}
}
void Helmets::setHit(bool h){ hit = h; }
void Helmets::setAddingJump(float f){ addingJump = f; }
void Helmets::setSlowFromSlope(bool b){ slowFromSlope = b; }
bool Helmets::getKey(std::string s){ return key[s]; }
void Helmets::setKey(std::string a){ key[a] = true; }
