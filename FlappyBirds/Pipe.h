#pragma once
#include <SFML/Graphics.hpp>
#include "GraphicObject.h"
class Game;
class Pipe : public GraphicObject
{
public:
	enum class pipe_type {
		pipe_top = 1,
		pipe_bottom = 0
	};
private:
	pipe_type type;
	void setTexture(pipe_type type);
public:
	virtual void move(sf::Vector2f shift);
	Pipe(Vector2f pPosition, Vector2f pSize, Texture pTexture, Game* pGame, pipe_type type);
	void update(float deltaTime);
};

