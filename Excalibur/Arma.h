#pragma once
#include "Item.h"

class Arma :
	public Item
{
public:
	Arma(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, int dano);
	~Arma();
	const int getAttack() { return dano; }
	void setTexture(sf::Texture* texture) { this->texture = texture; }

private:
	int dano;
	sf::Texture* texture;
};

