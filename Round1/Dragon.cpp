#include "source\Dragon.h"
Dragon::Dragon(std::vector<Entity*>*e, std::vector<Object> &st, AnimationManager &a, int x, int y) :Enemy(e, a, x, y)
{
	std::srand(std::time(NULL));
	option("enemy", 0, 15, "walk");

	obj.reserve(st.size());//obj статические
	obj.insert(obj.end(), st.begin(), st.end());
	obj.shrink_to_fit();
	anim.animList["attack"].loop = false;
	dir = 1;
}

void Dragon::Animation(float time)
{
	if (STATE == walk) anim.set("walk");
	if (STATE == attack) { anim.set("attack"); anim.play(); }
	if (STATE == dead) { anim.set("dead"); }
	if (!dir) anim.flip();

	anim.tick(time);
}
void Dragon::staticCollision(int num, Object&obj){
	if (dy>0 && num == 1)	{ y = obj.rect.top - h;  dy = 0; }
	else if (dy<0 && num == 1)	{ y = obj.rect.top + obj.rect.height;   dy = 0; }
	if (dx>0 && num == 0)	{ dir = 1; }
	else if (dx < 0 && num == 0)	{ dir = 0; }
}
void Dragon::dynamicCollision(int num, Entity*e)
{
	Blocks *block = nullptr;
	block = dynamic_cast<Blocks*>(e);
	if (dy > 0 && num == 1)	{ y = block->getRect().top - h;  dy = 0; }
	else if (dy<0 && num == 1)	{ y = block->getRect().top + block->getRect().height;   dy = 0; }
	if (dx>0 && num == 0)	{ x = block->getRect().left - w; dir = 1; }
	else if (dx < 0 && num == 0)	{ x = block->getRect().left + block->getRect().width;  dir = 0; }
}
void Dragon::Collision(int num)
{
	//статическая коллизия
	for (int i = 0; i<obj.size(); i++){
		if (getRect().intersects(obj[i].rect))
		{
			if (obj[i].name == "solid"  || 
				obj[i].name == "upHill" ||
				obj[i].name == "downHill") { staticCollision(num, obj[i]); }
		}
	}
	//динамическая коллизия
	for (it = entities->begin(); it != entities->end();){
		if ((((*it)->getName() == "steelBlock")
			|| ((*it)->getName() == "rockBlock")
			|| ((*it)->getName() == "rubberBlock")
			|| ((*it)->getName() == "prizeBlock"))
			&& getRect().intersects((*it)->getRect())) {
			dynamicCollision(num, (*it));
		}
		else it++;
	}
}
void Dragon::setAction(float time){
	timer += time;
	timer2 += time;
	bool randNumber = rand() % 2;
	if (timer > 10000){
		timer = 0;
		if (STATE != attack){
			STATE = attack; dx = 0;
		}
	}
	else if (timer < 10000){
		if (STATE != attack){
			STATE = walk;
			if (dir)
				dx = -0.04;
			else dx = 0.04;
		}
	}
	if (STATE == attack && anim.isPlaying() == false){
		STATE = walk;
		if (dir)
			dx = -0.04;
		else dx = 0.04;
	}
	if (timer2 > 4000){
		timer2 = 0;
		if (randNumber&&STATE == walk) {
			if (dir){
				dir = 0;
				dx = 0.04;
			}
			else { dir = 1; dx = -0.04; }
		}
	}
}
void Dragon::deadAction(float time){
	timer3 += time;
	if (timer3 < 3500){
		STATE = dead;
		dx = 0;
	}
	else{
		life = false;
	}
}
void Dragon::update(float time)
{
	if (!hit)setAction(time);
	Animation(time);
	x += dx*time;
	Collision(0);

	dy += 0.00058*time;
	y += dy*time;
	Collision(1);

	if (hit) {
		deadAction(time);
	}
	anim.tick(time);
}
void Dragon::draw(RenderWindow &window)
{
	if (STATE == attack){
		if (dir == 1){
			switch ((int)anim.animList[anim.currentAnim].currentFrame){
			case 0:case 3:case 6:case 9:case 12:case 15:	{anim.draw(window, x - 20, y + h); break; }
			case 1:case 4:case 7:case 10:case 13:case 16:	{anim.draw(window, x - 18, y + h); break; }
			case 2:case 5:case 8:case 11:case 14:case 17:	{anim.draw(window, x - 15, y + h); break; }
			}
		}
		else{
			anim.draw(window, x, y + h);
		}
	}
	else if (STATE == dead){ anim.draw(window, x, y + h); }
	else anim.draw(window, x, y + h-2);
}