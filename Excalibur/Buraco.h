#pragma once
#include "Obstaculo.h"
class Buraco :
	public Obstaculo
{
public:
	Buraco(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Buraco();
private:
	sf::Texture buracoTexture;
};

