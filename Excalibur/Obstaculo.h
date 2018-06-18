#pragma once
#include "Item.h"
#include <SFML\Graphics.hpp>

class Obstaculo :
	public Item
{
public:
	Obstaculo(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, int dano);
	~Obstaculo();
	const int getDano() { return dano; }
	 //verificar

protected:
	int dano;
};

