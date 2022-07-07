#pragma once
#include <SFML/Graphics.hpp>
#include "const.h"
#include "DrawableObject.h"
#include "UpdateableObject.h"
using namespace sf;
class Game;
class GraphicObject : public DrawableObject, public UpdateableObject
{
protected:
	Game* game;
	RectangleShape shape;
	Texture texture;
	Vector2f position;
	float switchTime;
	float totalTime;
public:
	GraphicObject(Vector2f pPosition, Vector2f pSize, Texture pTexture, Game* pGame);
	void setPosition(Vector2f pPosition);
	Vector2f getPosition();
	virtual void onCollision() {};
	virtual void draw();
	virtual bool isColliding(GraphicObject& testedObject);
	virtual void move(sf::Vector2f shift);
	sf::FloatRect getCollisionBox();
};

