#include "source\InfoClass.h"
InfoClass::InfoClass(Player* pl) : player(pl){
	view.reset(sf::FloatRect(0, 113, 320, 230));
	center = view.getCenter();
	size = view.getSize();

	ankhTextPos.x = center.x - size.x / 2 + 270;
	ankhTextPos.y = center.y - size.y / 2 + 18;
	emeraldTextPos.x = center.x - size.x / 2 + 270;
	emeraldTextPos.y = center.y - size.y / 2 + 40;
	timePos.x = center.x - size.x / 2 + 10;
	timePos.y = center.y - size.y / 2 + 15;
	ankhPos.x = center.x - size.x / 2 + 292;
	ankhPos.y = center.y - size.y / 2 + 30;
	emeraldPos.x = center.x - size.x / 2 + 290;
	emeraldPos.y = center.y - size.y / 2 + 50;
	lifePos.x = center.x - size.x / 2 + 10;
	lifePos.y = center.y - size.y / 2 + 40;

	chronometer.reset(true);
	font.loadFromFile("files\\Font\\pressStart2P.ttf");

	text.setFont(font);
	text.setScale(0.3, 0.3);
	text.setStyle(sf::Text::Style::Bold);

	tAnkh.loadFromFile("files\\PNG\\ankh.png");
	tEmerald.loadFromFile("files\\PNG\\emerald.png");
	tClock.loadFromFile("files\\PNG\\clock.png");
	
	aAnkh.loadFromXML("files\\XML\\ankhXML.xml", tAnkh);
	aEmerald.loadFromXML("files\\XML\\emeraldXML.xml", tEmerald);
	aClock.loadFromXML("files\\XML\\clockXML.xml", tClock);

	aEmerald.set("default");
	aClock.set("default");
}
bool InfoClass::update(float time){
	chronometer.resume();
	aAnkh.tick(time);
	aEmerald.tick(time);
	aClock.tick(time);
	if (chronometer.getElapsedTime().asSeconds() > roundTime + player->getAddingTime()){ player->setLife(false); }
	else return true;
}
void InfoClass::draw(RenderWindow &window)
{
	window.setView(view);
	
	std::string l = std::to_string(player->getCountAnkhs());
	l += "x";
	text.setString(l);
	text.setPosition(ankhTextPos.x, ankhTextPos.y);
	window.draw(text);
	l.clear();

	l = std::to_string(player->getCountEmeralds());
	if (player->getCountEmeralds() < 10){
		l += "x";
	}
	text.setString(l);
	text.setPosition(emeraldTextPos.x, emeraldTextPos.y);
	window.draw(text);
	l.clear();

	int min = ((int)(roundTime + player->getAddingTime() - chronometer.getElapsedTime().asSeconds())) / 60;
	int sec = ((int)(roundTime + player->getAddingTime() - chronometer.getElapsedTime().asSeconds())) % 60;
	l = std::to_string(min) + ":";
	if (sec < 10)
		l += "0" + std::to_string(sec);
	else l += std::to_string(sec);
	text.setString(l);
	text.setPosition(timePos.x,timePos.y);
	window.draw(text);

	aAnkh.draw(window, ankhPos.x, ankhPos.y);
	aEmerald.draw(window, emeraldPos.x, emeraldPos.y);
	
	if (player->getState() != 13&&player->getState()!=8){
		player->getAnimLifes().draw(window, lifePos.x, lifePos.y);
	}
}
void InfoClass::setPauseTime(){
	chronometer.pause();
}
void InfoClass::restartTime(){
	chronometer.reset();
	player->setAddingTime(0);
}
