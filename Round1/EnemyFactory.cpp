#include "source\EnemyFactory.h"
EnemyFactory::EnemyFactory(std::vector<Entity*>*e, std::vector<Object> &st) {
	obj.reserve(st.size());//obj статические
	obj.insert(obj.end(), st.begin(), st.end());
	obj.shrink_to_fit();

	entities = e;

	tDragon.loadFromFile("files\\PNG\\dragonPNG.png");
	dragon.loadFromXML("files\\XML\\dragonXML.xml", tDragon);
}
Enemy* EnemyFactory::makeEnemy(std::string name, int x, int y){
	if (name == "dragon"){
		return new Dragon(entities, obj, dragon, x, y);
	}
	else return nullptr;
}

