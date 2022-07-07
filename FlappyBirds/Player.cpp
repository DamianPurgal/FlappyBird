#include "Player.h"

void Player::setTexture(texture_type type)
{
	sf::Vector2u textureSize = texture.getSize();
	shape.setTextureRect(sf::IntRect(0, textureSize.y/3*int(type), textureSize.x, textureSize.y/3));
}

Player::Player(Vector2f pPosition, Vector2f pSize, Texture pTexture, Game* pGame,bool pAlive)
    : alive(pAlive),
	velocity(V_MIN),
	acceleration(A_MIN),
	friction(0),
	actualTexture(texture_type::look_forward),
    GraphicObject(pPosition,pSize,pTexture,pGame)
{
	setTexture(actualTexture);
}

void Player::update(float deltaTime)
{
	totalTime += deltaTime;
	if (totalTime >= switchTime)
	{
		texture_type newActualTexture;
		totalTime -= switchTime;
		if (friction > 2) friction = 0;
		friction += 0.05;
		acceleration -= atan(friction);
		if (acceleration < A_MIN) acceleration = A_MIN;
 		velocity += acceleration;
		if (velocity > V_MAX) velocity = V_MAX;
		else if (velocity < V_MIN) velocity = V_MIN;
		
		if (velocity > 0) newActualTexture = texture_type::look_up;
		else if (velocity < 0) newActualTexture = texture_type::look_down;
		else if (velocity == 0) newActualTexture = texture_type::look_forward;
		if (newActualTexture != actualTexture)
		{
			actualTexture = newActualTexture;
			setTexture(actualTexture);
		}
		move({ 0,-velocity });
	}
}
bool Player::isAlive()
{
    return alive;
}

void Player::onCollision()
{
	alive = false;
}

bool Player::isOutOfMap()
{
	if (position.y + PLAYER_HEIGHT / 2 > WINDOW_HEIGHT)
		return true;
	return false;
}

bool Player::isColliding(GraphicObject& testedObject)
{
	return false;
}

void Player::setAcceleration(float acc)
{
    acceleration = acc;
	friction = 0;
}
