#pragma once
#include <SFML\Graphics.hpp>

class Colisor
{
public:
	Colisor(sf::RectangleShape& body);
	~Colisor();

	void Move(float dx, float dy) { body.move(dx, dy); }

	bool CheckCollision(Colisor* other, sf::Vector2f& direcao, float push); 
	bool CheckPlayerCollision(Colisor* other, sf::Vector2f& direcao, float push);
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }

protected:
	sf::RectangleShape& body;
};


