#pragma once
#include <SFML\Graphics.hpp>

class Colisor
{
public:
	Colisor(sf::RectangleShape& body);
	~Colisor();

	void Move(float dx, float dy) { body.move(dx, dy); }

	bool CheckCollision(Colisor* other, sf::Vector2f& direcao, float push); //push verifica se player deve poder empurrar objeto, &other e &direcao
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }

private:
	sf::RectangleShape& body;
};


