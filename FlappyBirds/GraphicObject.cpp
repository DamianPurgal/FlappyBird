#include "GraphicObject.h"
#include "Game.h"

GraphicObject::GraphicObject(Vector2f pPosition, Vector2f pSize, Texture pTexture, Game* pGame)
	:position(pPosition),
	texture(pTexture),
	game(pGame),
	totalTime(0),
	switchTime(0.015)
{
	shape.setSize(pSize);
	shape.setPosition(pPosition);
	shape.setTexture(&texture);
}

void GraphicObject::draw()
{
	game->getRenderWindow()->draw(shape);
}

void GraphicObject::setPosition(Vector2f pPosition)
{
	position.x = pPosition.x;
	position.y = pPosition.y;
	shape.setPosition(position);
}

Vector2f GraphicObject::getPosition()
{
	return position;
}

bool GraphicObject::isColliding(GraphicObject& testedObject)
{
	if (this->getCollisionBox().intersects(testedObject.getCollisionBox()))
	{
		this->onCollision();
		testedObject.onCollision();
		return true;
	}
	return false;
}

void GraphicObject::move(sf::Vector2f shift)
{
	//if ((position.x + shift.x > 0) && (position.x + shift.x + shape.getSize().x <= WINDOW_WIDTH))
		position.x += shift.x;
	//if ((position.y + shift.y > 0) && (position.y + shift.y + shape.getSize().y <= WINDOW_HEIGHT))
		position.y += shift.y;
	shape.setPosition(position);
}

sf::FloatRect GraphicObject::getCollisionBox()
{
	return sf::FloatRect(shape.getPosition(), shape.getSize());
}