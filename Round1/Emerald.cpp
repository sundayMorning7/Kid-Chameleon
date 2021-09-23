#include "source\Emerald.h"
Emerald::Emerald(std::vector<Entity*>*e, std::vector<Object> &st, AnimationManager&a, int x = 0, int y=0) : Prizes(e, a, x, y) {
	option("prize", 0.0, 10, "default");
	obj.reserve(st.size());//obj статические
	obj.insert(obj.end(), st.begin(), st.end());
	obj.shrink_to_fit();
}
void Emerald::Animation(float time){
	if (dir) anim.flip();
	anim.tick(time);
}
void Emerald::hitAction(){
	if (xCopy + 3 < center.x - size.x / 2 + 290)xCopy += 3;
	else if (xCopy - 3 > center.x - size.x / 2 + 290)xCopy -= 3;
	else xCopy = center.x - size.x / 2 + 290;

	if (yCopy - 2 > center.y - size.y / 2 + 36)yCopy -= 2;
	else if (yCopy + 2 < center.y - size.y / 2 + 36)yCopy += 2;
	else yCopy = center.y - size.y / 2 + 36;

	anim.animList[anim.currentAnim].sprite.setPosition(xCopy, yCopy);
	if (xCopy == center.x - size.x / 2 + 290 && yCopy == center.y - size.y / 2 + 36)life = false;
}
void Emerald::update(float time)
{
	Animation(time);
	if (hit){
		y = 0;
		x = 0;
		hitAction();
	}
	else{
		xCopy = x;
		yCopy = y;
		if (!landed){
			dy += 0.0005*time;
			x += dx*time;
			Collision(0);

			y += dy*time;
			Collision(1);
		}
		else timer += time;;
	}
}

void Emerald::draw(RenderWindow &window)//(int)timer % 100 == 0
{
	if (!hit){
		if (landed){
			if (timer > 4000 && timer<4100 || timer>4200 && timer<4300 ||
				timer>4400 && timer<4500 || timer>4600 && timer<4700 ||
				timer>4800 && timer<4900 || timer>5000 && timer<5100 ||
				timer>5200 && timer<5300 || timer>5400 && timer<5500 ||
				timer>5600 && timer<5700 || timer>5800 && timer<5900 ||
				timer>6000 && timer<6100 || timer>6200 && timer<6300 ||
				timer>6400 && timer<6500 || timer>6600 && timer<6700 ||
				timer>6800 && timer<6900 || timer>7000 && timer<7100 || 
				timer>7200 && timer<7300 || timer>7400 && timer<7500 || 
				timer>7600 && timer<7700 || timer>7800 && timer<7900 ) {//
				
			}
			else if (timer>8000){
				life = false;
			}
			else anim.draw(window, x, y + h);
		}
		else{
			anim.draw(window, x, y + h);
		}
	}
	else{
		center = window.getView().getCenter();
		size = window.getView().getSize();
		anim.draw(window, xCopy, yCopy + h);
	}
}
void Emerald::Collision(int num)
{
	for (int i = 0; i < obj.size(); i++){
		if (getRect().intersects(obj[i].rect))
		{
			if (obj[i].name == "solid")
			{
				if (dy>0 && num == 1)	{ y = obj[i].rect.top - h;  dy = 0; landed = true; }
				if (dy<0 && num == 1)	{ y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (dx>0 && num == 0)	{ x = obj[i].rect.left - w; }
				if (dx < 0 && num == 0)	{ x = obj[i].rect.left + obj[i].rect.width; }
			}
		}
	}
}
