#pragma once
#include <SFML/Graphics.hpp>
#include "GraphicObject.h"
#include "Player.h"
#include "Obstruction.h"
#include "Pipe.h"
#include <ctime>
#include <string>
using namespace std;
class Game
{
public:
	sf::RenderWindow* window;
	vector<GraphicObject*> objects;
	int score;
	sf::Font fontNumbers;
	sf::Font font;
	sf::Text score_text;
	sf::Text end_text;
	Player* player;
	sf::RenderWindow* getRenderWindow();
	Game();
	~Game();
	void removeObject(GraphicObject* objectToRemove);
private:
	sf::Texture pipeTexture;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	void handlePlayerJump(sf::Clock& playerJumpClock);
	void startGameLoop();
	void init();
};

