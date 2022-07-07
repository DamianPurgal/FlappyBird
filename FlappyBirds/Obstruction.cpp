#include "Obstruction.h"
#include "Game.h"
Obstruction::Obstruction(float x, float yHole, Texture pTexture, Game* pGame)
	:GraphicObject({ x,0 }, {0,0}, pTexture, pGame),
	point(1)
{
	pipes.push_back(new Pipe({ x, 0 }, { PIPE_WIDTH,PIPE_HEIGHT }, pTexture, pGame, Pipe::pipe_type::pipe_top));
	pipes[0]->setPosition({ pipes[0]->getPosition().x, -PIPE_HEIGHT+yHole });
	pipes.push_back(new Pipe({ x, 0 }, { PIPE_WIDTH,PIPE_HEIGHT }, pTexture, pGame, Pipe::pipe_type::pipe_bottom));
	pipes[1]->setPosition({ pipes[1]->getPosition().x, yHole + HOLE_SIZE });
}
Obstruction::~Obstruction()
{
	while (pipes.size() > 0)
	{
		delete pipes.back();
		pipes.pop_back();
	}
}
void Obstruction::draw()
{
	for (auto i : pipes)
		i->draw();
}

void Obstruction::move(sf::Vector2f shift)
{
	if (pipes.back()->getPosition().x <= WINDOW_WIDTH * 0.1)
	{
		game->score = game->score + point;
		point = 0;
	}
	if (pipes.back()->getPosition().x + PIPE_WIDTH + shift.x > 0)
		for (auto i : pipes)
			i->move(shift);
	else
		game->removeObject(this);
	
}

void Obstruction::update(float deltaTime)
{
	totalTime += deltaTime;
	if (totalTime >= switchTime)
	{
		move({ -OBSTRUCTION_VELOCITY, 0 });
	}
}

bool Obstruction::isColliding(GraphicObject& testedObject)
{
	return pipes[0]->isColliding(testedObject) + pipes[1]->isColliding(testedObject);
}
