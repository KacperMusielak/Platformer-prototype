#pragma once
#include "Collision.h"

class Enemy
{
public:
	Enemy(sf::Texture* texture, float speed, float rangeL, float rangeR, sf::Vector2f position);
	~Enemy();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collision GetCollision(){ return Collision(body); }

private:
	sf::RectangleShape body;
	float speed;
	float rangeR, rangeL;
	int enemyDir;

	sf::Vector2f velocity;
};

