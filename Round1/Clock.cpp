#include "source\Clock.h"
MyClock::Clock::Clock(std::vector<Entity*>*e, std::vector<Object> &st, AnimationManager&a, int x = 0, int y = 0) : Prizes(e, a, x, y) {
	option("prize", 0.0, 10, "default");
	obj.reserve(st.size());//obj статические
	obj.insert(obj.end(), st.begin(), st.end());
	obj.shrink_to_fit();
}
void MyClock::Clock::Animation(float time){
	if (dir) anim.flip();
	anim.tick(time);
}
void MyClock::Clock::hitAction(){
	if (xCopy + 12 < center.x - size.x / 2 + 60)xCopy += 12;
	else if (xCopy - 12 > center.x - size.x / 2 + 60)xCopy -= 12;
	else xCopy = center.x - size.x / 2 + 60;

	if (yCopy - 12 > center.y - size.y / 2 + 12)yCopy -= 12;
	else if (yCopy + 8 < center.y - size.y / 2 + 12)yCopy += 12;
	else yCopy = center.y - size.y / 2 + 12;

	anim.animList[anim.currentAnim].sprite.setPosition(xCopy, yCopy);
	if (xCopy == center.x - size.x / 2 + 60 && yCopy == center.y - size.y / 2 + 12){ life = false; }
}
void MyClock::Clock::update(float time)
{
	Animation(time);
	if (hit){
		y = 0;
		x = 0;
		hitAction();
		landed = true;
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
	}
}
void MyClock::Clock::Collision(int num)
{
	for (int i = 0; i < obj.size(); i++){
		if (getRect().intersects(obj[i].rect))
		{
			if (obj[i].name == "solid")
			{
				if (dy>0 && num == 1)	{ y = obj[i].rect.top - h;  dy = 0; landed = true; }
				if (dy < 0 && num == 1)	{ y = obj[i].rect.top + obj[i].rect.height;   dy = 0; }
				if (dx > 0 && num == 0)	{ x = obj[i].rect.left - w; }
				if (dx < 0 && num == 0)	{ x = obj[i].rect.left + obj[i].rect.width; }
			}
		}
	}
}
void MyClock::Clock::draw(RenderWindow &window)
{
	if (!hit){
		anim.draw(window, x, y + h);
	}
	else{
		center = window.getView().getCenter();
		size = window.getView().getSize();
		anim.draw(window, xCopy, yCopy + h);
	}
}
