#pragma once
#include "source\IronKnight.h"
#include "source\KidChameleon.h"
#include "source\Ankh.h"
#include "source\Emerald.h"
#include "source\Clock.h"
#include "source\Dragon.h"
#include "source\Flag.h"
#include "source\RockBlock.h"
#include "source\RubberBlock.h"
#include "source\SteelBlock.h"
#include "source\PrizeBlock.h"
#include "source\BlockFactory.h"
#include "source\EnemyFactory.h"
#include "source\PrizeFactory.h"
#include "source\Player.h"
#include "source\InfoClass.h"
#include "source\GameMenu.h"
using namespace sf;
void main()
{
	GameMenu gameMenu;
	srand(time(NULL));
	RenderWindow window;
	sf::Vector2i screenDimensions;
	View view;
	Vector2f position;
	Level lvl;
	lvl.LoadFromFile("files\\Map\\Map.tmx");
	screenDimensions.x = 640;
	screenDimensions.y = 448;
	position.x = 0.0f;
	position.y = 0.0f;
	window.create(VideoMode(screenDimensions.x, screenDimensions.y), "Kid Chameleon");
	window.setMouseCursorVisible(false);
	window.setFramerateLimit(90);
	view.reset(sf::FloatRect(0, 113, 320, 230));
	/////////////////////////////////////////////////////////////////////////
	std::vector<Object> staticObjects;
	std::vector<Object>::iterator itObject;
	staticObjects.reserve(60);
	std::vector<Object> solids = lvl.GetObjects("solid");
	std::vector<Object> upHills = lvl.GetObjects("upHill");
	std::vector<Object> downHills = lvl.GetObjects("downHill");
	staticObjects.insert(staticObjects.end(), solids.begin(), solids.end());
	staticObjects.insert(staticObjects.end(), upHills.begin(), upHills.end());
	staticObjects.insert(staticObjects.end(), downHills.begin(), downHills.end());
	staticObjects.shrink_to_fit();
	solids.clear();
	upHills.clear();
	downHills.clear();
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	Image ibkColor;
	Texture fl, groundTexture, skyTexture, mountainTexture, elkaTexture, bridgeTexture, tree1Texture, tree2Texture, tree3Texture, tree4Texture, bushBehindTexture, bushFrontTexture, tGrey, tbkColor;
	Sprite ground, sky, mount, elka, bridge, tree1, tree2, tree3, tree4, bushBehind, bushFront, grey, bkColor;
	AnimationManager flag;
	std::vector<std::pair<float, Sprite*>> backgrounds;
	std::pair<float, Sprite*> pairs;
	tGrey.loadFromFile("files\\PNG\\Grey.png");
	fl.loadFromFile("files\\PNG\\flag.png");
	flag.loadFromXML("files\\XML\\flagXML.xml", fl);

	groundTexture.loadFromFile("files\\PNG\\ground.png");
	skyTexture.loadFromFile("files\\PNG\\sky.png");
	mountainTexture.loadFromFile("files\\PNG\\mount.png");
	elkaTexture.loadFromFile("files\\PNG\\elka.png");
	bridgeTexture.loadFromFile("files\\PNG\\bridge.png");
	tree1Texture.loadFromFile("files\\PNG\\tree1.png");
	tree2Texture.loadFromFile("files\\PNG\\tree2.png");
	tree3Texture.loadFromFile("files\\PNG\\tree3.png");
	tree4Texture.loadFromFile("files\\PNG\\tree4.png");
	bushBehindTexture.loadFromFile("files\\PNG\\bushBehind.png");
	bushFrontTexture.loadFromFile("files\\PNG\\bushFront.png");

	grey.setTexture(tGrey);
	ground.setTexture(groundTexture);
	sky.setTexture(skyTexture);
	mount.setTexture(mountainTexture);
	mount.setPosition(-96, -100);
	elka.setTexture(elkaTexture);
	elka.setPosition(-100, -70);
	bridge.setTexture(bridgeTexture);
	tree1.setTexture(tree1Texture);
	tree2.setTexture(tree2Texture);
	tree3.setTexture(tree3Texture);
	tree4.setTexture(tree4Texture);
	bushBehind.setTexture(bushBehindTexture);
	bushFront.setTexture(bushFrontTexture);

	pairs.first = 1.0f;
	pairs.second = &sky;
	backgrounds.push_back(pairs);
	pairs.first = 0.4f;
	pairs.second = &mount;
	backgrounds.push_back(pairs);
	pairs.first = 0.6;
	pairs.second = &elka;
	backgrounds.push_back(pairs);
	pairs.first = 1.0f;
	pairs.second = &ground;
	backgrounds.push_back(pairs);
	pairs.first = 1.0f;
	pairs.first = 1.0f;
	pairs.second = &bushBehind;
	backgrounds.push_back(pairs);
	pairs.second = &tree1;
	backgrounds.push_back(pairs);
	pairs.first = 1.0f;
	pairs.second = &tree2;
	backgrounds.push_back(pairs);
	pairs.first = 1.0f;
	pairs.second = &tree3;
	backgrounds.push_back(pairs);
	pairs.first = 1.0f;
	pairs.second = &tree4;
	backgrounds.push_back(pairs);
	pairs.first = 1.0f;
	pairs.second = &bushFront;
	backgrounds.push_back(pairs);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	BlockFactory blockFactory;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	std::vector<Entity*> entities;
	std::vector<Entity*>::iterator it;
	Object pl = lvl.GetObject("player");
	Object flagObj = lvl.GetObject("flag");
	std::vector<Object> steelBlocks = lvl.GetObjects("solidItem");
	std::vector<Object> rubberBlocks = lvl.GetObjects("jumpItem");
	std::vector<Object> rockBlocks = lvl.GetObjects("zebraItem");
	std::vector<Object> prizeBlocks = lvl.GetObjects("pItem");
	std::vector<Object> dragons = lvl.GetObjects("dragon");

	entities.push_back(new Flag(flag, flagObj.rect.left, flagObj.rect.top));
	for (itObject = rockBlocks.begin(); itObject != rockBlocks.end(); itObject++){
		entities.push_back(blockFactory.makeBlock("rockBlock", itObject->rect.left, itObject->rect.top));
	}
	for (itObject = rubberBlocks.begin(); itObject != rubberBlocks.end(); itObject++){
		entities.push_back(blockFactory.makeBlock("rubberBlock", itObject->rect.left, itObject->rect.top));
	}
	for (itObject = steelBlocks.begin(); itObject != steelBlocks.end(); itObject++){
		entities.push_back(blockFactory.makeBlock("steelBlock", itObject->rect.left, itObject->rect.top));
	}
	for (itObject = prizeBlocks.begin(); itObject != prizeBlocks.end(); itObject++){
		entities.push_back(blockFactory.makeBlock("prizeBlock", itObject->rect.left, itObject->rect.top, itObject->type));
		if (itObject->type == "ankh")
			itObject->type = "";
	}
	EnemyFactory enemyFactory(&entities, staticObjects);
	for (itObject = dragons.begin(); itObject != dragons.end(); itObject++){
		entities.push_back(enemyFactory.makeEnemy("dragon", itObject->rect.left, itObject->rect.top));
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	PrizeFactory prizeFactory(&entities, staticObjects);
	Player player(static_cast<KidChameleon*>(prizeFactory.makePrize("kidChameleon", pl.rect.left, pl.rect.top)));
	InfoClass infoClass(&player);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	Blocks* rock = nullptr;
	Prizes* prize = nullptr;
	Clock clock;
	float cameraDown = 0.0f;
	float alphaBlend = 255.0f;
	int helpCamera = 0;
	float time = 0.0f;
	bool released = true;
	////////////////////////////////////////////////////////Start Main cycle 
	while (window.isOpen()){
		time = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		if (time > 40) time = 40;
		Event event;
		
		while (window.pollEvent(event))
		{
			switch (event.type){
			case Event::KeyReleased:{
										switch (event.key.code){
										case Keyboard::X:
											released = true;
											break;
										case Keyboard::Up:
											if (gameMenu.isShowMenu())
												gameMenu.MoveUp();
											break;
										case Keyboard::Down:
											if (gameMenu.isShowMenu())
												gameMenu.MoveDown();
											break;
										case Keyboard::Return:
											if (player.getState() != 8){
												if (gameMenu.isShowMenu()){
													if (gameMenu.getIndex() == 0) {
														gameMenu.setShowMenu(false);
													}
													else if (gameMenu.getIndex() == 1){
														player.setLife(false);
														gameMenu.setIndex(false);
														gameMenu.setShowMenu(false);
													}
												}
												else{
													gameMenu.setShowMenu(true);
												}
											}
										}
										break;
			}
			case Event::Closed:
				window.close();
				break;
			}
		}
		





		//Start Update Entities
		if (!gameMenu.isShowMenu()){
			if (player.getState() != 13 && player.getState() != 8){
				for (it = entities.begin(); it != entities.end();){
					Entity *b = *it;
					if (b->getName() == "enemy"){
						if ((b->getX() > player.getX() && b->getX() < player.getX() + 320 || b->getX()<player.getX() && b->getX()>player.getX() - 320)) {
							b->update(time);
						}
					}
					else{
						b->update(time);
					}
					if (b->getName() == "prizeBlock"){
						PrizeBlock* p;
						p = dynamic_cast<PrizeBlock*>(b);
						if (p->isRockBlock()){
							p->setRockBlock(false);
							rock = blockFactory.makeBlock("rockBlock", p->getX(), p->getY());
						}
						if (p->isPrize()){
							p->setPrize(false);
							if (p->getType() == "ankh"){ prize = prizeFactory.makePrize("ankh", b->getX(), b->getY() - 12); }
							else if (p->getType() == "emerald"){ prize = prizeFactory.makePrize("emerald", b->getX(), b->getY() - 12); }
							else if (p->getType() == "clock"){ prize = prizeFactory.makePrize("clock", b->getX(), b->getY() - 12); }
							else if (p->getType() == "ironKnight"){ prize = prizeFactory.makePrize("ironKnight", b->getX(), b->getY() - 30); }
						}
					}

					if (b->isLife() == false)	{
						if (b->getName() == "prize"){
							if (dynamic_cast<Emerald*>(b))
								player.increaseEmeralds();
							else if (dynamic_cast<MyClock::Clock*>(b))
								player.increaseClocks();
							else if (dynamic_cast<Ankh*>(b))
								player.increaseAnkhs();
						}
						it = entities.erase(it);
						delete b;
					}
					else it++;
				}
				//Start Чтобы не сломать итератор во время Update Entities;
				if (rock != nullptr){
					rock->update(time);
					entities.insert(entities.begin(), rock);
					rock = nullptr;
				}
				if (prize != nullptr){
					prize->update(time);
					entities.insert(entities.begin() + 1, prize);
					prize = nullptr;
				}
				//End
			}
			//End 





			//Start Обработка коллизии с динамическими обьектами
			for (it = entities.begin(); it != entities.end();){
				if (((*it)->getName() == "IronKnight") && player.getRect().intersects((*it)->getRect())){
					Helmets* h = nullptr;
					h = dynamic_cast<Helmets*>(*it);
					h->setLanded(false);
					player.changeMask(h);
					it = entities.erase(it);
				}
				else if (((*it)->getName() == "enemy") && player.getHitbox().intersects((*it)->getRect())){
					Enemy*enemy = nullptr;
					enemy = dynamic_cast<Enemy*>(*it);
					if (player.getState() == 9){
						if (!enemy->getHit()){
							player.setDy(-0.2); enemy->setHit(true);
						}
					}
					else if (!enemy->getHit()){
						player.setHit(true);
					}
					it++;
				}
				else if (((*it)->getName() == "prize") && player.getRect().intersects((*it)->getRect())){
					Prizes* prize = nullptr;
					prize = dynamic_cast<Prizes*>(*it);
					prize->setHit(true);
					it++;
				}
				else it++;
			}
			//End


			//Камера!МОТОР!
			if (player.getState() != 8 ){
				if (player.getX() < 160){ position.x = 160; }
				else if (player.getX()>3034){ position.x = 3034; }
				else { position.x = player.getX(); }

				if (player.getY() - 23 <= 115){ position.y = 115; }
				else if (player.getY() - 23 >= 331){ position.y = 331; }
				else { position.y = player.getY() - 23; }

				view.setCenter(position.x, position.y);
				if (player.getKey("Down") == true && (player.getState() == 0 || player.getState() == 1 || player.getState() == 2 || player.getState() == 3 || player.getState() == 11 || player.getState() == 14)){
					if (helpCamera < 25) helpCamera++;
					if (helpCamera >= 25 && view.getCenter().y + cameraDown < 331 && view.getCenter().y + cameraDown<player.getY() + 120)  {
						view.move(0, cameraDown += 0.8);
					}
					else view.move(0, cameraDown);
				}
				else if (cameraDown>0.0f){ view.move(0, cameraDown -= 8.0); helpCamera = 0; }
				else { cameraDown = 0.0f; helpCamera = 0; }
			}
			//End


			//Start Update Player и ShowStats
			if (player.getState() != 13 && player.getState() != 8){
				infoClass.update(time);
			}
			player.update(time);
			if (player.isLife() == false&&player.getName()=="KidChameleon"){
				infoClass.restartTime();
				player.decreaseAnkhs();
				entities.clear();
				if (player.getCountAnkhs() <= 0){
					window.close();
					return;
				}
				player.recreateCharacter(static_cast<KidChameleon*>(prizeFactory.makePrize("kidChameleon", pl.rect.left, pl.rect.top)));
				entities.push_back(new Flag(flag, flagObj.rect.left, flagObj.rect.top));
				for (itObject = rockBlocks.begin(); itObject != rockBlocks.end(); itObject++){
					entities.push_back(blockFactory.makeBlock("rockBlock", itObject->rect.left, itObject->rect.top));
				}
				for (itObject = rubberBlocks.begin(); itObject != rubberBlocks.end(); itObject++){
					entities.push_back(blockFactory.makeBlock("rubberBlock", itObject->rect.left, itObject->rect.top));
				}
				for (itObject = steelBlocks.begin(); itObject != steelBlocks.end(); itObject++){
					entities.push_back(blockFactory.makeBlock("steelBlock", itObject->rect.left, itObject->rect.top));
				}
				for (itObject = prizeBlocks.begin(); itObject != prizeBlocks.end(); itObject++){
					entities.push_back(blockFactory.makeBlock("prizeBlock", itObject->rect.left, itObject->rect.top, itObject->type));
				}
				for (itObject = dragons.begin(); itObject != dragons.end(); itObject++){
					entities.push_back(enemyFactory.makeEnemy("dragon", itObject->rect.left, itObject->rect.top));
				}
				clock.restart();
				alphaBlend = 255;
				continue;
			}
			//End
			
			//Start Получение ввода с клавиатуры
			if (Keyboard::isKeyPressed(Keyboard::Left)) player.setKey("L");
			if (Keyboard::isKeyPressed(Keyboard::Right)) player.setKey("R");
			if (Keyboard::isKeyPressed(Keyboard::X)) {
				if (player.getState() == 9){ released = false; }
				if (player.getState() == 4 || released){ player.setKey("X"); }
				if (!released){ player.setKey("S"); }
			}
			if (Keyboard::isKeyPressed(Keyboard::Down)) player.setKey("Down");
			if (Keyboard::isKeyPressed(Keyboard::Z)) player.setKey("Z");
			if (Keyboard::isKeyPressed(Keyboard::C)) player.setKey("C");
			//End
		}



		//Start Вывод картинки на экран
		for (auto iter = backgrounds.begin(); iter != backgrounds.end(); iter++)
		{
			float parallax = iter->first;
			sf::Sprite* bg = iter->second;
			view.setCenter(position*parallax);
			view.move(0, cameraDown);
			window.setView(view);

			window.draw(*(bg));
		}
		for (it = entities.begin(); it != entities.end(); it++){
			(*it)->draw(window);
		}
		player.draw(window);
		window.draw(bridge);
		infoClass.draw(window);
		if (gameMenu.isShowMenu()){
			window.draw(grey);
			infoClass.setPauseTime();
			gameMenu.draw(window);
		}
		
		if (alphaBlend > 0){
			ibkColor.create(320, 343, Color(255, 255, 255, alphaBlend));
			if (alphaBlend > 0)alphaBlend--;
			else alphaBlend = 0;
			tbkColor.loadFromImage(ibkColor);
			bkColor.setTexture(tbkColor);

			window.draw(bkColor);
		}
		window.display();
		//End
	}
	////////////////////////////////////////////////////////End Main cycle 
}