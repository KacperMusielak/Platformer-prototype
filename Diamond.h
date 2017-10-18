#pragma once
#include <SFML/Graphics.hpp>
#include "Collision.h"

class Diamond
{
public:
	Diamond(sf::Texture* texture, sf::Vector2f position);
	~Diamond();

	void Draw(sf::RenderWindow& window);
	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collision GetCollision() { return Collision(body); }
	void setPos(sf::Vector2f newPos) { body.setPosition(newPos); }

private:
	sf::RectangleShape body;
	sf::Vector2f size;
};

