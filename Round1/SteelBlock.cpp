#include "source\SteelBlock.h"
SteelBlock::SteelBlock(AnimationManager &a, int x, int y) : Blocks(a, x, y){
	option("steelBlock", 0.0, 10, "default");
	anim.animList["hit"].loop = 0;
	anim.animList["default"].loop = 0;
	yCopy = y;
}
void SteelBlock::hitAction(){
	if (anim.isPlaying()){
		if ((int)anim.animList[anim.currentAnim].currentFrame < 3){
			if (y - 0.6 >= yCopy - 8)
				y -= 0.6;
			else y = yCopy - 8;
		}
		else{
			if (y + 4 <= yCopy)
				y += 4;
			else y = yCopy;
		}
	}
	else if (!anim.isPlaying()){
		anim.play();
		anim.set("default");
		hit = false;
	}
}
void SteelBlock::update(float time)
{
	if (hit){
		anim.set("hit");
		hitAction();
	}
	anim.tick(time);
}
