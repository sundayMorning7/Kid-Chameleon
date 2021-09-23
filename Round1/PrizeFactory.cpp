#include "source\PrizeFactory.h"
PrizeFactory::PrizeFactory(std::vector<Entity*>*e, std::vector<Object> &st) {
	obj.reserve(st.size());//obj статические
	obj.insert(obj.end(), st.begin(), st.end());
	obj.shrink_to_fit();

	entities = e;

	tCharacterSprites.loadFromFile("files\\PNG\\CharactersSprites.png");
	tAnkh.loadFromFile("files\\PNG\\ankh.png");
	tEmerald.loadFromFile("files\\PNG\\emerald.png");
	tClock.loadFromFile("files\\PNG\\clock.png");

	ironKnight.loadFromXML("files\\XML\\ironKnightXML.xml", tCharacterSprites);
	kidChameleon.loadFromXML("files\\XML\\kidChameleonXML.xml", tCharacterSprites);
	ankh.loadFromXML("files\\XML\\ankhXML.xml", tAnkh);
	emerald.loadFromXML("files\\XML\\emeraldXML.xml", tEmerald);
	clock.loadFromXML("files\\XML\\clockXML.xml", tClock);

	tKidLifes.loadFromFile("files\\PNG\\kidLifes.png");
	aKidLifes.loadFromXML("files\\XML\\kidLifesXML.xml", tKidLifes);

	tIronLifes.loadFromFile("files\\PNG\\ironLifes.png");
	aIronLifes.loadFromXML("files\\XML\\ironLifesXML.xml", tIronLifes);
}
Prizes* PrizeFactory::makePrize(std::string name, int x, int y){
	if (name == "ankh"){
		return new Ankh(entities, obj, ankh, x, y);
	}
	else if (name == "emerald"){
		return new Emerald(entities, obj, emerald, x, y);
	}
	else if (name == "clock"){
		return new MyClock::Clock(entities, obj, clock, x, y);
	}
	else if (name == "ironKnight"){
		return new IronKnight(entities, obj, ironKnight, aIronLifes, x, y);
	}
	else if (name == "kidChameleon"){
		return new KidChameleon(entities, obj, kidChameleon,aKidLifes, x, y);
	}
	else return nullptr;
}