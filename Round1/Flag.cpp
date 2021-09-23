#include "source\Flag.h"
Flag::Flag(AnimationManager &a, int x, int y) : Entity(a, x, y){
	option("flag", 0.0, 0, "default");
}
void Flag::update(float time)
{
	anim.tick(time);
}