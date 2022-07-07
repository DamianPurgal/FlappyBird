#include "Game.h"
#include "const.h"


sf::RenderWindow* Game::getRenderWindow()
{
	return window;
}

Game::Game() 
	:window(new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Space Invaders")),
	score(0),
	player(nullptr)
{
	fontNumbers.loadFromFile("flappy.ttf");
	font.loadFromFile("flappy2.ttf");
	score_text.setFont(fontNumbers);
	end_text.setFont(font);
	score_text.setCharacterSize(40);
	end_text.setCharacterSize(FONT_SIZE);
	score_text.setPosition({ 10,10 });
	score_text.setString("123");
	end_text.setString("PRZEGRALES");
	
	end_text.setPosition({(WINDOW_WIDTH - end_text.getGlobalBounds().width)/2 , 70 });
	init();
	startGameLoop();
}

Game::~Game()
{
	while (objects.size() > 0)
	{
		delete objects.back();
		objects.pop_back();
	}
}

void Game::handlePlayerJump(sf::Clock& playerJumpClock)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (playerJumpClock.getElapsedTime().asSeconds() >= JUMP_DELAY)
		{
			playerJumpClock.restart();
			player->setAcceleration(A_MAX);
		}
	}
}

void Game::startGameLoop()
{
	float deltaTime = 0.0f;
	sf::Clock clock;
	sf::Clock playerJumpClock;
	sf::Event event;
	sf::Text starting_text;
	starting_text.setFont(font);
	starting_text.setCharacterSize(100);
	starting_text.setString("Flappy Bird");
	starting_text.setPosition({ (WINDOW_WIDTH - starting_text.getGlobalBounds().width) / 2 , 100 });
	sf::Text starting_text2;
	starting_text2.setFont(font);
	starting_text2.setCharacterSize(70);
	starting_text2.setString("Kliknij Spacje aby zaczac");
	starting_text2.setPosition({ (WINDOW_WIDTH - starting_text2.getGlobalBounds().width) / 2 , 200 });
	srand(time(NULL));
	bool isStarted = false;
	playerJumpClock.restart();
	while (window->isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		while (window->pollEvent(event))
			if (event.type == sf::Event::Closed)
				window->close();

		if (!isStarted) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				isStarted = true;
			window->draw(background);
			for (auto i : objects)
				i->draw();
			window->draw(starting_text);
			window->draw(starting_text2);
			window->display();
		}
		else {
			window->clear();
			window->draw(background);
			for (auto i : objects)
				i->draw();
			score_text.setString(to_string(score));
			window->draw(score_text);
			if (player->isAlive() == true)
			{
				for (auto i : objects)
					i->update(deltaTime);
				handlePlayerJump(playerJumpClock);
				for (auto i : objects)
					i->isColliding(*player);
			}
			else
			{
				window->draw(end_text);
				player->update(deltaTime);
			}
			if (player->isOutOfMap())
			{
				window->draw(end_text);
				window->display();
				sf::sleep(seconds(1.5f));
				break;
			}
			window->display();
		
			if(objects.size()<PIPE_AMOUNT)
				objects.push_back(new Obstruction(WINDOW_WIDTH * 1, rand()%200 + 50, pipeTexture, this));
		}
	}
}

void Game::init()
{

	sf::Texture playerTexture;
	playerTexture.loadFromFile("player.png");
	pipeTexture.loadFromFile("pipes.png");
	backgroundTexture.loadFromFile("bg.png");
	background.setSize({ float(WINDOW_WIDTH),float(WINDOW_HEIGHT) });
	background.setTexture(&backgroundTexture);
	background.setTextureRect(sf::IntRect(0, 0, backgroundTexture.getSize().x, backgroundTexture.getSize().y));
	player = new Player({ WINDOW_WIDTH * 0.1, WINDOW_HEIGHT / 2 }, { PLAYER_WIDTH,PLAYER_HEIGHT }, playerTexture, this, true);
	objects.push_back(player);
	int values[] = { 150,100,250,100,150,250,200,100,150,250,200,100,150,200,250,250 };
	float inc = 1.3 / PIPE_AMOUNT;
	for (float i = 0; i < PIPE_AMOUNT; i++)
		objects.push_back(new Obstruction(WINDOW_WIDTH * (0.4 +i*inc), values[int(i)], pipeTexture, this));
}

void Game::removeObject(GraphicObject* objectToRemove)
{
	for (auto it = objects.begin(); it != objects.end(); it++)
	{
		if (*it == objectToRemove)
		{
			objects.erase(it);
			delete objectToRemove;
			return;
		}
	}
}
