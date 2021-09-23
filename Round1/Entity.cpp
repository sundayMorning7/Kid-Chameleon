#include "source\Entity.h"
Entity::Entity(AnimationManager &A, int X, int Y)
	{
		anim = A;
		x = X;
		y = Y;
		dir = 0;

		life = true;
		timer = 0;
		timer_end = 0;
		dx = dy = 0;
	}

void Entity::option(std::string NAME, float SPEED = 0, int HEALTH = 10, std::string FIRST_ANIM = "")
{
	Name = NAME;
	if (FIRST_ANIM != "") anim.set(FIRST_ANIM);
	dx = SPEED;
	w = anim.getW();
	h = anim.getH();

	Health = HEALTH;
}
void Entity::draw(RenderWindow &window){ anim.draw(window, x, y + h); }

std::string Entity::getName(){ return Name; }
float Entity::getX(){ return x; }
float Entity::getY(){ return y; }
float Entity::getDx(){ return dx; }
float Entity::getDy(){ return dy; }
bool Entity::getDir(){ return dir; }

void Entity::setX(float i){ x = i; }
void Entity::setY(float i){ y = i; }
void Entity::setDx(float i){ dx = i; }
void Entity::setDy(float i){ dy = i; }
void Entity::setDir(bool d){ dir = d; }

bool Entity::isLife(){ return life; }
void Entity::setLife(bool l){ life = l; }
void Entity::setTimer(float t){ timer = t; }

FloatRect Entity::getRect(){ return FloatRect(x, y, w, h); }
AnimationManager& Entity::getAnim(){ return anim; }  
std::vector<Object>& Entity::getObjects(){ return obj; }
