#include "source\PrizeBlock.h"
PrizeBlock::PrizeBlock(AnimationManager &a, int x, int y, std::string t) : Blocks(a, x, y){
	type = t;
	option("prizeBlock", 0.0, 10, "default");
	anim.animList["default"].loop = 0;
	anim.animList["hit"].loop = 0;
	w = 16;
	h = 16;
}
std::string PrizeBlock::getType(){ return type; }
void PrizeBlock::hitAction(){
	if (!anim.isPlaying()){
		life = false;
	}
	else{
		int frame = (int)anim.animList[anim.currentAnim].currentFrame;
		if ((frame == 42 || frame == 43) && times1 == 0){
			createRockBlock = true;
			times1++;
		}
		if ((frame == 47 || frame == 48) && times == 0){
			createPrize = true;
			times++;
		}
	}
}
void PrizeBlock::update(float time)
{
	if (hit){
		anim.set("hit");
		hitAction();
	}
	anim.tick(time);
}
void PrizeBlock::draw(RenderWindow &window)
{
	anim.draw(window, x - 4, y + h + 2);
}


bool PrizeBlock::isPrize(){
	return createPrize;
}
void PrizeBlock::setPrize(bool f){
	createPrize = f;
}

bool PrizeBlock::isRockBlock(){
	return createRockBlock;
}
void PrizeBlock::setRockBlock(bool f){
	createRockBlock = f;
}