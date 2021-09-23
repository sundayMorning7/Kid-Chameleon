#pragma once
#include "RockBlock.h"
#include "SteelBlock.h"
#include "RubberBlock.h"
#include "PrizeBlock.h"
class BlockFactory{
private:
	Texture tRock;
	AnimationManager rock;

	Texture tRockBlock;
	Texture tPrizeBlock;
	Texture tSteelBlock;
	Texture tRubberBlock;
	AnimationManager rockBlock;
	AnimationManager prizeBlock;
	AnimationManager steelBlock;
	AnimationManager rubberBlock;
public:
	BlockFactory();
	Blocks* makeBlock(std::string blockName, int x, int y, std::string prizeType = "");
};

