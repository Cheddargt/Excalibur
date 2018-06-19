#pragma once
#include "Plataforma.h"
class Checkpoint :
	public Plataforma
{
public:
	Checkpoint(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
	~Checkpoint();
};

