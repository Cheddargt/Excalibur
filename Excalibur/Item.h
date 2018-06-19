#pragma once
#include "SFML\Graphics.hpp"
#include "Colisor.h"

class Item
{
public:
	Item(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Item();

	void Draw(sf::RenderWindow& window);
	Colisor GetCollider() { return Colisor(body); }
	void setPosition(sf::Vector2f position) { body.setPosition(position);}

protected:
	sf::RectangleShape body;
};

