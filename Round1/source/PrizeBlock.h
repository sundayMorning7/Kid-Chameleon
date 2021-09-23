#pragma once
#include "Blocks.h"
class PrizeBlock : public Blocks {
	std::string type;
	bool createPrize;
	bool createRockBlock;
	int times = 0;
	int times1 = 0;
public:
	PrizeBlock(AnimationManager &a, int x, int y, std::string t);
	std::string getType();
	void hitAction();
	void update(float time);
	virtual void draw(RenderWindow &window);


	bool isPrize();
	void setPrize(bool f);

	bool isRockBlock();
	void setRockBlock(bool f);
};
