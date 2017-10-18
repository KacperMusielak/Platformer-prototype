#include "Enemy.h"
#include<iostream>

Enemy::Enemy(sf::Texture* texture, float speed, float rangeL, float rangeR, sf::Vector2f position)
{
	this->speed = speed;
	this->rangeR = rangeR;
	this->rangeL = rangeL;
	enemyDir = 0;
	body.setSize(sf::Vector2f(100.0f, 100.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);
	//body.setFillColor(sf::Color::Red);
}


Enemy::~Enemy()
{
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Enemy::Update(float deltaTime)
{
	
	velocity.x = 0.0f;
	//velocity.x *= 0.5f;
	if (enemyDir == 0)
	{
		//std::cout << "enemy dir 0" << std::endl;
		//body.move({ speed, 0 });
		velocity.x += speed;
		if (body.getPosition().x>rangeR) enemyDir = 1;
	}
	if (enemyDir == 1)
	{
		//std::cout << "enemy dir 1" << std::endl;
		//body.move({ -Speed, 0 });
		velocity.x -= speed;
		if (body.getPosition().x<rangeL) enemyDir = 0;
	}

	body.move(velocity * deltaTime);
}

