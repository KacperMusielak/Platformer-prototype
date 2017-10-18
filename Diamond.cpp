#include "Diamond.h"


Diamond::Diamond(sf::Texture* texture, sf::Vector2f position)
{
	size = sf::Vector2f(60, 50);
	body.setSize(size);
	body.setPosition(position);
	//body.setFillColor(sf::Color::Blue);
	body.setTexture(texture);
}


Diamond::~Diamond()
{
}

void Diamond::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
