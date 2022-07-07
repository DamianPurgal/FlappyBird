#include "Pipe.h"

void Pipe::setTexture(pipe_type type)
{
	sf::Vector2u textureSize = texture.getSize();
	if (type == pipe_type::pipe_top)
		shape.setTextureRect(sf::IntRect(textureSize.x / 2 * int(type), 0, textureSize.x / 2, textureSize.y));
	else
		shape.setTextureRect(sf::IntRect(textureSize.x / 2 * int(type), 0, textureSize.x / 2, textureSize.y));
}

void Pipe::move(sf::Vector2f shift)
{
	position.x += shift.x;
	position.y += shift.y;
	shape.setPosition(position);
}

Pipe::Pipe(Vector2f pPosition, Vector2f pSize, Texture pTexture, Game* pGame, pipe_type type)
	:GraphicObject(pPosition, pSize, pTexture, pGame)
{
	setTexture(type);
}


void Pipe::update(float deltaTime)
{
}
