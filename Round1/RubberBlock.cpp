#include "source\RubberBlock.h"
RubberBlock::RubberBlock(AnimationManager &a, int x, int y) : Blocks(a, x, y){
	option("rubberBlock", 0.0, 10, "default");
	anim.animList["hit"].loop = 0;
	anim.animList["default"].loop = 0;
}
void RubberBlock::hitAction(){
	if (!anim.isPlaying()){
		anim.play();
		anim.set("default");
		hit = false;
	}
}
void RubberBlock::update(float time)
{
	if (hit){
		anim.set("hit");
		hitAction();
	}
	anim.tick(time);
}
void RubberBlock::draw(RenderWindow &window)
{
	if (anim.currentAnim == "hit"&&anim.isPlaying()){
		anim.draw(window, x + 1, y + h - 1);
	}
	else{
		anim.draw(window, x, y + h);
	}
}