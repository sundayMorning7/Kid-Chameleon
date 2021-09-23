#include "source\BlockFactory.h"
BlockFactory::BlockFactory() {
	tRock.loadFromFile("files\\PNG\\rock.png");
	rock.loadFromXML("files\\XML\\rockXML.xml", tRock);

	tRockBlock.loadFromFile("files\\PNG\\RockBlockReadyEND.png");
	tPrizeBlock.loadFromFile("files\\PNG\\destroyPrizeBlock.png");
	tSteelBlock.loadFromFile("files\\PNG\\steel.png");
	tRubberBlock.loadFromFile("files\\PNG\\rubber.png");

	rockBlock.loadFromXML("files\\XML\\RockBlockReadyENDXML.xml", tRockBlock);
	prizeBlock.loadFromXML("files\\XML\\destroyPrizeBlockXML.xml", tPrizeBlock);
	steelBlock.loadFromXML("files\\XML\\steelBlockXML.xml", tSteelBlock);
	rubberBlock.loadFromXML("files\\XML\\rubberBlockXML.xml", tRubberBlock);
}
Blocks* BlockFactory::makeBlock(std::string blockName, int x, int y, std::string prizeType){
	if (blockName == "steelBlock"){
		return new SteelBlock(steelBlock, x, y);
	}
	else if (blockName == "rubberBlock"){
		return new RubberBlock(rubberBlock, x, y);
	}
	else if (blockName == "rockBlock"){
		return new RockBlock(rockBlock, x, y, rock);
	}
	else if (blockName == "prizeBlock"){
		return new PrizeBlock(prizeBlock, x, y, prizeType);
	}
	else return nullptr;
}

