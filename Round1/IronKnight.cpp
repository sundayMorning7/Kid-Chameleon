#include "source\IronKnight.h"
void IronKnight::solidCollision(int num, Object&obj){
	if (dy > 0 && num == 1)	{ y = obj.rect.top - h;  dy = 0;   if (STATE != mask&&STATE != dead) STATE = stay; }
	if (dy<0 && num == 1)	{ y = obj.rect.top + obj.rect.height;   dy = 0; }
	if (dx>0 && num == 0)	{ x = obj.rect.left - w; if (!dir){ stopRight = true; } else{ dx = 0; } }
	if (dx < 0 && num == 0)	{ x = obj.rect.left + obj.rect.width; if (dir){ stopLeft = true; } else{ dx = 0; } }
}
void IronKnight::downHillCollision(int num, Object& obj){
	FloatRect r = obj.rect;
	int y0 = (x + w / 2 - r.left) * r.height / r.width + r.top - h;
	if (y>y0){
		if (x + w / 2 > r.left)
		{
			y = y0; dy = 0.3;
			if (dir == 0){ if (STATE != mask&&STATE != dead) STATE = downHill; }
			else if (dir == 1){ if (STATE != mask&&STATE != dead) STATE = upHill; }

		}
	}
}
void IronKnight::upHillCollision(int num, Object& obj){
	FloatRect r = obj.rect;
	int y0 = -(x + w / 2 - r.left) * r.height / r.width + r.top + r.height - h;
	if (y > y0){
		if (x + w / 2 < r.left + r.width)
		{
			y = y0; dy = 0.7;
			if (dir == 0) { if (STATE != mask&&STATE != dead) STATE = upHill; }
			else if (dir == 1) { if (STATE != mask&&STATE != dead) STATE = downHill; }
		}
	}
}
void IronKnight::prizeBlockCollision(int num){
	Blocks* block = nullptr;
	block = dynamic_cast<Blocks*>(*it);
	if (dy > 0 && num == 1)	{ y = (*it)->getRect().top - h;  dy = 0;   STATE = stay; }
	if (dy<0 && num == 1)	{ y = (*it)->getRect().top + (*it)->getRect().height;   dy = 0; block->setHit(true); }
	if (dx>0 && num == 0)	{
		dx = 0;
		x = (*it)->getRect().left - 20;
	}
	if (dx < 0 && num == 0)	{
		dx = 0;
		x = ((*it)->getRect().left + (*it)->getRect().width - 10);
	}
}
void IronKnight::steelBlockCollision(int num){
	Blocks* block = nullptr;
	block = dynamic_cast<Blocks*>(*it);
	if (dy > 0 && num == 1)	{ y = block->getRect().top - h;  dy = 0;  if (STATE != mask&&STATE != dead) STATE = stay; }
	if (dy<0 && num == 1)	{ y = block->getRect().top + block->getRect().height;   dy = 0; block->setHit(true); }
	if (dx>0 && num == 0)	{
		x = block->getRect().left - 20;
		if (!dir){ stopRight = true; }
		else{ dx = 0; }
	}
	if (dx < 0 && num == 0)	{
		x = block->getRect().left + block->getRect().width - 10;
		if (dir){ stopLeft = true; }
		else{ dx = 0; }
	}
}
void IronKnight::rubberBlockCollision(int num){
	Blocks* block = nullptr;
	block = dynamic_cast<Blocks*>(*it);
	if (dy > 0 && num == 1)	{
		if (dy > 0.2){
			block->setHit(true);
			y = block->getRect().top - h;
			dy = dy*(-1) + 0.005;
		}
		else if (dy < 0.2){
			y = block->getRect().top - h;
			STATE = stay;
			dy = 0;
		}
	}
	else if (dy<0 && num == 1)	{ y = block->getRect().top + block->getRect().height;   dy = 0; block->setHit(true); }
	if (dx>0 && num == 0)	{ x = block->getRect().left - w; dx *= -1; block->setHit(true); }
	else if (dx < 0 && num == 0)	{ x = block->getRect().left + block->getRect().width;  dx *= -1; block->setHit(true); }
}
void IronKnight::zebraCollision(int num){
	Blocks* block = nullptr;
	block = dynamic_cast<Blocks*>(*it);
	if (dy > 0 && num == 1)	{ y = (*it)->getRect().top - h;     STATE = stay; if (dy > 0.3){ block->setHit(true); /*dy = 0.15;*/ } /*else if (dy < 0.3){ dy = 0; }*/ dy = 0; }
	if (dy<0 && num == 1)	{ y = (*it)->getRect().top + (*it)->getRect().height;   dy = 0; block->setHit(true); }
	if (dx>0 && num == 0)	{
		dx = 0;
		x = (*it)->getRect().left - 20;
	}
	if (dx < 0 && num == 0)	{
		dx = 0;
		x = ((*it)->getRect().left + (*it)->getRect().width - 10);
	}
}

IronKnight::IronKnight(std::vector<Entity*>*e, std::vector<Object> &st, AnimationManager&a, AnimationManager&lifes, int x, int y) :
Helmets(e, -0.007, -0.002, -0.3, 0.07, 0.1, 0.1,
0.05, 0.15, 0.07, 0.14, 0.2, 0.05, 5, a, lifes, x, y) {
	obj.reserve(st.size());//obj статические
	obj.insert(obj.end(), st.begin(), st.end());
	obj.shrink_to_fit();

	option("IronKnight", 0, 100, "mask");
	STATE = mask;
	w = 20;
	h = 32;

	anim.animList["transformation"].loop = 0;
	anim.animList["mask"].loop = 0;
	anim.animList["dead"].loop = 0;
}
FloatRect IronKnight::getHitbox(){ return FloatRect(x + 10, y, 10, h); }
void IronKnight::Keyboard()
{
	if (key["R"])
	{
		dir = 0;
		if (STATE == stay) STATE = walk;
		if (STATE == slide&&!key["L"]){
			if (dx < 0){
				dx += 0.005;
			}
			else {
				STATE = walk;
			}
		}
		if (STATE == walk){
			if (dx < 0 && !key["L"]){
				STATE = slide;
				dx += 0.005;
			}
			else if (dx >= 0 && dx + 0.005 < walkSpeed) {
				dx += 0.005;
			}
		}
		if (STATE == jump || STATE == fall){
			if (dx < 0){
				dx += 0.005;
			}
			else if (dx >= 0 && dx + 0.005 < walkSpeed) {
				dx += 0.005;
			}
		}
		if (STATE == downHill){ dx = downHillSpeed; }
		if (STATE == upHill){ dx = upHillSpeed; }
	}
	if (key["L"])
	{

		dir = 1;
		if (STATE == stay) {
			STATE = walk;
		}
		if (STATE == slide){
			if (dx > 0){
				dx -= 0.005;
			}
			else{
				STATE = walk;
			}
		}
		if (STATE == walk){
			if (dx > 0){
				STATE = slide;
				dx -= 0.005;
			}
			else if (dx <= 0 && dx - 0.005 > -walkSpeed) {
				dx -= 0.005;
			}
		}

		if (STATE == jump || STATE == fall){
			if (dx > 0){
				dx -= 0.005;
			}
			else if (dx <= 0 && dx - 0.005 > -walkSpeed) {
				dx -= 0.005;
			}
		}
		if (STATE == downHill){ dx = -downHillSpeed; }
		if (STATE == upHill){ dx = -upHillSpeed; }
	}
	if (key["X"])
	{

		if (STATE == stay || STATE == walk || STATE == upHill || STATE == downHill){
			STATE = jump;
			dy = jumpHeight;
			addingJump = 0;
		}
		if (STATE == jump){
			if (addingJump >= Max_Velocity){ addingJump = Max_Velocity; }
			else if (addingJump < Min_Velocity){ addingJump = Min_Velocity; }
			else { addingJump -= 0.02; }
			dy += addingJump;
		}
	}
	if (key["Down"])
	{
		if (STATE == stay || STATE == walk || STATE == crawl || STATE == lie) {

			if (key["L"]){
				dx = -crawlSpeed;
				dir = 1;
				STATE = crawl;
			}
			else if (key["R"]){
				dx = crawlSpeed;
				dir = 0;
				STATE = crawl;
			}
			else{
				STATE = lie;
			}
		}
	}if (key["Z"]){
		if (STATE == walk&&abs(dx) >= walkSpeed - 0.005){
			if (dir == 0){
				if (dx + 0.002 < boostWalkSpeed){
					dx += 0.002;
				}
				else{
					dx = boostWalkSpeed;
				}
			}
			else{
				if (dx - 0.002 > -boostWalkSpeed){
					dx -= 0.002;
				}
				else{
					dx = -boostWalkSpeed;
				}
			}
		}
		else if (STATE == upHill){
			if (dir == 1) dx = -boostUpHillSpeed;
			else dx = boostUpHillSpeed;
		}
		else if (STATE == downHill){
			if (dir == 1) dx = -boostDownHillSpeed;
			else dx = boostDownHillSpeed;
		}

	}
	if (key["C"]){

	}


	/////////////////////если клавиша отпущена///////////////////////////
	if (!(key["R"] || key["L"]))
	{
		//slowFromSlope = true;
		if (STATE == slide&&dx == 0)STATE = stay;//при прекращении slide
		if (STATE == stay) {//пошаговая остановка
			if (dx != 0){
				STATE = walk;
			}
		}
		if (STATE != fall && STATE != jump){
			if (dx > 0){//продолжение slide без нажатия клавишь ПО инерции
				if (dx - 0.01 > 0)
					dx -= 0.01;
				else dx = 0;
			}
			else if (dx < 0){
				if (dx + 0.01 < 0)
					dx += 0.01;
				else dx = 0;
			}
		}


		if (STATE == downHill){
			if (dir == 1){ dx = -noKeyPressedDownHillSpeed; }
			else { dx = noKeyPressedDownHillSpeed; }
		}
		if (STATE == upHill){
			STATE = downHill;
			if (dir == 1){ dir = 0; dx = noKeyPressedDownHillSpeed; }
			else { dir = 1; dx = -noKeyPressedDownHillSpeed; }
		}

	}
	if (!key["Down"])
	{
		if (STATE == lie) STATE = stay;
		if (STATE == crawl) STATE = walk;
	}
	if (!key["Z"]){
		if (STATE == walk){//постепенное уменьшение скорости до скорости ходьбы
			if (dir == 0){
				if (dx > walkSpeed){
					dx -= 0.002;
				}
			}
			else{
				if (dx < -walkSpeed){
					dx += 0.002;
				}
			}
		}
	}
	if (!key["C"]){

	}

	if (STATE != jump&&STATE != fall){
		if (stopLeft){
			STATE = stay;
			stopLeft = false;
		}
		if (stopRight){
			STATE = stay;
			stopRight = false;
		}
	}
	key["R"] = key["L"] = key["X"] = key["Down"] = key["Z"] = key["C"] = false;
	if (dy > 0 && STATE != upHill && STATE != downHill &&STATE != mask&&STATE != transformation) STATE = fall;
	if (dy < 0 && STATE != upHill && STATE != downHill&&STATE != mask&&STATE != transformation) STATE = jump;


}
void IronKnight::Animation(float time)
{
	if (STATE == stay) { anim.set("stay"); }
	if (STATE == walk) { if (anim.currentAnim != "walk"){ anim.set("walk"); if (!hit){ anim.animList[anim.currentAnim].currentFrame = 0; } } else{ anim.set("walk");  anim.animList[anim.currentAnim].speed = (abs(dx / 8)); } }
	if (STATE == lie) { anim.set("lie"); }
	if (STATE == crawl) { anim.set("crawl"); anim.animList[anim.currentAnim].speed = (abs(dx / 8)); }
	if (STATE == jump) { anim.set("jump"); }
	if (STATE == upHill) { anim.set("upHill"); if (abs(dx) < 0.07){ anim.animList[anim.currentAnim].speed = 0.014; } else if (abs(dx) < 0.15){ anim.animList[anim.currentAnim].speed = 0.018; } }
	if (STATE == downHill) { anim.set("downHill"); if (abs(dx) < 0.07){ anim.animList[anim.currentAnim].speed = 0.014; } else if (abs(dx) < 0.15){ anim.animList[anim.currentAnim].speed = 0.019; } else{ anim.animList[anim.currentAnim].speed = 0.022; } }
	if (STATE == dead) {
		anim.set("dead");
		dx = 0; dy = 0;
		if (!anim.animList[anim.currentAnim].isPlaying)
			life = false;
	}
	if (STATE == fall) anim.set("fall");
	if (STATE == climb) anim.set("climb");
	if (STATE == transformation){
		dx = 0;
		dy = 0;
		anim.set("transformation");
		if (!anim.isPlaying()){
			STATE = stay;
		}
	}
	if (STATE == slide){ anim.set("walk"); }
	if (hit) {
		hitAction(time);
	}
	if (dir) anim.flip();
	anim.tick(time);
	switch (lifes){
	case 5:aLifes.set("full"); break;
	case 4:aLifes.set("four"); break;
	case 3:aLifes.set("three"); break;
	case 2:aLifes.set("two"); break;
	case 1:aLifes.set("one"); break;
	case 0:aLifes.set("zero"); break;
	}
	aLifes.tick(time);
}
void IronKnight::Collision(int num)
{
	for (int i = 0; i < obj.size(); i++){
		if (getRect().intersects(obj[i].rect))
		{
			if (obj[i].name == "solid"){ solidCollision(num, obj[i]); if (STATE == mask){ landed = true; } }
			else if (obj[i].name == "downHill"){ downHillCollision(num, obj[i]); }
			else if (obj[i].name == "upHill"){ upHillCollision(num, obj[i]); }
		}
	}
	//цикл динам обьектов
	for (it = entities->begin(); it != entities->end();){
		if (((*it)->getName() == "zebraItem") && getHitbox().intersects((*it)->getRect()) && STATE != mask){ zebraCollision(num); }
		else if (((*it)->getName() == "steelBlock") && getHitbox().intersects((*it)->getRect())){ steelBlockCollision(num); }
		else if (((*it)->getName() == "prizeBlock") && getHitbox().intersects((*it)->getRect()) && STATE != mask){ prizeBlockCollision(num); }
		else if (((*it)->getName() == "rubberBlock") && getHitbox().intersects((*it)->getRect())){ rubberBlockCollision(num); }
		else it++;
	}
}
void IronKnight::update(float time){
	if (!landed){
		Keyboard();
		Animation(time);
		if (STATE == mask)
			dy += 0.0005*time;
		else if (STATE != transformation&&STATE != dead)
			dy += 0.001*time;


		x += dx*time;
		Collision(0);

		y += dy*time;
		Collision(1);
	}
}
void IronKnight::draw(RenderWindow &window)
{
	if (STATE == upHill){ if (dir == 0){ anim.draw(window, x - 6, y + h); } else anim.draw(window, x - 2, y + h); }
	else if (STATE == downHill){ if (dir == 0){ anim.draw(window, x - 10, y + h); } else anim.draw(window, x + 6, y + h); }
	else if (STATE == dead){
		switch ((int)anim.animList[anim.currentAnim].currentFrame){
		case 0:{anim.draw(window, x - 6, y + h + 9); break; }
		case 1:{anim.draw(window, x - 6, y + h + 14); break; }
		case 2:{anim.draw(window, x - 6, y + h + 9); break; }
		case 3:{anim.draw(window, x - 6, y + h + 14); break; }
		case 4:{anim.draw(window, x - 6, y + h + 9); break; }
		case 5:{anim.draw(window, x - 9, y + h + 6); break; }
		case 6:{anim.draw(window, x - 6, y + h + 9); break; }
		case 7:{anim.draw(window, x - 9, y + h + 6); break; }
		case 8:{anim.draw(window, x - 6, y + h + 9); break; }
		case 9:{anim.draw(window, x - 9, y + h + 6); break; }
		case 10:{anim.draw(window, x - 6, y + h + 9); break; }
		case 11:{anim.draw(window, x - 9, y + h + 6); break; }
		case 12:{anim.draw(window, x - 6, y + h + 9); break; }
		case 13:{anim.draw(window, x - 3, y + h + 9); break; }
		case 14:{anim.draw(window, x - 6, y + h + 9); break; }
		case 15:{anim.draw(window, x - 3, y + h + 9); break; }
		}
	}
	else if (STATE == transformation){
		switch ((int)anim.animList[anim.currentAnim].currentFrame){
		case 0:{anim.draw(window, x - 6, y + h + 6); break; }
		case 1:{anim.draw(window, x - 9, y + h + 6); break; }
		case 2:{anim.draw(window, x - 6, y + h + 6); break; }
		case 3:{anim.draw(window, x - 9, y + h + 6); break; }
		case 4:{anim.draw(window, x - 12, y + h + 3); break; }
		case 5:{anim.draw(window, x - 9, y + h + 6); break; }
		case 6:{anim.draw(window, x - 12, y + h + 3); break; }
		case 7:{anim.draw(window, x - 9, y + h + 6); break; }
		case 8:{anim.draw(window, x - 12, y + h + 3); break; }
		case 9:{anim.draw(window, x - 9, y + h + 6); break; }
		case 10:{anim.draw(window, x - 12, y + h + 3); break; }
		case 11:{anim.draw(window, x - 8, y + h + 12); break; }
		}
	}
	else{
		anim.draw(window, x, y + h);
	}
}