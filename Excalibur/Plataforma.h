#pragma once
#include "Item.h"
class Plataforma :
	public Item
{
public:
	Plataforma(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Plataforma();
};

