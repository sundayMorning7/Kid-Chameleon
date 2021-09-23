#include "source\RockBlock.h"
RockBlock::RockBlock(AnimationManager &a, int x, int y, AnimationManager&rock) : Blocks(a, x, y),
rocks({ Rock(rock, x, y - 5), Rock(rock, x + 10, y - 5), Rock(rock, x, y + 5), Rock(rock, x + 10, y + 5), Rock(rock, x + 7, y - 2) }) {
	option("zebraItem", 0.0, 10, "default");
	anim.animList["hit"].loop = false;
	w = 16;
	h = 16;
	rocks[0].setDir(1);
	rocks[1].setDir(0);
	rocks[2].setDir(1);
	rocks[3].setDir(0);
	rocks[4].setDir(0);
}
void RockBlock::hitAction(){
	for (int i = 0; i < 5; i++){
		rocks[i].setLife(true);
	}
	x = 0;
	y = 0;
	rocks[0].setDy(-0.3);
	rocks[1].setDy(-0.3);
	rocks[2].setDy(-0.2);
	rocks[3].setDy(-0.2);
	rocks[4].setDy(-0.4);

	rocks[0].setDx(-0.1);
	rocks[1].setDx(0.1);
	rocks[2].setDx(-0.1);
	rocks[3].setDx(0.1);
	rocks[4].setDx(0.1);

	hit = false;
}
void RockBlock::update(float time)
{
	if (hit){
		anim.set("hit");
		if (!anim.isPlaying()){
			hitAction();
		}
	}

	if (anim.currentAnim == "hit"&&!anim.isPlaying()){
		for (int i = 0; i < 5; i++){
			rocks[i].update(time);
		}
	}
	anim.tick(time);
}
void RockBlock::draw(RenderWindow &window)
{
	if (anim.isPlaying()){
		anim.draw(window, x, y + h);
	}
	else{
		for (int i = 0; i < 5; i++){
			rocks[i].draw(window);
			if (rocks[i].getY() >= 448)life = false;
		}
	}

}

