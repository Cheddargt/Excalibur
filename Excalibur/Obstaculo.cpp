#include "stdafx.h"
#include "Obstaculo.h"


Obstaculo::Obstaculo(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, int dano) :
	Item (texture, size, position)
{

	body.setSize(size);
	body.setOrigin(size / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}


Obstaculo::~Obstaculo()
{
}
