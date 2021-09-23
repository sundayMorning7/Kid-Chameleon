#pragma once
#include "Cronometer.h"
#include "Player.h"
class InfoClass  {
	View view;
	Font font;
	Text text;

	Player* player;
	Texture tAnkh;
	Texture tEmerald;
	Texture tClock;
	
	AnimationManager aAnkh;
	AnimationManager aEmerald;
	AnimationManager aClock;

	Vector2f center;
	Vector2f size;

	Vector2f ankhTextPos;
	Vector2f emeraldTextPos;
	Vector2f timePos;
	Vector2f ankhPos;
	Vector2f emeraldPos;
	Vector2f lifePos;

	const int roundTime = 181;
	sftools::Chronometer chronometer;
public:
	InfoClass(Player* pl);
	bool update(float time);
	void draw(RenderWindow &window);
	void setPauseTime();
	void restartTime();
};