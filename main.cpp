#include <iostream>
#include <vector>
#include <sstream>
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Player.h"
#include "Platform.h"
#include "Enemy.h"
#include "Diamond.h"

static const float VIEW_HEIGHT = 512.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
	//sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works", sf::Style::Close | sf::Style::Resize);
	sf::RenderWindow window(sf::VideoMode(600, 600), "Game", sf::Style::Close);
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(800.0f, 800.0f));

	sf::Texture playerTexture;
	sf::Texture enemyTexture;
	sf::Texture diamondTexture;
	sf::Texture backgroundTexture;

	playerTexture.loadFromFile("tux_from_linux.png");
	enemyTexture.loadFromFile("snowman-game-character.png");
	diamondTexture.loadFromFile("Diamond_Sprite.png");
	backgroundTexture.loadFromFile("Snow_background.png");

	sf::Sprite background;
	sf::Sprite background2;
	sf::Sprite background3;
	background.setTexture(backgroundTexture);
	background2.setTexture(backgroundTexture);
	background2.setPosition(sf::Vector2f(-2352.0f, 0.0f));
	background3.setTexture(backgroundTexture);
	background3.setPosition(sf::Vector2f(2352.0f, 0.0f));
	//background.setTextureRect(sf::IntRect(0.0f, 0.0f, 2352.0f, 1168.0f));
	//background.setTextureRect(sf::IntRect(0.0f, 0.0f, 2352.0f, 1168.0f));
	//background.setPosition(sf::Vector2f(0.0f, 0.0f));
	
	Player player(&playerTexture, sf::Vector2u(3, 9), 0.3f, 250.0f, 200.0f);

	//Score Objects:
	int score = 0;

	sf::Font LucidaTypewriterRegular;
	LucidaTypewriterRegular.loadFromFile("LucidaTypewriterRegular.ttf");

	std::ostringstream ssScore;
	ssScore << "Score: " << score;

	sf::Text lblScore;
	lblScore.setCharacterSize(30);
	lblScore.setPosition({ 10.0f, 10.0f });
	lblScore.setFont(LucidaTypewriterRegular);
	lblScore.setString(ssScore.str());

	std::vector<Platform> platforms;
	std::vector<Enemy> enemies;
	std::vector<Diamond> diamonds;

	//platforms.push_back(Platform(nullptr, sf::Vector2f(1400.0f, 200.0f), sf::Vector2f(500.0f, 200.0f)));
	//platforms.push_back(Platform(nullptr, sf::Vector2f(400.0f, 200.0f), sf::Vector2f(300.0f, 200.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(1000.0f, 200.0f), sf::Vector2f(500.0f, 600.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(450.0f, 200.0f), sf::Vector2f(1350.0f, 450.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(300.0f, 100.0f), sf::Vector2f(800.0f, 250.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(300.0f, 100.0f), sf::Vector2f(1900.0f, 250.0f)));
	platforms.push_back(Platform(nullptr, sf::Vector2f(1000.0f, 100.0f), sf::Vector2f(2800.0f, 800.0f)));

	enemies.push_back(Enemy(&enemyTexture, 200.0f, 200.0f, 1000.0f, sf::Vector2f(500.0f, 450.0f)));
	enemies.push_back(Enemy(&enemyTexture, 200.0f, 1150.0f, 1600.0f, sf::Vector2f(1600.0f, 300.0f)));
	enemies.push_back(Enemy(&enemyTexture, 200.0f, 2350.0f, 2900.0f, sf::Vector2f(2500.0f, 700.0f)));
	enemies.push_back(Enemy(&enemyTexture, 300.0f, 2750.0f, 3300.0f, sf::Vector2f(2900.0f, 700.0f)));

	diamonds.push_back(Diamond(&diamondTexture, sf::Vector2f(500.0f, 400.0f)));
	diamonds.push_back(Diamond(&diamondTexture, sf::Vector2f(700.0f, 100.0f)));
	diamonds.push_back(Diamond(&diamondTexture, sf::Vector2f(350.0f, 0.0f)));
	diamonds.push_back(Diamond(&diamondTexture, sf::Vector2f(2500.0f, 650.0f)));
	diamonds.push_back(Diamond(&diamondTexture, sf::Vector2f(2900.0f, 650.0f)));
	diamonds.push_back(Diamond(&diamondTexture, sf::Vector2f(3400.0f, 550.0f)));

	float deltaTime = 0.0f;
	sf::Clock clock;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:window.close();
				break;
			case sf::Event::Resized:
				ResizeView(window, view);
				break;

			}

		}

		if (player.GetPosition().y > 1000)
			window.close();
		player.Update(deltaTime);

		for (Enemy& enemy : enemies)
			enemy.Update(deltaTime);

		sf::Vector2f direction;

		for (Platform& platform : platforms)
			if (platform.GetCollision().CheckCollision(player.GetCollision(), direction, 1.0f))
				player.OnCollision(direction);
		
		for (Enemy& enemy : enemies)
			if (enemy.GetCollision().CheckCollision(player.GetCollision(), direction, 1.0f))
				window.close();

		for (Diamond& diamond : diamonds)
		{
			if (diamond.GetCollision().CheckCollision(player.GetCollision(), direction, 1.0f))
			{
				diamond.setPos({ 444444, 444444 });
				score++;
				ssScore.str("");
				ssScore << "Score: " << score;
				lblScore.setString(ssScore.str());
			}
		}

		view.setCenter(player.GetPosition());
		lblScore.setPosition(player.GetPosition().x - 350.0f, player.GetPosition().y - 350.0f);

		window.clear(sf::Color(115, 144, 247));
		window.draw(background);
		window.draw(background2);
		window.draw(background3);
		window.setView(view);
		player.Draw(window);
		for (Platform& platform : platforms)
			platform.Draw(window);
		for (Enemy& enemy : enemies)
			enemy.Draw(window);
		for (Diamond& diamond : diamonds)
			diamond.Draw(window);
		window.draw(lblScore);
		window.display();
	}
	return 0;
}