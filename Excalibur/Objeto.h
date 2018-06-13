#pragma once
#include "SFML\Graphics.hpp"
#include "Colisor.h"

class Objeto
{
public:
	Objeto(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Objeto();

	void Draw(sf::RenderWindow& window);
	Colisor GetCollider() { return Colisor(body); }

private:
	sf::RectangleShape body;
};

