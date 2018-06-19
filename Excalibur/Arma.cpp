#include "stdafx.h"
#include "Arma.h"


Arma::Arma(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, int dano) :
	Item (texture, size, position)
{
	this->texture = texture;
}


Arma::~Arma()
{
}
