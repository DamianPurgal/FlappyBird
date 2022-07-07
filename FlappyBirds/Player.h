#pragma once
#include "GraphicObject.h"
#include <cmath>
class Player : public GraphicObject
{
private:
	enum class texture_type {
		look_up = 1,
		look_forward = 0,
		look_down = 2
	}actualTexture;
	int alive;
	float acceleration;
	float velocity;
	float friction;
	void setTexture(texture_type type);
public:
	Player(Vector2f pPosition, Vector2f pSize, Texture pTexture, Game* pGame, bool pAlive = true);
	void update(float deltaTime);
	bool isAlive();
	void onCollision();
	bool isOutOfMap();
	bool isColliding(GraphicObject& testedObject);
	void setAcceleration(float acc);
};

