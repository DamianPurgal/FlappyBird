#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GraphicObject.h"
#include "Pipe.h"
class Obstruction : public GraphicObject
{
	std::vector<Pipe*> pipes;
	int point;
public:
	Obstruction(float x, float yHole, Texture pTexture, Game* pGame);
	~Obstruction();
	void draw();
	void move(sf::Vector2f shift);
	void update(float deltaTime);
	bool isColliding(GraphicObject& testedObject);
};

