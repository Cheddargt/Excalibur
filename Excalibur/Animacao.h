#pragma once
#include <SFML\Graphics.hpp>

class Animacao
{
public:
	sf::IntRect uvRect;
	
	Animacao(sf::Texture* texture, sf::Vector2u imageCount, float switchTime);
	~Animacao();

	void Update(int row, float deltaTime, bool faceRight);

private:
	sf::Vector2u imageCount;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;
};

