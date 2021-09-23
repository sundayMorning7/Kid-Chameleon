#include "source\GameMenu.h"
GameMenu::GameMenu(){
	view.reset(sf::FloatRect(0, 113, 320, 230));
	tItems[0].loadFromFile("files\\PNG\\Menu1.png");
	tItems[1].loadFromFile("files\\PNG\\Menu2.png");

	items[0].setTexture(tItems[0]);
	items[1].setTexture(tItems[1]);

	items[0].setScale(0.5, 0.5);
	items[1].setScale(0.5, 0.5);

	items[0].setPosition(97, 188);
	items[1].setPosition(97, 188);
	selectedItem = 0;
	showMenu = false;
}
void GameMenu::setIndex(bool m){
	if (m)selectedItem = 1;
	else selectedItem = 0;
}
void GameMenu::setShowMenu(bool flag){
	showMenu = flag;
}
void GameMenu::MoveUp(){
	if (selectedItem == 1)
		selectedItem = 0;
}
void GameMenu::MoveDown(){
	if (selectedItem == 0)
		selectedItem = 1;
}
int GameMenu::getIndex(){
	return selectedItem;
}
void GameMenu::update(float time){
	
}
bool GameMenu::isShowMenu(){
	return showMenu;
}
void GameMenu::draw(RenderWindow &window)
{
	window.setView(view);
	window.draw(items[selectedItem]);
}

