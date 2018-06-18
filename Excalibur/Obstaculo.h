#pragma once
#include "Item.h"
#include <SFML\Graphics.hpp>

class Obstaculo :
	public Item
{
public:
	Obstaculo(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, int dano);
	const int getDano() { return dano; }
	void setDano(int dano) { this->dano = dano; } //verificar
	~Obstaculo();

private:
	int dano;
};

