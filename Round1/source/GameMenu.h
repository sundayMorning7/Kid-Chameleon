#pragma once
#include "Entity.h"
class GameMenu  {
	View view;
	Texture tItems[2];
	Sprite items[2];
	int selectedItem;
	bool showMenu;
public:
	GameMenu();
	bool isShowMenu();
	void setIndex(bool m);
	void setShowMenu(bool flag);
	void MoveUp();
	void MoveDown();
	int getIndex();
	void update(float time);
	void draw(RenderWindow &window);
};